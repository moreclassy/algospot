#include <iostream>
#include <utility>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

const int ALPHABETS = 26;

int toNumber(char ch) {
    return ch - 'a';
}

struct TrieNode {
    TrieNode* children[ALPHABETS];
    int terminal;
    TrieNode* fail;
    vector<int> output;
    int no;
    TrieNode* next[ALPHABETS];
    
    TrieNode() : terminal(-1), fail(NULL), output(0), no(-1) {
        memset(children, 0, sizeof(children));
        memset(next, 0, sizeof(next));
    }
    
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; i++)
            if (children[i])
                delete children[i];
    }
    
    void insert(const char* key, int id) {
        if (*key == 0) {
            terminal = id;
        } else {
            int next = toNumber(*key);
            if (children[next] == NULL) {
                children[next] = new TrieNode();
            }
            children[next]->insert(key + 1, id);
        }
    }
    
    TrieNode* find(const char* key) {
        if (*key == 0) return this;
        int next = toNumber(*key);
        if (children[next] == NULL)
            return NULL;
        return children[next]->find(key + 1);
    }
};

void computeFailFunc(TrieNode* root) {
    queue<TrieNode*> q;
    root->fail = root;
    q.push(root);
    
    while (!q.empty()) {
        TrieNode* here = q.front();
        q.pop();
        
        for (int edge = 0; edge < ALPHABETS; edge++) {
            TrieNode* child = here->children[edge];
            if (!child) continue;
            
            if (here == root) {
                child->fail = root;
            } else {
                TrieNode* t = here->fail;
                while (t != root && t->children[edge] == NULL)
                    t = t->fail;
                if (t->children[edge]) t = t->children[edge];
                child->fail = t;
            }
            
            child->output = child->fail->output;
            if (child->terminal != -1) {
                child->output.push_back(child->terminal);
            }
            
            q.push(child);
        }
    }
}

vector<pair<int, int>> ahoCorasick(const string& s, TrieNode* root) {
    vector<pair<int, int>> ret;
    TrieNode* state = root;
    
    for (int i = 0; i < s.size(); i++) {
        int chr = toNumber(s[i]);
        
        while (state != root && state->children[chr] == NULL)
            state = state->fail;
        
        if (state->children[chr]) state = state->children[chr];
        
        for (int j = 0; j < state->output.size(); j++)
            ret.push_back(make_pair(i, state->output[j]));
    }
    
    return ret;
}

const int MOD = 10007;
int cache[101][1001];
string pattern[100];

int count(int length, TrieNode* state) {
    if (state->output.size()) return 0;
    if (length == 0) return 1;
    
    int& ret = cache[length][state->no];
    if (ret != -1) return ret;
    
    ret = 0;
    
    for (int letter = 0; letter < ALPHABETS; letter++) {
        ret += count(length-1, state->next[letter]);
        ret %= MOD;
    }
    
    return ret;
}

void computeTransition(TrieNode* here, int& nodeCounter) {
    here->no = nodeCounter++;
    
    for (int chr = 0; chr < ALPHABETS; chr++) {
        TrieNode* next = here;
        
        while (next != next->fail && next->children[chr] == NULL)
            next = next->fail;
        
        if (next->children[chr]) next = next->children[chr];
        
        here->next[chr] = next;
        
        if (here->children[chr])
            computeTransition(here->children[chr], nodeCounter);
    }
}

void solve() {
    memset(cache, -1, sizeof(cache));
    int n, m;
    cin>>n>>m;
    
    TrieNode* trie = new TrieNode();
    
    for (int i = 0; i < m; i++) {
        cin>>pattern[i];
        trie->insert(pattern[i].c_str(), i);
    }
    
    computeFailFunc(trie);
    int nodeCounter = 0;
    computeTransition(trie, nodeCounter);
    
    cout<<count(n, trie)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
