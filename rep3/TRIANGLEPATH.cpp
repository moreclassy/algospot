#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int triangle[101][101];
int cache[101][101];
int n;

int maxPath(int r, int c) {
    if (r >= n || c > r) return 0;
    
    int& ret = cache[r][c];
    if (ret != -1) return ret;
    
    return ret = triangle[r][c] + max(maxPath(r+1, c), maxPath(r+1, c+1));
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c <= r; c++) {
            cin>>triangle[r][c];
        }
    }
    cout<<maxPath(0, 0)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
