#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 20;
int candidates[10][46][1024];
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
int q, sum[MAXN*MAXN*2], length[MAXN*MAXN*2], known[MAXN*MAXN*2];
const int WHITE = 1;

void put(int y, int x, int val) {
    for (int r = y; r >= 0; r--)
        if (color[r][x] == WHITE) {
            known[hint[r][x][1]] |= (1<<val);
        } else {
            break;
        }
    for (int r = y+1; r < n; r++)
        if (color[r][x] == WHITE) {
            known[hint[r][x][1]] |= (1<<val);
        } else {
            break;
        }
    
    for (int c = x; c >= 0; c--)
        if (color[y][c] == WHITE) {
            known[hint[y][c][0]] |= (1<<val);
        } else {
            break;
        }
    for (int c = x+1; c < n; c++)
        if (color[y][c] == WHITE) {
            known[hint[y][c][0]] |= (1<<val);
        } else {
            break;
        }
    
    for (int h = 0; h < 2; h++)
        known[hint[y][x][h]] |= (1<<val);
    value[y][x] = val;
}

void remove(int y, int x, int val) {
    for (int r = y; r >= 0; r--)
        if (color[r][x] == WHITE) {
            known[hint[r][x][1]] &= ~(1<<val);
        } else {
            break;
        }
    for (int r = y+1; r < n; r++)
        if (color[r][x] == WHITE) {
            known[hint[r][x][1]] &= ~(1<<val);
        } else {
            break;
        }
    
    for (int c = x; c >= 0; c--)
        if (color[y][c] == WHITE) {
            known[hint[y][c][0]] &= ~(1<<val);
        } else {
            break;
        }
    for (int c = x+1; c < n; c++)
        if (color[y][c] == WHITE) {
            known[hint[y][c][0]] &= ~(1<<val);
        } else {
            break;
        }
    
    for (int h = 0; h < 2; h++)
        known[hint[y][x][h]] &= ~(1<<val);
    value[y][x] = 0;
}

int getCandHint(int hint) {
    return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int y, int x) {
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

int getSize(int mask) {
    return __builtin_popcount(mask);
}

int getSum(int mask) {
    int ret = 0;
    for (int i = 1; i <= 9; i++)
        if (mask & (1<<i))
            ret += i;
    return ret;
}

void printSolution() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout<<value[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

bool search() {
    int y = -1, x = -1, minCands = 1023;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (color[i][j] == WHITE && value[i][j] == 0) {
                int cands = getCandCoord(i, j);
                if (getSize(minCands) > getSize(cands)) {
                    minCands = cands;
                    y = i;
                    x = j;
                }
            }
    
    if (minCands == 0) return false;
    
    if (y == -1) {
        printSolution();
        return true;
    }
    
    for (int val = 1; val <= 9; val++)
        if (minCands & (1<<val)) {
            put(y, x, val);
            if (search()) return true;
            remove(y, x, val);
        }
    
    return false;
}

void solve() {
    memset(color, 0, sizeof(color));
    memset(value, 0, sizeof(value));
    memset(hint, 0, sizeof(hint));
    memset(sum, 0, sizeof(sum));
    memset(length, 0, sizeof(length));
    memset(known, 0, sizeof(known));
    cin>>n;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin>>color[i][j];
    
    cin>>q;
    
    int hintCnt = 0;
    for (int i = 0; i < q; i++) {
        int y, x, direction, s;
        cin>>y>>x>>direction>>s;
        y--; x--;
        int len = 0;
        if (direction == 1) {
            for (int r = y+1; r < n; r++)
                if (color[r][x] == WHITE)
                    len++;
                else
                    break;
        } else {
            for (int c = x+1; c < n; c++)
                if (color[y][c] == WHITE)
                    len++;
                else
                    break;
        }
        
        if (direction == 1) {
            for (int r = y+1; r < n; r++)
                if (color[r][x] == WHITE) {
                    hint[r][x][direction] = hintCnt;
                    sum[hintCnt] = s;
                    length[hintCnt] = len;
                    hintCnt++;
                }
        } else {
            for (int c = x+1; c < n; c++)
                if (color[y][c] == WHITE) {
                    hint[y][c][direction] = hintCnt;
                    sum[hintCnt] = s;
                    length[hintCnt] = len;
                    hintCnt++;
                }
        }
    }
    
    search();
}

void generateCandidates() {
    memset(candidates, 0, sizeof(candidates));
    
    for (int set = 0; set < 1024; set += 2) {
        int l = getSize(set);
        int s = getSum(set);
        int subset = set;
        
        while (true) {
            candidates[l][s][subset] |= (set & ~subset);
            if (subset == 0) break;
            subset = (subset - 1) & set;
        }
    }
}

int main() {
    generateCandidates();
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
