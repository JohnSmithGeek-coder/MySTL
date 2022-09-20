#include <iostream>
#include <ctime>
#include "vector.h"
#include "algo.h"
#include "list.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T>
void output(T& v)
{   
    for (auto iter = v.begin(); iter != v.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(void)
{
    int a[10] = {2, 3, 1, 7, 5, 11, 4, 8, 9, 10};
    vector<int> iv(a, a + 10);
    output(iv);
    cout << iv.size() << endl;
    cout << iv.capacity() << endl;
    auto iter = MTL::find(iv.begin(), iv.end(), 7); 
    iter = iv.insert(iter, 111);  
    output(iv);
    iter = iv.erase(iter, iter + 4); 
    output(iv);
    iter = iv.insert(iter, 5, 0); 
    output(iv);
    iv.erase(iter);
    MTL::quick_sort(iv.begin(), iv.end()); 
    output(iv);
    iv.erase(iv.begin(), iv.begin() + 5);
    output(iv);
    cout << iv.front() << endl;
    cout << iv.back() << endl;
    string st[5] = {"hello", "world", "good", "job", "great"};
    vector<string> sv(st, st + 5);
    output(sv);
    MTL::quick_sort(sv.begin(), sv.end());
    output(sv);
    sv.pop_back();
    sv.pop_back();
    output(sv);
    return 0;
}