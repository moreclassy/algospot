#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int ALPHABETS = 26;

int toNumber(char c) {
    return c - 'A';
}

vector<string> strs;

struct TrieNode {
    TrieNode* children[ALPHABETS];
    
    int recommend;
    int frequency;
    TrieNode() {
        this->frequency = 0;
        this->recommend = -1;
        memset(children, 0, sizeof(children));
    }
    
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; i++) {
            if (children[i])
                delete children[i];
        }
    }
    
    void insert(int si, int frequency) {
        insert(si, frequency, 0);
    }
    
    void insert(int si, int frequency, int curi) {
        if (curi != 0) {
            if (frequency > this->frequency) {
                recommend = si;
                this->frequency = frequency;
            } else if (frequency == this->frequency) {
                if (strs[si] < strs[recommend]) {
                    recommend = si;
                }
            }
        }
        if (curi >= strs[si].size()) return;
        int num = toNumber(strs[si][curi]);
        if (!children[num]) children[num] = new TrieNode();
        children[num]->insert(si, frequency, curi+1);
    }
    
    int find(string& str) {
        return find(str, 0);
    }
    
    int find(string& str, int curi) {
        if (curi >= str.size()) return 0;
        if (recommend >= 0 && str == strs[recommend]) return 1;
        int num = toNumber(str[curi]);
        if (!children[num]) return -1;
        int childCnt = children[num]->find(str, curi+1);
        return childCnt == -1 ? -1 : childCnt + 1;
    }
};

void solve() {
    strs.clear();
    int n, m;
    cin>>n>>m;
    string str;
    int frequency;
    auto trieRoot = new TrieNode();
    for (int i = 0; i < n; i++) {
        cin>>str>>frequency;
        strs.push_back(str);
        trieRoot->insert((int)strs.size() -1, frequency);
    }
    
    int ret = m - 1;
    for (int i = 0; i < m; i++) {
        cin>>str;
        int cnt = trieRoot->find(str);
        if (cnt == -1) ret += str.size();
        else
            ret += cnt;
    }
    
    cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
