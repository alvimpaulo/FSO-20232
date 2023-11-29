#include "FileManager.hpp"
#include <stdlib.h>

FileManager& FileManager::GetInstance(){
    if(instance == nullptr){
        instance = new FileManager(1024, 8);
    }
    return *instance;
}

FileManager::FileManager(int size, int blockSize): storage(size, std::pair<bool, std::vector<bool>>(0, std::vector<bool>(blockSize, 0))){
    if(instance != nullptr){
        exit(1);
    }else{
        instance = this;
    }
    this->size = size;
    this->blockSize = blockSize;
}

std::pair<int, int> FileManager::CreateFile(std::vector<bool> data){
    int fileSizeInBlocks = data.size() / blockSize;
    if((data.size() % blockSize) > 0){
        fileSizeInBlocks++;
    }
    int freeAddress = -1;

    // procura espaco disponivel para o arquivo
    for(int i = 0; i < size - fileSizeInBlocks; ++i){
        bool ableToWrite = true;
        for(int j = 0; j < fileSizeInBlocks; ++j){
            if(storage.at(i).first == 1){
                ableToWrite = false;
            }
        }
        if(ableToWrite){
            freeAddress = i;
            break;
        }
    }

    // se nao achar sai e retorna -1

    if(freeAddress == -1){
        return;
    }

    // escreve o arquivo no espaco encontrado
    for(int i = 0; i < fileSizeInBlocks; ++i){
        for(int j = 0; j < blockSize; ++j){
            storage.at(freeAddress + i).first = 1;
            if(i * blockSize + j < data.size()){
                storage.at(freeAddress + i).second.at(j) = data.at(i * blockSize + j);
            }
            else{
                storage.at(freeAddress + i).second.at(j) = 0;
            }
        }
    }

    //retorna o endereço onde escreveu o arquivo e o tamanho do arquivo
    std::pair<int, int> result = std::make_pair(freeAddress, fileSizeInBlocks);
    return result;
}

bool FileManager::DeleteFile(int address, int size){
    //verificando a validade da requisicao de delete
    for(int i = 0; i < size; ++i){
        if(!(storage.at(address + i).first)){
            //requisicao de delete maior que o arquivo
            return false;
        }
    }

    //deletando o arquivo

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < blockSize; ++j){
            storage.at(address + i).second.at(j) = 0;
            storage.at(address + i).first = false;
        }
    }
    return true;
}

std::vector<bool> FileManager::OpenFile(int address, int size){
    if (address >= storage.size()){
        exit(2);
    }
    std::vector<bool>file;

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < blockSize; ++j){
            file.push_back(storage.at(address + i).second.at(j));
        }
    }

    return file;
}

bool FileManager::CheckIfFileExists(int address, int size){
    //verificando a validade da requisicao de delete
    for(int i = 0; i < size; ++i){
        if(!(storage.at(address + i).first)){
            //requisicao de delete maior que o arquivo
            return false;
        }
    }
    return true;
}
