#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <fstream>

/*LIST OF TODO*/
/* encript Affine */
/* decript Affine */
/* force decript Affine */

/* Global runtime variables */

#define ALPHABET_LENGTH               26
#define TEXT_MAX_LENGTH               100

#define MODE_ENCRYPT                  0
#define MODE_DECRYPT                  1
#define MODE_FORCE                    2
#define MODE_DEFAULT                  MODE_DECRYPT

bool isUpper(char l)
{
    return (l >= 'A' && l <= 'Z');
}

bool isLower(char l)
{
    return (l >= 'a' && l <= 'z');
}

bool isLetter(char l)
{
    return ((l >= 'a' && l <= 'z') ||
            (l >= 'A' && l <= 'Z'));
}

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

char itol(int i)
{
    return (char)(i + 'a');
}

void parseinput(int argc, char **argv, int *mode, char *key) {
    int opt;

    while((opt = getopt(argc,argv, "defk")) != -1) {
        switch (opt)
        {
            case 'k':
                memcpy(key, optarg, ALPHABET_LENGTH*sizeof(char)); break;
            case 'd':
                *mode = MODE_DECRYPT; break;
            case 'e':
                *mode = MODE_ENCRYPT; break;
            case 'f':
                *mode = MODE_FORCE; break;
        }
    }
}

void invert_key(char *key)
{
    int key_length;
    char *key_copy;
    int i;

    key_length = strlen(key);
    key_copy = (char*)malloc(key_length * sizeof(*key));
    memcpy(key_copy, key, key_length * sizeof(*key));

    for(i = 0; i < key_length; i++)
    {
        key[ltoi(key_copy[i])] = itol(i);
    }
    free(key_copy);
}

int* letter_frequency(char *text)
{
    int *freq;
    freq = (int*)malloc(ALPHABET_LENGTH * sizeof(int));

    return freq;
}

void substitution_encrypt(const char *text, char *cipher, char *key) {
    int i;
    char c;

    i = 0;
    while((c = text[i]) != '\0') //TODO
    {
        if(isLetter(c))
            cipher[i] = key[ltoi(c)];
        else
            cipher[i] = c;
        i++;
    }
    cipher[i] = '\0';
}

int substitution_decrypt(const char *cipher, char *text, char *key) {
    int i;
    char c;

    invert_key(key);
    i = 0;
    while((c = cipher[i]) != '\0') //TODO
    {
        if(isLetter(c))
            text[i] = key[ltoi(c)];
        else
            text[i] = c;
        i++;
    }
    text[i] = '\0';
    return 0;
}

void substitution_Force_HillClimb(const char *cipher, char *text) {
}

//TODO use realloc with shorter max size
int fileIn(char * fileName, char ** input, char ** output) {
    std::ifstream iFile(*input);
    iFile.open(fileName, std::ifstream::in);
    if(!iFile.is_open())
        return -1;

    *input = (char*)malloc(TEXT_MAX_LENGTH);
    *output = (char*)malloc(TEXT_MAX_LENGTH);

    iFile.getline(*input, TEXT_MAX_LENGTH);

    iFile.close();
    return 0;
}

int main(int argc, char **argv) {

    char *input = NULL;
    char *output = NULL;
    char *fileName;

    int mode = MODE_DEFAULT;

    char key[ALPHABET_LENGTH + 1];
    char text[TEXT_MAX_LENGTH];
    char cipher[TEXT_MAX_LENGTH];

    parseinput(argc, argv, &mode, key);
    if(argc - optind == 0)
    {
        printf("No file provided\n");
        return 1;
    }
    fileName = argv[optind];
    fileIn(fileName, &input, &output);
    switch(mode)
    {
        case MODE_ENCRYPT:
            substitution_encrypt(input, output, key);
            printf("%s\n", output);
            break;
        case MODE_DECRYPT:
            substitution_decrypt(input, output, key);
            printf("%s\n", output);
            break;
        case MODE_FORCE:
            //affine_Force(input, output, a, b);
            break;
    }


    return 0;
}

