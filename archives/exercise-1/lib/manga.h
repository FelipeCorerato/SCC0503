#ifndef SCC0503_MANGA_H
#define SCC0503_MANGA_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

struct Manga {
    std::string ISBN;
    std::string title;
    std::string authors;
    int startYear;
    int endYear;
    std::string genre;
    std::string magazine;
    std::string publisher;
    int editionYear;
    int volumeCount;
    int acquiredVolumes;
    std::vector<int> volumeList;
    bool removed = false;  // Novo campo para marcar o registro como removido

    friend std::ostream& operator<<(std::ostream& os, const Manga& manga) {
        if (manga.removed) return os;  // Não imprime registros removidos
        os << "ISBN: " << manga.ISBN << "\n"
           << "Titulo: " << manga.title << "\n"
           << "Autores: " << manga.authors << "\n"
           << "Ano de Inicio: " << manga.startYear << "\n"
           << "Ano de Fim: " << manga.endYear << "\n"
           << "Genero: " << manga.genre << "\n"
           << "Revista: " << manga.magazine << "\n"
           << "Editora: " << manga.publisher << "\n"
           << "Ano da Edicao: " << manga.editionYear << "\n"
           << "Volumes: " << manga.volumeCount << "\n"
           << "Volumes Adquiridos: " << manga.acquiredVolumes << "\n"
           << "Lista dos Volumes Adquiridos: ";
        for (const int volume : manga.volumeList) {
            os << volume << " ";
        }
        os << "\n" << std::string(40, '-') << "\n";
        return os;
    }

    void serialize(std::ofstream& out) const {
        size_t length;

        length = ISBN.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(ISBN.c_str(), length);

        length = title.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(title.c_str(), length);

        length = authors.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(authors.c_str(), length);

        out.write(reinterpret_cast<const char*>(&startYear), sizeof(startYear));
        out.write(reinterpret_cast<const char*>(&endYear), sizeof(endYear));

        length = genre.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(genre.c_str(), length);

        length = magazine.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(magazine.c_str(), length);

        length = publisher.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(publisher.c_str(), length);

        out.write(reinterpret_cast<const char*>(&editionYear), sizeof(editionYear));
        out.write(reinterpret_cast<const char*>(&volumeCount), sizeof(volumeCount));
        out.write(reinterpret_cast<const char*>(&acquiredVolumes), sizeof(acquiredVolumes));

        length = volumeList.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(reinterpret_cast<const char*>(volumeList.data()), length * sizeof(int));

        out.write(reinterpret_cast<const char*>(&removed), sizeof(removed));
    }

    void deserialize(std::ifstream& in) {
        size_t length;
        char* buffer;

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        ISBN = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        title = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        authors = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&startYear), sizeof(startYear));
        in.read(reinterpret_cast<char*>(&endYear), sizeof(endYear));

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        genre = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        magazine = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        buffer = new char[length + 1];
        in.read(buffer, length);
        buffer[length] = '\0';
        publisher = buffer;
        delete[] buffer;

        in.read(reinterpret_cast<char*>(&editionYear), sizeof(editionYear));
        in.read(reinterpret_cast<char*>(&volumeCount), sizeof(volumeCount));
        in.read(reinterpret_cast<char*>(&acquiredVolumes), sizeof(acquiredVolumes));

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        volumeList.resize(length);
        in.read(reinterpret_cast<char*>(volumeList.data()), length * sizeof(int));

        in.read(reinterpret_cast<char*>(&removed), sizeof(removed));
    }
};

#endif //SCC0503_MANGA_H
