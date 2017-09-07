#include<vector>
using namespace std;

vector<vector<int>> dp;

int helper(vector<vector<int>> &land, int i, int j) {
    if (j < 0 || j >= land[0].size()) return -987654321;
    int& ret = dp[i][j];
    if (ret != -1) return ret;
    ret = 0;
    for (int k = 0; k < 4; k++) {
        if (k == j) continue;
        ret = max(ret, helper(land, i -1, k) + land[i][j]);
    }
    return ret;
}

int solution(vector<vector<int>> land)
{
    dp = vector<vector<int>>(land.size(), vector<int>(4, -1));
    for (int i = 0; i < 4; i++) {
        dp[0][i] = land[0][i];
    }
    int answer = 0;
    for (int i = 0; i < 4; i++) {
        answer = max(answer, helper(land, land.size() -1, i));
    }
    return answer;
}
