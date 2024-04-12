#include "lex_funct.hpp"

void print_msg (const char* my_msg, char* yytext) {
    if (yytext != nullptr) {
        std::cout << my_msg << yytext << std::endl;
    } else {
        std::cout << my_msg << std::endl;
    }
}