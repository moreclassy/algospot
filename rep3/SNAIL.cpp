#include <iostream>
#include <cstring>

using namespace std;

int n, m;
double cache[1001][1001];

double climb(int days, int climbed) {
    if (days == 0) {
        if (climbed == 0) return 1.0;
        return 0.0;
    }
    if (climbed <= 0) return 0.0;
    
    double& ret = cache[days][climbed];
    if (ret > -0.1) return ret;
    
    ret = 0.75 * climb(days-1, climbed-2) + 0.25 * climb(days-1, climbed-1);
    
    return ret;
}

void solve() {
    cin>>n>>m;
    
    double ret = 0.0;
    for (int d = 1; d < m; d++) {
        ret += 0.75 * climb(d, n-2) + climb(d, n-1);
    }
    
    cout<<ret<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    for (int c = 0; c <= 1000; c++) {
        for (int d = 0; d <= 1000; d++) {
            cache[d][c] = -1.0;
        }
    }
    
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
