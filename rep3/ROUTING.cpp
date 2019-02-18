#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>

using namespace std;

const int MAX_V = 10000;
vector<pair<int, double>> adj[MAX_V];
const double INF = pow(10, 300);

double dijkstra(int nodeCnt) {
    vector<double> dist(nodeCnt, INF);
    dist[0] = 1;
    priority_queue<pair<double, int>> pq;
    pq.push(make_pair(-1, 0));
    
    while (!pq.empty()) {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        
        if (dist[here] < cost) continue;
        
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            double nextDist = cost * adj[here][i].second;
            
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
    
    return dist.back();
}

void solve() {
    int n, m;
    cin>>n>>m;
    
    for (int i = 0; i < n; i++)
        adj[i] = vector<pair<int, double>>();
    
    for (int i = 0; i < m; i++) {
        int a, b;
        double d;
        cin>>a>>b>>d;
        adj[a].push_back(make_pair(b, d));
        adj[b].push_back(make_pair(a, d));
    }
    
    cout<<dijkstra(n)<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
