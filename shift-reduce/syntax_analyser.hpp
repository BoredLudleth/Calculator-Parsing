#include <stack>
#include <iostream>
#include <string>

#define SUCCESS 1
#define FAILED 0

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
    SUB, 
    ERROR_TOK
};

enum Action {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
};

enum Grammar {
    LR0, // only implement this
    LR1,
    LALR,
    NONE
};

template <Grammar G>
class SyntaxAnalyzer{};

template<>
class SyntaxAnalyzer<LR0> {
    private:
        std::stack<int> input;
        std::stack<int> stack;

        bool hasTokens () const {
            return input.empty();
        }

        bool stackEmpty () const {
            return stack.empty();
        }
    public:

    SyntaxAnalyzer (std::stack<int> tokens) : input (tokens) {};
        int state = 0;

    int stateMachine () {
        switch (state) {
            case 0:
                return I0();
            case 1:
                return I1();
            case 2:
                return I2();
            case 3:
                return I3();
            case 4:
                return I4();
            case 5:
                return I5();
            case 6:
                return I6();
            case 7:
                return I7();
            case 8:
                return I8();
            case 9:
                return I9();
            case 10:
                return I10();
            case 11:
                return I11();
            default:
                std::cout << "ERROR::Undefiend state of state machine" << std::endl;
                return ERROR;
        };
    }
    int shift () {
        int temp = input.top();
        input.pop();
        stack.push (temp);

        return temp;
    }

    int I0 () {
        int token = shift();
        
        switch (token) {
            case E:
                state = 1;
                break;
            case T:
                state = 2;
                break;
            case P:
                state = 3;
                break;
            case OPEN_SCOPE:
                state = 4;
                break;
            case VAR:
            case NUM:
                state = 5;
                break;
            default:
                return ERROR;

        };

        return SHIFT;
    }

    int I1 () {
        if (hasTokens()) {
            stack.pop();
            stack.push(E);
            return ACCEPT;
        }

        int token = shift();

        switch (token) {
            case ADD:
            case SUB:
                state = 6;
                break;
            default:
                return ERROR;
        }

        return SHIFT;
    }

    int I2 () {
        if (hasTokens()) {
            state = 0;
            stack.pop();
            stack.push(E);
            return REDUCE;
        }

        int token = shift();

        switch (token) {
            case MUL:
            case DIV:
                state = 7;
                return I7();
            case ADD:   //??????
            case SUB:
                state = 1;
                input.push(stack.top());
                stack.pop();
                stack.pop();
                if (stackEmpty() || stack.top() == OPEN_SCOPE) {
                    stack.push(E);
                } else {
                    stack.push(T);
                }
                return REDUCE;
            default:
                return ERROR;
        }
    }

    int I3 () {
        if (hasTokens()) {
            state = 1;
            return REDUCE;
        }
        state = 9;
        stack.pop();
        stack.push(T);
        return REDUCE;
    }

    int I4 () {
        int token = shift();

        switch (token) {
            case E:
                state = 8;
                break;
            case OPEN_SCOPE:
                state = 4;
                break;
            case T:
                state = 2;
                break;
            case P:
                state = 3;
                break;
            case NUM:
            case VAR: 
                state = 5;
                break;
            default:
                printf ("error\n");
                return ERROR;
        };

        return SHIFT;
    }

    int I5 () {
        state = 3;
        stack.pop();
        if (stackEmpty()) {
            state = 3;
            stack.push(P);

            return REDUCE;
        }
        switch (stack.top()) {
            case DIV:
            case MUL:
                state = 10;
                break;
            default:
                state = 3;
                break;
        }
        stack.push(P);

        return REDUCE;
    }

    int I6 () {
        int token = shift ();

        switch (token) {
            case T:
                state = 9;
                break;
            case P:
                state = 3;
                break;
            case OPEN_SCOPE:
                state = 4;
                break;
            case NUM:
            case VAR:
                state = 5;
                break;
            default:
                return ERROR;

        };

        return SHIFT;
    }

    int I7 () {
        int token = shift ();

        switch (token) {
            case P:
                state = 10;
                break;
            case OPEN_SCOPE:
                state = 4;
                break;
            case NUM:
            case VAR:
                state = 5;
                break;
            default:
                return ERROR;

        };

        return REDUCE;
    }

    int I8 () {
        int token = shift ();

        switch (token) {
            case CLOSE_SCOPE:
                state = 11;
                break;
            case ADD:
            case SUB:
                state = 6;
                break;
            default:
                return ERROR;

        };

        return SHIFT;
    }

    int I9 () {
        int token = shift ();

        switch (token) {
            case MUL:
            case DIV:
                state = 7;
                break;
            default:
                input.push(stack.top());
                stack.pop();
                input.push(stack.top());
                stack.pop();
                if (stack.top() == ADD || stack.top() == SUB) {
                    state = 8;
                    input.pop();
                    stack.pop();
                    return REDUCE;
                } else {
                    state = 2;
                    stack.push(input.top());
                    input.pop();
                    return SHIFT;
                }
        };

        return SHIFT;
    }

    int I10 () {
        state = 3;
        stack.pop();
        stack.pop();

        return REDUCE;
    }

    int I11 () {
        stack.pop();
        stack.pop();
        stack.pop();

        if (stackEmpty()) {
            stack.push(P);
            state = 3;
            return REDUCE;
        }
        
        if (stack.top() == MUL || stack.top() == DIV) {
            state = 10;
        } else {
            state = 3;
        }
        stack.push(P);

        return REDUCE;
    }

    void dumpBackOrderStack (std::stack<int> s) const {
    std::cout << "$";
    std::stack<int> t; 
    while (!s.empty()) {
        t.push(s.top());
        s.pop(); 
    } 
        while(!t.empty()) {
            std::cout << ' ' << translateCodeToTokenName (t.top());
            t.pop();
        }
    }

    void dumpStack (std::stack<int> s) const {
        while(!s.empty()) {
            std::cout << ' ' << translateCodeToTokenName (s.top());
            s.pop();
        }
        
        std::cout << "$";
    }

    std::string translateCodeToTokenName(int code) const {
        switch (code) {
            case E:
                return "E";
            case T:
                return "T";
            case P:
                return "P";
            case ID:
                return "ID";
            case VAR:
                return "VAR";
            case NUM:
                return "NUM";
            case OPEN_SCOPE:
                return "(";
            case CLOSE_SCOPE:
                return ")";
            case DIV:
                return "/";
            case MUL:
                return "*";
            case ADD:
                return "+";
            case SUB:
                return "-";
            default:
                return "UNKNOWN";
        }
    }

    void output () const {
        dumpBackOrderStack (stack);
        std::cout << " ||";
        dumpStack (input);
    }
};
