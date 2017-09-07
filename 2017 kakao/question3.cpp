#include <iostream>
#include <vector>
using namespace std;

vector<int> solution(vector<vector<int> > vs) {
    //vector<vector<int> >의 값은 다음과 같이 읽어올 수 있습니다.
    vector<int> ans(2, 0);
    for (auto v : vs) {
        ans[0] ^= v[0];
        ans[1] ^= v[1];
    }
    return ans;
}
