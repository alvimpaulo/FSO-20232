#include "FileManager.hpp"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "util.hpp"
#include "ProcessoManager.hpp"

FileManager *FileManager::instance = nullptr;
std::vector<std::vector<std::string>> *FileManager::initialValues = nullptr;

static std::vector<std::vector<std::string>> *ReadInitialFile(std::string directory)
{
    std::ifstream dataFile(directory);
    if (!dataFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        exit(1);
    }

    std::string str;
    auto fileContentVector = new std::vector<std::vector<std::string>>();

    while (std::getline(dataFile, str))
    {
        auto splittedInfo = splitString(str, ',');
        for (size_t i = 0; i < splittedInfo.size(); i++)
        {
            trim(splittedInfo[i]);
        }

        fileContentVector->push_back(splittedInfo);
    }

    return fileContentVector;
}

FileManager &FileManager::GetInstance()
{
    if (instance == nullptr)
    {
        initialValues = ReadInitialFile("files.txt");
        instance = new FileManager(std::stoi(initialValues->at(0).at(0)));
    }
    return *instance;
}

FileManager::FileManager(int size) : storage(size, 0)
{
    if (instance != nullptr)
    {
        exit(1);
    }
    else
    {
        instance = this;
    }
    this->size = size;

    for (int i = 2; i < std::stoi(initialValues->at(1).at(0)) + 2; ++i)
    {
        std::tuple<std::string, int, int> line(initialValues->at(i).at(0), std::stoi(initialValues->at(i).at(1)), std::stoi(initialValues->at(i).at(2)));
        FAT.push_back(line);
        for (int j = 0; j < std::get<2>(line); ++j)
        {
            storage.at(std::get<1>(line) + j) = true;
        }
    }
    auto processManager = ProcessoManager::getInstance();
    for (size_t i = stoi((*initialValues)[1][0]) + 2; i < initialValues->size(); i++)
    {
        auto operationProcessPid = stoi(initialValues->at(i)[0]);
        auto operationProcess = processManager->getProcessById(operationProcessPid);
        if (operationProcess != nullptr)
        {
            operationProcess->fileInstructions.push_back(initialValues->at(i));
        }
    }
}

int FileManager::CreateFile(std::string fileName, int fileSize, int firstAddress)
{
    Color::Modifier termMagenta(Color::FG_LIGHT_MAGENTA);
    Color::Modifier termBackRed(Color::FG_LIGHT_MAGENTA, Color::BG_RED);
    Color::Modifier termReset(Color::FG_DEFAULT);
    Color::Modifier termBold(Color::FG_BOLD);
    int freeAddress = -1;

    if (freeAddress == -1)
    {

        // procura espaco disponivel para o arquivo
        for (int i = firstAddress; i < size - fileSize; ++i)
        {
            bool ableToWrite = true;
            for (int j = 0; j < fileSize; ++j)
            {
                if (storage.at(i + j) == 1)
                {
                    ableToWrite = false;
                }
            }
            if (ableToWrite)
            {
                freeAddress = i;
                break;
            }
        }
    }

    // se nao achar sai e retorna -1

    if (freeAddress == -1)
    {
        std::cout << termBackRed << "Nao ha espaco para o arquivo " << termBold << fileName << termReset << std::endl;
        return freeAddress;
    }

    // escreve o arquivo no espaco encontrado
    for (int i = freeAddress; i < fileSize; ++i)
    {
        storage.at(i) = 1;
    }

    std::tuple<std::string, int, int> line(fileName, freeAddress, fileSize);

    FAT.push_back(line);

    // retorna o endereço onde escreveu o arquivo
    return freeAddress;
}

bool FileManager::DeleteFile(std::string fileName)
{
    Color::Modifier termMagenta(Color::FG_LIGHT_MAGENTA);
    Color::Modifier termBackRed(Color::FG_LIGHT_MAGENTA, Color::BG_RED);

    Color::Modifier termReset(Color::FG_DEFAULT);
    Color::Modifier termBold(Color::FG_BOLD);
    for (int i = 0; i < FAT.size(); ++i)
    {
        if (fileName.compare(std::get<0>(FAT.at(i))) == 0)
        {
            for (int j = 0; j < std::get<2>(FAT.at(i)); ++j)
            {
                storage.at(std::get<1>(FAT.at(i)) + j) = 0;
            }
            FAT.erase(FAT.begin() + i);
            return true;
        }
    }

    std::cout << termBackRed << "O arquivo " << termBold << fileName << termReset << termBackRed << " a ser deletado nao foi encontrado" << termReset << std::endl;
    return false;
}

void FileManager::PrintStorage()
{
    Color::Modifier termMagenta(Color::FG_LIGHT_MAGENTA);
    Color::Modifier termReset(Color::FG_DEFAULT);
    cout << termMagenta;
    for (int i = 0; i < storage.size(); ++i)
    {
        std::cout << storage.at(i) << ' ';
    }
    std::cout << termReset << std::endl;
}

void FileManager::PrintFAT()
{
    Color::Modifier termMagenta(Color::FG_LIGHT_MAGENTA);
    Color::Modifier termReset(Color::FG_DEFAULT);
    cout << termMagenta;
    for (int i = 0; i < FAT.size(); ++i)
    {
        std::cout << std::get<0>(FAT.at(i)) << std::get<1>(FAT.at(i)) << std::get<2>(FAT.at(i)) << '\n';
    }
    cout << termReset;
}
