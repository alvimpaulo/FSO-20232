#pragma once
#include "MemorySpace.hpp"
#include <bits/stdc++.h>

using namespace std;

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
             int sata, int filaDeExecucao);
    int id;
    int timeLeft;
    int startTime;
    int priority;
    int memory;
    int printer;
    int scanner;
    int modem;
    int sata;
    int isPronto;
    int totalTime;
    unsigned long long cpuTimeCurrentList;
    int filaDeExecucao;
    MemorySpace *memorySpace;
    vector<vector<string>> fileInstructions;

    void setProcessoIsPronto(bool newState);
    Processo *run(int cpuTime);
    bool hasDied();
};