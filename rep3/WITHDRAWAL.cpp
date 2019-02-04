#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, k;
int r[1000], c[1000];

bool decision(double average) {
    vector<double> v;
    for (int i = 0; i < n; i++)
        v.push_back(average * c[i] - r[i]);
    sort(v.begin(), v.end());
    
    double sum = 0;
    for (int i = n-k; i < n; i++)
        sum += v[i];
    
    return sum >= 0;
}

double optimize() {
    double lo = -1e-9, hi = 1;
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2.0;
        if (decision(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    return hi;
}

void solve() {
    cin>>n>>k;
    for (int i = 0; i < n; i++) {
        cin>>r[i]>>c[i];
    }
    
    cout<<optimize()<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}
