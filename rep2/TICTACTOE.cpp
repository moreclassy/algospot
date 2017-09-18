#include <iostream>
#include <vector>

using namespace std;

int dp[20000];

void print(vector<vector<char>>& g) {
    for (auto row : g) {
        for (auto elm : row) {
            cout<<"["<<elm<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

vector<vector<char>> convert(int n) {
    vector<vector<char>> ret(3, vector<char>(3));
    for (int i = 2; i >= 0; i--) {
        int cur = n % 27;
        for (int j = 2; j >= 0; j--) {
            int elm = cur % 3;
            
            if (elm == 0) ret[i][j] = '.';
            else if (elm == 1) ret[i][j] = 'x';
            else ret[i][j] = 'o';
            
            cur /= 3;
        }
        n /= 27;
    }
    return ret;
}

int convert(vector<vector<char>>& g) {
    int ret = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret *= 3;
            if (g[i][j] == 'x') {
                ret += 1;
            } else if (g[i][j] == 'o') {
                ret += 2;
            }
        }
    }
    return ret;
}

bool isWin(vector<vector<char>>& g, char c) {
    vector<int> row(3, 0);
    vector<int> col(3, 0);
    vector<int> dia(2, 0);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g[i][j] == c) {
                row[i]++;
                col[j]++;
                if (i == j) dia[0]++;
                if (i + j == 2) dia[1]++;
            }
        }
    }
    
    for (auto i : row) if (i == 3) return true;
    for (auto i : col) if (i == 3) return true;
    for (auto i : dia) if (i == 3) return true;
    return false;
}

int game(int i) {
    int& ret = dp[i];
    if (ret != -1) return ret;
    
    vector<vector<char>> g = convert(i);
    if (isWin(g, 'x')) return ret = 1;
    if (isWin(g, 'o')) return ret = 1;
    
    
    
    return ret;
}

void solve() {
    vector<vector<char>> input(3, vector<char>(3));
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin>>input[i][j];
        }
    }
    
}

int main() {
	int c;
	cin>>c;
    
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
	
	for (int i = 0; i < c; i++) {
		solve();
	}

	return 0;
}
