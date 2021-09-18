#include <iostream>
#include <chrono>
#include <string>
#include "key.h"
#include <unordered_map>
#include <cmath>

using namespace std;

struct MyHash
{
    std::size_t operator()(Key const& k) const noexcept
    {
        std::size_t potens{0};
        std::size_t hash{0};
        for(int i{0}; i < N; i++)
        {
            if(k.bit(i))
            {
                hash += pow(2, potens) * 20;
            }
            potens++;
        }
        return hash;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {    
        cout << "Usage:" << endl;
        cout << argv[0] << " <hashed password> < rand8.txt" << endl;
        return 1;
    }

    // Hashed password.
    Key hashed{argv[1]};

    // Table.
    Key table[N];

    // Read table.
    for (int i{0}; i < N; i++) {
        string buffer;
        if (!(cin >> buffer)) {
            cerr << "Too short table!" << endl;
            return 1;
        }
        table[i] = Key{buffer.c_str()};
    }

    auto begin = chrono::high_resolution_clock::now();

    unordered_map <Key, Key, MyHash> map;
    Key candidate{};
    Key zero{};

    for(int i{0}; i < pow(2, N/2) ; i++)
    {
        Key enc = subset_sum(candidate, table);
        map[enc] = candidate;
        candidate++;
    }
    Key step = candidate;

    do
    {
        auto search = map.find( hashed - subset_sum(candidate, table) );
        if(search != map.end())
            {
                cout << (search -> second + candidate) << endl;
            }
        candidate += step;
    } while (candidate != zero);
    
    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    return 0;
}
