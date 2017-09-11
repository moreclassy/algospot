#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int findMax(vector<vector<int>>& tri, vector<vector<int>>& dp, int i, int j) {
    if (i < 0) return 0;
    int &ret = dp[i][j];
    if (ret != -1) return ret;
    if (j > 0) ret = findMax(tri, dp, i-1, j-1);
    if (i-1 >= j) ret = max(ret, findMax(tri, dp, i-1, j));
    ret += tri[i][j];
    return ret;
}

int findPath(vector<vector<int>>& tri, vector<vector<int>>& dp, vector<vector<int>>& path, int i, int j) {
    if (i < 0) return 0;
    int& ret = path[i][j];
    if (ret != -1) return ret;
    if (i == 0) return 1;
    
    int leftVal = 0;
    int leftPath = 0;
    if (j > 0) {
        leftVal = findMax(tri, dp, i-1, j-1);
        leftPath = findPath(tri, dp, path, i-1, j-1);
    }
    int rightVal = 0;
    int rightPath = 0;
    if (i-1 >= j) {
        rightVal = findMax(tri, dp, i-1, j);
        rightPath = findPath(tri, dp, path, i-1, j);
    }
    
    if (leftVal > rightVal) ret = leftPath;
    else if (rightVal > leftVal) ret = rightPath;
    else ret = leftPath + rightPath;
    
    return ret;
}

void solve() {
    int n;
    cin>>n;
    
    vector<vector<int>> tri(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin>>tri[i][j];
        }
    }
    
    vector<vector<int>> dp(n, vector<int>(n, -1));
    dp[0][0] = tri[0][0];
    vector<vector<int>> path(n, vector<int>(n, -1));
    path[0][0] = 1;
    int maxVal = 0;
    int maxPath = 0;
    for (int i = 0; i < n; i++) {
        int nextVal = findMax(tri, dp, n - 1, i);
        if (maxVal < nextVal) {
            maxVal = nextVal;
            maxPath = findPath(tri, dp, path, n - 1, i);
        } else if (maxVal == nextVal) {
            maxPath += findPath(tri, dp, path, n - 1, i);
        }
    }
    cout<<maxPath<<endl;
}

int main()
{
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }
	
	return 0;
}
