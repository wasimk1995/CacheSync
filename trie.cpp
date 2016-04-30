#include "trie.h"

Trie::Trie(const string & val) {
    value = val;
    flag = false;
}

void Trie::add(char c) {
    if (value == "")
        children[c] = Trie(string(1, c));
    else
        children[c] = Trie(value + c);
}

string Trie::find(const string &word) {
    Trie * node = this;
    int size = word.length();
    for (int i = 0; i < size; i++) {
        const char c = word[i];
        if (node->children.find(c) == node->children.end())
            return "";
        else
            node = &node->children[c];
    }
    return node->value;
}

void Trie::insert(const string &word) {
    Trie * node = this;
    int size = word.length();
    for (int i = 0; i < size; i++) {
        const char c = word[i];
        if (node->children.find(c) == node->children.end())
            node->add(c);
        node = &node->children[c];
    }
    node->flag = true;
}

vector<string> Trie::all_prefixes() {
    vector<string> results;
    if (flag)
        results.push_back(value);

    if (children.size()) {
        map<char, Trie>::iterator iter;
        vector<string>::iterator node;
        for(iter = children.begin(); iter != children.end(); iter++) {
            vector<string> nodes = iter->second.all_prefixes();
            results.insert(results.end(), nodes.begin(), nodes.end());
        }
    }
    return results;
}

vector<string> Trie::autocomplete(const string &prefix) {
    Trie * node = this;
    vector<string> results;
    int size = prefix.length();
    for (int i = 0; i < size; i++) {
        const char c = prefix[i];
        if (node->children.find(c) == node->children.end())
            return results;
        else
            node = &node->children[c];
    }
    return node->all_prefixes();
}
