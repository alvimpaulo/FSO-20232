#include "MemoryVector.hpp"

MemoryVector::MemoryVector(int size)
{
    this->size = size;

    this->spaces = {MemorySpace(-1, size, false)};
}

void MemoryVector::splitMemory(int index, MemorySpace mem1, MemorySpace mem2)
{
    this->spaces.insert(spaces.begin() + index + 1, mem1);
    this->spaces.insert(spaces.begin() + index + 2, mem2);

    this->spaces.erase(spaces.begin() + index);
}