#include <iostream>
#include <ctime>
#include "stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void)
{
    stack<int> s(100);
    for (int i = 0; i < 10; i++) {
        int t = rand()%100;
        cout << t << " ";
        s.push(t);
    }
    cout << endl;
    cout << s.size() << endl;
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    stack<string> str(100);
    str.push("hello"); cout << "hello" << " ";
    str.push("world"); cout << "world" << " ";
    str.push("good");  cout << "good"  << " ";
    str.push("great"); cout << "great" << " ";
    cout << endl;
    cout << str.size() << endl;
    while (!str.empty()) {
        cout << str.top() << " ";
        str.pop();
    }
    cout << endl;
    cout << str.size() << endl;
    stack<string> st(10);
    st = str;
    return 0;
}