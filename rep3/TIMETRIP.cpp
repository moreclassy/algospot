#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

const int MAX_V = 101;
int V;
vector<pair<int, int>> adj[MAX_V];
bool reachable[MAX_V][MAX_V];
const int INF = 200000000;

int bellman2(int src, int target) {
    vector<int> upper(V, INF);
    upper[src] = 0;
    
    for (int iter = 0; iter < V-1; iter++) {
        for (int here = 0; here < V; here++) {
            for (int i = 0; i < adj[here].size(); i++) {
                int there = adj[here][i].first;
                int cost = upper[here] + adj[here][i].second;
                upper[there] = min(upper[there], cost);
            }
        }
    }
    
    for (int here = 0; here < V; here++) {
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            int cost = upper[here] + adj[here][i].second;
            if (cost < upper[there]) {
                if (reachable[src][here] && reachable[here][target]) {
                    return -INF;
                }
            }
        }
    }
    
    return upper[target];
}

void floyd() {
    for (int a = 0; a < V; a++)
        for (int b = 0; b < V; b++)
            for (int c = 0; c < V; c++)
                reachable[b][c] = reachable[b][c] || (reachable[b][a] && reachable[a][c]);
}

void solve() {
    int w;
    cin>>V>>w;
    
    for (int i = 0; i < V; i++) {
        adj[i].resize(0);
    }
    
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            if (i == j) reachable[i][j] = true;
            else reachable[i][j] = false;
        }
    
    for (int i = 0; i < w; i++) {
        int a, b, d;
        cin>>a>>b>>d;
        adj[a].push_back(make_pair(b, d));
        reachable[a][b] = true;
    }
    
    floyd();
    
    if (!reachable[0][1]) {
        cout<<"UNREACHABLE"<<endl;
        return;
    }
    
    int past = bellman2(0, 1);
    if (past == -INF) cout<<"INFINITY";
    else cout<<past;
    
    cout<<" ";
    
    for (int i = 0; i < V; i++) {
        for (int e = 0; e < adj[i].size(); e++) {
            adj[i][e].second *= -1;
        }
    }
    
    int future = bellman2(0, 1);
    if (future == -INF) cout<<"INFINITY";
    else cout<<-future;
    
    cout<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
