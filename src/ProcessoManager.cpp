
#include "ProcessoManager.hpp"

ProcessoManager ::ProcessoManager(/* args */) : memoriaProcessosTempoReal(64), memoriaProcessosUsuario(960)
{
    this->filaProcesosTempoRealAlocados = {};
    this->filasProcessosUsuarioAlocados = {{}, {}, {}};
}

bool ProcessoManager::alocarMemoriaProcessoTempoReal(Processo process)
{
    vector<pair<MemorySpace, int>> freeSpaces;

    for (size_t i = 0; i < memoriaProcessosTempoReal.spaces.size(); i++)
    {
        if (memoriaProcessosTempoReal.spaces[i].isOccupied == false)
        {
            freeSpaces.push_back({memoriaProcessosTempoReal.spaces[i], i});
        }
    }

    bool _HasSpace = false;
    for (size_t i = 0; i < freeSpaces.size(); i++)
    {
        if (freeSpaces[i].first.space >= process.memory)
        {
            auto mem1 = MemorySpace(process.id, process.memory, true);
            auto mem2 = MemorySpace(-1, freeSpaces[i].first.space - process.memory, false);
            this->memoriaProcessosTempoReal.splitMemory(freeSpaces[i].second, mem1, mem2);
            _HasSpace = true;
            break;
        }
    }

    return _HasSpace;
}

bool ProcessoManager::alocarMemoriaProcessoUsuario(Processo process)
{

    vector<pair<MemorySpace, int>> freeSpaces;

    for (size_t i = 0; i < memoriaProcessosUsuario.spaces.size(); i++)
    {
        if (memoriaProcessosUsuario.spaces[i].isOccupied == false)
        {
            freeSpaces.push_back({memoriaProcessosUsuario.spaces[i], i});
        }
    }

    bool _HasSpace = false;
    for (size_t i = 0; i < freeSpaces.size(); i++)
    {
        if (freeSpaces[i].first.space >= process.memory)
        {
            auto mem1 = MemorySpace(process.id, process.memory, true);
            auto mem2 = MemorySpace(-1, freeSpaces[i].first.space - process.memory, false);
            this->memoriaProcessosUsuario.splitMemory(freeSpaces[i].second, mem1, mem2);
            _HasSpace = true;
            break;
        }
    }

    return _HasSpace;
}

void ProcessoManager::run(int cpuTime)
{
    cout << "-------------- Ciclo de CPU ----------------- Tempo: " << cpuTime << " -------------------" << endl;

    if (filaProcesosTempoRealAlocados.size() > 0)
    {
        auto currentProcess = filaProcesosTempoRealAlocados.front().run(cpuTime);
        if (currentProcess->hasDied())
        {
            cout << "Processo Id: " << currentProcess->id << " morreu" << endl;
            filaProcesosTempoRealAlocados.pop_front();
            auto memorySpaces = &memoriaProcessosTempoReal.spaces;

            auto processMemorySpace = find_if(memorySpaces->begin(), memorySpaces->end(), [currentProcess](MemorySpace memory)
                                              { return memory.pidOwner == currentProcess->id; });

            if (processMemorySpace != memorySpaces->end())
            {
                auto currentIndex = processMemorySpace - memorySpaces->begin();
                if (currentIndex <= memorySpaces->size() - 1)
                {
                    auto nextSpaceIt = memorySpaces->begin() + currentIndex + 1;

                    if (nextSpaceIt != memorySpaces->end() && nextSpaceIt->isOccupied == false)
                    {
                        memoriaProcessosTempoReal.joinMemory(processMemorySpace - memorySpaces->begin(), *processMemorySpace, *nextSpaceIt);
                    }
                }

                if (currentIndex >= 1)
                {
                    auto prevSpaceIt = memorySpaces->begin() + currentIndex - 1;

                    if (prevSpaceIt != memorySpaces->begin() && prevSpaceIt->isOccupied == false)
                    {
                        memoriaProcessosTempoReal.joinMemory(processMemorySpace - memorySpaces->begin() - 1, *processMemorySpace, *prevSpaceIt);
                    }
                }
            }
        }
    }
    else
    {
        if (filasProcessosUsuarioAlocados[0].size() > 0)
        {
            auto currentProcess = filasProcessosUsuarioAlocados[0].front().run(cpuTime);
        }
        else if (filasProcessosUsuarioAlocados[1].size() > 0)
        {
            auto currentProcess = filasProcessosUsuarioAlocados[1].front().run(cpuTime);
        }
        else if (filasProcessosUsuarioAlocados[2].size() > 0)
        {
            auto currentProcess = filasProcessosUsuarioAlocados[2].front().run(cpuTime);
        }
    }

    // Process Aging


    //End of run
    cout << endl;
    // cout << "-------------- Fim do Ciclo de CPU ----------- Tempo: " << cpuTime << " --------------------" << endl;
}

vector<Processo> ProcessoManager::getProcessosAlocados()
{
    vector<Processo> returnVector;

    for (size_t i = 0; i < filaProcesosTempoRealAlocados.size(); i++)
    {
        returnVector.push_back(filaProcesosTempoRealAlocados[i]);
    }

    for (size_t i = 0; i < filasProcessosUsuarioAlocados.size(); i++)
    {
        for (size_t j = 0; j < filasProcessosUsuarioAlocados[i].size(); j++)
        {
            returnVector.push_back(filasProcessosUsuarioAlocados[i][j]);
        }
    }
    return returnVector;
}