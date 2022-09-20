#include <iostream>
#include <assert.h>
#include <string>
#include "stack.h"

bool isNum(char ch);
bool isOp(char ch);
bool compare(char a, char b);
bool isCorrect(std::string str);
int  calculate(int a, int b, char c);
bool POP(stack<int>& num, stack<char>& op);
bool compute(std::string s, int& ans);
void printInfo();

int main(void)
{
    std::string s;
    int ans;
    printInfo();
    std::cout << ">>>";
    while (getline(std::cin, s)) {
        if (s == "exit") {
            break;
        }
        if (!isCorrect(s)) {
            std::cout << ">>>Error : Wrong Expression!\n>>>";
            continue;
        }
        if (!compute(s, ans)) {
            std::cout << ">>>Error : Denominator cannot be 0!\n>>>";
            continue;
        }
        std::cout << ">>>" << ans << "\n>>>";
    }
    return 0;
}

bool isNum(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

bool isOp(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return true;
    }
    return false;
}

bool compare(char a, char b)
{
    if (a == '+' || a == '-') {
        if (b == '*' || b == '/' || b == '+' || b == '-') {
            return true;
        }
    }
    if (a == '*' || a == '/') {
        if (b == '*' || b == '/') {
            return true;
        }
    }
    return false;
}

bool isCorrect(std::string str)
{
    stack<char> S(1024);
    if(isOp(str[0]) || str[0] == ')') {
        return false;
    }
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '(') {
            S.push(str[i]);
            if (isOp(str[i]) || str[i + 1] == ')' || str[i + 1] == '\0') {
                return false;
            }
        } else if(str[i] == ')') {
            if(!S.empty()) {
                S.pop();
            }
            if(str[i + 1] == '(') {
                return false;
            }
        } else if(isOp(str[i])) {
            if(isOp(str[i+1]) || str[i + 1] == ')' || str[i + 1] == '\0') {
                return false;
            }
        } else if (isNum(str[i]) || str[i] == ' ') {
            continue;
        } else {
            return false;
        }
    }
    if(!S.empty()) return false;
    return true;
}

int calculate(int a, int b, char c)
{
    switch (c) {
        case '+':
            return a + b; break;
        case '-':
            return a - b; break;
        case '*':
            return a * b; break;
        case '/':
            return a / b;
    }
    return 0;
}

bool POP(stack<int>& num, stack<char>& op)
{
    int a, b;
    char c;
    b = num.top(); num.pop();
    a = num.top(); num.pop();
    c = op.top();  op.pop();
    if (b == 0 && c == '/') {
        return false;
    }
    num.push(calculate(a, b, c));
    return true;
}

bool compute(std::string s, int& ans)
{
    int i = 0, t;
    stack<int> num(1024);
    stack<char> op(1024);
    while (i < s.length()){
        if (isNum(s[i])) {
            t = 0;
            while (isNum(s[i])) {
                t = t * 10 + s[i] - '0';
                i++;
            }
            num.push(t);
        }
        if (s[i] == '(') {
            op.push(s[i]);
        }
        if (isOp(s[i])) {
            if (!op.empty()) {
                while (!op.empty() && compare(s[i], op.top())) {
                    if (!POP(num, op)) {
                        return false;
                    }
                }
            }
            op.push(s[i]);
        }
        if (s[i] == ')') {
            while (op.top() != '(') {
                if (!POP(num, op)) {
                    return false;
                }
            }
            op.pop();
        }
        i++;
    }
    while (!op.empty()) {
        if (!POP(num, op)) {
            return false;
        }
    }
    ans = num.top();
    return true;
}

void printInfo()
{
    std::cout << "-+---------------------------------------------------------------------------------+-\n"
              << " |  This is a program that helps you perform non-negative integer operations.      |\n"
              << " |  You need to know the following points:                                         |\n"
              << " |  1.Make sure your keyboard is in English input method.                          |\n"
              << " |  2.You can only enter expressions consisting of '+', '-', '*', '/', '(', ')'.   |\n"
              << " |  3.Use 'exit' command to exit.                                                  |\n"
              << "-+---------------------------------------------------------------------------------+-\n";
}