#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
int isFriend[10][10];

int countPair(int pi, int check) {
    if (check == ((1<<n)-1)) return 1;
    if (pi > n) return 0;
    if (pi == n) return 0;
    if (check & (1<<pi)) return countPair(pi+1, check);
    
    int ret = 0;
    check |= (1<<pi);
    for (int i = pi+1; i < n; i++) {
        if (!isFriend[pi][i]) continue;
        if (check & (1<<i)) continue;
        ret += countPair(pi+1, check | (1<<i));
    }
    
    return ret;
}

void solve() {
    cin>>n>>m;
    memset(isFriend, 0, sizeof(isFriend));
    
    int a, b;
    for (int i = 0; i < m; i++) {
        cin>>a>>b;
        isFriend[a][b] = isFriend[b][a] = true;
    }
    
    cout<<countPair(0, 0)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
