#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isRightAssociative(char op) {
    return op == '^';
}

vector<string> shuntingYard(const string& expression) {
    stack<char> opStack;
    vector<string> output;

    for (size_t i = 0; i < expression.length(); ++i) {
        char token = expression[i];
        if (isspace(token)) continue;
        if (isdigit(token)) {
            string number;
            while (i < expression.length() && isdigit(expression[i])) {
                number += expression[i];
                i++;
            }
            i--; 
            output.push_back(number);
        }
        else if (isOperator(token)) {
            while (!opStack.empty() && isOperator(opStack.top())) {
                char topOp = opStack.top();
                if ((isRightAssociative(token) && getPrecedence(token) < getPrecedence(topOp)) ||
                    (!isRightAssociative(token) && getPrecedence(token) <= getPrecedence(topOp))) {
                    output.push_back(string(1, topOp));
                    opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(token);
        }
        else if (token == '(') {
            opStack.push(token);
        }
        else if (token == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                output.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop(); 
            }
        }
    }
    while (!opStack.empty()) {
        output.push_back(string(1, opStack.top()));
        opStack.pop();
    }

    return output;
}
void printPostfix(const vector<string>& postfix) {
    for (const string& token : postfix) {
        cout << token << " ";
    }
    cout << endl;
}
int main() {
    string infix;
    cout << "Enter infix expression (e.g., 3 + 4 * (2 - 1)):\n> ";
    getline(cin, infix);

    vector<string> postfix = shuntingYard(infix);

    cout << "Postfix Expression: ";
    printPostfix(postfix);

    return 0;
}
