#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int n;
int russia[100], korea[100];

void solve() {
    cin>>n;
    for (int i = 0; i < n; i++)
        cin>>russia[i];
    for (int i = 0; i < n; i++)
        cin>>korea[i];
    
    multiset<int> ratings(korea, korea + n);
    
    int ret = 0;
    for (int r = 0; r < n; r++) {
        if (*ratings.rbegin() < russia[r]) {
            ratings.erase(ratings.begin());
        } else {
            ratings.erase(ratings.lower_bound(russia[r]));
            ret++;
        }
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
