#include "FileManager.hpp"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>

FileManager* FileManager::instance = nullptr;
std::vector<std::vector<std::string>>* FileManager::initialValues = nullptr;

static std::vector<std::vector<std::string>>* ReadInitialFile(std::string directory){
    std::ifstream dataFile(directory);
    if (!dataFile.is_open()) {
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        exit(1);
    }

    std::string str;
    std::vector<std::vector<std::string>>* openedFile = new std::vector<std::vector<std::string>>();

    unsigned int i = 0;
    while(std::getline(dataFile, str)){
        openedFile->push_back({});
        openedFile->at(i).push_back({});
        unsigned int j = 0;
        char lastChar = 0;
        for(char it : str){
            if(it != '\n' && it != '\r'){
                if(it != ','){
                    if(it != ' ' && it != '\t'){
                        openedFile->at(i).at(j) += it;
                    }
                }
                else{
                    if(lastChar != it){
                        openedFile->at(i).push_back({});
                        ++j;
                    }
                }
                lastChar = it;
            }
        }
        ++i;
    }
    return openedFile;
}

FileManager& FileManager::GetInstance(){
    if(instance == nullptr){
        initialValues = ReadInitialFile("files.txt");
        instance = new FileManager(std::stoi(initialValues->at(0).at(0)));
    }
    return *instance;
}

FileManager::FileManager(int size): storage(size, 0){
    if(instance != nullptr){
        exit(1);
    }else{
        instance = this;
    }
    this->size = size;

    for (int i = 2; i < std::stoi(initialValues->at(1).at(0)) + 2; ++i){
        std::tuple<std::string, int, int> line(initialValues->at(i).at(0), std::stoi(initialValues->at(i).at(1)), std::stoi(initialValues->at(i).at(2)));
        FAT.push_back(line);
        for(int j = 0; j < std::get<2>(line); ++j){
            storage.at(std::get<1>(line) + j) = true;
        }
    }
}

int FileManager::CreateFile(std::string fileName, int fileSize, int firstAddress){

    int freeAddress = -1;

    if(freeAddress == -1){

        // procura espaco disponivel para o arquivo
        for(int i = firstAddress; i < size - fileSize; ++i){
            bool ableToWrite = true;
            for(int j = 0; j < fileSize; ++j){
                if(storage.at(i + j) == 1){
                    ableToWrite = false;
                }
            }
            if(ableToWrite){
                freeAddress = i;
                break;
            }
        }
    }

    // se nao achar sai e retorna -1

    if(freeAddress == -1){
        return freeAddress;
    }

    // escreve o arquivo no espaco encontrado
    for(int i = freeAddress; i < fileSize; ++i){
        storage.at(i) = 1;
    }

    std::tuple<std::string, int, int> line(fileName, freeAddress, fileSize);

    FAT.push_back(line);

    //retorna o endereço onde escreveu o arquivo
    return freeAddress;
}

bool FileManager::DeleteFile(std::string fileName){
    for(int i = 0; i < FAT.size(); ++i){
        if(fileName.compare(std::get<0>(FAT.at(i))) == 0){
            for(int j = 0; j < std::get<2>(FAT.at(i)); ++j){
                storage.at(std::get<1>(FAT.at(i)) + j) = 0;
            }
            FAT.erase(FAT.begin() + i);
            return true;
        }
    }
    return false;
}

void FileManager::PrintStorage(){
    for(int i = 0; i < storage.size(); ++i){
        std::cout << storage.at(i) << ' ';
    }
    std::cout << std::endl;
}

void FileManager::PrintFAT(){
    for(int i = 0; i < FAT.size(); ++i){
        std::cout << std::get<0>(FAT.at(i)) << std::get<1>(FAT.at(i)) << std::get<2>(FAT.at(i)) << '\n';
    }
}

