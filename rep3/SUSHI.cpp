#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, price[20], pref[20];
int c[201];

int sushi3() {
    int ret = 0;
    
    for (int budget = 1; budget <= m; budget++) {
        int cand = 0;
        for (int dish = 0; dish < n; dish++) {
            if (budget >= price[dish]) {
                cand = max(cand, c[(budget - price[dish])%201] + pref[dish]);
            }
        }
        c[budget % 201] = cand;
        ret = max(ret, cand);
    }
    
    return ret;
}

void solve() {
    memset(c, 0, sizeof(c));
    cin>>n>>m;
    m /= 100;
    for (int i = 0; i < n; i++) {
        cin>>price[i]>>pref[i];
        price[i] /= 100;
    }
    sushi3();
    
    cout<<c[m % 201]<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
