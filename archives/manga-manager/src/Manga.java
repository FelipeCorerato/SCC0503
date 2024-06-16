import java.io.Serializable;
import java.util.List;

public class Manga implements Serializable {
    private static final long serialVersionUID = 1L;

    private String isbn;
    private String title;
    private List<String> authors;
    private int startYear;
    private int endYear;
    private String genre;
    private String magazine;
    private String publisher;
    private int editionYear;
    private int volumeCount;
    private int acquiredVolumes;
    private List<Integer> volumeList;

    public Manga(String isbn, String title, List<String> authors, int startYear, int endYear, String genre,
                 String magazine, String publisher, int editionYear, int volumeCount, int acquiredVolumes,
                 List<Integer> volumeList) {
        this.isbn = isbn;
        this.title = title;
        this.authors = authors;
        this.startYear = startYear;
        this.endYear = endYear;
        this.genre = genre;
        this.magazine = magazine;
        this.publisher = publisher;
        this.editionYear = editionYear;
        this.volumeCount = volumeCount;
        this.acquiredVolumes = acquiredVolumes;
        this.volumeList = volumeList;
    }

    public String getIsbn() { return isbn; }
    public String getTitle() { return title; }
    public List<String> getAuthors() { return authors; }
    public int getStartYear() { return startYear; }
    public int getEndYear() { return endYear; }
    public String getGenre() { return genre; }
    public String getMagazine() { return magazine; }
    public String getPublisher() { return publisher; }
    public int getEditionYear() { return editionYear; }
    public int getVolumeCount() { return volumeCount; }
    public int getAcquiredVolumes() { return acquiredVolumes; }
    public List<Integer> getVolumeList() { return volumeList; }

    public void setIsbn(String isbn) { this.isbn = isbn; }
    public void setTitle(String title) { this.title = title; }
    public void setAuthors(List<String> authors) { this.authors = authors; }
    public void setStartYear(int startYear) { this.startYear = startYear; }
    public void setEndYear(int endYear) { this.endYear = endYear; }
    public void setGenre(String genre) { this.genre = genre; }
    public void setMagazine(String magazine) { this.magazine = magazine; }
    public void setPublisher(String publisher) { this.publisher = publisher; }
    public void setEditionYear(int editionYear) { this.editionYear = editionYear; }
    public void setVolumeCount(int volumeCount) { this.volumeCount = volumeCount; }
    public void setAcquiredVolumes(int acquiredVolumes) { this.acquiredVolumes = acquiredVolumes; }
    public void setVolumeList(List<Integer> volumeList) { this.volumeList = volumeList; }
}
