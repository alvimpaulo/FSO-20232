#pragma once
#include <bits/stdc++.h>
#include "DispositivoIO.hpp"
#include "Processo.hpp"
using namespace std;

class IOManager
{
public:
    IOManager();

    vector<DispositivoIO *> scanner;
    vector<DispositivoIO *> impressoras;
    vector<DispositivoIO *> modem;
    vector<DispositivoIO *> satas;

    bool alocateNewScanner(int pid);
    bool alocateNewImpressora(int pid, int id);
    bool alocateNewModem(int pid);
    bool alocateNewSATA(int pid, int id);

    DispositivoIO *getScanner(int pid);
    DispositivoIO *getImpressora(int pid, int id);
    DispositivoIO *getModem(int pid);
    DispositivoIO *getSata(int pid, int id);

    bool isScannerFree();
    bool isImpressoraFree(int id);
    bool isModemFree();
    bool isSataFree(int id);

    void freeScanner();
    void freePrinter(int id);
    void freeModem();
    void freeSATA(int id);

    void freeIOFromDeadProcess(Processo* process);

    bool isProcessGoodToRun(Processo *process);
};
