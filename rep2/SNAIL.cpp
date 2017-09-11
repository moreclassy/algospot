#include <iostream>
#include <vector>

using namespace std;

const double rainy = 0.75;
const double sunny = 0.35;

double prob(vector<vector<double>>& dp, int i, int j) {
    if (i < 0 || j < 0) return 0;
    double& ret = dp[i][j];
    if (ret > 0) return ret;
    ret = prob(dp, i-1, j-1) * rainy + prob(dp, i-1, j-2) * sunny;
    return ret;
}

void solve() {
    int n, m;
    cin>>n>>m;
    
    vector<vector<double>> dp(m, vector<double>(n, -1.0));
    dp[0][0] = 1.0;
    
    
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
