#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getPartialMatch(const string& str) {
    int begin = 1, matched = 0;
    vector<int> pi(str.size(), 0);
    while (begin + matched < str.size()) {
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

// max length of string which is a's suffix and b's prefix
int maxOverlap(const string& a, const string& b) {
    auto pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while (begin < a.size()) {
        if (matched < b.size() && a[begin + matched] == b[matched]) {
            ++matched;
            if (begin + matched == a.size()) return matched;
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
    string input; cin>>input;
    string reversed = input;
    reverse(reversed.begin(), reversed.end());
    
    cout<<input.size() * 2 - maxOverlap(input, reversed)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) solve();
    
    return 0;
}
