#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

const int INF = 987654321;
const int MAX_V = 2000;
int V, E;
vector<pair<int, int>> adj[MAX_V];
vector<int> weights;
vector<pair<int, pair<int, int>>> edges;

struct DisjointSet {
    vector<int> parent;
    
    DisjointSet(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }
    
    int merge(int a, int b) {
        return parent[find(a)] = find(b);
    }
};

bool hasPath(int lo, int hi) {
    vector<int> visited(V, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            int cost = adj[here][i].second;
            
            if (visited[there] || cost < lo || cost > hi) continue;
            
            if (there == V - 1) return true;
            
            visited[there] = true;
            q.push(there);
        }
    }
    
    return false;
}

int binarySearchMinUpperBound(int low) {
    int lo = low - 1, hi = (int)weights.size();
    
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (hasPath(weights[low], weights[mid])) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    if (hi == weights.size()) return INF;
    
    return weights[hi];
}

int minUpperBound(int low) {
    DisjointSet ds(V);
    
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].first < weights[low]) continue;
        
        ds.merge(edges[i].second.first, edges[i].second.second);
        
        if (ds.find(0) == ds.find(V - 1)) return edges[i].first;
    }
    
    return INF;
}

int minWeightDifference() {
    int ret = INF;
    
    for (int i = 0; i < weights.size(); i++) {
        //ret = min(ret, binarySearchMinUpperBound(i) - weights[i]); // 시간초과
        ret = min(ret, minUpperBound(i) - weights[i]);
    }
    
    return ret;
}

int scanning() {
    int lo = 0, hi = 0, ret = INF;
    
    while (lo < weights.size() && hi < weights.size()) {
        if (hasPath(weights[lo], weights[hi])) {
            ret = min(ret, weights[hi] - weights[lo]);
            lo++;
        } else {
            hi++;
        }
    }
    
    return ret;
}

void solve() {
    cin>>V>>E;
    
    for (int i = 0; i < V; i++) adj[i] = vector<pair<int, int>>();
    weights = vector<int>(E);
    edges = vector<pair<int, pair<int, int>>>();
    
    for (int i = 0; i < E; i++) {
        int a, b;
        cin>>a>>b>>weights[i];
        adj[a].push_back(make_pair(b, weights[i]));
        adj[b].push_back(make_pair(a, weights[i]));
        edges.push_back(make_pair(weights[i], make_pair(a, b)));
    }
    
    sort(weights.begin(), weights.end());
    sort(edges.begin(), edges.end());
    
    //cout<<scanning()<<endl;
    cout<<minWeightDifference()<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
