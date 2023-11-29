#include "Processo.hpp"
#include "iostream"
#include "FileManager.hpp"

Processo::Processo(int id, int startTime, int timeLeft,
                   int priority,
                   int memory,
                   int printer,
                   int scanner,
                   int modem,
                   int disk, int filaDeExecucao) : id(id), timeLeft(timeLeft), startTime(startTime), priority(priority),
                                                   memory(memory),
                                                   scanner(scanner),
                                                   modem(modem),
                                                   disk(disk), filaDeExecucao(filaDeExecucao)
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

    for(int i = 2 + std::stoi(fileManager.initialValues->at(1).at(0)); i < fileManager.initialValues->size(); ++i){
        if(std::stoi(fileManager.initialValues->at(i).at(0)) == this->id){
            switch(std::stoi(fileManager.initialValues->at(i).at(1))){
            case 0:
                fileManager.CreateFile(fileManager.initialValues->at(i).at(2), std::stoi(fileManager.initialValues->at(i).at(3)));
                break;
            case 1:
                fileManager.DeleteFile(fileManager.initialValues->at(i).at(2));
                break;
            }
        }
    }

    return this;
}

bool Processo::hasDied()
{
    return this->timeLeft <= 0;
}
