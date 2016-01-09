const mode_selected_t VIGENERE_MODE_DEFAULT = MODE_DECRYPT;

int vigenere_Encrypt(const std::string &text, std::string &cipher, std::string &key);
int vigenere_Decrypt(const std::string &cipher, std::string &text, std::string &key);
int vigenere_Force_List(const std::string &cipher, std::vector<std::string> &key);
