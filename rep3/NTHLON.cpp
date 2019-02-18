#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int V = 402;
vector<pair<int, int>> adj[402];
const int START = 401;
const int INF = 987654321;

int vertex(int delta) {
    return delta + 200;
}

vector<int> dijkstra(int src) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));
    
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        
        for (int i = 0; i < (int)adj[here].size(); i++) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;
            
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
    
    return dist;
}

void solve() {
    for (int i = 0; i < V; i++) adj[i] = vector<pair<int, int>>();
    
    int m; cin>>m;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin>>a[i]>>b[i];
        int delta = a[i] - b[i];
        adj[START].push_back(make_pair(vertex(delta), a[i]));
    }
    
    for (int delta = -200; delta <= 200; delta++) {
        for (int i = 0; i < m; i++) {
            int next = delta + a[i] - b[i];
            if (abs(next) > 200) continue;
            adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
        }
    }
    
    vector<int> shortest = dijkstra(START);
    
    int ret = shortest[vertex(0)];
    if (ret == INF) {
        cout<<"IMPOSSIBLE"<<endl;
    } else {
        cout<<ret<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
