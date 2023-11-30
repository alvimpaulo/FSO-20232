#pragma once

#include "Processo.hpp"
#include <bits/stdc++.h>
#include "util.hpp"
#include "MemorySpace.hpp"
#include "MemoryVector.hpp"
#include "IOManager.hpp"

using namespace std;

class ProcessoManager
{
private:
    ProcessoManager(/* args */);
    static ProcessoManager* instance;
public:
    
    deque<Processo*> filaProcesosTempoRealAlocados;
    vector<deque<Processo*>> filasProcessosUsuarioAlocados;
    deque<Processo *> processosParaAlocar;
    MemoryVector memoriaProcessosTempoReal;
    MemoryVector memoriaProcessosUsuario;
    bool alocarMemoriaProcessoTempoReal(Processo* process);
    bool alocarMemoriaProcessoUsuario(Processo* process);
    void run(int cpuTime);
    vector<Processo*> getProcessosAlocados();
    IOManager* ioManager;
    void ageProcesses(int cpuTime);
    Processo* getProcessById(int id);

    static ProcessoManager* getInstance();
};