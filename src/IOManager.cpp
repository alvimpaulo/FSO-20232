#include "IOManager.hpp"
#include "DispositivoIO.hpp"

IOManager::IOManager()
{
    scanner = {new DispositivoIO(DispositivoIO::Scanner)};

    impressoras = {new DispositivoIO(DispositivoIO::Impressora), new DispositivoIO(DispositivoIO::Impressora)};

    modem = {new DispositivoIO(DispositivoIO::Modem)};

    satas = {new DispositivoIO(DispositivoIO::SATA), new DispositivoIO(DispositivoIO::SATA)};
}

bool IOManager::alocateNewScanner(int pid)
{
    if (scanner.front()->isFree == true)
    {
        scanner.front()->alocateDevice(pid);
        return true;
    }

    else
    {
        return false;
    }
}
bool IOManager::alocateNewImpressora(int pid, int id)
{
    if (impressoras[id]->isFree == true)
    {
        impressoras[id]->alocateDevice(pid);
        return true;
    }

    else
    {
        return false;
    }
}
bool IOManager::alocateNewModem(int pid)
{
    if (modem.front()->isFree == true)
    {
        modem.front()->alocateDevice(pid);
        return true;
    }

    else
    {
        return false;
    }
}
bool IOManager::alocateNewSATA(int pid, int id)
{
    if (satas[id]->isFree == true)
    {
        satas[id]->alocateDevice(pid);
        return true;
    }

    else
    {
        return false;
    }
}

DispositivoIO *IOManager::getScanner(int pid)
{
    if (pid == scanner.front()->pidOwner)
    {
        return scanner.front();
    }
    else
    {
        return nullptr;
    }
}
DispositivoIO *IOManager::getImpressora(int pid, int id)
{
    if (pid == impressoras[id]->pidOwner)
    {
        return impressoras[id];
    }
    else
    {
        return nullptr;
    }
}
DispositivoIO *IOManager::getModem(int pid)
{
    if (pid == modem.front()->pidOwner)
    {
        return modem.front();
    }
    else
    {
        return nullptr;
    }
}
DispositivoIO *IOManager::getSata(int pid, int id)
{
    if (pid == satas[id]->pidOwner)
    {
        return satas[id];
    }
    else
    {
        return nullptr;
    }
}

bool IOManager::isScannerFree()
{
    return scanner.front()->isFree;
}
bool IOManager::isImpressoraFree(int id)
{
    return impressoras[id]->isFree;
}
bool IOManager::isModemFree() { return modem.front()->isFree; }
bool IOManager::isSataFree(int id)
{
    return satas[id]->isFree;
}

void IOManager::freeScanner()
{
    this->scanner.front()->isFree = true;
    this->scanner.front()->pidOwner = -1;
}
void IOManager::freePrinter(int id)
{
    this->impressoras[id - 1]->isFree = true;
    this->impressoras[id - 1]->pidOwner = -1;
}
void IOManager::freeModem()
{
    this->modem.front()->isFree = true;
    this->modem.front()->pidOwner = -1;
}
void IOManager::freeSATA(int id)
{
    this->satas[id - 1]->isFree = true;
    this->satas[id - 1]->pidOwner = -1;
}

bool IOManager::isProcessGoodToRun(Processo *process)
{
    // Checando se ele pode rodar por causa de I/O
    bool isScannerOk = false;
    bool isImpressoraOk = false;
    bool isModemOk = false;
    bool isSataOk = false;

    if (process->scanner > 0)
    {
        if (this->isScannerFree() || this->getScanner(process->id))
        {
            isScannerOk = true;
        }
        else
        {
            isScannerOk = false;
        }
    }
    else
    {
        isScannerOk = true;
    }

    if (process->modem > 0)
    {
        if (this->isModemFree() || this->getModem(process->id))
        {
            isModemOk = true;
        }
        else
        {
            isModemOk = false;
        }
    }
    else
    {
        isModemOk = true;
    }

    if (process->printer > 0)
    {
        if (this->isImpressoraFree(process->printer - 1) || this->getImpressora(process->id, process->printer - 1))
        {
            isImpressoraOk = true;
        }
        else
        {
            isImpressoraOk = false;
        }
    }
    else
    {
        isImpressoraOk = true;
    }

    if (process->sata > 0)
    {
        if (this->isSataFree(process->sata - 1) || this->getSata(process->id, process->sata - 1))
        {
            isSataOk = true;
        }
        else
        {
            isSataOk = false;
        }
    }
    else
    {
        isSataOk = true;
    }
    if (isScannerOk && isImpressoraOk && isModemOk && isSataOk)
    {
        if (process->scanner > 0)
            this->alocateNewScanner(process->id);
        if (process->printer > 0)
            this->alocateNewImpressora(process->id, process->printer - 1);
        if (process->modem > 0)
            this->alocateNewModem(process->id);
        if (process->sata > 0)
            this->alocateNewSATA(process->id, process->sata - 1);

        return true;
    }
    return false;
}

void ::IOManager::freeIOFromDeadProcess(Processo *process)
{
    if (process->hasDied())
    {
        if (process->scanner > 0)
        {
            this->freeScanner();
        }
        if (process->modem > 0)
        {
            this->freeModem();
        }

        if (process->printer > 0)
        {
            this->freePrinter(process->printer - 1);
        }

        if (process->sata > 0)
        {
            this->freeSATA(process->sata - 1);
        }
    }
}