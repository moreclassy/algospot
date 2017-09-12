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

	int ret = 0;
	for (int i = 0; i < n; i++) {
		ret = max(ret, findMax(tri, dp, n-1, i));
	}

	cout<<ret<<endl;
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
