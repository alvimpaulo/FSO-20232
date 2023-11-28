#pragma once

class Processo
{
private:
    /* data */
public:
    Processo(int id, int startTime, int timeLeft, int priority,
             int memory,
             int printer,
             int scanner,
             int modem,
             int disk);
    int id;
    int timeLeft;
    int startTime;
    int priority;
    int memory;
    int printer;
    int scanner;
    int modem;
    int disk;
    int isPronto;

    void setProcessoIsPronto(bool newState);
    Processo* run(int cpuTime);
    bool hasDied();
};