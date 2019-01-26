#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];
int n;

int countTile(int num) {
    int& ret = cache[num];
    if (ret != -1) return ret;
    
    return ret = (countTile(num-1) + countTile(num-2)) % MOD;
}

int countAsym(int num) {
    if (num < 3) return 0;
    
    int ret = countTile(n);
    ret = (ret + MOD - countTile(n/2)) % MOD;
    if (n%2 == 0)
        ret = (ret + MOD - countTile(n/2 - 1)) % MOD;
    
    return ret;
}

void solve() {
    cin>>n;
    cout<<countAsym(n)<<endl;
}

int main() {
    memset(cache, -1, sizeof(cache));
    cache[0] = 0; cache[1] = 1; cache[2] = 2;
    
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
