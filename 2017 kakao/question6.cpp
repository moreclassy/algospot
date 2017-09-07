#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;

int helper(vector<int>& s, int i, int j) {
    int& ret = dp[i][j];
    if (ret != -1) return ret;
    if (j == 0) {
        ret = max(helper(s, i -1, 0), helper(s, i -1, 1));
    } else {
        ret = helper(s, i -1, 0) + s[i];
    }
    return ret;
}

int solution(vector<int> s)
{
    if (s.size() == 1) return s[0];
    if (s.size() == 2) return max(s[0], s[1]);
    
    // 첫 번째를 선택 안함
    dp = vector<vector<int>>(s.size(), vector<int>(2, -1));
    dp[0][1] = dp[0][0] = 0;
    int answer = max(helper(s, s.size() -1, 0), helper(s, s.size() -1, 1));
    
    // 첫 번째를 선택함
    fill(dp.begin(), dp.end(), vector<int>(2, -1));
    dp[0][0] = 0;
    dp[0][1] = s[0];
    answer = max(answer, helper(s, s.size() -1, 0));
    
    return answer;
}
