#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAX_V = 1000;
vector<pair<int, int>> adj[MAX_V];
const int INF = 987654321;

vector<int> dijkstra(int nodeCnt) {
    vector<int> dist(nodeCnt+1, INF);
    priority_queue<pair<int, int>> pq;
    
    pq.push(make_pair(0, 0));
    dist[0] = 0;
    
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        
        if (dist[here] < cost) continue;
        
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            int nextCost = cost + adj[here][i].second;
            
            if (dist[there] > nextCost) {
                dist[there] = nextCost;
                pq.push(make_pair(-nextCost, there));
            }
        }
    }
    
    return dist;
}

void solve() {
    int v, e, n, m;
    cin>>v>>e>>n>>m;
    
    for (int i = 0; i <= v; i++) adj[i] = vector<pair<int, int>>();
    
    for (int i = 0; i < e; i++) {
        int a, b, t;
        cin>>a>>b>>t;
        adj[a].push_back(make_pair(b, t));
        adj[b].push_back(make_pair(a, t));
    }
    
    vector<int> fire(n);
    for (int i = 0; i < n; i++) cin>>fire[i];
    
    int station;
    for (int i = 0; i < m; i++) {
        cin>>station;
        adj[0].push_back(make_pair(station, 0));
    }
    
    auto dist = dijkstra(v);
    
    int ret = 0;
    for (int f : fire) {
        ret += dist[f];
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
