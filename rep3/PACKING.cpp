#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, w;
string name[100];
int volume[100];
int score[100];
int cache[1001][100];

const int NEGINF = -987654321;

int findMax(int capa, int idx) {
    if (capa < 0) return NEGINF;
    if (idx == n) return 0;
    
    int& ret = cache[capa][idx];
    if (ret != -1) return ret;
    
    return ret = max(findMax(capa - volume[idx], idx+1) + score[idx], findMax(capa, idx+1));
}

void reconstruct(int capa, int idx, vector<int>& picked) {
    if (idx == n) return;
    
    if (findMax(capa, idx) == findMax(capa, idx+1)) {
        reconstruct(capa, idx+1, picked);
    } else {
        picked.push_back(idx);
        reconstruct(capa - volume[idx], idx+1, picked);
    }
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>n>>w;
    for (int i = 0; i < n; i++) {
        cin>>name[i];
        cin>>volume[i];
        cin>>score[i];
    }
    
    cout<<findMax(w, 0)<<" ";
    vector<int> picked;
    reconstruct(w, 0, picked);
    cout<<picked.size()<<endl;
    for (int idx : picked) {
        cout<<name[idx]<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
