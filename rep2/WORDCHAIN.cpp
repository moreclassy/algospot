#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> words;
vector<vector<bool>> adj;
vector<bool> visited;
vector<int> path;
int n;

void getInput() {
    cin>>n;
    
    words = vector<string>(n);
    adj = vector<vector<bool>>(n, vector<bool>(n, false));
    visited = vector<bool>(n, false);
    path.clear();
    
    cin>>words[0];
    for (int i = 1; i < n; i++) {
        cin>>words[i];
        for (int j = 0; j < i; j++) {
            if (words[i].back() == words[j][0])
                adj[i][j] = true;
            if (words[j].back() == words[i][0])
                adj[j][i] = true;
        }
    }
}

void solve() {
    getInput();
    
    for (int i = 0; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) if (
    }
    
}

int main() {
    int c; cin>>c;
    
    for (int i = 0; i < c; i++) solve();
    
    return 0;
}
