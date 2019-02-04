#include <iostream>

using namespace std;

int n, m;
double location[200];

bool decision(double gap) {
    double limit = -1;
    int installed = 0;
    for (int i = 0; i < m; i++) {
        if (limit <= location[i]) {
            installed++;
            limit = location[i] + gap;
        }
    }
    
    return installed >= n;
}

double optimize() {
    double b = 0.0, e = 241.0;
    for (int i = 0; i < 100; i++) {
        double mid = (b + e)/2.0;
        if (decision(mid)) {
            b = mid;
        } else {
            e = mid;
        }
    }
    
    return b;
}

void solve() {
    cin>>n>>m;
    for (int i = 0; i < m; i++)
        cin>>location[i];
    
    cout<<optimize()<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(2);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
