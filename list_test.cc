#include <iostream>
#include "list.h"
#include "algo.h"
#include "vector.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T>
void output(T& l) 
{
    for (auto iter = l.begin(); iter != l.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(void)
{
    int a[5] = {5, 3, 2, 7, 9};
    vector<int> iv(a, a + 5);
    list<int> lx(iv.begin(), iv.end());
    output(lx);
    cout << lx.front() << endl;
    cout << lx.back() << endl;
    cout << lx.size() << endl;
    lx.push_back(111);
    lx.push_front(222);
    output(lx);
    lx.reverse();
    output(lx);
    auto iter = MTL::find(lx.begin(), lx.end(), 7);
    lx.insert(iter, 333);
    output(lx);
    lx.remove(222);
    output(lx);
    int b[5] = {7, 6, 2, 5, 4};
    list<int> l2(b, b + 5);
    output(l2);
    MTL::bubble_sort(lx.begin(), lx.end());
    MTL::bubble_sort(l2.begin(), l2.end());
    lx.merge(l2);
    output(lx);
    lx.unique();
    output(lx);
    string s[3] = {"hello", "good", "haha"};
    list<string> str(s, s + 3);
    output(str);
    str.clear();
    return 0;
}