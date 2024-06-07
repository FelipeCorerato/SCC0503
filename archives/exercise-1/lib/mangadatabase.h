#ifndef SCC0503_MANGADATABASE_H
#define SCC0503_MANGADATABASE_H

#include "manga.h"
#include <map>
#include <vector>
#include <fstream>
#include <stdexcept>

class MangaDatabase {
private:
    std::map<std::string, std::streampos> primaryIndex;
    std::multimap<std::string, std::string> secondaryIndex;
    std::string dataFileName;
    std::string primaryIndexFileName;
    std::string secondaryIndexFileName;

    void loadDatabase();
    void saveDatabase();
    void loadIndices();
    void saveIndices();
    void markAsRemoved(const std::string& ISBN);

public:
    MangaDatabase(const std::string& dataFile, const std::string& primaryIndexFile, const std::string& secondaryIndexFile);

    void addManga(const Manga& manga);
    Manga getMangaByISBN(const std::string& ISBN);
    std::vector<Manga> getMangaByTitle(const std::string& title);
    void updateManga(const Manga& manga);
    void deleteManga(const std::string& ISBN);
    void listAllMangas();
    void compactDatabase(); // Adicione esta linha
};

#endif //SCC0503_MANGADATABASE_H
