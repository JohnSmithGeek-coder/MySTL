#include <iostream>
#include "map.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void output(map<string, int>& m) {
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }
    cout << endl;
}

int main(void)
{
    map<string, int> m;
    m["John"] = 82;
    m["Mike"] = 79;
    m["July"] = 76;
    m["Jack"] = 88;
    output(m);
    auto iter = m.find("Jack");
    (iter->second)++;
    m.insert(pair<string, int>("LiMing", 81));
    output(m);
    cout << m.size() << endl;
    m.erase("Mike");
    output(m);
    m.clear();
    cout << m.size() << endl;
    return 0;
}