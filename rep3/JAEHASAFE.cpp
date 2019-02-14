#include <iostream>
#include <algorithm>

using namespace std;

int countDial(const string& prev, const string& next) {
    int find = (int)(prev + prev).find(next);
    return find;
}

void solve() {
    int n; cin>>n;
    string input[2];
    cin>>input[0];
    
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        cin>>input[i%2];
        if (i%2 == 0)
            ret += countDial(input[(i+1)%2], input[i%2]);
        else
            ret += countDial(input[i%2], input[(i+1)%2]);
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
