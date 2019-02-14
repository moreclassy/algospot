#include <iostream>
#include <stack>

using namespace std;

bool wellMatched(const string& formula) {
    const string opening("({["), closing(")}]");
    stack<char> openStack;
    for (char f : formula) {
        if (opening.find(f) != string::npos) {
            openStack.push(f);
        } else {
            if (openStack.empty()) return false;
            if (opening.find(openStack.top()) != closing.find(f)) return false;
            openStack.pop();
        }
    }
    
    return openStack.empty();
}

void solve() {
    string input;
    cin>>input;
    
    if (wellMatched(input))
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
