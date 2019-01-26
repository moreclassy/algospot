#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

string input;
int cache[10000];
const int INF = 987654321;

int getCost(int idx, int len) {
    bool cost1 = true;
    for (int i = 1; i < len; i++) {
        if (input[idx] != input[idx + i]) {
            cost1 = false;
            break;
        }
    }
    if (cost1) return 1;
    
    bool cost25 = true;
    int gap = input[idx+1] - input[idx];
    for (int i = 1; i < len; i++) {
        if (input[idx + i] - input[idx + i - 1] != gap) {
            cost25 = false;
            break;
        }
    }
    if (cost25) {
        if (abs(gap) == 1) return 2;
        return 5;
    }
    
    bool cost4 = true;
    for (int i = 2; i < len; i++) {
        if (input[idx + i - 2] != input[idx + i]) {
            cost4 = false;
            break;
        }
    }
    if (cost4) return 4;
    
    return 10;
}

int minCost(int idx) {
    if (idx >= input.size()) return 0;
    
    int& ret = cache[idx];
    if (ret != -1) return ret;
    
    ret = INF;
    for (int len = 3; len <= 5; len++) {
        ret = min(ret, getCost(idx, len) + minCost(idx + len));
    }
    
    return ret;
}

void solve() {
    memset(cache, -1, sizeof(cache));
    cin>>input;
    cout<<minCost(0)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
