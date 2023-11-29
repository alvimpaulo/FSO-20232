#include "MemorySpace.hpp"

MemorySpace::MemorySpace(int pidOwner, int space, bool isOccupied, int offset)
{
    this->pidOwner = pidOwner;
    this->space = space;
    this->isOccupied = isOccupied;
    this->offset = offset;
}