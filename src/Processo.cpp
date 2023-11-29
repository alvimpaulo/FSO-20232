#include "Processo.hpp"
#include "iostream"
#include "FileManager.hpp"
#include "util.hpp"

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
    this->totalTime = timeLeft;
}

void Processo::setProcessoIsPronto(bool newState)
{
    this->isPronto = newState;
}

Processo *Processo::run(int cpuTime)
{
    // Terminal colors
    Color::Modifier termBlue(Color::FG_BLUE);
    Color::Modifier termReset(Color::FG_DEFAULT);
    Color::Modifier termBold(Color::FG_BOLD);

    // ARQUIVOS

    FileManager &fileManager = FileManager::GetInstance();

    int i = 2 + std::stoi(fileManager.initialValues->at(1).at(0)) + (this->totalTime - this->timeLeft);

    if (i < fileManager.initialValues->size())
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

    // for (int i = 2 + std::stoi(fileManager.initialValues->at(1).at(0)) + (this->totalTime - this->timeLeft); i < fileManager.initialValues->size(); ++i)
    // {
    // }

    this->timeLeft--;
    std::cout << termBlue << "Rodou o processo de id " << termBold << this->id << termReset << termBlue << " faltam: " << this->timeLeft << " operações" << termReset << std::endl;

    return this;
}

bool Processo::hasDied()
{
    return this->timeLeft <= 0;
}
