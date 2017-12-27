#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

const int ALPHABETS = 26;

int n, m;
vector<pair<int, string>> words;

int toNumber(const char c) {
    return c - 'A';
}

struct TrieNode {
    TrieNode* children[ALPHABETS];
    int terminal;
    int first;
    
    TrieNode():terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
    }
    
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; i++) delete children[i];
    }
    
    void insert(const char* key, int id) {
        if (first == -1) first = id;
        if (*key == 0)
            terminal = id;
        else {
            int next = toNumber(*key);
            if (children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1, id);
        }
    }
    
    TrieNode* find(const char* key) {
        if (*key == 0) {
            if (terminal == -1) return NULL;
            else return this;
        }
        int next = toNumber(*key);
        if (children[next] == NULL) return NULL;
        return children[next]->find(key + 1);
    }
    
    int type(const char* key, int id) {
        if (*key == 0) return 0;
        if (first == id) return 1;
        int next = toNumber(*key);
        return 1 + children[next]->type(key + 1, id);
    }
};

void getInput() {
    cin>>n>>m;
    words.clear();
    for (int i = 0; i < n; i++) {
        string second; cin>>second;
        int first; cin>>first;
        words.push_back(make_pair(-first, second));
    }
    sort(words.begin(), words.end());
}

TrieNode* makeTrie() {
    TrieNode* trie = new TrieNode();
    for (int i = 0; i < words.size(); i++)
        trie->insert(words[i].second.c_str(), i);
    trie->first = -1;
    return trie;
}

int countKeys(TrieNode* trie, const char* word) {
    TrieNode* node = trie->find(word);
    if (node == NULL || node->terminal == -1) return (int)strlen(word);
    return trie->type(word, node->terminal);
}

void solve() {
    getInput();
    
    TrieNode* trie = makeTrie();
    
    int ret = m - 1;
    for (int i = 0; i < m; i++) {
        string input; cin>>input;
        ret += countKeys(trie, input.c_str());
    }
    
    cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) solve();
    return 0;
}
