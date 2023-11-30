#include <bits/stdc++.h>
using namespace std;
#include "util.hpp"

//Terminal Colors https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal


std::vector<std::string> splitString(std::string str, char splitter)
{
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == splitter)
        {
            if (current != "")
            {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.size() != 0)
        result.push_back(current);
    return result;
}

string memoryToString(vector<pair<int, bool>> memory)
{
    string returnString = "";
    for (size_t i = 0; i < memory.size(); i++)
    {
        returnString.append(memory[i].second ? "1" : "0");
    }
    return returnString;
}

vector<string> splitMemoryString(string memory)
{
    vector<string> returnVector;
    int lastStringStart = 0;
    char lastCharacter = 'a';
    int currentSubstringSize = 0;
    for (size_t i = 0; i < memory.size(); i++)
    {
        if (memory[i] == '1')
        {
            if (lastCharacter == '1')
            {
                currentSubstringSize++;
                if (i == memory.size() - 1)
                {
                    returnVector.push_back(memory.substr(lastStringStart, currentSubstringSize));
                }
            }
            else if (lastCharacter == '0')
            {
                string lastSubstring = memory.substr(lastStringStart, currentSubstringSize);
                returnVector.push_back(lastSubstring);

                lastStringStart = i;
                currentSubstringSize = 1;
            }
            else
            {
                // first character
                // First character
                lastStringStart = i;
                currentSubstringSize = 1;
            }
        }
        if (memory[i] == '0')
        {
            if (lastCharacter == '0')
            {
                currentSubstringSize++;
                if (i == memory.size() - 1)
                {
                    returnVector.push_back(memory.substr(lastStringStart, currentSubstringSize));
                }
            }
            else if (lastCharacter == '1')
            {
                string lastSubstring = memory.substr(lastStringStart, currentSubstringSize);
                returnVector.push_back(lastSubstring);

                lastStringStart = i;
                currentSubstringSize = 1;
            }
            else
            {
                // First character
                lastStringStart = i;
                currentSubstringSize = 1;
            }
        }
        lastCharacter = memory[i];
    }

    return returnVector;
}

