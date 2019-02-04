#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int ceil(int a, int b) {
    return (a + b - 1) / b;
}

vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
    int n = (int)recipe.size();
    int b = recipe[0];
    for (int i = 1; i < n; i++)
        b = gcd(recipe[i], b);
    
    int a = b;
    for (int i = 0; i < n; i++) {
        a = max(a, ceil(put[i] * b, recipe[i]));
    }
    
    vector<int> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = recipe[i] * a / b - put[i];
    }
    
    return ret;
}

void solve() {
    int n; cin>>n;
    
    vector<int> recipe(n);
    for (int i = 0; i < n; i++)
        cin>>recipe[i];
    
    vector<int> put(n);
    for (int i = 0; i < n; i++)
        cin>>put[i];
    
    auto ret = solve(recipe, put);
    
    for (int r : ret)
        cout<<r<<" ";
    cout<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
