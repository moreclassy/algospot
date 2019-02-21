#include <iostream>
#include <queue>
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

pair<int, int> nodes[500];

struct DisjointSet {
    vector<int> parent;
    
    DisjointSet(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int e) {
        if (parent[e] == e) return e;
        return parent[e] = find(parent[e]);
    }
    
    int merge(int a, int b) {
        return parent[find(a)] = find(b);
    }
};

double nodesDist(int a, int b) {
    return sqrt(pow(nodes[a].first - nodes[b].first, 2) + pow(nodes[a].second - nodes[b].second, 2));
}

void solve() {
    int n, m;
    cin>>n>>m;
    
    for (int i = 0; i < n; i++) cin>>nodes[i].first;
    for (int i = 0; i < n; i++) cin>>nodes[i].second;
    
    DisjointSet ds(n);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin>>a>>b;
        ds.merge(a, b);
    }
    
    vector<pair<double, pair<int, int>>> edges;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (a == b || ds.find(a) == ds.find(b)) continue;
            edges.push_back(make_pair(nodesDist(a, b), make_pair(a, b)));
        }
    }
    sort(edges.begin(), edges.end());
    
    double ret = 0;
    for (int i = 0; i < edges.size(); i++) {
        double cost = edges[i].first;
        int a = edges[i].second.first, b = edges[i].second.second;
        
        if (ds.find(a) == ds.find(b)) continue;
        ds.merge(a, b);
        
        ret += cost;
    }
    
    cout<<ret<<endl;
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
