#include <iostream>
#include <cstring>

using namespace std;

int n, d, p;
int t;
bool route[50][50];
int edges[50];
double cache[100][50];

double prisoner(int days, int vil) {
    if (days == 0) {
        return vil == p ? 1 : 0;
    }
    
    double& ret = cache[days][vil];
    if (ret > -0.1) return cache[days][vil];
    
    ret = 0;
    for (int i = 0; i < n; i++) {
        if (!route[vil][i]) continue;
        ret += prisoner(days-1, i) / edges[i];
    }
    
    return ret;
}

void solve() {
    for (int r = 0; r < 100; r++) {
        for (int c = 0; c < 50; c++)
            cache[r][c] = -1.0;
    }
    
    cin>>n>>d>>p;
    for (int r = 0; r < n; r++) {
        int edgeCnt = 0;
        for (int c = 0; c < n; c++) {
            int in; cin>>in;
            if (in) {
                route[r][c] = true;
                edgeCnt++;
            } else {
                route[r][c] = false;
            }
        }
        edges[r] = edgeCnt;
    }
    
    cin>>t;
    for (int i = 0; i < t; i++) {
        int q; cin>>q;
        cout<<prisoner(d, q)<<" ";
    }
    cout<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(8);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
