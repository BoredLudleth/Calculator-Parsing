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
    FILE* in = fopen ("build/out.bin", "rb");
    int len_in = lenFile (in) / sizeof (int);
    int token_array[len_in];
    fread (token_array, sizeof(int), len_in, in);

    fclose(in);

    std::stack<int> token;

    for (int i = len_in - 1; i >= 0; i--) {
        token.push(token_array[i]);
    }

    SyntaxAnalyzer<LR0> shift_reduce (token);
    int action = 0;
    shift_reduce.output ();
    do {
        std::cout << "\t\t\tstate: " << shift_reduce.state << std::endl;
        action = shift_reduce.stateMachine();
        shift_reduce.output ();
        switch (action) {
            case REDUCE:
                std::cout << " reduce" << std::endl;
                break;
            case SHIFT:
                std::cout << " shift" << std::endl;
                break;
            case ERROR:
                std::cout << " error" << std::endl;
                break;
            case ACCEPT:
                std::cout << " accept" << std::endl;
                break;
        }
    } while  (action == SHIFT || action == REDUCE);

    return 0;
}