#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool isOperator(char opr) {
    return opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '%';
}

vector<string> parseInfix(string infix) {
    vector<string> result;
    string num = "";
    
    for (size_t i = 0; i < infix.length(); ++i) {
        char opr = infix[i];
        if (isdigit(opr)) {
            num += opr;
        } else {
            if (!num.empty()) {
                result.push_back(num);
                num = "";
            }
            if (isOperator(opr) || opr == '(' || opr == ')') {
                if (opr == '-' && (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1]))) {
                   
                    if (i + 1 < infix.length() && isdigit(infix[i + 1])) {
                        num += opr; 
                    } else if (i + 1 < infix.length() && infix[i + 1] == '(') {
                        result.push_back("-1");
                        result.push_back("*");
                    }
                } else {
                    result.push_back(string(1, opr));
                }
            } else if (!isspace(opr)) {
                cerr << "Terdapat input tidak valid: " << opr << endl;
            }
        }
    }
    if (!num.empty()) {
        result.push_back(num);
    }
    return result;
}


int main() {
    string input;
    cout << "Input Operasi Bilangan: ";
    getline(cin, input);
    
    vector<string> infixTokens = parseInfix(input);
    
    for (const string& token : infixTokens) {
        cout << token << " ";
    }
    cout << endl;

    return 0;
}

