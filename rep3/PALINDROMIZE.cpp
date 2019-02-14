#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> getPartialMatch(const string& str) {
    int n = (int)str.size();
    vector<int> pi(n, 0);
    int begin = 1, matched = 0;
    
    while (begin + matched < n) {
        if (str[begin + matched] == str[matched]) {
            matched++;
            pi[begin + matched - 1] = matched;
        } else {
            if (matched == 0) {
                begin++;
            } else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    
    return pi;
}

int maxOverlap(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    auto pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    
    while (begin + matched < n) {
        if (matched < m && a[begin + matched] == b[matched]) {
            matched++;
            if (begin + matched == n)
                return matched;
        } else {
            if (matched == 0) {
                begin++;
            } else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    
    return 0;
}

void solve() {
    string in; cin>>in;
    string rev = in;
    reverse(rev.begin(), rev.end());
    
    cout<<2*(int)in.size() - maxOverlap(in, rev)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
