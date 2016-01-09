const int AFFINE_A_DEFAULT = 1;
const int AFFINE_B_DEFAULT = 0;
const int AFFINE_M_DEFAULT = ALPHABET_LENGTH;
const mode_selected_t AFFINE_MODE_DEFAULT = MODE_DECRYPT;

int affine_Encrypt(const std::string &text, std::string &cipher, int a, int b);
int affine_Decrypt(const std::string &cipher, std::string &text, int a, int b);
int affine_Force_Brute(const std::string &cipher, int max_a, int max_b);


