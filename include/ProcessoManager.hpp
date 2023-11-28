#pragma once

#include "Processo.hpp"
#include <bits/stdc++.h>
#include "util.hpp"
#include "MemorySpace.hpp"
#include "MemoryVector.hpp"

using namespace std;

class ProcessoManager
{
private:
    /* data */
public:
    ProcessoManager(/* args */);
    vector<Processo> procesosTempoRealAlocados;
    vector<vector<Processo>> filasProcessosUsuarioAlocados;
    MemoryVector memoriaProcessosTempoReal;
    MemoryVector memoriaProcessosUsuario;
    void alocateTempoRealMemory(int size);
    void alocateUserMemory(int size);
    bool alocarProcessoTempoReal(Processo process);
    bool alocarProcessoUsuario(Processo process);
};