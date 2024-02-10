#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

#include "Map.h"
#include <string>
#include <stack>
#include <cctype>

using namespace std;

int toPostfix(string infix, string& postfix, int& i, bool& inParen);
int getPrecedence(char c);
int operate(int x, int y, char operation);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    int i = 0;
    bool inParen = false;
    postfix = "";
    if(toPostfix(infix, postfix, i, inParen) == 1) {
        return 1;
    }

    stack<int> oStack;

    int value;
    int operand1;
    int operand2;
    for(int i = 0; i < postfix.size(); i++) {
        if(islower(postfix[i])) {
            if(!values.get(postfix[i], value)) {
                return 2;
            }
            oStack.push(value);
        } else {
            operand2 = oStack.top();
            oStack.pop();
            
            if(operand2 == 0 && postfix[i] == '/') {
                return 3;
            }

            operand1 = oStack.top();
            oStack.pop();

            oStack.push(operate(operand1, operand2, postfix[i]));
        }
    }

    result = oStack.top();
    return 0;
}

int toPostfix(string infix, string& postfix, int& i, bool& inParen) {
    stack<char> oStack;

    int counter = 0;
    bool openParen = false;
    for(; i < infix.size(); i++) {
        if(islower(infix[i])) {
            counter++;
            postfix += infix[i];

        } else if(infix[i] == '(') {
            i++;
            openParen = true;
            if(toPostfix(infix, postfix, i, openParen) == 1) {
                return 1;
            }
            counter++;
        } else if(infix[i] == ')') {
            if(inParen == false) {
                return 1;
            }
            inParen = false;
            break;
        } else if(infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-') {
            counter--;
            while(!oStack.empty() && oStack.top() != '(' && getPrecedence(infix[i]) <= getPrecedence(oStack.top())) {
                postfix += oStack.top();
                oStack.pop();
            }
            oStack.push(infix[i]);

        } else if(infix[i] != ' ') {
            return 1;
        }

        if(counter < 0 || counter > 1) { return 1;}
    }
    while(!oStack.empty()) {
        postfix += oStack.top();
        oStack.pop();
    }

    return (counter == 1 && !inParen) ? 0 : 1;
}

int getPrecedence(char c) {
    return (c == '*' || c == '/') ? 2 : 1;
}

int operate(int x, int y, char operation) {
    switch(operation) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
    }
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}

