import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class MangaManagerCLI {
    private MangaManager mangaManager;
    private Scanner scanner;

    public MangaManagerCLI() {
        mangaManager = new MangaManager();
        scanner = new Scanner(System.in);
    }

    public static void main(String[] args) {
        MangaManagerCLI cli = new MangaManagerCLI();
        cli.run();
    }

    public void run() {
        while (true) {
            System.out.println("Escolha uma opção:");
            System.out.println("1. Adicionar Mangá");
            System.out.println("2. Ler Mangá por ISBN");
            System.out.println("3. Ler Mangá por Título");
            System.out.println("4. Atualizar Mangá");
            System.out.println("5. Deletar Mangá");
            System.out.println("6. Listar Todos os Mangás");
            System.out.println("7. Sair");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    addManga();
                    break;
                case 2:
                    readMangaByIsbn();
                    break;
                case 3:
                    readMangaByTitle();
                    break;
                case 4:
                    updateManga();
                    break;
                case 5:
                    deleteManga();
                    break;
                case 6:
                    listAllMangas();
                    break;
                case 7:
                    System.out.println("Saindo...");
                    return;
                default:
                    System.out.println("Opção inválida");
            }
        }
    }

    private void addManga() {
        System.out.println("Digite o ISBN:");
        String isbn = scanner.nextLine();

        System.out.println("Digite o Título:");
        String title = scanner.nextLine();

        System.out.println("Digite os Autores (separados por vírgula):");
        List<String> authors = Arrays.asList(scanner.nextLine().split(","));

        System.out.println("Digite o Ano de Início:");
        int startYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite o Ano de Fim:");
        int endYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite o Gênero:");
        String genre = scanner.nextLine();

        System.out.println("Digite a Revista:");
        String magazine = scanner.nextLine();

        System.out.println("Digite a Editora:");
        String publisher = scanner.nextLine();

        System.out.println("Digite o Ano da Edição:");
        int editionYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a Quantidade de Volumes:");
        int volumeCount = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a Quantidade de Volumes Adquiridos:");
        int acquiredVolumes = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a Lista de Volumes (separados por vírgula):");
        List<Integer> volumeList = Arrays.stream(scanner.nextLine().split(","))
                .map(Integer::parseInt)
                .collect(Collectors.toList());

        Manga manga = new Manga(isbn, title, authors, startYear, endYear, genre, magazine, publisher, editionYear,
                volumeCount, acquiredVolumes, volumeList);
        boolean success = mangaManager.addManga(manga);
        if (success) {
            System.out.println("Mangá adicionado com sucesso!");
        } else {
            System.out.println("Erro: ISBN duplicado. Mangá não adicionado.");
        }
    }

    private void readMangaByIsbn() {
        System.out.println("Digite o ISBN do mangá:");
        String isbn = scanner.nextLine();

        Manga manga = mangaManager.getMangaByIsbn(isbn);
        if (manga != null) {
            printMangaDetails(manga);
        } else {
            System.out.println("Mangá não encontrado");
        }
    }

    private void readMangaByTitle() {
        System.out.println("Digite o Título do mangá:");
        String title = scanner.nextLine();

        List<Manga> mangas = mangaManager.getMangaByTitle(title);
        if (!mangas.isEmpty()) {
            for (Manga manga : mangas) {
                printMangaDetails(manga);
                System.out.println("---");
            }
        } else {
            System.out.println("Mangá não encontrado");
        }
    }

    private void updateManga() {
        System.out.println("Digite o ISBN do mangá a ser atualizado:");
        String isbn = scanner.nextLine();

        Manga existingManga = mangaManager.getMangaByIsbn(isbn);
        if (existingManga == null) {
            System.out.println("Mangá não encontrado.");
            return;
        }

        System.out.println("Você tem certeza que deseja atualizar este mangá? (s/n)");
        String confirm = scanner.nextLine();
        if (!confirm.equalsIgnoreCase("s")) {
            System.out.println("Atualização cancelada.");
            return;
        }

        System.out.println("Digite o novo Título:");
        String title = scanner.nextLine();

        System.out.println("Digite os novos Autores (separados por vírgula):");
        List<String> authors = Arrays.asList(scanner.nextLine().split(","));

        System.out.println("Digite o novo Ano de Início:");
        int startYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite o novo Ano de Fim:");
        int endYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite o novo Gênero:");
        String genre = scanner.nextLine();

        System.out.println("Digite a nova Revista:");
        String magazine = scanner.nextLine();

        System.out.println("Digite a nova Editora:");
        String publisher = scanner.nextLine();

        System.out.println("Digite o novo Ano da Edição:");
        int editionYear = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a nova Quantidade de Volumes:");
        int volumeCount = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a nova Quantidade de Volumes Adquiridos:");
        int acquiredVolumes = Integer.parseInt(scanner.nextLine());

        System.out.println("Digite a nova Lista de Volumes (separados por vírgula):");
        List<Integer> volumeList = Arrays.stream(scanner.nextLine().split(","))
                .map(Integer::parseInt)
                .collect(Collectors.toList());

        Manga updatedManga = new Manga(isbn, title, authors, startYear, endYear, genre, magazine, publisher,
                editionYear, volumeCount, acquiredVolumes, volumeList);
        mangaManager.updateManga(isbn, updatedManga);
        System.out.println("Mangá atualizado com sucesso!");
    }

    private void deleteManga() {
        System.out.println("Digite o ISBN do mangá a ser deletado:");
        String isbn = scanner.nextLine();

        Manga existingManga = mangaManager.getMangaByIsbn(isbn);
        if (existingManga == null) {
            System.out.println("Mangá não encontrado.");
            return;
        }

        System.out.println("Você tem certeza que deseja deletar este mangá? (s/n)");
        String confirm = scanner.nextLine();
        if (!confirm.equalsIgnoreCase("s")) {
            System.out.println("Deleção cancelada.");
            return;
        }

        mangaManager.deleteManga(isbn);
        System.out.println("Mangá deletado com sucesso!");
    }

    private void listAllMangas() {
        List<Manga> mangas = mangaManager.listAllMangas();
        if (mangas.isEmpty()) {
            System.out.println("Nenhum mangá encontrado.");
        } else {
            System.out.println("Lista de todos os mangás:");
            for (Manga manga : mangas) {
                System.out.println("ISBN: " + manga.getIsbn() + ", Título: " + manga.getTitle());
            }
        }
    }

    private void printMangaDetails(Manga manga) {
        System.out.println("Mangá encontrado: ");
        System.out.println("ISBN: " + manga.getIsbn());
        System.out.println("Título: " + manga.getTitle());
        System.out.println("Autores: " + String.join(", ", manga.getAuthors()));
        System.out.println("Ano de Início: " + manga.getStartYear());
        System.out.println("Ano de Fim: " + manga.getEndYear());
        System.out.println("Gênero: " + manga.getGenre());
        System.out.println("Revista: " + manga.getMagazine());
        System.out.println("Editora: " + manga.getPublisher());
        System.out.println("Ano da Edição: " + manga.getEditionYear());
        System.out.println("Quantidade de Volumes: " + manga.getVolumeCount());
        System.out.println("Volumes Adquiridos: " + manga.getAcquiredVolumes());
        System.out.println("Lista de Volumes: " + manga.getVolumeList());
    }
}
