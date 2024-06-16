import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class MangaManagerGUI extends JFrame {
    private MangaManager mangaManager;
    private JTextField isbnField, titleField, authorsField, startYearField, endYearField, genreField,
            magazineField, publisherField, editionYearField, volumeCountField, acquiredVolumesField, volumeListField;
    private JTextField searchIsbnField, searchTitleField;
    private JTextArea displayArea;
    private JLabel statusBar;

    public MangaManagerGUI() {
        mangaManager = new MangaManager();
        initializeGUI();
    }

    private void initializeGUI() {
        setTitle("Manga Manager");
        setSize(1000, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }

        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenuItem exitMenuItem = new JMenuItem("Exit");
        exitMenuItem.addActionListener(e -> System.exit(0));
        fileMenu.add(exitMenuItem);
        menuBar.add(fileMenu);

        JMenu helpMenu = new JMenu("Help");
        JMenuItem aboutMenuItem = new JMenuItem("About");
        aboutMenuItem.addActionListener(e -> showAboutDialog());
        helpMenu.add(aboutMenuItem);
        menuBar.add(helpMenu);

        setJMenuBar(menuBar);

        JPanel inputPanel = new JPanel(new GridLayout(14, 2));

        isbnField = addInputField(inputPanel, "ISBN:");
        titleField = addInputField(inputPanel, "Title:");
        authorsField = addInputField(inputPanel, "Authors (comma-separated):");
        startYearField = addInputField(inputPanel, "Start Year:");
        endYearField = addInputField(inputPanel, "End Year:");
        genreField = addInputField(inputPanel, "Genre:");
        magazineField = addInputField(inputPanel, "Magazine:");
        publisherField = addInputField(inputPanel, "Publisher:");
        editionYearField = addInputField(inputPanel, "Edition Year:");
        volumeCountField = addInputField(inputPanel, "Volume Count:");
        acquiredVolumesField = addInputField(inputPanel, "Acquired Volumes:");
        volumeListField = addInputField(inputPanel, "Volume List (comma-separated):");

        add(inputPanel, BorderLayout.WEST);

        displayArea = new JTextArea();
        displayArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(displayArea);
        add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new GridLayout(6, 1));

        JButton addButton = new JButton("Add Manga");
        addButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addManga();
            }
        });
        buttonPanel.add(addButton);

        JButton updateButton = new JButton("Update Manga");
        updateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                updateManga();
            }
        });
        buttonPanel.add(updateButton);

        JButton deleteButton = new JButton("Delete Manga");
        deleteButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                deleteManga();
            }
        });
        buttonPanel.add(deleteButton);

        JButton listButton = new JButton("List All Mangas");
        listButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listAllMangas();
            }
        });
        buttonPanel.add(listButton);

        searchIsbnField = addInputField(inputPanel, "Search by ISBN:");
        JButton searchIsbnButton = new JButton("Search by ISBN");
        searchIsbnButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchMangaByIsbn();
            }
        });
        buttonPanel.add(searchIsbnButton);

        searchTitleField = addInputField(inputPanel, "Search by Title:");
        JButton searchTitleButton = new JButton("Search by Title");
        searchTitleButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchMangaByTitle();
            }
        });
        buttonPanel.add(searchTitleButton);

        add(buttonPanel, BorderLayout.EAST);

        statusBar = new JLabel("Welcome to Manga Manager");
        add(statusBar, BorderLayout.SOUTH);
    }

    private JTextField addInputField(JPanel panel, String labelText) {
        JLabel label = new JLabel(labelText);
        JTextField textField = new JTextField();
        panel.add(label);
        panel.add(textField);
        return textField;
    }

    private void addManga() {
        try {
            String isbn = isbnField.getText();
            if (isbn.isEmpty()) {
                displayMessage("Error: ISBN is required.");
                return;
            }
            String title = titleField.getText();
            if (title.isEmpty()) {
                displayMessage("Error: Title is required.");
                return;
            }
            List<String> authors = Arrays.asList(authorsField.getText().split(","));
            int startYear = parseInteger(startYearField.getText(), "Start Year");
            int endYear = parseInteger(endYearField.getText(), "End Year");
            String genre = genreField.getText();
            String magazine = magazineField.getText();
            String publisher = publisherField.getText();
            int editionYear = parseInteger(editionYearField.getText(), "Edition Year");
            int volumeCount = parseInteger(volumeCountField.getText(), "Volume Count");
            int acquiredVolumes = parseInteger(acquiredVolumesField.getText(), "Acquired Volumes");
            List<Integer> volumeList = parseVolumeList(volumeListField.getText());

            Manga manga = new Manga(isbn, title, authors, startYear, endYear, genre, magazine, publisher,
                    editionYear, volumeCount, acquiredVolumes, volumeList);
            boolean success = mangaManager.addManga(manga);
            if (success) {
                displayMessage("Manga added successfully!");
            } else {
                displayMessage("Error: Duplicate ISBN. Manga not added.");
            }
            clearFields();
        } catch (NumberFormatException e) {
            displayMessage("Error: Invalid input. Please check your data.");
        }
    }

    private void updateManga() {
        String isbn = isbnField.getText();
        Manga existingManga = mangaManager.getMangaByIsbn(isbn);
        if (existingManga == null) {
            displayMessage("Manga not found.");
            return;
        }

        int confirm = JOptionPane.showConfirmDialog(this, "Are you sure you want to update this manga?", "Update Confirmation", JOptionPane.YES_NO_OPTION);
        if (confirm != JOptionPane.YES_OPTION) {
            displayMessage("Update canceled.");
            return;
        }

        try {
            String title = titleField.getText();
            List<String> authors = Arrays.asList(authorsField.getText().split(","));
            int startYear = parseInteger(startYearField.getText(), "Start Year");
            int endYear = parseInteger(endYearField.getText(), "End Year");
            String genre = genreField.getText();
            String magazine = magazineField.getText();
            String publisher = publisherField.getText();
            int editionYear = parseInteger(editionYearField.getText(), "Edition Year");
            int volumeCount = parseInteger(volumeCountField.getText(), "Volume Count");
            int acquiredVolumes = parseInteger(acquiredVolumesField.getText(), "Acquired Volumes");
            List<Integer> volumeList = parseVolumeList(volumeListField.getText());

            Manga updatedManga = new Manga(isbn, title, authors, startYear, endYear, genre, magazine, publisher,
                    editionYear, volumeCount, acquiredVolumes, volumeList);
            mangaManager.updateManga(isbn, updatedManga);
            displayMessage("Manga updated successfully!");
            clearFields();
        } catch (NumberFormatException e) {
            displayMessage("Error: Invalid input. Please check your data.");
        }
    }

    private void deleteManga() {
        String isbn = isbnField.getText();
        Manga existingManga = mangaManager.getMangaByIsbn(isbn);
        if (existingManga == null) {
            displayMessage("Manga not found.");
            return;
        }

        int confirm = JOptionPane.showConfirmDialog(this, "Are you sure you want to delete this manga?", "Delete Confirmation", JOptionPane.YES_NO_OPTION);
        if (confirm != JOptionPane.YES_OPTION) {
            displayMessage("Deletion canceled.");
            return;
        }

        mangaManager.deleteManga(isbn);
        displayMessage("Manga deleted successfully!");
        clearFields();
    }

    private void listAllMangas() {
        List<Manga> mangas = mangaManager.listAllMangas();
        if (mangas.isEmpty()) {
            displayMessage("No mangas found.");
        } else {
            StringBuilder sb = new StringBuilder();
            for (Manga manga : mangas) {
                sb.append("ISBN: ").append(manga.getIsbn())
                        .append(", Title: ").append(manga.getTitle()).append("\n");
            }
            displayMessage(sb.toString());
        }
    }

    private void searchMangaByIsbn() {
        String isbn = searchIsbnField.getText();
        Manga manga = mangaManager.getMangaByIsbn(isbn);
        if (manga != null) {
            displayMessage(printMangaDetails(manga));
        } else {
            displayMessage("Manga not found.");
        }
    }

    private void searchMangaByTitle() {
        String title = searchTitleField.getText();
        List<Manga> mangas = mangaManager.getMangaByTitle(title);
        if (!mangas.isEmpty()) {
            StringBuilder sb = new StringBuilder();
            for (Manga manga : mangas) {
                sb.append(printMangaDetails(manga)).append("\n---\n");
            }
            displayMessage(sb.toString());
        } else {
            displayMessage("Manga not found.");
        }
    }

    private String printMangaDetails(Manga manga) {
        StringBuilder sb = new StringBuilder();
        sb.append("Mangá encontrado: \n")
                .append("ISBN: ").append(manga.getIsbn()).append("\n")
                .append("Título: ").append(manga.getTitle()).append("\n")
                .append("Autores: ").append(String.join(", ", manga.getAuthors())).append("\n")
                .append("Ano de Início: ").append(manga.getStartYear()).append("\n")
                .append("Ano de Fim: ").append(manga.getEndYear()).append("\n")
                .append("Gênero: ").append(manga.getGenre()).append("\n")
                .append("Revista: ").append(manga.getMagazine()).append("\n")
                .append("Editora: ").append(manga.getPublisher()).append("\n")
                .append("Ano da Edição: ").append(manga.getEditionYear()).append("\n")
                .append("Quantidade de Volumes: ").append(manga.getVolumeCount()).append("\n")
                .append("Volumes Adquiridos: ").append(manga.getAcquiredVolumes()).append("\n")
                .append("Lista de Volumes: ").append(manga.getVolumeList());
        return sb.toString();
    }

    private void displayMessage(String message) {
        displayArea.setText(message);
        statusBar.setText(message);
    }

    private void clearFields() {
        isbnField.setText("");
        titleField.setText("");
        authorsField.setText("");
        startYearField.setText("");
        endYearField.setText("");
        genreField.setText("");
        magazineField.setText("");
        publisherField.setText("");
        editionYearField.setText("");
        volumeCountField.setText("");
        acquiredVolumesField.setText("");
        volumeListField.setText("");
        searchIsbnField.setText("");
        searchTitleField.setText("");
    }

    private void showAboutDialog() {
        JOptionPane.showMessageDialog(this, "Manga Manager v1.0\nDeveloped by Your Name", "About Manga Manager", JOptionPane.INFORMATION_MESSAGE);
    }

    private int parseInteger(String text, String fieldName) {
        try {
            return Integer.parseInt(text);
        } catch (NumberFormatException e) {
            throw new NumberFormatException("Error: " + fieldName + " must be an integer.");
        }
    }

    private List<Integer> parseVolumeList(String text) {
        try {
            return Arrays.stream(text.split(","))
                    .map(Integer::parseInt)
                    .collect(Collectors.toList());
        } catch (NumberFormatException e) {
            throw new NumberFormatException("Error: Volume List must contain integers separated by commas.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new MangaManagerGUI().setVisible(true);
            }
        });
    }
}
