%option noyywrap

%{
#include <iostream>
#include "lex_funct.hpp"
#include "settings.hpp"

enum Tokens {
    E,
    T,
    P,
    ID,
    VAR,
    NUM,
    OPEN_SCOPE,
    CLOSE_SCOPE,
    DIV,
    MUL,
    ADD,
    SUB
};


char  string_buffer[MAX_STRING_LENGTH];
char* string_pointer;
%}

DIGIT         [0-9]
VAR           [xyz]

%x IN_COMMENT FOO_COMMENT STRING

%%

{DIGIT}+                                            {
    print_msg ("Token class: DIGIT, Token value: ", yytext);
    print_token (yyout, NUM);
}

"("                             {
    print_msg ("Token class: OPEN_SCOPE, Token value: ", yytext);
    print_token (yyout, OPEN_SCOPE);
}

")"                             {
    print_msg ("Token class: CLOSE_SCOPE, Token value: ", yytext);
    print_token (yyout, CLOSE_SCOPE);
    
}

"+"                             {
    print_msg ("Token class: ADD, Token value: ", yytext);
    print_token (yyout, ADD);
}

"-"                             {
    print_msg ("Token class: SUB, Token value: ", yytext);
    print_token (yyout, SUB);   
}

"/"                             {
    print_msg ("Token class: DIV, Token value: ", yytext);
    print_token (yyout, DIV);
}

"*"                             {
    print_msg ("Token class: MUL, Token value: ", yytext);
    print_token (yyout, MUL);
}

{VAR}                                     {
    print_msg ("Token class: VAR, Token value: ", yytext);
    print_token (yyout, VAR);
}

[ \n\t]+                                            // eat spaces

%%