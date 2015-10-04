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

#define BASE64_A_DEFAULT              1
#define BASE64_B_DEFAULT              0
#define BASE64_M_DEFAULT              ALPHABET_LENGTH
#define BASE64_MODE_DEFAULT           MODE_DECRYPT

void parseinput(int argc, char **argv, int *mode, int *a, int *b) {
    int opt;

    while((opt = getopt(argc,argv, "defa:b:")) != -1) {
        switch (opt)
        {
            case 'd':
                *mode = MODE_DECRYPT; break;
            case 'e':
                *mode = MODE_ENCRYPT; break;
            case 'f':
                *mode = MODE_FORCE; break;
            case 'a':
                *a = atoi(optarg); break;
            case 'b':
                *b = atoi(optarg); break;
        }
    }
}

//TODO investigate a better algorithm (Edit: Not worth the effort)
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

void affine_Encrypt(const char *text, char *cipher, int a, int b) {
    int i;
    char c;

    i = 0;
    while((c = cipher[i]) != '\0')
    {
        if(c >= 'A' && c <= 'Z')
            cipher[i] = (((a * (c - 'A')) + b) % ALPHABET_LENGTH) + 'A';
        else if(c >= 'a' && c <= 'z')
            cipher[i] = (((a * (c - 'a')) + b) % ALPHABET_LENGTH) + 'a';
        else
            cipher[i] = c;
        i++;
    }
    cipher[i] = '\0';
}

int affine_Decrypt(const char *cipher, char *text, int a, int b) {
    int i;
    char c;

    a = modinv(a, ALPHABET_LENGTH);
    if(a == -1)
        return 1;

    i = 0;
    while((c = cipher[i]) != '\0')
    {
        if(c >= 'A' && c <= 'Z')
            text[i] = ((((c - 'A') - b + ALPHABET_LENGTH) * a) % ALPHABET_LENGTH) + 'A';
        else if(c >= 'a' && c <= 'z')
            text[i] = ((((c - 'a') - b + ALPHABET_LENGTH) * a) % ALPHABET_LENGTH) + 'a';
        else
            text[i] = c;
        i++;
    }
    text[i] = '\0';
    return 0;
}

void affine_Force(const char *cipher, char *text, int max_a, int max_b) {
    int b;
    int a;

    for(int b = 1; b <= max_b; b++)
    {
        for(int a = 1; a <= max_a; a++)
        {
            if(affine_Decrypt(cipher, text, a, b) == 0)
                printf("a=%d,b=%d:%s\n", a,b,text);
        }
    }
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

    int a = AFFINE_A_DEFAULT;
    int b = AFFINE_B_DEFAULT;
    int mode = AFFINE_MODE_DEFAULT;

    parseinput(argc, argv, &mode, &a, &b);
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
            affine_Encrypt(input, output, a, b);
            printf("%s\n", output);
            break;
        case MODE_DECRYPT:
            affine_Decrypt(input, output, a, b);
            printf("%s\n", output);
            break;
        case MODE_FORCE:
            affine_Force(input, output, a, b);
            break;
    }


    return 0;
}

