#include "lex_funct.hpp"

void print_msg (const char* my_msg, char* yytext) {
    if (yytext != nullptr) {
        std::cout << my_msg << yytext << std::endl;
    } else {
        std::cout << my_msg << std::endl;
    }
}

void print_token (FILE* out, int type) {
    fwrite (&type, sizeof (int), 1, out);
}
