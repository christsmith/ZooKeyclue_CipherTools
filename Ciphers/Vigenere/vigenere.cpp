#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <vector>

#include "cipherTools.h"
#include "vigenere.h"

int vigenere_Encrypt(const std::string &text, std::string &cipher, std::string &key)
{
    int cipher_v;
    int text_v;
    int key_v;
    letter_case_t text_v_letter_case;
    letter_case_t key_v_letter_case;

    cipher.resize(text.size());

    for(int i  = 0; i < text.size(); i++)
    {
        text_v = ascii_to_value(text[i], text_v_letter_case);
        key_v = ascii_to_value(key[i % key.size()], key_v_letter_case);

        if(text_v_letter_case != LETTER_CASE_SPECIAL && key_v_letter_case != LETTER_CASE_SPECIAL)
            cipher_v = (text_v + key_v) % ALPHABET_LENGTH;
        else
            cipher_v = text_v;

        cipher[i] = value_to_ascii(cipher_v, text_v_letter_case );
    }

    return 0;
}
int vigenere_Decrypt(const std::string &cipher, std::string &text, std::string &key)
{
    int cipher_v;
    int text_v;
    int key_v;
    letter_case_t cipher_v_letter_case;
    letter_case_t key_v_letter_case;

    text.resize(cipher.size());

    for(int i  = 0; i < cipher.size(); i++)
    {
        cipher_v = ascii_to_value(cipher[i], cipher_v_letter_case);
        key_v = ascii_to_value(key[i % key.size()], key_v_letter_case);

        if(cipher_v_letter_case != LETTER_CASE_SPECIAL && key_v_letter_case != LETTER_CASE_SPECIAL)
            text_v = (cipher_v - key_v + ALPHABET_LENGTH) % ALPHABET_LENGTH;
        else
            text_v = cipher_v;

        text[i] = value_to_ascii(text_v, cipher_v_letter_case );
    }

    return 0;
}

//Speed is important and real time feedback is important in this case. Print as soon as results are made available!
int vigenere_Force_List(const std::string &cipher, std::vector<std::string> &key_list)
{
    std::string text;

    text.resize(cipher.size());

    for(int i = 0; i < key_list.size(); i++)
    {
        if(vigenere_Decrypt(cipher, text, key_list[i]) == 0)
            std::cout << "k=" << key_list[i] << ", "
                      << std::endl << text << std::endl;
    }

    return 0;
}

