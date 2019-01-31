#include <iostream>
#include <cstring>

using namespace std;

int n;
int cache[101][101];
const int MOD = 10000000;

int countPoly(int num, int bot) {
    if (num < bot) return 0;
    if (num == bot) return 1;
    if (num < 0) return 0;
    
    if (num == 1) return 1;
    
    int& ret = cache[num][bot];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int pbot = 1; pbot <= num - bot; pbot++) {
        ret += (countPoly(num - bot, pbot) * (bot + pbot - 1)) % MOD;
        ret %= MOD;
    }
    
    return ret;
}

int solve() {
    cin>>n;
    
    int ret = 0;
    for (int bot = 1; bot <= n; bot++) {
        ret += countPoly(n, bot);
        ret %= MOD;
    }
    
    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        cout<<solve()<<endl;
    }
    
    return 0;
}
