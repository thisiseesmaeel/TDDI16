#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<string> finddd(unordered_set<string> s)
{
    vector<string> empty{};
    return empty;
}
int main()
{   
    unordered_set<string> set{"aaaa", "aaab", "baaa", "aabb", "baba", "babb" };
    string s = "aaaa";

    for(auto i : finddd(set))
    {
        cout << i << endl;
    }

    return 1;
}