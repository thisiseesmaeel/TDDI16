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
        std::size_t hash{0};
        for(int i { N - 1 }; i >= 0; i--)  /// convert a binary number to a decimal number.
        {                                  ///Ex: 1010 in binary = 0 * (2^0) + 1 * (2^1) + 0 * (2^2) + 1 * (2^3) = 10 in decimal 
            if(k.bit(i))
            {
                hash += pow(2, N - 1 - i);
            }
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
    int index = N / 2;
    if(N % 2 != 0)
        index = N * 0.6;
    cout << "N :\t" << N << "\tindex:\t" << index << endl;

    do
    {
        Key enc = subset_sum(candidate, table);
        map[enc] = candidate;
        candidate++;
    } while(!candidate.bit( index ));

    Key step{};
    step += candidate;
    int counter{0};

    do
    {
        auto search = map.find( hashed - subset_sum(candidate, table) );
        if(search != map.end())
            {
                cout << (search -> second + candidate) << endl;
                counter ++;
            }
        candidate += step;
    } while (candidate != zero);

    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    cout << "Founded passwords:\t" << counter << endl;
    return 0;
}
