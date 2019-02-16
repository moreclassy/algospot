#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<bool>> adj;

void makeGraph(int n) {
    adj = vector<vector<bool>>(26, vector<bool>(26, false));
    
    string word[2]; cin>>word[0];
    for (int i = 1; i < n; i++) {
        cin>>word[i%2];
        string &prev = word[(i+1)%2], &cur = word[i%2];
        int len = (int)min(prev.size(), cur.size());
        
        for (int k = 0; k < len; k++) {
            if (prev[k] != cur[k]) {
                adj[prev[k] - 'a'][cur[k] - 'a'] = true;
                break;
            }
        }
    }
}

vector<bool> seen;
vector<int> order;

void dfs(int here) {
    seen[here] = true;
    for (int there = 0; there < adj.size(); there++) {
        if (adj[here][there] && !seen[there]) {
            dfs(there);
        }
    }
    order.push_back(here);
}

vector<int> topologicalSort() {
    int n = (int)adj.size();
    seen = vector<bool>(n, false);
    order.clear();
    
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            dfs(i);
        }
    }
    
    reverse(order.begin(), order.end());
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (adj[order[j]][order[i]]) {
                return vector<int>();
            }
        }
    }
    
    return order;
}

void solve() {
    int n; cin>>n;
    makeGraph(n);
    vector<int> sorted = topologicalSort();
    
    if (sorted.empty()) {
        cout<<"INVALID HYPOTHESIS"<<endl;
    } else {
        for (int w : sorted) {
            cout<<(char)('a' + w);
        }
        cout<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
