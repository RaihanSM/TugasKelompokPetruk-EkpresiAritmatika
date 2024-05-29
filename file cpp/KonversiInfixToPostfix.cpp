#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;


bool isOperator(char opr) {
    return opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '%';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

string infixToPostfix(string infix) {
    stack<string> operators;
    vector<string> output;
    stringstream ss(infix);
    string token;
    char lastChar = 0;
    bool lastWasOperatorOrParen = true; 

    while (ss >> token) {
        
        if (isdigit(token[0])) {
            // Token is an operand
            output.push_back(token);
            lastWasOperatorOrParen = false;
        } else if (token[0] == '-' && (lastWasOperatorOrParen || lastChar == '(')) {
            
            output.push_back("-1");
            operators.push("*");
        } else if (isOperator(token[0])) {
           
            while (!operators.empty() && precedence(operators.top()[0]) >= precedence(token[0])) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
            lastWasOperatorOrParen = true;
        } else if (token[0] == '(') {
          
            operators.push(token);
            lastWasOperatorOrParen = true;
        } else if (token[0] == ')') {
         
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop(); 
            lastWasOperatorOrParen = false;
        }
        lastChar = token[0];
    }

  
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }


    string result;
    for (const auto &s : output) {
        result += s + " ";
    }

    return result;
}

int main() {
    string infix;
    getline(cin, infix);


    for (int i = 0; i < infix.size(); ++i) {
        if (isOperator(infix[i]) || infix[i] == '(' || infix[i] == ')') {
            infix.insert(i, " ");
            infix.insert(i + 2, " ");
            i += 2;
        }
    }

  string postfix = inflixToPostfix(infix);

  cout << postfix << endl;

    return 0;
}

