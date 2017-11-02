#include <iostream>
#include <vector>

using namespace std;

const int MOD = 20091101;
int n, k;
int psum[100001];

void getInput() {
    cin>>n>>k;
    for (int i = 1; i <= n; i++) {
        int d;
        cin>>d;
        psum[i] = (psum[i-1] + d) % k;
    }
}

int countOne() {
    vector<int> count(k, 0);
    
    for (int i = 0; i <= n; i++)
        count[psum[i]]++;
    
    int ret = 0;
    for (int c : count) {
        if (c > 1) {
            ret = (ret + (c * (c - 1)) / 2) % MOD;
        }
    }
    
    return ret;
}

int countTwo() {
    vector<int> count(n+1, 0);
    
    vector<int> pos(k, -1);
    pos[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        count[i] = count[i-1];
        
        int loc = pos[psum[i]];
        if (loc != -1) count[i] = max(count[i], 1 + count[loc]);
        
        pos[psum[i]] = i;
    }
    
    return count.back();
}

void solve() {
    getInput();
    
    cout<<countOne()<<" "<<countTwo()<<endl;
}

int main() {
    psum[0] = 0;
    
    int t;
    cin>>t;
    
    for (int i = 0; i < t; i++)
        solve();
    
    return 0;
}
