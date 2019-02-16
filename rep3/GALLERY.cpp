#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[1000];
vector<bool> visited;
const int UNWATCHED = 0, WATCHED = 1, INSTALLED = 2;
int installed;

int dfs(int here) {
    visited[here] = true;
    int children[3] = {0, 0, 0};
    
    for (int i = 0; i < adj[here].size(); i++) {
        int there = adj[here][i];
        if (!visited[there])
            ++children[dfs(there)];
    }
    
    if (children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    
    if (children[INSTALLED]) {
        return WATCHED;
    }
    
    return UNWATCHED;
}

void solve() {
    int g, h;
    cin>>g>>h;
    
    for (int i = 0; i < g; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < h; i++) {
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    visited = vector<bool>(g, false);
    installed = 0;
    
    for (int u = 0; u < g; u++) {
        if (!visited[u] && dfs(u) == UNWATCHED) {
            ++installed;
        }
    }
    
    cout<<installed<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
