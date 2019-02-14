#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const int MAXN = 12;

int n, k, m, l;

int prerequisite[MAXN];
int classes[10];
int cache[10][1<<MAXN];

int bitCount(int n) {
    return __builtin_popcount(n);
}

int graduate(int semester, int taken) {
    if (bitCount(taken) >= k) return 0;
    if (semester == m) return INF;
    
    int& ret = cache[semester][taken];
    if (ret != -1) return ret;
    
    ret = INF;
    int canTake = (classes[semester] & ~taken);
    
    for (int i = 0; i < n; i++)
        if ((canTake & (1<<i)) && (taken & prerequisite[i]) != prerequisite[i])
            canTake &= ~(1<<i);
        
    for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
        if (bitCount(take) > l) continue;
        ret = min(ret, graduate(semester+1, taken | take) + 1);
    }
    
    ret = min(ret, graduate(semester+1, taken));
    return ret;
}

void solve() {
    memset(prerequisite, 0, sizeof(prerequisite));
    memset(classes, 0, sizeof(classes));
    memset(cache, -1, sizeof(cache));
    cin>>n>>k>>m>>l;
    
    for (int i = 0; i < n; i++) {
        int r; cin>>r;
        for (int j = 0; j < r; j++) {
            int pre; cin>>pre;
            prerequisite[i] |= (1<<pre);
        }
    }
    
    for (int i = 0; i < m; i++) {
        int c; cin>>c;
        for (int j = 0; j < c; j++) {
            int cl; cin>>cl;
            classes[i] |= (1<<cl);
        }
    }
    
    int ret = graduate(0, 0);
    if (ret >= INF)
        cout<<"IMPOSSIBLE"<<endl;
    else
        cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
