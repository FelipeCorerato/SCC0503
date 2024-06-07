#include "mangadatabase.h"
#include <iostream>
#include <algorithm>

MangaDatabase::MangaDatabase(const std::string& dataFile, const std::string& primaryIndexFile, const std::string& secondaryIndexFile)
        : dataFileName(dataFile), primaryIndexFileName(primaryIndexFile), secondaryIndexFileName(secondaryIndexFile) {
    loadDatabase();
    loadIndices();
}

void MangaDatabase::loadDatabase() {
    std::ifstream dataFile(dataFileName, std::ios::in | std::ios::binary);
    if (!dataFile) {
        return; // Arquivo não existe ou não pode ser aberto
    }

    while (dataFile.peek() != EOF) {
        Manga manga;
        std::streampos pos = dataFile.tellg();
        manga.deserialize(dataFile);
        if (!manga.removed) {
            primaryIndex[manga.ISBN] = pos;
            secondaryIndex.insert(std::make_pair(manga.title, manga.ISBN));
        }
    }

    dataFile.close();
}

void MangaDatabase::saveDatabase() {
    std::ofstream dataFile(dataFileName, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!dataFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de dados");
    }

    for (const auto& pair : primaryIndex) {
        Manga manga = getMangaByISBN(pair.first);
        manga.serialize(dataFile);
    }

    dataFile.close();
    saveIndices();
}

void MangaDatabase::loadIndices() {
    primaryIndex.clear();
    secondaryIndex.clear();

    std::ifstream primaryFile(primaryIndexFileName);
    if (primaryFile) {
        std::string ISBN;
        std::streamoff offset;
        while (primaryFile >> ISBN >> offset) {
            primaryIndex[ISBN] = static_cast<std::streampos>(offset);
        }
        primaryFile.close();
    }

    std::ifstream secondaryFile(secondaryIndexFileName);
    if (secondaryFile) {
        std::string title, ISBN;
        while (secondaryFile >> title >> ISBN) {
            secondaryIndex.insert(std::make_pair(title, ISBN));
        }
        secondaryFile.close();
    }
}

void MangaDatabase::saveIndices() {
    std::ofstream primaryFile(primaryIndexFileName, std::ios::out | std::ios::trunc);
    if (!primaryFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de índice primário");
    }

    for (const auto& pair : primaryIndex) {
        primaryFile << pair.first << " " << pair.second << "\n";
    }
    primaryFile.close();

    std::ofstream secondaryFile(secondaryIndexFileName, std::ios::out | std::ios::trunc);
    if (!secondaryFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de índice secundário");
    }

    for (const auto& pair : secondaryIndex) {
        secondaryFile << pair.first << " " << pair.second << "\n";
    }
    secondaryFile.close();
}

void MangaDatabase::addManga(const Manga& manga) {
    std::ofstream dataFile(dataFileName, std::ios::app | std::ios::binary);
    if (!dataFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de dados");
    }

    std::streampos pos = dataFile.tellp();
    manga.serialize(dataFile);
    dataFile.close();

    primaryIndex[manga.ISBN] = pos;
    secondaryIndex.insert(std::make_pair(manga.title, manga.ISBN));

    saveIndices();
}

Manga MangaDatabase::getMangaByISBN(const std::string& ISBN) {
    auto it = primaryIndex.find(ISBN);
    if (it == primaryIndex.end()) {
        throw std::runtime_error("Manga not found");
    }

    std::ifstream dataFile(dataFileName, std::ios::in | std::ios::binary);
    if (!dataFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de dados");
    }

    Manga manga;
    dataFile.seekg(it->second);
    manga.deserialize(dataFile);
    dataFile.close();

    return manga;
}

std::vector<Manga> MangaDatabase::getMangaByTitle(const std::string& title) {
    std::vector<Manga> results;
    auto range = secondaryIndex.equal_range(title);
    for (auto it = range.first; it != range.second; ++it) {
        results.push_back(getMangaByISBN(it->second));
    }
    return results;
}

void MangaDatabase::updateManga(const Manga& manga) {
    deleteManga(manga.ISBN);
    addManga(manga);
}

void MangaDatabase::deleteManga(const std::string& ISBN) {
    auto it = primaryIndex.find(ISBN);
    if (it == primaryIndex.end()) {
        throw std::runtime_error("Manga not found");
    }

    markAsRemoved(ISBN);

    primaryIndex.erase(it);
    auto range = secondaryIndex.equal_range(getMangaByISBN(ISBN).title);
    for (auto it2 = range.first; it2 != range.second; ) {
        if (it2->second == ISBN) {
            it2 = secondaryIndex.erase(it2);
        } else {
            ++it2;
        }
    }

    saveIndices();
}

void MangaDatabase::markAsRemoved(const std::string& ISBN) {
    std::ifstream dataFile(dataFileName, std::ios::in | std::ios::binary);
    if (!dataFile) {
        throw std::runtime_error("Erro ao abrir o arquivo de dados");
    }

    std::ofstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    if (!tempFile) {
        throw std::runtime_error("Erro ao abrir o arquivo temporário");
    }

    while (dataFile.peek() != EOF) {
        Manga manga;
        std::streampos pos = dataFile.tellg();
        manga.deserialize(dataFile);
        if (manga.ISBN == ISBN) {
            manga.removed = true;
        }
        manga.serialize(tempFile);
    }

    dataFile.close();
    tempFile.close();

    std::remove(dataFileName.c_str());
    std::rename("temp.dat", dataFileName.c_str());
}

void MangaDatabase::compactDatabase() {
    std::ofstream tempFile("temp.dat", std::ios::out | std::ios::binary);
    std::ifstream dataFile(dataFileName, std::ios::in | std::ios::binary);

    if (!tempFile || !dataFile) {
        throw std::runtime_error("Erro ao abrir os arquivos para compactação");
    }

    std::map<std::string, std::streampos> newPrimaryIndex;
    std::multimap<std::string, std::string> newSecondaryIndex;

    while (dataFile.peek() != EOF) {
        Manga manga;
        manga.deserialize(dataFile);
        if (!manga.removed) {
            std::streampos newPos = tempFile.tellp();
            manga.serialize(tempFile);
            newPrimaryIndex[manga.ISBN] = newPos;
            newSecondaryIndex.insert(std::make_pair(manga.title, manga.ISBN));
        }
    }

    dataFile.close();
    tempFile.close();

    std::remove(dataFileName.c_str());
    std::rename("temp.dat", dataFileName.c_str());

    primaryIndex = newPrimaryIndex;
    secondaryIndex = newSecondaryIndex;

    saveIndices();
}

void MangaDatabase::listAllMangas() {
    for (const auto& pair : primaryIndex) {
        std::cout << getMangaByISBN(pair.first) << "\n";
    }
}
