#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "MemorySpace.hpp"

class MemoryVector
{
public:
    MemoryVector(int size);
    std::vector<MemorySpace *> spaces;
    int size;

    void splitMemory(int index, MemorySpace *mem1, MemorySpace *mem2);
    void joinMemory(int index, MemorySpace *mem1, MemorySpace *mem2);
};
