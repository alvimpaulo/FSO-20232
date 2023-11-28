#include "MemoryVector.hpp"

MemoryVector::MemoryVector(int size)
{
    this->size = size;

    this->spaces =  {new MemorySpace(-1, size, false)};
}

void MemoryVector::splitMemory(int index, MemorySpace* mem1, MemorySpace* mem2)
{
    this->spaces.insert(spaces.begin() + index + 1, mem1);
    this->spaces.insert(spaces.begin() + index + 2, mem2);

    this->spaces.erase(spaces.begin() + index);
}

void MemoryVector::joinMemory(int index, MemorySpace* mem1, MemorySpace* mem2)
{
    this->spaces.erase(spaces.begin() + index);
    this->spaces.erase(spaces.begin() + index + 1);
    this->spaces.insert(spaces.begin() + index + 1, new MemorySpace(-1, mem1->space + mem2->space, false));
    
}