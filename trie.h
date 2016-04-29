#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Trie {
    public:
        map<char, Trie> children;
        string value;
        bool flag;

        Trie(const string &val="");
        void add(char);
        string find(const string &);
        void insert(const string &);
        vector<string> all_prefixes();
        vector<string> autocomplete(const string &);
};

#endif // TRIE_H
