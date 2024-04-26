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

enum States {
    i0,     i1,     i2,
    i3,     i4,     i5,
    i6,     i7,     i8,
    i9,     i10,    i11
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
        int state = i0;

    int stateMachine () {
        switch (state) {
            case i0:
                return I0();
            case i1:
                return I1();
            case i2:
                return I2();
            case i3:
                return I3();
            case i4:
                return I4();
            case i5:
                return I5();
            case i6:
                return I6();
            case i7:
                return I7();
            case i8:
                return I8();
            case i9:
                return I9();
            case i10:
                return I10();
            case i11:
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
                state = i1;
                break;
            case T:
                state = i2;
                break;
            case P:
                state = i3;
                break;
            case OPEN_SCOPE:
                state = i4;
                break;
            case VAR:
            case NUM:
                state = i5;
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
            if (stack.size() == 1) {
                return ACCEPT;
            }

            return ERROR;
        }

        int token = shift();

        switch (token) {
            case ADD:
            case SUB:
                state = i6;
                break;
            default:
                return ERROR;
        }

        return SHIFT;
    }

    int I2 () {
        if (hasTokens()) {
            state = i0;
            stack.pop();
            stack.push(E);
            return REDUCE;
        }

        int token = shift();

        switch (token) {
            case MUL:
            case DIV:
                state = i7;
                return I7();
            case ADD:   //??????
            case SUB:
                state = i1;
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
        if (stackEmpty()) {
            state = i1;
        } else {
            state = i9;
        }
        stack.pop();
        stack.push(T);
        return REDUCE;
    }

    int I4 () {
        int token = shift();

        switch (token) {
            case E:
                state = i8;
                break;
            case OPEN_SCOPE:
                state = i4;
                break;
            case T:
                state = i2;
                break;
            case P:
                state = i3;
                break;
            case NUM:
            case VAR: 
                state = i5;
                break;
            default:
                printf ("error\n");
                return ERROR;
        };

        return SHIFT;
    }

    int I5 () {
        state = i3;
        stack.pop();
        if (stackEmpty()) {
            state = i3;
            stack.push(P);

            return REDUCE;
        }
        switch (stack.top()) {
            case DIV:
            case MUL:
                state = i10;
                break;
            default:
                state = i3;
                break;
        }
        stack.push(P);

        return REDUCE;
    }

    int I6 () {
        int token = shift ();

        switch (token) {
            case T:
                state = i9;
                break;
            case P:
                state = i3;
                break;
            case OPEN_SCOPE:
                state = i4;
                break;
            case NUM:
            case VAR:
                state = i5;
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
                state = i10;
                break;
            case OPEN_SCOPE:
                state = i4;
                break;
            case NUM:
            case VAR:
                state = i5;
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
                state = i11;
                break;
            case ADD:
            case SUB:
                state = i6;
                break;
            default:
                return ERROR;

        };

        return SHIFT;
    }

    int I9 () {
        if (hasTokens()) {
            if (stack.top() == T) {
                if (stack.size() > 2) {
                    state = i1;
                    stack.pop();
                    stack.pop();
                } else {
                    state = i1;
                }
                return REDUCE;      //???
            } else {
                return ERROR;
            }
        }
        int token = shift ();

        switch (token) {
            case MUL:
            case DIV:
                state = i7;
                break;
            default:
                input.push(stack.top());
                stack.pop();
                input.push(stack.top());
                stack.pop();

                if (stackEmpty()) {
                    state = i2;
                    stack.push(input.top());
                    input.pop();
                    return REDUCE;
                }

                if (stack.top() == ADD || stack.top() == SUB) {
                    state = i8;
                    input.pop();
                    stack.pop();
                    return REDUCE;
                } else {
                    state = i2;
                    stack.push(input.top());
                    input.pop();
                    return SHIFT;
                }
        };

        return SHIFT;
    }

    int I10 () {
        state = i3;
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
            state = i3;
            return REDUCE;
        }
        
        if (stack.top() == MUL || stack.top() == DIV) {
            state = i10;
        } else {
            state = i3;
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
