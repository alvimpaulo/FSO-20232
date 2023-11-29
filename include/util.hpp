#pragma once
#include <bits/stdc++.h>
using namespace std;

std::vector<std::string> splitString(std::string str, char splitter);

string memoryToString(vector<pair<int, bool>> memory);
vector<string> splitMemoryString(string memory);

namespace Color
{

    enum BackgroundCode
    {
        BG_DEFAULT = -1,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_LIGHT_RED = 101
    };

    enum ForegroundCode
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

        FG_DARK_GRAY = 90,
        FG_LIGHT_RED = 91,
        FG_LIGHT_GREEN = 92,
        FG_LIGHT_YELLOW = 93,
        FG_LIGHT_BLUE = 94,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_CYAN = 96,
        FG_WHITE = 97,

    };
    class Modifier
    {
        ForegroundCode fgCode;
        BackgroundCode bgCode;

    public:
        Modifier(ForegroundCode pFgCode, BackgroundCode pBgCode = BackgroundCode::BG_DEFAULT) : fgCode(pFgCode), bgCode(pBgCode) {}
        friend std::ostream &
        operator<<(std::ostream &os, const Modifier &mod)
        {
            if (mod.bgCode != BG_DEFAULT)
            {
                 return os << "\033[" << mod.fgCode << ";" << mod.bgCode << "m";
            }
            else
            {
                return os << "\033[" << mod.fgCode << "m";
            }
        }
    };
}
 