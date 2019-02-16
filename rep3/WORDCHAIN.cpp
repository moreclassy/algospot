#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABETS = 26;

vector<vector<int>> adj;
vector<string> graph[ALPHABETS][ALPHABETS];
vector<int> indegree, outdegree;

void makeGraph(int wordCnt) {
    for (int i = 0; i < ALPHABETS; i++) {
        for (int j = 0; j < ALPHABETS; j++) {
            graph[i][j].clear();
        }
    }
    adj = vector<vector<int>>(ALPHABETS, vector<int>(ALPHABETS, 0));
    indegree = outdegree = vector<int>(ALPHABETS, 0);
    
    for (int i = 0; i < wordCnt; i++) {
        string word; cin>>word;
        int a = word[0] - 'a';
        int b = word.back() - 'a';
        graph[a][b].push_back(word);
        adj[a][b]++;
        outdegree[a]++;
        indegree[b]++;
    }
}

void getEulerCircuit(int here, vector<int>& circuit) {
    for (int there = 0; there < ALPHABETS; there++) {
        while (adj[here][there] > 0) {
            adj[here][there]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit() {
    vector<int> circuit;
    
    for (int i = 0; i < ALPHABETS; i++) {
        if (outdegree[i] == indegree[i] + 1) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    
    for (int i = 0; i < ALPHABETS; i++) {
        if (outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    
    return circuit;
}

bool checkEuler() {
    int plus1 = 0, minus1 = 0;
    
    for (int i = 0; i < ALPHABETS; i++) {
        int delta = outdegree[i] - indegree[i];
        if (delta < -1 || delta > 1) return false;
        if (delta == 1) plus1++;
        if (delta == -1) minus1++;
    }
    
    return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

void solve() {
    int n; cin>>n;
    makeGraph(n);
    
    if (!checkEuler()) {
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }
    
    vector<int> circuit = getEulerTrailOrCircuit();

    if (circuit.size() != n + 1) {
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }
    
    reverse(circuit.begin(), circuit.end());
    
    for (int i = 1; i < circuit.size(); i++) {
        int a = circuit[i-1], b = circuit[i];
        if (i != 1) cout<<" ";
        cout<<graph[a][b].back();
        graph[a][b].pop_back();
    }
    cout<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
