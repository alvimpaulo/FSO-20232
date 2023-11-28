#include "Processo.hpp"

Processo::Processo(int startTime, int timeLeft,
                   int priority,
                   int memory,
                   int printer,
                   int scanner,
                   int modem,
                   int disk,
                   bool isPronto) : timeLeft(timeLeft), startTime(startTime), priority(priority),
                                    memory(memory),
                                    printer(printer),
                                    scanner(scanner),
                                    modem(modem),
                                    disk(disk), isPronto(true)
{
}

void Processo::spend1Time()
{
    {
        if (timeLeft > 0)
        {
            timeLeft--;
        }
    }
}

void Processo::setProcessoIsPronto(bool newState)
{
    this->isPronto = newState;
}