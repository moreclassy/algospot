#include <iostream>
#include <cstring>

using namespace std;

int cache[100][100];
int board[100][100];
int n;

bool canGo(int r, int c) {
    if (r == n-1 && c == n-1) return 1;
    if (r < 0 || r >= n || c < 0 || c >= n) return 0;
    
    int& ret = cache[r][c];
    if (ret != -1) return ret;
    return ret = canGo(r + board[r][c], c) || canGo(r, c + board[r][c]);
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin>>board[r][c];
        }
    }
    
    cout<<(canGo(0, 0) ? "YES" : "NO")<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
