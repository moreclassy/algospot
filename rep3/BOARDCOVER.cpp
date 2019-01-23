#include <iostream>
#include <utility>

using namespace std;

int h, w;
string board[20];
const int block[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, -1}, {1, 0}}
};

bool isCovered() {
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            if (board[r][c] == '.') return false;
    return true;
}

bool isOut(int r, int c) {
    return r < 0 || r >= h || c < 0 || c >= w;
}

pair<int, int> getNext(const pair<int, int>& point) {
    int r = point.first, c = point.second;
    if (c + 1 < w) return make_pair(r, c+1);
    return make_pair(r+1, 0);
}

bool canPut(int r, int c, int bi) {
    for (int i = 0; i < 3; i++) {
        int nr = r + block[bi][i][0], nc = c + block[bi][i][1];
        if (isOut(nr, nc) || board[nr][nc] == '#') return false;
    }
    return true;
}

void putBlock(int r, int c, int bi, char p) {
    for (int i = 0; i < 3; i++) {
        int nr = r + block[bi][i][0], nc = c + block[bi][i][1];
        board[nr][nc] = p;
    }
}

int countCover(const pair<int, int>& point) {
    if (isCovered()) return 1;
    int r = point.first, c = point.second;
    if (isOut(r, c)) return 0;
    pair<int, int> nextPoint = getNext(point);
    if (board[r][c] == '#') return countCover(nextPoint);
    
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        if (!canPut(r, c, i)) continue;
        putBlock(r, c, i, '#');
        ret += countCover(nextPoint);
        putBlock(r, c, i, '.');
    }
    
    return ret;
}

void solve() {
    cin>>h>>w;
    for (int i = 0; i < h; i++) {
        cin>>board[i];
    }
    
    cout<<countCover(make_pair(0, 0))<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
