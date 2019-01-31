#include <iostream>
#include <vector>

using namespace std;

int n, k, m;
int length[50];
double T[50][50];

vector<vector<double>> multi(vector<vector<double>> W1, vector<vector<double>>& W2) {
    vector<vector<double>> ret(W1.size(), vector<double>(W1.size(), 0));
    
    for (int r = 0; r < W1.size(); r++)
        for (int c = 0; c < W1.size(); c++)
            for (int i = 0; i < W1.size(); i++)
                ret[r][c] += W1[r][i] * W2[i][c];
    
    return ret;
}

vector<vector<double>> mPow(vector<vector<double>>& W, int p) {
    if (p == 1) return W;
    if (p == 0) {
        vector<vector<double>> ret(W.size(), vector<double>(W.size(), 0));
        for (int i = 0; i < W.size(); i++)
            ret[i][i] = 1;
        return ret;
    }
    
    if (p%2) return multi(mPow(W, p/2), W);
    
    auto tmp = mPow(W, p/2);
    
    return multi(tmp, tmp);
}

vector<double> getProb2() {
    vector<vector<double>> W(4*n, vector<double>(4*n, 0));
    
    for (int i = 0; i < 3*n; i++)
        W[i][i+1] = 1.0;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            W[3*n + i][(4 - length[j])*n + j] = T[j][i];
    
    auto Wk = mPow(W, k);
    
    vector<double> ret(n, 0);
    
    for (int song = 0; song < n; song++)
        for (int start = 0; start < length[song]; start++)
            ret[song] += Wk[(3 - start)*n + song][3*n];
    
    return ret;
}

void solve() {
    cin>>n>>k>>m;
    for (int i = 0; i < n; i++)
        cin>>length[i];
    
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            cin>>T[r][c];
    
    auto ret = getProb2();
    
    for (int i = 0; i < m; i++) {
        int song; cin>>song;
        cout<<ret[song]<<" ";
    }
    
    cout<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(8);
    int c; cin>>c;
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
