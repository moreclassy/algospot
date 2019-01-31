#include <iostream>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

const long long MAX = 3000000000;

int n, k;   // n: 수열 원소 수, k: k 번째 LIS 찾기
int sequence[500];
int subLen[501];    // subLen[i]: i 에서 시작하는 증가수열의 최대 길이
long long lisCnt[501];    // lisCnt[i]: i 에서 시작하는 lis의 갯수

int lis(int start) {
    if (start == n-1) return 1;
    int& ret = subLen[start+1];
    if (ret != -1) return ret;
    
    ret = 1;
    for (int i = start+1; i < n; i++) {
        if (start == -1 || sequence[start] < sequence[i])
            ret = max(ret, 1 + lis(i));
    }
    
    return ret;
}

long long countLis(int start) {
    if (lis(start) == 1) return 1;
    
    long long& ret = lisCnt[start+1];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int i = start+1; i < n; i++) {
        if ((start == -1 || sequence[start] < sequence[i]) && lis(start) == lis(i)+1) {
            ret = min(MAX, ret + countLis(i));
        }
    }
    
    return ret;
}

void reconstruct(int start, int skip, vector<int>& ret) {
    if (start != -1) ret.push_back(sequence[start]);
    
    vector<pair<int, int>> followers;
    for (int next = start+1; next < n; next++) {
        if ((start == -1 || sequence[start] < sequence[next]) && lis(start) == lis(next) + 1) {
            followers.push_back(make_pair(sequence[next], next));
        }
    }
    sort(followers.begin(), followers.end());
    
    for (int i = 0; i < followers.size(); i++) {
        int idx = followers[i].second;
        int cnt = (int)countLis(idx);
        if (cnt <= skip) {
            skip -= cnt;
        } else {
            reconstruct(idx, skip, ret);
            break;
        }
    }
}

void solve() {
    memset(subLen, -1, sizeof(subLen));
    memset(lisCnt, -1, sizeof(lisCnt));
    cin>>n>>k;
    for (int i = 0; i < n; i++) {
        cin>>sequence[i];
    }
    
    cout<<lis(-1) - 1<<endl;
    
    vector<int> ret;
    reconstruct(-1, k, ret);
    for (int r : ret) {
        cout<<r<<" ";
    }
    cout<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
