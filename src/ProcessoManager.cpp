
#include "ProcessoManager.hpp"

ProcessoManager ::ProcessoManager(/* args */) : memoriaProcessosTempoReal(64), memoriaProcessosUsuario(960)
{
}

void ProcessoManager::alocateTempoRealMemory(int size)
{
    int currentSize = size;
    int memoryIndex = 0;
}

void ProcessoManager::alocateUserMemory(int size)
{
    int currentSize = size;
    int memoryIndex = 0;
}

bool ProcessoManager::alocarProcessoTempoReal(Processo process)
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

bool ProcessoManager::alocarProcessoUsuario(Processo process)
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