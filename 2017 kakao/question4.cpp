#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int helper(vector<vector<int>>& bd, int i, int j) {
    if (bd[i][j] == 0) return 0;
    if (i == 0 || j == 0) return 1;
    int& ret = dp[i][j];
    if (ret != -1) return ret;
    ret = min(helper(bd, i -1, j), helper(bd, i, j -1)) + 1;
    ret = min(ret, helper(bd, i -1, j -1) + 1);
    return ret;
}

int solution(vector<vector<int>> bd)
{
    dp = vector<vector<int>>(bd.size(), vector<int>(bd[0].size(), -1));
    int answer = 0;
    for (int i = 0; i < bd.size(); i++) {
        for (int j = 0; j < bd[i].size(); j++) {
            answer = max(answer, helper(bd, i, j));
        }
    }
    return answer * answer;
}
