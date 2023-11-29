
#include "ProcessoManager.hpp"

bool comparatorSJF(Processo *a, Processo *b)
{
    return a->timeLeft < b->timeLeft;
}

ProcessoManager ::ProcessoManager(/* args */) : memoriaProcessosTempoReal(64), memoriaProcessosUsuario(960)
{
    this->filaProcesosTempoRealAlocados = {};
    this->filasProcessosUsuarioAlocados = {{}, {}, {}};
    this->ioManager = new IOManager();
}

bool ProcessoManager::alocarMemoriaProcessoTempoReal(Processo *process)
{
    vector<pair<MemorySpace *, int>> freeSpaces;

    for (size_t i = 0; i < memoriaProcessosTempoReal.spaces.size(); i++)
    {
        if (memoriaProcessosTempoReal.spaces[i]->isOccupied == false)
        {
            freeSpaces.push_back({memoriaProcessosTempoReal.spaces[i], i});
        }
    }

    bool _HasSpace = false;
    for (size_t i = 0; i < freeSpaces.size(); i++)
    {
        if (freeSpaces[i].first->space >= process->memory)
        {
            auto mem1 = new MemorySpace(process->id, process->memory, true, freeSpaces[i].first->offset);
            auto mem2 = new MemorySpace(-1, freeSpaces[i].first->space - process->memory, false, mem1->offset + mem1->space);
            this->memoriaProcessosTempoReal.splitMemory(freeSpaces[i].second, mem1, mem2);
            _HasSpace = true;
            process->memorySpace = mem1;
            break;
        }
    }

    return _HasSpace;
}

bool ProcessoManager::alocarMemoriaProcessoUsuario(Processo *process)
{

    vector<pair<MemorySpace *, int>> freeSpaces;

    for (size_t i = 0; i < memoriaProcessosUsuario.spaces.size(); i++)
    {
        if (memoriaProcessosUsuario.spaces[i]->isOccupied == false)
        {
            freeSpaces.push_back({memoriaProcessosUsuario.spaces[i], i});
        }
    }

    bool _HasSpace = false;
    for (size_t i = 0; i < freeSpaces.size(); i++)
    {
        if (freeSpaces[i].first->space >= process->memory)
        {
            auto mem1 = new MemorySpace(process->id, process->memory, true, freeSpaces[i].first->offset);
            auto mem2 = new MemorySpace(-1, freeSpaces[i].first->space - process->memory, false, mem1->offset + mem1->space);
            this->memoriaProcessosUsuario.splitMemory(freeSpaces[i].second, mem1, mem2);
            _HasSpace = true;
            process->memorySpace = mem1;
            break;
        }
    }

    return _HasSpace;
}

void ProcessoManager::run(int cpuTime)
{
    if (filaProcesosTempoRealAlocados.size() > 0)
    {
        auto currentProcess = filaProcesosTempoRealAlocados.front()->run(cpuTime);
        if (currentProcess->hasDied())
        {
            cout << "Processo de tempo real Id: " << currentProcess->id << " morreu" << endl;
            filaProcesosTempoRealAlocados.pop_front();
            auto memorySpaces = &memoriaProcessosTempoReal.spaces;

            auto processMemorySpace = find_if(memorySpaces->begin(), memorySpaces->end(), [currentProcess](MemorySpace *memory)
                                              { return memory->pidOwner == currentProcess->id; });

            if (processMemorySpace != memorySpaces->end())
            {
                auto currentIndex = processMemorySpace - memorySpaces->begin();
                if (currentIndex <= memorySpaces->size() - 1)
                {
                    auto nextSpaceIt = memorySpaces->begin() + currentIndex + 1;

                    if (nextSpaceIt != memorySpaces->end() && (*nextSpaceIt)->isOccupied == false)
                    {
                        memoriaProcessosTempoReal.joinMemory(processMemorySpace - memorySpaces->begin(), *processMemorySpace, *nextSpaceIt);
                    }
                }

                if (currentIndex >= 1)
                {
                    auto prevSpaceIt = memorySpaces->begin() + currentIndex - 1;

                    if (prevSpaceIt != memorySpaces->begin() && (*prevSpaceIt)->isOccupied == false)
                    {
                        memoriaProcessosTempoReal.joinMemory(processMemorySpace - memorySpaces->begin() - 1, *processMemorySpace, *prevSpaceIt);
                    }
                }
            }
        }
    }
    else
    {
        Processo *currentProcess = nullptr;
        if (filasProcessosUsuarioAlocados[0].size() > 0)
        {
            Processo *shortestProcessWithIOOpen = nullptr;
            sort(filasProcessosUsuarioAlocados[0].begin(), filasProcessosUsuarioAlocados[0].end(), comparatorSJF);

            for (size_t i = 0; i < filasProcessosUsuarioAlocados[0].size(); i++)
            {
                currentProcess = filasProcessosUsuarioAlocados[0][i];

                if (ioManager->isProcessGoodToRun(currentProcess))
                {
                    shortestProcessWithIOOpen = currentProcess;
                    break;
                }
            }
            currentProcess = shortestProcessWithIOOpen->run(cpuTime);
        }
        if (currentProcess == nullptr && filasProcessosUsuarioAlocados[1].size() > 0)
        {
            Processo *shortestProcessWithIOOpen = nullptr;
            sort(filasProcessosUsuarioAlocados[1].begin(), filasProcessosUsuarioAlocados[1].end(), comparatorSJF);

            for (size_t i = 0; i < filasProcessosUsuarioAlocados[1].size(); i++)
            {
                currentProcess = filasProcessosUsuarioAlocados[1][i];

                if (ioManager->isProcessGoodToRun(currentProcess))
                {
                    shortestProcessWithIOOpen = currentProcess;
                    break;
                }
            }
            currentProcess = shortestProcessWithIOOpen->run(cpuTime);
        }
        if (currentProcess == nullptr && filasProcessosUsuarioAlocados[2].size() > 0)
        {
            Processo *shortestProcessWithIOOpen = nullptr;
            sort(filasProcessosUsuarioAlocados[2].begin(), filasProcessosUsuarioAlocados[2].end(), comparatorSJF);

            for (size_t i = 0; i < filasProcessosUsuarioAlocados[2].size(); i++)
            {
                currentProcess = filasProcessosUsuarioAlocados[2][i];

                if (ioManager->isProcessGoodToRun(currentProcess))
                {
                    shortestProcessWithIOOpen = currentProcess;
                    break;
                }
            }
            currentProcess = shortestProcessWithIOOpen->run(cpuTime);
        }

        if (currentProcess && currentProcess->hasDied())
        {
            cout << "Processo de usuario Id: " << currentProcess->id << " morreu" << endl;

            filasProcessosUsuarioAlocados[currentProcess->filaDeExecucao].pop_front();

            // Se o processo morreu, limpar as IO.

            ioManager->freeIOFromDeadProcess(currentProcess);

            auto memorySpaces = &memoriaProcessosUsuario.spaces;

            auto processMemorySpace = find_if(memorySpaces->begin(), memorySpaces->end(), [currentProcess](MemorySpace *memory)
                                              { return memory->pidOwner == currentProcess->id; });

            if (processMemorySpace != memorySpaces->end())
            {
                auto currentIndex = processMemorySpace - memorySpaces->begin();
                if (currentIndex <= memorySpaces->size() - 1)
                {
                    auto nextSpaceIt = memorySpaces->begin() + currentIndex + 1;

                    if (nextSpaceIt != memorySpaces->end() && (*nextSpaceIt)->isOccupied == false)
                    {
                        memoriaProcessosUsuario.joinMemory(processMemorySpace - memorySpaces->begin(), *processMemorySpace, *nextSpaceIt);
                    }
                }

                if (currentIndex >= 1)
                {
                    auto prevSpaceIt = memorySpaces->begin() + currentIndex - 1;

                    if (prevSpaceIt != memorySpaces->begin() && (*prevSpaceIt)->isOccupied == false)
                    {
                        memoriaProcessosUsuario.joinMemory(processMemorySpace - memorySpaces->begin() - 1, *processMemorySpace, *prevSpaceIt);
                    }
                }

                (*processMemorySpace)->isOccupied = false;
                (*processMemorySpace)->pidOwner = -1;
            }
        }
    }
    // Process Aging
    this->ageProcesses(cpuTime);
    // End of run
    cout << endl;
    // cout << "-------------- Fim do Ciclo de CPU ----------- Tempo: " << cpuTime << " --------------------" << endl;
}

vector<Processo *> ProcessoManager::getProcessosAlocados()
{
    vector<Processo *> returnVector;

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

void ProcessoManager::ageProcesses(int cpuTime)
{
    vector<int> toErase; // Vetor para guardar quais processos serao apagados da lista 2

    for (size_t i = 0; i < filasProcessosUsuarioAlocados[1].size(); i++)
    {
        if (cpuTime - filasProcessosUsuarioAlocados[1][i]->cpuTimeCurrentList >= 30)
        {
            toErase.push_back(i);
        }
    }
    for (size_t i = 0; i < toErase.size(); i++)
    {
        auto process = filasProcessosUsuarioAlocados[1][toErase[i] - i];
        process->cpuTimeCurrentList = cpuTime;
        (process->filaDeExecucao)--;
        filasProcessosUsuarioAlocados[1].erase(filasProcessosUsuarioAlocados[1].begin() + toErase[i] - i);
        filasProcessosUsuarioAlocados[0].push_back(process);
    }

    toErase.clear(); // Limpando o vetor para guardar quais serão apagados da lista 3

    for (size_t i = 0; i < filasProcessosUsuarioAlocados[2].size(); i++)
    {
        if (cpuTime - filasProcessosUsuarioAlocados[2][i]->cpuTimeCurrentList >= 20)
        {
            toErase.push_back(i);
        }
    }

    for (size_t i = 0; i < toErase.size(); i++)
    {
        auto process = filasProcessosUsuarioAlocados[2][toErase[i] - i];
        process->cpuTimeCurrentList = cpuTime;
        (process->filaDeExecucao)--;
        filasProcessosUsuarioAlocados[2].erase(filasProcessosUsuarioAlocados[2].begin() + toErase[i] - i);
        filasProcessosUsuarioAlocados[1].push_back(process);
    }

    toErase.clear();
}