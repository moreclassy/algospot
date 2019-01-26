#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int n;
int cache[100];

int tileCount(int idx) {
    if (idx == n) return 0;
    if (idx+1 == n) return 1;
    if (idx+2 == n) return 2;
    
    int& ret = cache[idx];
    if (ret != -1) return ret;
    
    ret = 0;
    ret = tileCount(idx+1) + tileCount(idx+2);
    ret %= MOD;
    
    return ret;
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>n;
    cout<<tileCount(0)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
