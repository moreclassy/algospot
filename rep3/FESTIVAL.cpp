#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void solve() {
    int n, l;
    cin>>n>>l;
    vector<double> qsum(n+1, 0);
    cin>>qsum[1];
    for (int i = 1; i < n; i++) {
        cin>>qsum[i+1];
        qsum[i+1] += qsum[i];
    }
    
    double ret = INT_MAX;
    for (int i = 0; i <= n - l; i++) {
        for (int j = i + l; j <= n; j++) {
            ret = min(ret, (qsum[j] - qsum[i])/(j-i));
        }
    }
    cout<<ret<<endl;
}

int main() {
    cout << fixed;
    cout.precision(10);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
