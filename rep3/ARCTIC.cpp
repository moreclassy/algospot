#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

int n;
double dist[100][100];
pair<double, double> base[100];

bool decision(double d) {
    vector<bool> visited(n, false);
    visited[0] = true;
    queue<int> q;
    q.push(0);
    int seen = 0;
    
    while (!q.empty()) {
        int here = q.front(); q.pop();
        seen++;
        for (int there = 0; there < n; there++)
            if (!visited[there] && dist[here][there] <= d) {
                visited[there] = true;
                q.push(there);
            }
    }
    
    return seen == n;
}

double optimize() {
    double lo = 0, hi = 1000001.0;
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
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>base[i].first>>base[i].second;
    
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= r; c++)
            dist[r][c] = dist[c][r] = (base[r].first - base[c].first)*(base[r].first - base[c].first) + (base[r].second - base[c].second)*(base[r].second - base[c].second);
    
    cout<<sqrt(optimize())<<endl;
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
