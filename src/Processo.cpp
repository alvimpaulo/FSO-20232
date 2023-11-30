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
    this->fileInstructions = {};
}

void Processo::setProcessoIsPronto(bool newState)
{
    this->isPronto = newState;
}

Processo *Processo::run(int cpuTime)
{
    // Terminal colors
    Color::Modifier termLightBlue(Color::FG_LIGHT_CYAN);
    Color::Modifier termReset(Color::FG_DEFAULT);
    Color::Modifier termBold(Color::FG_BOLD);

    std::cout << termLightBlue << "Rodando o processo de id " << termBold << this->id << termReset << endl;

    // ARQUIVOS

    FileManager &fileManager = FileManager::GetInstance();

    auto currentOperationIndex = (totalTime - timeLeft);
    if (currentOperationIndex < fileInstructions.size())
    {
        auto currentOperation = fileInstructions[currentOperationIndex];

        switch (std::stoi(currentOperation[1]))
        {
        case 0:
            std::cout << termLightBlue << "Tentando executar criacao de arquivo" << termReset << std::endl;
            fileManager.CreateFile(currentOperation[2], std::stoi(currentOperation[3]));
            break;
        case 1:
            std::cout << termLightBlue << "Tentando executar delecao de arquivo" << termReset << std::endl;
            fileManager.DeleteFile(currentOperation[2]);
            break;
        }
    }

    this->timeLeft--;
    std::cout << termLightBlue << "Rodou o processo de id " << termBold << this->id << termReset << termLightBlue << " faltam: " << this->timeLeft << " operações" << termReset << std::endl;

    return this;
}

bool Processo::hasDied()
{
    return this->timeLeft <= 0;
}
