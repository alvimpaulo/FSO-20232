#pragma once
#include <bits/stdc++.h>
using namespace std;

std::vector<std::string> splitString(std::string str, char splitter);

string memoryToString(vector<pair<int, bool>> memory);
vector<string> splitMemoryString(string memory);

namespace Color
{

    enum Code
    {
        FG_BOLD = 1,
        FG_UNDERLINE = 4,
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_LIGHT_GRAY = 37,
        FG_DEFAULT = 0,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49,
        FG_DARK_GRAY = 90,
        FG_LIGHT_RED = 91,
        FG_LIGHT_GREEN = 92,
        FG_LIGHT_YELLOW = 93,
        FG_LIGHT_BLUE = 94,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_CYAN = 96,
        FG_WHITE = 97,
        BG_LIGHT_RED = 101
    };
    class Modifier
    {
        Code code;

    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream &
        operator<<(std::ostream &os, const Modifier &mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
}



