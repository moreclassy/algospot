#include <iostream>

using namespace std;

string input;

string flipQuadTree(int& si) {
    if (input[si] != 'x') return string(1, input[si++]);
    
    si++;
    string lu = flipQuadTree(si);
    string ru = flipQuadTree(si);
    string ld = flipQuadTree(si);
    string rd = flipQuadTree(si);
    
    return "x" + ld + rd + lu + ru;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        cin>>input;
        int si = 0;
        cout<<flipQuadTree(si)<<endl;
    }
    
    return 0;
}
