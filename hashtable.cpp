#include "hashtable.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "trie.h"

using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < size_max; i++) {
        keys[i] = string();
        values[i] = int();
    }
}

HashTable::HashTable(string filename){
    ifstream filedata;
    istringstream iss;
    string line;
    string tempq;
    int tempd;
    vector<string> data;

    filedata.open(filename.c_str());
    while(getline(filedata,line)){
        data.push_back(line);
    }
    filedata.close();

    filterArray.resize(size_max);
    int size = data.size();
    for (int i = 0; i < size; i++) {
        iss.clear();
        iss.str(data[i]);
        iss >> tempq >> tempd;
        const string str = tempq;
        unsigned int index = hash(str);
        keys[index] = tempq;
        mytrie.insert(tempq);
        values[index] = tempd;
        filterArray[index] = 1;
    }
}

unsigned int HashTable::hash(const string& k)
{
    unsigned int value = 0 ;
    int length = k.length();
    for (int i = 0; i < length; i++)
        value = (37*value + k[i]) % size_max;
    return value;
}

void HashTable::print() {
    cout << "{";
    for (int i = 0; i < size_max; i++)
        if (!keys[i].empty())
            cout << keys[i] << ":" << values[i] << ", ";
    cout << "}" << endl;
}

int HashTable::find_index(const string& key, bool override_duplicate_key = true) {
    unsigned int h = hash(key) % size_max, offset = 0, index;
    while (offset < size_max) {
        index = (h + offset) % size_max;
        if (keys[index].empty() || (override_duplicate_key && keys[index] == key))
            return index;
        offset++;
    }
    return -1;
}

void HashTable::insert(const string& key, const int& value) {
    int index = find_index(key,true);
    if (index == -1) {
        cerr << "Table is full!" << endl;
        return;
    }
    keys[index] = key;
    mytrie.insert(key);
    values[index] += value;


}

void FillMap(vector<string> &queries1, vector<string> &queries2,
         vector<int> counts1, vector<int> counts2, int n,
         HashTable &map) {
    for (int i = 0; i < n; i++){
        map.insert(queries1[i],counts1[i]);
    }
    for (int i = 0; i < n; i++){
        map.insert(queries2[i],counts2[i]);
    }
}
