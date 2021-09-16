#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, int> m1 {{"kkk", 2},{"hhh", 21}};

    auto it = m1.find("kkk");

    if(it != m1.end())
    {
        cout << it -> first << "    " << it -> second << endl;
        //cout << "YES" << endl;
    }
//      for (int i{0}; i < 33 ;i++)
//      {  
//          bool t = true;
//          k1 ++;
//          cout << k1 << "  " << k1.bit(4) << " " << t <<endl;
//      }
    return 1;
}