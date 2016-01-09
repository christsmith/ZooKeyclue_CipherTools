#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "cipherTools.h"
#include "vigenere.h"

void parseinput(int argc, char **argv, mode_selected_t &mode, std::string &key, std::string &key_file);

void parseinput(int argc, char **argv, mode_selected_t &mode, std::string &key, std::string &key_file)
{
    int opt;

    while((opt = getopt(argc,argv, "defk:l:")) != -1) {
        switch (opt)
        {
            case 'd':
                mode = MODE_DECRYPT; break;
            case 'e':
                mode = MODE_ENCRYPT; break;
            case 'f':
                mode = MODE_FORCE; break;
            case 'k':
                key = optarg; break;
            case 'l':
                key_file = optarg; break;
        }
    }
}

int parse_key_file(std::string &key_file, std::vector<std::string> &key_list)
{

    std::ifstream iFile(key_file.c_str());
    std::string line;

    if(!iFile.is_open())
        return 1;

    while (std::getline(iFile, line))
    {
        if(line.size() != 0)
            key_list.push_back(line);
    }

    iFile.close();
    return 0;
}

int main(int argc, char **argv)
{
    std::string input;
    std::string output;
    char *fileName;

    mode_selected_t mode = VIGENERE_MODE_DEFAULT;
    std::string key;
    std::string key_file;
    std::vector<std::string> key_list;

    parseinput(argc, argv, mode, key, key_file);
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

    if(key_file.size() > 0)
    {
        parse_key_file(key_file, key_list);
    }

    switch(mode)
    {
        case MODE_ENCRYPT:
            vigenere_Encrypt(input, output, key);
            std::cout << output << std::endl;
            break;
        case MODE_DECRYPT:
            vigenere_Decrypt(input, output, key);
            std::cout << output << std::endl;
            break;
        case MODE_FORCE:
            vigenere_Force_List(input, key_list);
            break;
    }

    return 0;
}

