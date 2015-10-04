
#if defined (CIPHER_TOOLS_H)
#define CIPHER_TOOLS_H


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

#endif // CIPHER_TOOLS_H

