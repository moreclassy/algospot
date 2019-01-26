#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int pathVal[100][100];
int pathCnt[100][100];
int triangle[100][100];

int maxPathVal(int r, int c) {
    if (r >= n || c >= n) return 0;
    
    int& ret = pathVal[r][c];
    if (ret != -1) return ret;
    
    return ret = max(maxPathVal(r+1, c), maxPathVal(r+1, c+1)) + triangle[r][c];
}

int countPath(int r, int c) {
    if (r+1 == n || c+1 == n) return 1;
    
    int& ret = pathCnt[r][c];
    if (ret != -1) return ret;
    
    ret = 0;
    
    int downCnt = countPath(r+1, c);
    int downVal = maxPathVal(r+1, c);
    
    int rightCnt = countPath(r+1, c+1);
    int rightVal = maxPathVal(r+1, c+1);
    
    if (downVal > rightVal)
        return ret = downCnt;
    
    if (downVal < rightVal)
        return ret = rightCnt;
    
    return ret = downCnt + rightCnt;
}

void solve() {
    memset(pathVal, -1, sizeof(pathVal));
    memset(pathCnt, -1, sizeof(pathCnt));
    cin>>n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c <= r; c++) {
            cin>>triangle[r][c];
        }
    }
    
    cout<<countPath(0, 0)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
