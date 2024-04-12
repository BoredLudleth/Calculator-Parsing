%option noyywrap

%{
#include <iostream>
#include "lex_funct.hpp"
#include "settings.hpp"

int rec_comment_num;

char  string_buffer[MAX_STRING_LENGTH];
char* string_pointer;
%}

DIGIT         [0-9]
VAR           [xyz]

%x IN_COMMENT FOO_COMMENT STRING

%%

{DIGIT}+                                            {
    print_msg ("Token class: DIGIT, Token value: ", yytext);
}

{DIGIT}+"."{DIGIT}*                                 {
    print_msg ("Token class: FLOAT, Token value: ", yytext);
}

"("|")"|"+"|"-"|"/"|"*"                             {
    print_msg ("Token class: SPEC_SYM, Token value: ", yytext);
}

{VAR}                                     {
    print_msg ("Token class: VAR, Token value: ", yytext);
}

[ \n\t]+                                            // eat spaces

%%