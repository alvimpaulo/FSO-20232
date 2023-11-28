#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "Processo.hpp"
#include "ProcessoManager.hpp"
#include "util.hpp"

bool sortProcessos(Processo* a, Processo* b)
{
    return a->startTime < b->startTime;
}

int main()
{
    unsigned long long cpuTime = 0;
    unsigned long long lastStartedProcessID = 0;

    auto processManager = ProcessoManager();

    std::ifstream processesFile;
    processesFile.open("processes.txt");
    std::string processInfo;
    long long lineCount = 1;

    deque<Processo*> processosParaAlocar;

    while (getline(processesFile, processInfo))
    {
        lineCount++;
        auto splitedInfo = splitString(processInfo, ',');
        auto newProcess = new Processo(++lastStartedProcessID, stoi(splitedInfo[0]), stoi(splitedInfo[2]), stoi(splitedInfo[1]), stoi(splitedInfo[3]), stoi(splitedInfo[4]), stoi(splitedInfo[5]), stoi(splitedInfo[6]), stoi(splitedInfo[7]));
        processosParaAlocar.push_back(newProcess);
    }

    sort(processosParaAlocar.begin(), processosParaAlocar.end(), sortProcessos);

    while (processosParaAlocar.empty() == false || processManager.getProcessosAlocados().size() > 0)
    {
        std::deque<Processo*> processosStartadosAgora;
        while (!processosParaAlocar.empty() && processosParaAlocar.front()->startTime <= cpuTime)
        {
            processosStartadosAgora.push_back(processosParaAlocar.front());
            processosParaAlocar.pop_front();
        }
        for (size_t i = 0; i < processosStartadosAgora.size(); i++)
        {
            auto newProcess = processosStartadosAgora.front();
            processosStartadosAgora.pop_front();

            if (newProcess->priority == 0)
            {
                auto resultAlocation = (processManager.alocarMemoriaProcessoTempoReal(newProcess));

                if (resultAlocation == false)
                {
                    cout << "Não consegui alocar o processo de tempo real de id: " << newProcess->id << " porque não havia espaço na memoria de tempo-real" << endl;
                }
                else
                {
                    cout << "Startei o processo de tempo real de id: " << newProcess->id << " no tempo: " << cpuTime << endl;
                    processManager.filaProcesosTempoRealAlocados.push_back(newProcess);
                }
            }
            else
            {
                auto resultAlocation = processManager.alocarMemoriaProcessoUsuario(newProcess);

                if (resultAlocation == false)
                {

                    cout << "Não consegui alocar o processo de id: " << newProcess->id << " porque não havia espaço na memoria de usuario" << endl;
                }
                else
                {
                    cout << "Startei o processo de usuário de id: " << newProcess->id << " no tempo: " << cpuTime << endl;
                }
            }
        }

        processManager.run(cpuTime);
        cpuTime++;
    }

    return 0;
}