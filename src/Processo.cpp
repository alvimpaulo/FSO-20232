#include "Processo.hpp"
#include "iostream"
#include "FileManager.hpp"

Processo::Processo(int id, int startTime, int timeLeft,
                   int priority,
                   int memory,
                   int printer,
                   int scanner,
                   int modem,
                   int sata, int filaDeExecucao)
{
    this->id = id;
    this->timeLeft = timeLeft;
    this->startTime = startTime;
    this->priority = priority;
    this->memory = memory;
    this->scanner = scanner;
    this->modem = modem;
    this->sata = sata;
    this->filaDeExecucao = filaDeExecucao;
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
    // FAZER IO E ARQUIVOS AQUI

    // ARQUIVOS

    std::cout << cpuTime << " " << this->timeLeft << " " << this->startTime << std::endl;

    FileManager &fileManager = FileManager::GetInstance();

    for (int i = 2 + std::stoi(fileManager.initialValues->at(1).at(0)) ; i < fileManager.initialValues->size(); ++i)
    {
        if (std::stoi(fileManager.initialValues->at(i).at(0)) == this->id)
        {
            switch (std::stoi(fileManager.initialValues->at(i).at(1)))
            {
            case 0:
                std::cout << "Tentando executar criacao de arquivo" << std::endl;
                fileManager.CreateFile(fileManager.initialValues->at(i).at(2), std::stoi(fileManager.initialValues->at(i).at(3)));
                break;
            case 1:
                std::cout << "Tentando executar delecao de arquivo" << std::endl;
                fileManager.DeleteFile(fileManager.initialValues->at(i).at(2));
                break;
            }
        }
    }

    this->timeLeft--;
    std::cout << "Rodou o processo de id " << this->id << " faltam: " << this->timeLeft << " operações" << std::endl;

    return this;
}

bool Processo::hasDied()
{
    return this->timeLeft <= 0;
}
