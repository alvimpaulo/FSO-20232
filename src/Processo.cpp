#include "Processo.hpp"
#include "iostream"

Processo::Processo(int id, int startTime, int timeLeft,
                   int priority,
                   int memory,
                   int printer,
                   int scanner,
                   int modem,
                   int disk) : id(id), timeLeft(timeLeft), startTime(startTime), priority(priority),
                               memory(memory),
                               printer(printer),
                               scanner(scanner),
                               modem(modem),
                               disk(disk), isPronto(true)
{
}

void Processo::setProcessoIsPronto(bool newState)
{
    this->isPronto = newState;
}

Processo* Processo::run(int cpuTime){
    this->timeLeft--;
    std::cout << "Rodou o processo de id " << this->id << " faltam: " << this->timeLeft << " operações" << std::endl;
    //FAZER IO E ARQUIVOS AQUI

    return this;
}

bool Processo::hasDied(){
    return this->timeLeft <= 0;
}