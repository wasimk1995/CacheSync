#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include "trie.h"
const static int size_max = 250000;

using namespace std;

class HashTable {
    public:
        HashTable();
        HashTable(string filename);
        string find(const string& key);
        void insert(const string& key, const int& value);
        void print();
        unsigned int hash(const string& key);
        int find_index(const string& key, bool override_duplicated_key);
        string keys[size_max];
        int values[size_max];
        Trie mytrie;
        vector<char> filterArray;
    };

#endif // HASHTABLE_H
