#include <iostream>
#include <stack>
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
                begin += matched - pi[matched];
                matched = pi[matched];
            }
        }
    }
    
    return pi;
}

void printSuffix(const vector<int>& pi, int len) {
    if (len == 0) return;
    printSuffix(pi, pi[len - 1]);
    cout<<len<<" ";
}

int main() {
    string str1, str2;
    cin>>str1>>str2;
    
    stack<int> ret;
    
    auto pi = getPartialMatch(str1 + str2);
    printSuffix(pi, (int)pi.size());
    
//    int n = (int)pi.size();
//    while (n > 0) {
//        ret.push(n);
//        n = pi[n-1];
//    }
//
//    while (!ret.empty()) {
//        cout<<ret.top()<<" ";
//        ret.pop();
//    }
    
    return 0;
}
