#include "DispositivoIO.hpp"

DispositivoIO::DispositivoIO(type deviceType){
    this->deviceType = deviceType;
    this->pidOwner = pidOwner;
    this->isFree = true;
}

void DispositivoIO::setDeviceFree(){
    this->pidOwner = -1;
    this->isFree = true;
}

void DispositivoIO::alocateDevice(int pid){
    this->pidOwner = pid;
    this->isFree = false;
}

