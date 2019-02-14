#include <iostream>
#include <queue>

using namespace std;

struct RNG {
    unsigned seed;
    RNG() : seed(1983) {}
    unsigned next() {
        unsigned ret = seed;
        seed = (seed * 214013u + 2531011u);
        return ret % 10000 + 1;
    }
};

int countRanges(int k, int n) {
    RNG rng;
    int rangeSum = 0;
    queue<int> range;
    int ret = 0;
    
    for (int i = 0; i < n; i++) {
        int newSignal = rng.next();
        rangeSum += newSignal;
        range.push(newSignal);
        
        while (rangeSum > k) {
            rangeSum -= range.front();
            range.pop();
        }
        
        if (rangeSum == k) ret++;
    }
    
    return ret;
}

void solve() {
    int k, n;
    cin>>k>>n;
    
    cout<<countRanges(k, n)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
