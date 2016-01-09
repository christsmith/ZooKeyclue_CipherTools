#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "cipherTools.h"
#include "affine.h"

void parseinput(int argc, char **argv, int *mode, int *a, int *b);

void parseinput(int argc, char **argv, mode_selected_t *mode, int *a, int *b) {
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

int main(int argc, char **argv)
{
    std::string input;
    std::string output;
    char *fileName;

    mode_selected_t  mode = AFFINE_MODE_DEFAULT;
    int a = AFFINE_A_DEFAULT;
    int b = AFFINE_B_DEFAULT;

    parseinput(argc, argv, &mode, &a, &b);
    if(argc - optind == 0)
    {
        std::cout << "No cipher/text file provided" << std::endl;
        return 1;
    }
    fileName = argv[optind];
    if(fileIn(fileName, input) == -1)
    {
        std::cout << "File \"" << fileName << "\" could not be opened" << std::endl;
        return 1;
    }

    switch(mode)
    {
        case MODE_ENCRYPT:
            affine_Encrypt(input, output, a, b);
            std::cout << output << std::endl;
            break;
        case MODE_DECRYPT:
            affine_Decrypt(input, output, a, b);
            std::cout << output << std::endl;
            break;
        case MODE_FORCE:
            affine_Force_Brute(input, 25, 25);
            break;
    }

    return 0;
}

