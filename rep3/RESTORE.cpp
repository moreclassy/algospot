#include <iostream>
#include <unordered_set>
#include <cstring>
#include <vector>

using namespace std;


const int MAX_N = 15;
int k;
vector<string> word;
int overlap[MAX_N][MAX_N];
int cache[MAX_N][1<<MAX_N];

int restore(int last, int used) {
    if (used == (1<<word.size())-1) return 0;
    
    int& ret = cache[last][used];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int next = 0; next < word.size(); next++) {
        if ((used & (1<<next)) == 0) {
            int cand = overlap[last][next] + restore(next, used | (1<<next));
            ret = max(ret, cand);
        }
    }
    
    return ret;
}

string reconstruct(int last, int used) {
    if (used == (1<<word.size())-1) return "";
    
    for (int next = 0; next < word.size(); next++) {
        if (used & (1<<next)) continue;
        int ifUsed = restore(next, used | (1<<next)) + overlap[last][next];
        
        if (restore(last, used) == ifUsed) {
            return (word[next].substr(overlap[last][next]) + reconstruct(next, used | (1<<next)));
        }
    }
    
    return "#################";
}

int countOverlap(string& a, string& b) {
    int maxOverlap = (int)min(a.size(), b.size());
    for (int i = maxOverlap; i > 0; i--) {
        if (a.substr(a.size() - i) == b.substr(0, i))
            return i;
    }
    return 0;
}

void solve() {
    word = vector<string>();
    memset(cache, -1, sizeof(cache));
    cin>>k;
    
    vector<string> tmp;
    for (int i = 0; i < k; i++) {
        string input; cin>>input;
        bool isSubstr = false;
        for (int s = 0; s < tmp.size(); s++)
            if (tmp[s].find(input) != string::npos) {
                isSubstr = true;
                break;
            }
        if (isSubstr) continue;
        tmp.push_back(input);
    }
    
    int i = 0;
    for (; i < tmp.size(); i++) {
        bool isSubstr = false;
        for (int j = i+1; j < tmp.size(); j++) {
            if (tmp[j].find(tmp[i]) != string::npos) {
                isSubstr = true;
                break;
            }
        }
        if (isSubstr) continue;
        word.push_back(tmp[i]);
    }
    
    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < word.size(); j++) {
            if (i == j) continue;
            overlap[i][j] = countOverlap(word[i], word[j]);
        }
    }
    
    int totalOverlap = 0;
    int first = 0;
    for (int i = 0; i < word.size(); i++) {
        if (totalOverlap < restore(i, (1<<i))) {
            totalOverlap = restore(i, (1<<i));
            first = i;
        }
    }
    
    cout<<word[first]<<reconstruct(first, (1<<first))<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
