#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
#include <utility>
#include <string>
#include <tuple>

class FileManager{
public:
    static FileManager& GetInstance();
    int CreateFile(std::string fileName, int fileSize, int firstAddress = 0);
    bool DeleteFile(std::string fileName);
    void PrintStorage();
    void PrintFAT();

    static std::vector<std::vector<std::string>>* initialValues;
private:
    FileManager(int size);
    std::vector<bool> storage;
    std::vector<std::tuple<std::string, int, int>> FAT;

    static FileManager* instance;

    int size;
};

#endif // FILEMANAGER_HPP
