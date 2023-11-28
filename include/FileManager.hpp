#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
#include <utility>

class FileManager{
public:
    static FileManager& GetInstance();
    std::pair<int, int> CreateFile(std::vector<bool> data);
    bool DeleteFile(int address, int size);
    std::vector<bool> OpenFile(int address, int size);
    bool CheckIfFileExists(int address, int size);
private:
    FileManager(int size, int blockSize);
    std::vector<std::pair<bool, std::vector<bool>>> storage;

    static inline FileManager* instance = nullptr;

    int size;
    int blockSize;
};

#endif // FILEMANAGER_HPP
