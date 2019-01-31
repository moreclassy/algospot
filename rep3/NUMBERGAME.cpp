#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NEGINF = -987654321;
const int MAX_N = 50;
int n;
int board[MAX_N];
vector<vector<int>> cache;

int maxScore(int s, int e) {
    if (s > e) return 0;
    
    int& ret = cache[s][e];
    if (ret > NEGINF) return ret;
    
    ret = NEGINF;
    
    ret = max(ret, board[s] - maxScore(s+1, e));
    ret = max(ret, board[e] - maxScore(s, e-1));
    if (s < e) {
        ret = max(ret, -maxScore(s+2, e));
        ret = max(ret, -maxScore(s, e-2));
    }
    
    return ret;
}

void solve() {
    cin>>n;
    cache = vector<vector<int>>(n, vector<int>(n, NEGINF));
    for (int i = 0; i < n; i++)
        cin>>board[i];
    
    cout<<maxScore(0, n-1)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
