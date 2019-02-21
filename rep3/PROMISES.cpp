#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_V = 200;
int V, adj[MAX_V][MAX_V];
const int INF = 200000000;

bool update(int a, int b, int c) {
    if (adj[a][b] <= c) return false;
    
    for (int x = 0; x < V; x++) {
        for (int y = 0; y < V; y++) {
            adj[x][y] = min(adj[x][y], min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[a][y]));
        }
    }
    
    return true;
}

void floyd() {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void solve() {
    int m, n;
    cin>>V>>m>>n;
    
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = (i == j ? 0 : INF);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        adj[a][b] = adj[b][a] = min(c, min(adj[a][b], adj[b][a]));
    }
    
    floyd();
    
    int ret = 0;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        if (!update(a, b, c)) ret++;
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
