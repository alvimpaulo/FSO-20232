#include "Processo.hpp"
#include "iostream"
#include "FileManager.hpp"

Processo::Processo(int id, int startTime, int timeLeft,
                   int priority,
                   int memory,
                   int printer,
                   int scanner,
                   int modem,
                   int sata, int filaDeExecucao) : id(id), timeLeft(timeLeft), startTime(startTime), priority(priority),
                                                   memory(memory),
                                                   scanner(scanner),
                                                   modem(modem),
                                                   sata(sata), filaDeExecucao(filaDeExecucao)
{
    isPronto = true;
    cpuTimeCurrentList = 0;
    memorySpace = nullptr;
}

void Processo::setProcessoIsPronto(bool newState)
{
    this->isPronto = newState;
}

Processo *Processo::run(int cpuTime)
{
    this->timeLeft--;
    std::cout << "Rodou o processo de id " << this->id << " faltam: " << this->timeLeft << " operações" << std::endl;
    // FAZER IO E ARQUIVOS AQUI

    //ARQUIVOS

    FileManager& fileManager = FileManager::GetInstance();

    srand(time(0));
    int instruction = rand()%4;
    std::vector<bool> file;
    int fileSize = rand() % 100;
    std::pair<int, int> fileData;

    switch(instruction){
    case 0:
        for(int i = 0; i < fileSize; ++i){
            file.push_back(rand()%2);
        }
        fileData = fileManager.CreateFile(file);
        break;
    case 1:
        if(fileManager.CheckIfFileExists(rand() % 100, rand() % 100)){
            std::cout << "Arquivo existe" << std::endl;
        }
        else{
            std::cout << "Arquivo nao existe" << std::endl;
        }
        break;
    case 2:
        if(fileManager.DeleteFile(rand() % 100, rand() % 100)){
            std::cout << "Arquivo deletado com sucesso" << std::endl;
        }
        else{
            std::cout << "Arquivo nao valido" << std::endl;
        }
        break;
    case 3:
        file = fileManager.OpenFile(rand() % 100, rand() % 100);
        break;
    }

    return this;
}

bool Processo::hasDied()
{
    return this->timeLeft <= 0;
}
