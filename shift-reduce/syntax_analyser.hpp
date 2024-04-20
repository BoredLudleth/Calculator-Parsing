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
    SUB
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

    bool shift () {
        if (hasTokens()) {
            return FAILED;
        }

        int temp = input.top();
        input.pop();
        stack.push (temp);

        return SUCCESS;
    }

    int reduce () {
        if (stackEmpty()) {
            return FAILED;
        }

        switch (stack.top()) {
            case NUM:
            case VAR:
                numOrVarToId ();
                break;
            case ID:
                return idToP ();
                break;
            case CLOSE_SCOPE:
                return scopeExprToP ();
                break;
            case P:
                return PToT ();
                break;
            case T:
                return TToE ();
                break;
            default:
                return FAILED;
        };

        return SUCCESS;
    }

    int numOrVarToId () {
        stack.pop ();
        stack.push (ID);

        return SUCCESS;
    }

    int idToP () {
        stack.pop ();
        stack.push (P);

        return SUCCESS;
    }

    int scopeExprToP () {
        stack.pop ();

        if (stack.top() == E) {
            stack.pop();
            if (stack.top() == OPEN_SCOPE) {
                stack.pop();
                stack.push (P);

                return SUCCESS;
            } else {
                stack.push(E);
                stack.push(CLOSE_SCOPE);
                return FAILED;
            }
        } else {
            stack.push(CLOSE_SCOPE);
            return FAILED;
        }
    }

    int PToT () {
        stack.pop();
        
        if (!stackEmpty() && (stack.top() == DIV || stack.top() == MUL)) {
            int sign = stack.top();
            stack.pop();

            if (stack.top() == T || stack.top() == P) {
                stack.pop ();
                stack.push (T);
                return SUCCESS;
            } else {
                stack.push (sign);
                stack.push(T);

                return FAILED;
            }
        } else {
            stack.push (T);
            return SUCCESS;
        }
    }

    int TToE () {
        stack.pop();

        if (!stackEmpty() && (stack.top() == SUB || stack.top() == ADD)) {
            int sign = stack.top();
            stack.pop();

            if (stack.top() == T || stack.top() == E) {
                stack.pop();
                stack.push (E);
                return SUCCESS;
            } else {
                stack.push (sign);
                stack.push(T);
                return FAILED;
            }
        } else {
            stack.push (E);
            return SUCCESS;
        }
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

    int syntaxAnalysis () {
        output();
        std::cout << std::endl;

        while (!hasTokens()) {
            if (reduce ()) {
                output();
                std::cout << " reduce" << std::endl;
                continue;
            } else {
                shift ();
                output();
                std::cout << " shift" << std::endl;
                continue;
            }
        }

        while (reduce()) {
            output ();
            std::cout << " reduce" << std::endl;
        };

        output();
        
        if (stack.size() == 1 && stack.top () == E) {
            std::cout << std::endl << "Success! All right! Good!" << std::endl;
            return SUCCESS;
        }

        return FAILED;
    }
};
