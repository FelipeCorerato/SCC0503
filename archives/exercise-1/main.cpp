#include "./lib/mangadatabase.h"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Adicionar Manga\n";
    std::cout << "2. Buscar Manga por ISBN\n";
    std::cout << "3. Buscar Manga por Titulo\n";
    std::cout << "4. Atualizar Manga\n";
    std::cout << "5. Apagar Manga\n";
    std::cout << "6. Listar Todos os Mangas\n";
    std::cout << "7. Compactar Banco de Dados\n"; // Nova opção para compactar
    std::cout << "8. Sair\n";
}

Manga getMangaDetails() {
    Manga manga;
    std::cout << "ISBN: ";
    std::cin >> manga.ISBN;
    std::cin.ignore();
    std::cout << "Titulo: ";
    std::getline(std::cin, manga.title);
    std::cout << "Autores: ";
    std::getline(std::cin, manga.authors);
    std::cout << "Ano de Inicio: ";
    std::cin >> manga.startYear;
    std::cout << "Ano de Fim: ";
    std::cin >> manga.endYear;
    std::cin.ignore();
    std::cout << "Genero: ";
    std::getline(std::cin, manga.genre);
    std::cout << "Revista: ";
    std::getline(std::cin, manga.magazine);
    std::cout << "Editora: ";
    std::getline(std::cin, manga.publisher);
    std::cout << "Ano da Edicao: ";
    std::cin >> manga.editionYear;
    std::cout << "Quantidade de Volumes: ";
    std::cin >> manga.volumeCount;
    std::cout << "Quantidade de Volumes Adquiridos: ";
    std::cin >> manga.acquiredVolumes;
    std::cout << "Lista dos Volumes Adquiridos: ";
    for (int i = 0; i < manga.volumeCount; ++i) {
        int volume;
        std::cin >> volume;
        manga.volumeList.push_back(volume);
    }
    return manga;
}

int main() {
    MangaDatabase db("mangas.dat", "primary_index.dat", "secondary_index.dat");

    while (true) {
        displayMenu();
        int choice;
        std::cout << "Escolha uma opcao: ";
        std::cin >> choice;

        try {
            if (choice == 1) {
                Manga manga = getMangaDetails();
                db.addManga(manga);
                std::cout << "Manga adicionado com sucesso!\n";
            } else if (choice == 2) {
                std::string ISBN;
                std::cout << "Digite o ISBN: ";
                std::cin >> ISBN;
                Manga manga = db.getMangaByISBN(ISBN);
                std::cout << manga << "\n";
            } else if (choice == 3) {
                std::string title;
                std::cout << "Digite o Titulo: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                auto mangas = db.getMangaByTitle(title);
                for (const auto& manga : mangas) {
                    std::cout << manga << "\n";
                }
            } else if (choice == 4) {
                Manga manga = getMangaDetails();
                db.updateManga(manga);
                std::cout << "Manga atualizado com sucesso!\n";
            } else if (choice == 5) {
                std::string ISBN;
                std::cout << "Digite o ISBN: ";
                std::cin >> ISBN;
                db.deleteManga(ISBN);
                std::cout << "Manga apagado com sucesso!\n";
            } else if (choice == 6) {
                db.listAllMangas();
            } else if (choice == 7) {
                db.compactDatabase();
                std::cout << "Banco de dados compactado com sucesso!\n";
            } else if (choice == 8) {
                break;
            } else {
                std::cout << "Opcao invalida. Tente novamente.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    return 0;
}
