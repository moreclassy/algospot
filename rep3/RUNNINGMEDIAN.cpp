#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

const int mod = 20090711;
const int a0 = 1983;

int getNext(long long pre, long long a, long long b) {
    return (pre*a%mod + b)%mod;
}

void solve() {
    priority_queue< int, vector<int>, less<int> > maxq;
    priority_queue< int, vector<int>, greater<int> > minq;
    int ret = a0, cur = a0;
    maxq.push(cur);
    int n, a, b;
    cin>>n>>a>>b;
    for (int i = 1; i < n; i++) {
        cur = getNext(cur, a, b);
        
        if (cur > maxq.top()) minq.push(cur);
        else maxq.push(cur);
        
        while (maxq.size() -1 > minq.size()) {
            minq.push(maxq.top());
            maxq.pop();
        }
        
        while (maxq.size() < minq.size()) {
            maxq.push(minq.top());
            minq.pop();
        }
        
        ret += maxq.top();
        ret %= mod;
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
