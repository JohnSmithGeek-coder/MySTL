#include <iostream>
#include <ctime>
#include "queue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void)
{
    queue<int> q(100);
    cout << q.capacity() << endl;
    for (int i = 0; i < 10; i++) {
        int t = rand()%100;
        cout << t << " ";
        q.push(t);
    }
    cout << endl;
    cout << q.size() << endl;
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    cout << q.size() << endl;
    queue<string> str(3);
    str.push("hello");
    str.push("world");
    str.push("good");
    str.pop();
    str.pop();
    str.push("great");
    while (!str.empty()) {
        cout << str.front() << " ";
        str.pop();
    }
    cout << endl;
    queue<string> qs(100);
    qs = str;
    queue<string> qst(str);
    return 0;
}