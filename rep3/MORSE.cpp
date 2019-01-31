#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int cache[101][101];
const int M = 1000000000 + 100;

int count(int l, int s) {
    if (l <= 0 || s <= 0) return 1;
    if (l == 1) return s+1;
    if (s == 1) return l+1;
    
    int& ret = cache[l][s];
    if (ret != -1) return ret;
    
    return ret = min(M, count(l-1, s) + count(l, s-1));
}

void findSig(int l, int s, int k, string& ret) {
    if (l == 0) {
        ret += string(s, 'o'); return;
    }
    
    if (k == 0) {
        ret += string(s, 'o') + string(l, '-'); return;
    }
    if (k == 1) {
        ret += string(l, '-') + string(s, 'o'); return;
    }
    
    int lCnt = 0;
    while (count(lCnt, s-1) <= k) {
        k -= count(lCnt++, s-1);
    }
    
    ret += string(l - lCnt, '-') + string(1, 'o');
    findSig(lCnt, s-1, k, ret);
}

void kth(int l, int s, int k, string& ret) {
    if (l == 0) {
        ret += string(s, 'o'); return;
    }
    
    if (k <= count(l-1, s)) {
        ret.push_back('-');
        kth(l-1, s, k, ret);
        return;
    }
    
    ret.push_back('o');
    kth(l, s-1, k - count(l-1, s), ret);
}

void solve() {
    int n, m, k;
    cin>>n>>m>>k;
    string ret;
    kth(n, m, k, ret);
    
    cout<<ret<<endl;
}

int main() {
    memset(cache, -1, sizeof(cache));
    
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
