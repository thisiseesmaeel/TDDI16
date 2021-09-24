#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using std::vector;
using std::string;
using std::queue;
using std::map;
using std::cout;
using std::endl;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef vector<string> Dictionary;

////////// Hadi ///////////
vector<string> find_neighbors(const Dictionary &dict, const string &word)
{
    vector<string> neighbors;
    // jämför ord med alla andra ord i dict
    for(int i{0}; i < word.size(); i++)
    {
        string temp = word;
        for(int j{97}; j < 123; j++)
        {
            temp[i] = (char) j;
            if(find(dict.begin(), dict.end(), temp) != dict.end())
            {
                neighbors.push_back(temp);
            }
        }
    }
    return neighbors;
}

//////////////////////

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    vector<string> result;
    vector<string> visited;    
    map<string, string> m; // en map som håller koll på var vi kom ifrån
    queue <string> q;

    q.push(from);
    visited.push_back(from);

    while(!q.empty())
    {
        string current = q.front(); q.pop();
        //cout << "current is:\t" << current << endl;
        //cout << "q is:\t"; 
        queue <string> q2 = q;
        // while(!q2.empty())
        // {
        //     cout << q2.front() << "  ";
        //     q2.pop();
        // }
        //cout << endl;

        //cout << "Visited:\t";
        // for(auto i : visited)
        // {
        //     cout << i << "  ";
        // }
        //cout << endl;
        //cout << "neighbors of " << current << ":"<< endl; 
        int number {1};
        for(auto i: find_neighbors(dict, current))
        {
            //cout << number << ". " << i << endl;
            number ++;
            if( i == to )
            {          
                visited.push_back(to);
                m[i] = current;
                //cout << endl;
                string temp = i;

                //cout << "This is the map:" << endl;
                // for(auto it: m)
                // {
                //     cout << it.first << " previous :  " << it.second << endl;
                // }
                while (temp != from)
                {
                    result.push_back(temp);
                    temp = m[temp];
                }
                result.push_back(temp);
                reverse(result.begin(), result.end());
                
                return result;
            }

            if(find(visited.begin(), visited.end(), i) == visited.end())
            {
                //cout << i << " is not visited" << endl;
                visited.push_back(i);
                q.push(i);
                m[i] = current;
            }

        }
        //cout << endl;
    }
    //cout << endl;

    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result(1, word);
    vector <vector<string>> word_chains{};
    int longest{0};

    for(auto &w: dict)
    {
        if(w == word)
            continue;
        vector<string> temp = find_shortest(dict, w, word);
        int size = temp.size();
        if(size != 0 && size > longest)
        {
            //cout << "Size is not zero" << endl;
            longest = size;
            result = temp;
        }
            
    }
    //cout << "Done with finding all path to " << word << endl;
    // if(word_chains.size() == 0) return result;
    // auto max = max_element(word_chains.begin(), word_chains.end(), 
    //     [](vector<string> &A, vector<string> &B) {
    //         return A.size() < B.size();
    //     });

    //cout << word_chains.size() << endl;

    // int num {1};
    // for(auto it: word_chains)
    // {
    //     cout << num << ". ";
    //     for(auto it2: it)
    //     {
    //         cout << it2 << "\t";
    //     }
    //     cout << endl;
    //     num ++;
    // }
    // cout << "Size of longest is " << (*max).size() << endl;
    // cout << "This is a longest of shortest path to " << word << endl;
    // for(auto i: *max)
    // { 
    //     cout << i << endl; 
    // }
    // if((*max).size() > 1)
    //     result = *max;

    //cout << "TODO: Implement me!" << endl;
    return result;
}


/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
    string line;
    vector<string> result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.push_back(line);
    }

    return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const vector<string> &chain) {
    if (chain.empty()) {
        cout << "ingen lösning" << endl;
    } else {
        cout << chain.size() << " ord" << endl;
        print_chain(chain);
    }
}

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
