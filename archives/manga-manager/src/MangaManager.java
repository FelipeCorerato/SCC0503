import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.*;
import java.lang.reflect.Type;
import java.util.*;

public class MangaManager {
    private List<Manga> mangas;
    private TreeMap<String, Long> primaryIndex;
    private TreeMap<String, List<String>> secondaryIndex;

    private static final String MANGA_FILE = "mangas.json";
    private static final String PRIMARY_INDEX_FILE = "primary_index.json";
    private static final String SECONDARY_INDEX_FILE = "secondary_index.json";

    private Gson gson;

    public MangaManager() {
        this.mangas = new ArrayList<>();
        this.primaryIndex = new TreeMap<>();
        this.secondaryIndex = new TreeMap<>();
        this.gson = new Gson();
        loadFromFile();
    }

    public boolean addManga(Manga manga) {
        if (primaryIndex.containsKey(manga.getIsbn())) {
            return false;
        }

        long position = saveMangaToFile(manga);
        primaryIndex.put(manga.getIsbn(), position);

        secondaryIndex.computeIfAbsent(manga.getTitle(), k -> new ArrayList<>()).add(manga.getIsbn());
        saveIndicesToFile();
        return true;
    }

    private long saveMangaToFile(Manga manga) {
        try (RandomAccessFile raf = new RandomAccessFile(MANGA_FILE, "rw")) {
            long position = raf.length();
            raf.seek(position);
            raf.writeUTF(gson.toJson(manga));
            return position;
        } catch (IOException e) {
            e.printStackTrace();
            return -1;
        }
    }

    public Manga getMangaByIsbn(String isbn) {
        Long position = primaryIndex.get(isbn);
        if (position == null) {
            return null;
        }
        return readMangaFromFile(position);
    }

    private Manga readMangaFromFile(long position) {
        try (RandomAccessFile raf = new RandomAccessFile(MANGA_FILE, "r")) {
            raf.seek(position);
            String json = raf.readUTF();
            return gson.fromJson(json, Manga.class);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public List<Manga> getMangaByTitle(String title) {
        List<String> isbns = secondaryIndex.getOrDefault(title, new ArrayList<>());
        List<Manga> mangas = new ArrayList<>();
        for (String isbn : isbns) {
            mangas.add(getMangaByIsbn(isbn));
        }
        return mangas;
    }

    public void updateManga(String isbn, Manga updatedManga) {
        Long position = primaryIndex.get(isbn);
        if (position != null) {
            Manga existingManga = readMangaFromFile(position);

            saveMangaToFileAtPosition(updatedManga, position);

            if (!isbn.equals(updatedManga.getIsbn())) {
                primaryIndex.remove(isbn);
                primaryIndex.put(updatedManga.getIsbn(), position);
            }

            if (!existingManga.getTitle().equals(updatedManga.getTitle())) {
                List<String> isbns = secondaryIndex.get(existingManga.getTitle());
                if (isbns != null) {
                    isbns.remove(isbn);
                    if (isbns.isEmpty()) {
                        secondaryIndex.remove(existingManga.getTitle());
                    }
                }
                secondaryIndex.computeIfAbsent(updatedManga.getTitle(), k -> new ArrayList<>()).add(updatedManga.getIsbn());
            }

            saveIndicesToFile();
        }
    }

    private void saveMangaToFileAtPosition(Manga manga, long position) {
        try (RandomAccessFile raf = new RandomAccessFile(MANGA_FILE, "rw")) {
            raf.seek(position);
            raf.writeUTF(gson.toJson(manga));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void deleteManga(String isbn) {
        Long position = primaryIndex.remove(isbn);
        if (position != null) {
            Manga manga = readMangaFromFile(position);
            if (manga != null) {
                List<String> isbns = secondaryIndex.get(manga.getTitle());
                if (isbns != null) {
                    isbns.remove(isbn);
                    if (isbns.isEmpty()) {
                        secondaryIndex.remove(manga.getTitle());
                    }
                }
            }
            saveIndicesToFile();
        }
    }

    public boolean confirmDeletion(String isbn) {
        return primaryIndex.containsKey(isbn);
    }

    public List<Manga> listAllMangas() {
        List<Manga> allMangas = new ArrayList<>();
        for (Long position : primaryIndex.values()) {
            allMangas.add(readMangaFromFile(position));
        }
        return allMangas;
    }

    private void saveIndicesToFile() {
        try (Writer writer = new FileWriter(PRIMARY_INDEX_FILE)) {
            gson.toJson(primaryIndex, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (Writer writer = new FileWriter(SECONDARY_INDEX_FILE)) {
            gson.toJson(secondaryIndex, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void loadFromFile() {
        try (Reader reader = new FileReader(PRIMARY_INDEX_FILE)) {
            Type mapType = new TypeToken<TreeMap<String, Long>>(){}.getType();
            primaryIndex = gson.fromJson(reader, mapType);
        } catch (IOException e) {
            primaryIndex = new TreeMap<>();
        }

        try (Reader reader = new FileReader(SECONDARY_INDEX_FILE)) {
            Type mapType = new TypeToken<TreeMap<String, List<String>>>(){}.getType();
            secondaryIndex = gson.fromJson(reader, mapType);
        } catch (IOException e) {
            secondaryIndex = new TreeMap<>();
        }
    }
}
