#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

string wild;
string file;
int cache[101][101];

bool isIncluded(int wi, int fi) {
    if (fi >= file.size()) {
        if (wi >= wild.size())
            return true;
        if (wild[wi] == '*')
            return isIncluded(wi+1, fi);
        return false;
    }
    
    int& ret = cache[wi][fi];
    if (ret != -1) return ret;
    
    if (wild[wi] == '*') {
        return ret = isIncluded(wi+1, fi) || isIncluded(wi, fi+1) || isIncluded(wi+1, fi+1);
    }
    
    if (wild[wi] == '?') {
        return ret = isIncluded(wi+1, fi+1);
    }
    
    if (wild[wi] == file[fi]) {
        return ret = isIncluded(wi+1, fi+1);
    }
    
    return ret = false;
}

void solve() {
    cin>>wild;
    int n; cin>>n;
    vector<string> ret;
    for (int i = 0; i < n; i++) {
        memset(cache, -1, sizeof(cache));
        cin>>file;
        if (isIncluded(0, 0))
            ret.push_back(file);
    }
    
    sort(ret.begin(), ret.end());
    for (auto s : ret)
        cout<<s<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
}
