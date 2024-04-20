#ifndef LEX_FUNCT_HPP
#define LEX_FUNCT_HPP

#include <iostream>
#include <fstream>
#include "settings.hpp"

//template function for messages for all things
void print_msg (const char* my_msg, char* yytext = nullptr);
void print_token (FILE* out, int type);

#endif
