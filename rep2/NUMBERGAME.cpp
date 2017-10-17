#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num;
vector<vector<int>> dp;
const int UNCALCULATED = -987654321;

int maxGap(int l, int r) {
    if (l > r) return 0;
    
    int &ret = dp[l][r];
    if (ret != UNCALCULATED) return ret;
    
    ret = max(num[l] - maxGap(l + 1, r), num[r] - maxGap(l, r - 1));
    if (r - l + 1 >= 2) {
        ret = max(ret, -maxGap(l + 2, r));
        ret = max(ret, -maxGap(l, r - 2));
    }
    
    return ret;
}

void getInput() {
    int cntOfNum;
    cin>>cntOfNum;
    
    num = vector<int>(cntOfNum);
    
    for (int i = 0; i < cntOfNum; i++)
        cin>>num[i];
}

void solve() {
    getInput();
    
    dp = vector<vector<int>>(num.size(), vector<int>(num.size(), UNCALCULATED));
    
    cout<<maxGap(0, (int)num.size() - 1)<<endl;
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }

	return 0;
}
