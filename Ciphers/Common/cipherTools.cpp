#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include "cipherTools.h"

char value_to_ascii(int v, letter_case_t letter_case)
{
    char c;
    switch (letter_case)
    {
        case LETTER_CASE_UPPER:
            c = (char)(v + 'A');
            break;
        case LETTER_CASE_LOWER:
            c = (char)(v + 'a');
            break;
        case LETTER_CASE_SPECIAL:
            c = (char)v;
            break;
        default:
            c = (char)v;
            break;
    }
    return c;
}

int ascii_to_value(char c, letter_case_t &letter_case)
{
    int v;
    if(isUpper(c))
    {
        letter_case = LETTER_CASE_UPPER;
        v = (int)(c - 'A');
    }
    else if(isLower(c))
    {
        letter_case = LETTER_CASE_LOWER;
        v = (int)(c - 'a');
    }
    else
    {
        letter_case = LETTER_CASE_SPECIAL;
        v = (int)c;
    }
    return v;
}

int ascii_to_value(char c)
{
    int v;
    if(isUpper(c))
    {
        v = (int)(c - 'A');
    }
    else if(isLower(c))
    {
        v = (int)(c - 'a');
    }
    else
    {
        v = (int)c;
    }
    return v;
}

bool isUpper(char l)
{
    return (l >= 'A' && l <= 'Z');
}

bool isLower(char l)
{
    return (l >= 'a' && l <= 'z');
}

int fileIn(const char * fileName, std::string &input)
{
    std::ifstream iFile(fileName);
    std::stringstream buffer;

    if(!iFile.is_open())
        return 1;

    buffer << iFile.rdbuf();
    input = buffer.str();

    iFile.close();
    return 0;
}

