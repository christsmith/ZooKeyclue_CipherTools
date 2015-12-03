#include <fstream>
#include "cipherTools.h"

/*
int ltoi(char l)
{
    int d;

    if(isUpper(l))
        d = (int)(l - 'A');
    else if(isLower(l))
        d = (int)(l - 'a');
    else
        d = (int)l;
    return d;
}

bool isUpper(char l)
{
    return ('A' <= l <= 'Z');
}

bool isLower(char l)
{
    return ('a' <= l <= 'z');
}
*/

//TODO use realloc with shorter max size
int fileIn(char * fileName, char * input)
{
    std::ifstream iFile(input);
    iFile.open(fileName, std::ifstream::in);
    if(!iFile.is_open())
        return -1;

    iFile.getline(input, TEXT_MAX_LENGTH);

    iFile.close();
    return 0;
}

