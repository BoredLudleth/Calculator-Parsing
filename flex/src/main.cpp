#include "lex_lib.hpp"
#include <iostream>

int main (int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen (argv[1], "r");
    } else {
        yyin = stdin;
    }

    yyout = fopen ("../../shift-reduce/out.bin", "w");;

    yylex();

    std::cout << "SUCCESS::File has been written" << std::endl;
    fclose (yyout); 
    fclose (yyin);

    return 0;
}
