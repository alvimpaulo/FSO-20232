#pragma once
#include <bits/stdc++.h>

class DispositivoIO
{
private:
    /* data */
public:
    
    enum type{
      Scanner,
      Impressora,
      Modem,
      SATA  
    };
    DispositivoIO(type deviceType);

    int pidOwner;
    type deviceType;
    bool isFree;

    void setDeviceFree();
    void alocateDevice(int pid);
};
    
    

