#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct BipartiteUnionFind {
    vector<int> parent, rank, enemy, size;
    
    BipartiteUnionFind (int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u, int v) {
        if (u == -1 || v == -1) return max(u, v);
        
        u = find(u); v = find(v);
        if (u == v) return u;
        
        if (rank[u] > rank[v]) swap(u, v);
        if (rank[u] == rank[v]) rank[v]++;
        parent[u] = v;
        size[v] += size[u];
        return v;
    }
    
    bool dis(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        
        int a = merge(u, enemy[v]);
        int b = merge(v, enemy[u]);
        enemy[a] = b; enemy[b] = a;
        
        return true;
    }
    
    bool ack(int u, int v) {
        u = find(u); v = find(v);
        if (enemy[u] == v) return false;
        
        int a = merge(u, v);
        int b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        if (b != -1) enemy[b] = a;
        
        return true;
    }
};

int maxParty(const BipartiteUnionFind& buf) {
    int ret = 0;
    for (int node = 0; node < buf.parent.size(); node++) {
        if (buf.parent[node] != node) continue;
        
        int enemy = buf.enemy[node];
        if (enemy > node) continue;
        int mySize = buf.size[node];
        int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
        
        ret += max(mySize, enemySize);
    }
    return ret;
}

void solve() {
    int n; cin>>n;
    BipartiteUnionFind buf(n);
    int m; cin>>m;
    string str;
    int u, v, contradictAt = 0;
    for (int i = 0; i < m; i++) {
        cin>>str>>u>>v;
        if (contradictAt) continue;
        if (str == "ACK") {
            if (!buf.ack(u, v))
                contradictAt = i+1;
        } else {
            if (!buf.dis(u, v))
                contradictAt = i+1;
        }
    }
    
    if (contradictAt)
        cout<<"CONTRADICTION AT "<<contradictAt<<endl;
    else
        cout<<"MAX PARTY SIZE IS "<<maxParty(buf)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
