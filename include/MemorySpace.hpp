#pragma once

class MemorySpace
{
public:
    MemorySpace(int pidOwner = -1, int space = 0, bool isOccupied = false, int offset = -1);
    int pidOwner;
    int space;
    bool isOccupied;
    int offset;
};