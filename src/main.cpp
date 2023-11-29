#include <bits/stdc++.h>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "Processo.hpp"
#include "ProcessoManager.hpp"
#include "util.hpp"
#include "FileManager.hpp"

bool sortProcessos(Processo *a, Processo *b)
{
    return a->startTime < b->startTime;
}

int main(int argc, char *argv[])
{

    // Terminal colors
    Color::Modifier termRed(Color::FG_RED);
    Color::Modifier termGreen(Color::FG_GREEN);
    Color::Modifier termBlue(Color::FG_BLUE);
    Color::Modifier termCyan(Color::FG_CYAN);
    Color::Modifier termLightYellow(Color::FG_LIGHT_YELLOW);
    Color::Modifier termReset(Color::FG_DEFAULT);
    Color::Modifier termBold(Color::FG_BOLD);
    Color::Modifier termUnderline(Color::FG_UNDERLINE);

    unsigned long long cpuTime = 0;
    unsigned long long lastStartedProcessID = 0;

    auto processManager = ProcessoManager();

    std::ifstream processesFile;
    if (argc == 1)
    {
        processesFile.open("processes.txt");
    }
    std::string processInfo;
    long long lineCount = 1;

    deque<Processo *> processosParaAlocar;

    while (getline(processesFile, processInfo))
    {
        lineCount++;
        auto splitedInfo = splitString(processInfo, ',');
        auto newProcess = new Processo(++lastStartedProcessID, stoi(splitedInfo[0]), stoi(splitedInfo[2]), stoi(splitedInfo[1]), stoi(splitedInfo[3]), stoi(splitedInfo[4]), stoi(splitedInfo[5]), stoi(splitedInfo[6]), stoi(splitedInfo[7]), stoi(splitedInfo[1]) - 1);
        processosParaAlocar.push_back(newProcess);
    }

    sort(processosParaAlocar.begin(), processosParaAlocar.end(), sortProcessos);

    while (processosParaAlocar.empty() == false || processManager.getProcessosAlocados().size() > 0)
    {
        cout << termGreen << termBold << "-------------- Ciclo de CPU ----------------- Tempo: " << cpuTime << " -------------------" << termReset << endl;

        std::deque<Processo *> processosStartadosAgora;
        while (!processosParaAlocar.empty() && processosParaAlocar.front()->startTime <= cpuTime)
        {
            processosStartadosAgora.push_back(processosParaAlocar.front());
            processosParaAlocar.pop_front();
        }
        while (processosStartadosAgora.empty() == false)
        {
            auto newProcess = processosStartadosAgora.front();
            processosStartadosAgora.pop_front();

            if (newProcess->priority == 0)
            {
                auto resultAlocation = (processManager.alocarMemoriaProcessoTempoReal(newProcess));

                if (resultAlocation == false)
                {
                    cout << termRed << "Não consegui alocar o processo de tempo real de id: " << newProcess->id << " porque não havia espaço na memoria de tempo-real" << termReset << endl;
                    processosParaAlocar.push_back(newProcess);
                }
                else
                {
                    cout << termLightYellow << termBold << termUnderline << "Aloquei memoria para o processo de tempo real de id: " << newProcess->id << " no tempo: " << cpuTime << termReset << endl;
                    newProcess->cpuTimeCurrentList = cpuTime;
                    cout << termLightYellow << "PID: " << newProcess->id << endl
                         << "Prioridade: " << newProcess->priority << endl
                         << "Offset de memoria: " << newProcess->memorySpace->offset << endl
                         << "Quantidade de blocos alocados: " << newProcess->memory << endl
                         << "Utilizacao de impressora: " << newProcess->printer << endl
                         << "Utilizacao de scanner: " << newProcess->scanner << endl
                         << "Utilizacao de modem: " << newProcess->modem << endl
                         << "Utilizacao de sata: " << newProcess->sata << endl
                         << termReset << endl;
                    processManager.filaProcesosTempoRealAlocados.push_back(newProcess);
                }
            }
            else
            {
                auto resultAlocation = processManager.alocarMemoriaProcessoUsuario(newProcess);

                if (resultAlocation == false)
                {

                    cout << termRed << "Não consegui alocar o processo de id: " << newProcess->id << " porque não havia espaço na memoria de usuario" << termReset << endl;
                    processosParaAlocar.push_back(newProcess);
                }
                else
                {
                    cout << termLightYellow << termBold << termUnderline << "Aloquei memoria para o processo de usuário de id: " << newProcess->id << " no tempo: " << cpuTime << "" << termReset << endl;
                    newProcess->cpuTimeCurrentList = cpuTime;

                    cout << termLightYellow << "PID: " << newProcess->id << endl
                         << "Prioridade: " << newProcess->priority << endl
                         << "Offset de memoria: " << newProcess->memorySpace->offset << endl
                         << "Quantidade de blocos alocados: " << newProcess->memory << endl
                         << "Utilizacao de impressora: " << newProcess->printer << endl
                         << "Utilizacao de scanner: " << newProcess->scanner << endl
                         << "Utilizacao de modem: " << newProcess->modem << endl
                         << "Utilizacao de sata: " << newProcess->sata << endl
                         << termReset << endl;
                    switch (newProcess->priority)
                    {
                    case 1:
                        processManager.filasProcessosUsuarioAlocados[0].push_back(newProcess);
                        break;
                    case 2:
                        processManager.filasProcessosUsuarioAlocados[1].push_back(newProcess);
                        break;
                    case 3:
                        processManager.filasProcessosUsuarioAlocados[2].push_back(newProcess);

                        break;

                    default:
                        break;
                    }
                }
            }
        }

        processManager.run(cpuTime);
        cpuTime++;
    }

    FileManager::GetInstance().PrintStorage();
    FileManager::GetInstance().PrintFAT();

    return 0;
}