#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int cache[501];
int nums[501];
int n;

int lis(int s) {
    if (s >= n) return 0;
    
    int& ret = cache[s];
    if (ret != -1) return ret;
    ret = 1;
    for (int i = s+1; i < n; i++) {
        if (nums[s] < nums[i]) {
            ret = max(ret, lis(i) + 1);
        }
    }
    
    return ret;
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>nums[i];
    }
    
    int ret = 0;
    for (int i = 0; i < n; i++) {
        ret = max(ret, lis(i));
    }
    cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
