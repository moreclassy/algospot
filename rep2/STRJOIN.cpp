#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <string>

using namespace std;

void solve() {
    int numOfStr;
    cin>>numOfStr;
    
    priority_queue<int> lenQ;
    
    for (int i = 0; i < numOfStr; i++) {
        int len;
        cin>>len;
        lenQ.push(-len);
    }
    
    int totalCost = 0;
    
    while (1) {
        int curCost = lenQ.top();
        lenQ.pop();
        
        if (lenQ.empty())
            break;
        
        curCost += lenQ.top();
        lenQ.pop();
        
        lenQ.push(curCost);
        
        totalCost -= curCost;
    }
    
    cout<<totalCost<<endl;
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
