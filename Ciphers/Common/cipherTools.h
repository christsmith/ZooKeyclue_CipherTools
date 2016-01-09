
#ifndef CIPHERTOOLS_H
#define CIPHERTOOLS_H

#include <vector>

const int ALPHABET_LENGTH = 26;

enum mode_selected_t { MODE_DECRYPT, MODE_ENCRYPT, MODE_FORCE };
enum letter_case_t { LETTER_CASE_UPPER, LETTER_CASE_LOWER, LETTER_CASE_SPECIAL };


char value_to_ascii(int v, letter_case_t letter_case);
int ascii_to_value(char c, letter_case_t &letter_case);
int ascii_to_value(char c);
int fileIn(const char * fileName, std::string &input);
void print_vector_chars(const std::vector<char> &v);
bool isUpper(char l);
bool isLower(char l);

#endif

