#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fstream>
#include <string>

#include "cipherTools.h"
#include "affine.h"

int modinv(int a, int m);

int modinv(int a, int m)
{
    int i;
    for(i = 0; i < m; i++)
    {
        if((i * a) % m == 1)
            break;
    }
    if(i == m)
        return -1;
    else
        return i;
}

int affine_Encrypt(const std::string &text, std::string &cipher, int a, int b)
{
    char c;

    cipher.resize(text.size());

    for(int i  = 0; i < text.size(); i++)
    {
        c = text[i];
        if(isUpper(c))
            cipher[i] = (((a * (c - 'A')) + b) % ALPHABET_LENGTH) + 'A';
        else if(isLower(c))
            cipher[i] = (((a * (c - 'a')) + b) % ALPHABET_LENGTH) + 'a';
        else
            cipher[i] = c;
    }
    return 0;
}

int affine_Decrypt(const std::string &cipher, std::string &text, int a, int b)
{
    char c;

    text.resize(cipher.size());

    a = modinv(a, ALPHABET_LENGTH);
    if(a == -1)
        return 1;

    for(int i  = 0; i < cipher.size(); i++)
    {
        c = cipher[i];
        if(isUpper(c))
            text[i] = ((((c - 'A') - b + ALPHABET_LENGTH) * a) % ALPHABET_LENGTH) + 'A';
        else if(isLower(c))
            text[i] = ((((c - 'a') - b + ALPHABET_LENGTH) * a) % ALPHABET_LENGTH) + 'a';
        else
            text[i] = c;
    }
    return 0;
}

//Speed is important and real time feedback is important in this case. Print as soon as results are made available!
int affine_Force_Brute(const std::string &cipher, int max_a, int max_b)
{
    std::string text;

    text.resize(cipher.size());

    for(int b = 0; b <= max_b; b++)
    {
        for(int a = 1; a <= max_a; a++)
        {
            if(affine_Decrypt(cipher, text, a, b) == 0)
                std::cout << "a=" << a << ", "
                          << "b=" << b << ","
                          << std::endl << text << std::endl;
        }
    }
    return 0;
}

