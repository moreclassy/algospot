#include <iostream>
#include <map>

using namespace std;

map<int, int> m;

bool isDominated(int x, int y) {
    auto it = m.lower_bound(x);
    if (it == m.end()) return false;
    return y < it->second;
}

void removeDominated(int x, int y) {
    auto it = m.lower_bound(x);
    if (it == m.begin()) return;
    --it;
    while (true) {
        if (it->second > y) break;
        if (it == m.begin()) {
            m.erase(it);
            break;
        } else {
            auto jt = it;
            --jt;
            m.erase(it);
            it = jt;
        }
    }
}

void solve() {
    int n; cin>>n;
    m.clear();
    int ret = 0, x, y;
    for (int i = 0; i < n; i++) {
        cin>>x>>y;
        if (isDominated(x, y)) {
            ret += m.size();
            continue;
        }
        removeDominated(x, y);
        m[x] = y;
        ret += m.size();
    }
    cout<<ret<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
