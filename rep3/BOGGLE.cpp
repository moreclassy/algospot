#include <iostream>
#include <vector>

using namespace std;

string board[5];
vector<vector<int>> check;
const int dr[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool checkStr(string& str, int idx, int r, int c) {
    if (idx >= str.size()) return true;
    if (r < 0 || r > 4 || c < 0 || c > 4) return false;
    if (board[r][c] != str[idx]) return false;
    if (check[r][c] & (1<<idx)) return false;
    check[r][c] |= (1<<idx);
    
    idx++;
    for (int i = 0; i < 8; i++) {
        if (checkStr(str, idx, r + dr[i], c + dc[i]))
            return true;
    }
    
    return false;
}

bool checkStr(string& str) {
    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 5; c++)
            if (checkStr(str, 0, r, c))
                return true;
    return false;
}

void solve() {
    for (int i = 0; i < 5; i++)
        cin>>board[i];
    
    int n; cin>>n;
    string in;
    for (int i = 0; i < n; i++) {
        check = vector<vector<int>>(5, vector<int>(5, 0));
        cin>>in;
        cout<<in<<(checkStr(in) ? " YES" : " NO")<<endl;
    }
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
