#include <fstream>
#include "syntax_analyser.hpp"

int lenFile(FILE *text)
{
    fseek(text, 0, SEEK_END);
    int length =  ftell(text);
    fseek(text, 0, SEEK_SET);

    return length;    
}

int main () {
    FILE* in = fopen ("out.bin", "rb");
    int len_in = lenFile (in) / sizeof (int);
    int token_array[len_in];
    fread (token_array, sizeof(int), len_in, in);

    fclose(in);

    std::stack<int> token;

    for (int i = len_in - 1; i >= 0; i--) {
        token.push(token_array[i]);
    }

    SyntaxAnalyzer<LR0> shift_reduce (token);
    shift_reduce.syntaxAnalysis();

    return 0;
}