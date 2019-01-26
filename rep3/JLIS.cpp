#include <iostream>
#include <cstring>
#include <algorithm>
#include <limits>

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int n, m;
int A[101], B[101];
int cache[101][101];

int jlis(int ai, int bi) {
    int& ret = cache[ai+1][bi+1];
    if (ret != -1) return ret;
    
    ret = 2;
    long long a = (ai == -1 ? NEGINF : A[ai]);
    long long b = (bi == -1 ? NEGINF : B[bi]);
    long long last = max(a, b);
    
    for (int i = ai+1; i < n; i++) {
        if (A[i] > last) {
            ret = max(ret, jlis(i, bi) + 1);
        }
    }
    
    for (int i = bi+1; i < m; i++) {
        if (B[i] > last) {
            ret = max(ret, jlis(ai, i) + 1);
        }
    }
    
    return ret;
}


void solve() {
    memset(cache, -1, sizeof(cache));
    
    cin>>n>>m;
    for (int i = 0; i < n; i++)
        cin>>A[i];
    for (int i = 0; i < m; i++)
        cin>>B[i];
    
    cout<<jlis(-1, -1) - 2<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
