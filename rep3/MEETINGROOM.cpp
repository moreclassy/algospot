#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

vector<vector<int>> adj;

bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second <= b.first || b.second <= a.first;
}

void makeGraph(const vector<pair<int, int>>& meatings) {
    int vars = (int)meatings.size();
    
    adj.clear();
    adj.resize(vars * 2);
    
    for (int i = 0; i < vars; i += 2) {
        int j = i + 1;
        adj[i*2 + 1].push_back(j * 2);
        adj[j*2 + 1].push_back(i * 2);
    }
    
    for (int i = 0; i < vars; i++) {
        for (int j = 0; j < i; j++) {
            if (!disjoint(meatings[i], meatings[j])) {
                adj[i*2].push_back(j*2 + 1);
                adj[j*2].push_back(i*2 + 1);
            }
        }
    }
}

vector<int> sccId;
vector<int> discovered;
stack<int> st;
int sccCnt, vertexCnt;

int scc(int here) {
    int ret = discovered[here] = vertexCnt++;
    st.push(here);
    
    for (int i = 0; i < adj[here].size(); i++) {
        int there = adj[here][i];
        if (discovered[there] == -1) {
            ret = min(ret, scc(there));
        } else if (sccId[there] == -1) {
            ret = min(ret, discovered[there]);
        }
    }
    
    if (ret == discovered[here]) {
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCnt;
            if (t == here) break;
        }
        sccCnt++;
    }
    
    return ret;
}

vector<int> tarjanSCC() {
    sccId = discovered = vector<int>(adj.size(), -1);
    sccCnt = vertexCnt = 0;
    st = stack<int>();
    
    for (int i = 0; i < adj.size(); i++) {
        if (discovered[i] == -1) {
            scc(i);
        }
    }
    
    return sccId;
}

vector<int> solve2SAT() {
    int n = (int)adj.size() / 2;
    vector<int> label = tarjanSCC();
    
    for (int i = 0; i < 2 * n; i += 2) {
        if (label[i] == label[i+1]) {
            return vector<int>();
        }
    }
    
    vector<int> value(2 * n, -1);
    vector<pair<int, int>> order;
    
    for (int i = 0; i < 2 * n; i++) {
        order.push_back(make_pair(-label[i], i));
    }
    
    sort(order.begin(), order.end());
    
    for (int i = 0; i < 2 * n; i++) {
        int vertex = order[i].second;
        int variable = vertex / 2, isTrue = vertex % 2 == 0;
        
        if (value[variable] != -1) continue;
        
        value[variable] = !isTrue;
    }
    
    return value;
}

void solve() {
    int n; cin>>n;
    
    vector<pair<int, int>> meatings(2 * n);
    for (int i = 0; i < 2 * n; i += 2) {
        cin>>meatings[i].first>>meatings[i].second>>meatings[i+1].first>>meatings[i+1].second;
    }
    
    makeGraph(meatings);
    
    vector<int> value = solve2SAT();
    
    if (value.empty()) {
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }
    
    cout<<"POSSIBLE"<<endl;
    for (int i = 0; i < value.size(); i++) {
        if (value[i] == 1) {
            cout<<meatings[i].first<<" "<<meatings[i].second<<endl;
        }
    }
    
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
