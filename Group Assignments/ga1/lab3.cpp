#include <iostream>
#include "ArgumentManager.h"
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stack>
#include <cmath>

using namespace std;

int priority(char let) {
    if (let == '/' || let == '*')
        return 2;
    else if (let == '+' || let == '-')
        return 1;
    else 
        return -1;
}

string operation(double dig2, char oper, double dig1) {
    if (oper == '/') {
        return to_string(dig2 / dig1);
    }
    else if (oper == '*') {
        return to_string(dig2 * dig1);
    }
    else if (oper == '+') {
        return to_string(dig2 + dig1);
    }
    else if (oper == '-') {
        return to_string(dig2 - dig1);
    }
    else {
        return "-1";
    }
}

string infixToPostfix(string str) {
    stack<char> mystack;
    string sol = "";
    for (int i = 0; str[i] != '='; i++) {
        if (isdigit(str[i]) || isalpha(str[i]))
            sol += str[i];
        else if (str[i] == '(')
            mystack.push('(');
        else if (str[i] == ')') {
            while (!mystack.empty() && mystack.top() != '(') {
                sol += mystack.top();
                mystack.pop();
            }
            if (!mystack.empty())
                mystack.pop();
        }

        else {
            while (!mystack.empty() && priority(mystack.top()) >= priority(str[i])) {
                sol += mystack.top();
                mystack.pop();
            }
            mystack.push(str[i]);
        }
    }

    while (!mystack.empty()) {
        sol += mystack.top();
        mystack.pop();
    }

    for (int i = str.find('='); i < str.length(); i++) {
        sol += str[i];
    }

    return sol;
}

double evalPostFix(string s) {
    stack<string> mystack;
    double sol, rhs;
    string temp;   
    for (int i = s.find('=') + 1 ; i < s.length(); i++) {
        temp.push_back(s[i]);
    }
    rhs = stod(temp);
    
    for (int i = 0; i != s.find('='); i++) {
        if(isdigit(s[i]) || isalpha(s[i])) {
            string c = "";
            c += s[i];
            mystack.push(c);

        }
        else {
            string dig1 = mystack.top();
            mystack.pop();
            string dig2 = mystack.top();
            mystack.pop();
            double num1;
            double num2;
            if (dig1 == "x" || dig2 == "x") {
                num1 = (dig1=="x") ? stod(dig2) : rhs;
                num2 = (dig2=="x") ? stod(dig1) : rhs;
                if (s[i] == '*') {
                    mystack.push(operation(num2, '/', num1));
                }
                if (s[i] == '/') {
                    if (dig1 == "x")
                        mystack.push(operation(num1, '/', num2));
                    else
                        mystack.push(operation(num2, '*', num1));
                }
                if (s[i] == '+')
                    mystack.push(operation(num2, '-', num1));
                if (s[i] == '-')
                    mystack.push(operation(num2, '+', num1));
            }
            else {
                mystack.push(operation(stod(dig2), s[i], stod(dig1)));
            }
        }
    }    

    sol = stod(mystack.top());
    return sol; 
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));

    string in = "";
    string post = "";
    double sol;

    getline(input, in);
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());

    post = infixToPostfix(in);
    sol = evalPostFix(post);
    out << fixed << setprecision(2) << sol << endl;

    return 0;
}
