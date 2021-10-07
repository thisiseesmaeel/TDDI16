#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"

using namespace std;

int main() {
    vector<int> v;


    cout <<  v.size() << endl;
    int a = v.back();
    v.pop_back();
    cout <<  a << endl;
    // cout <<  v.size() << endl;
    // for (auto p: v)
    // {
    //     cout << "this is the point" << p << endl;
    // }
    
    return 0;
}
