#include <iostream>
#include "algo.h"
#include "vector.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void output(vector<int>& v) {
    for (auto iter = v.begin(); iter != v.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(void)
{
    vector<int> v(3);
    v[0] = 3; v[1] = 2; v[2] = 1;

    auto ite = MTL::find(v.begin(), v.end(), 2);
    cout << *ite << endl;

    MTL::bubble_sort(v.begin(), v.end());
    output(v);

    ite = MTL::binary_search(v.begin(), v.end(), 1);
    cout << *ite << endl;

    v.push_back(11); v.push_back(7); v.push_back(9); v.push_back(8);
    MTL::quick_sort(v.begin(), v.end());
    output(v);

    v.push_back(45); v.push_back(34); v.push_back(22); v.push_back(3);
    MTL::heap_sort(v.begin(), v.end());
    output(v);

    return 0;
}