#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<vector<int>, int> toSort[8];

void precalc(int n) {
    map<vector<int>, int>& toSortN = toSort[n-1];
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    
    queue<vector<int>> q;
    q.push(perm);
    toSortN[perm] = 0;
    
    while (!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        int cost = toSortN[here];
        
        for (int i = 0; i < n; i++) {
            for (int j = i+2; j <= n; j++) {
                reverse(here.begin() + i, here.begin() + j);
                
                if (toSortN.count(here) == 0) {
                    toSortN[here] = cost + 1;
                    q.push(here);
                }
                
                reverse(here.begin() + i, here.begin() + j);
            }
        }
    }
}

void solve() {
    int n; cin>>n;
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        cin>>perm[i];
    }
    
    vector<int> fixed(n);
    
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = 0; j < n; j++) {
            if (perm[j] < perm[i]) smaller++;
        }
        fixed[i] = smaller;
    }
    
    cout<<toSort[n-1][fixed]<<endl;
}

int main() {
    for (int i = 1; i <= 8; i++) {
        precalc(i);
    }
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
