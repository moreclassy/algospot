#include <iostream>
#include <vector>

using namespace std;

vector<int> getPartialMatch(const string& str) {
    int begin = 1, matched = 0;
    vector<int> pi(str.size(), 0);
    
    while (begin + matched < str.size()) {
        if (str[matched] == str[begin + matched]) {
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

void getReversedNames(vector<int>& pi, int len, vector<int>& names) {
    if (len == 0) return;
    int p = pi[len - 1];
    if (p == 0) return;
    names.push_back(p);
    getReversedNames(pi, p, names);
}

int main() {
    string father; cin>>father;
    string mother; cin>>mother;
    
    string str = father + mother;
    
    auto pi = getPartialMatch(str);
    vector<int> names;
    int k = (int)str.size();
    while (k > 0) {
        names.push_back(k);
        k = pi[k - 1];
    }
    
    for (int i = (int)names.size() - 1; i >= 0; i--)
        cout<<names[i]<<' ';
    
    return 0;
}
