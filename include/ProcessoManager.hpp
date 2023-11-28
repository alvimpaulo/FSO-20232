#include "Processo.hpp"
#include <bits/stdc++.h>

using namespace std;

class ProcessoManager
{
private:
    /* data */
public:
    ProcessoManager(/* args */);
    vector<Processo> procesosTempoRealAlocados;
    vector<vector<Processo>> filasProcessosUsuarioAlocados;
    vector<bool> memoriaProcessosTempoReal;
    vector<bool> memoriaProcessosUsuario;
};