#include "MemorySpace.hpp"

MemorySpace::MemorySpace(int pidOwner, int space, bool isOccupied)
{
    this->pidOwner = pidOwner;
    this->space = space;
    this->isOccupied = isOccupied;
}