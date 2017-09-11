#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int mod = 1000000007;

int tile(vector<int> &dp, int i) {
    int &ret = dp[i];
    if (ret != -1) return ret;
    ret = (tile(dp, i - 1) + tile(dp, i - 2)) % mod;
    return ret;
}

void solve() {
    int n;
    cin>>n;
    if (n == 1) {
        cout<<1<<endl;
        return;
    }
    vector<int> dp(n, -1);
    dp[0] = 1; dp[1] = 2;
    cout<<tile(dp, n - 1)<<endl;
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
