#include <iostream>
#include <vector>

using namespace std;

const double rainy = 0.75;
const double sunny = 0.25;

double prob(vector<vector<double>>& dp, int i, int j) {
    if (i < 0 || j < 0 || i < j) return 0;
    double& ret = dp[i][j];
    if (ret >= -0.5) return ret;
    ret = prob(dp, i-2, j-1) * rainy + prob(dp, i-1, j-1) * sunny;
    return ret;
}

void solve() {
    int n, m;
    cin>>n>>m;
	if (m >= n) {
		cout<<1.0<<endl;
		return;
	}

    vector<vector<double>> dp(n, vector<double>(m + 1, -1.0));
    dp[0][0] = 1.0;
    
    double ret = 1.0;
	for (int i = m; i < n; i++) {
		ret -= prob(dp, i, m);
	}
	cout<<ret<<endl;
}

int main() {
    int c;
    cin>>c;

	cout << fixed;         //소수점 고정
	cout.precision(10);
    
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
