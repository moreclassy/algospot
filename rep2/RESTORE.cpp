#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>

using namespace std;

vector<string> word;
vector<vector<int>> overlap;
int visited;
vector<vector<int>> dp;

void print(vector<vector<int>>& in) {
    for (auto i : in) {
        for (auto j : i) {
            cout<<j<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}

int countOverlap(string& a, string& b) {
    int maxOverlap = (int)min(a.size(), b.size());
    for (int i = maxOverlap; i > 0; i--) {
        if (a.substr(a.size() - i) == b.substr(0, i))
            return i;
    }
    return 0;
}

void getInput() {
    word = vector<string>();
    auto allword = vector<string>();
    visited = 0;
    
    int k;
    cin>>k;
    
    for (int i = 0; i < k; i++) {
        string input;
        cin>>input;
        allword.push_back(input);
    }
    
    for (int i = 0; i < allword.size(); i++) {
        bool skip = false;
        for (int j = 0; j < allword.size(); j++) {
            if (i == j) continue;
            if (allword[j].find(allword[i]) != string::npos) {
                if (i < j && allword[i] == allword[j]) {
                    continue;
                }
                skip = true;
                break;
            }
        }
        if (skip) continue;
        word.push_back(allword[i]);
    }
    
    overlap = vector<vector<int>>(word.size(), vector<int>(word.size(), -987654321));
    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < word.size(); j++) {
            if (i == j) continue;
            overlap[i][j] = countOverlap(word[i], word[j]);
        }
    }
    
    dp = vector<vector<int>>(word.size(), vector<int>(1<<word.size(), -1));
}

int restore(int last, int used) {
    if (used == (1<<word.size()) - 1) return 0;
    
    int &ret = dp[last][used];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int i = 0; i < word.size(); i++) {
        if (used & (1<<i)) continue;
        ret = max(ret, overlap[last][i] + restore(i, used | (1<<i)));
    }
    
    return ret;
}

string reconstruct(int last, int used) {
    if (used == (1<<word.size()) - 1) return "";
    
    for (int i = 0; i < word.size(); i++) {
        if (used & (1<<i)) continue;
        int ifUsed = overlap[last][i] + restore(i, used | (1<<i));
        if (restore(last, used) == ifUsed)
            return word[i].substr(overlap[last][i]) + reconstruct(i, used | (1<<i));
    }
    
    assert (0);
    return "*****error*****";
}

void solve() {
    getInput();
    
    int totalOverlap = 0;
    int first = 0;
    for (int i = 0; i < word.size(); i++) {
        if (totalOverlap <= restore(i, 1<<i)) {
            totalOverlap = restore(i, 1<<i);
            first = i;
        }
    }
    
    cout<<word[first]<<reconstruct(first, 1<<first)<<endl;
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
