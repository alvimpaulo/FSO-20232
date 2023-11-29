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
    /* data */
public:
    ProcessoManager(/* args */);
    deque<Processo*> filaProcesosTempoRealAlocados;
    vector<deque<Processo*>> filasProcessosUsuarioAlocados;
    MemoryVector memoriaProcessosTempoReal;
    MemoryVector memoriaProcessosUsuario;
    bool alocarMemoriaProcessoTempoReal(Processo* process);
    bool alocarMemoriaProcessoUsuario(Processo* process);
    void run(int cpuTime);
    vector<Processo*> getProcessosAlocados();
    IOManager* ioManager;
    void ageProcesses(int cpuTime);
};