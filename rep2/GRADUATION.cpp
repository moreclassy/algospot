#include <iostream>
#include <string>
#include <vector>

using namespace std;

int subjects = 0, need = 0, termcnt = 0, step = 0;
int pre[12];
int term[10];

void solve() {
    cin>>subjects>>need>>termcnt>>step;
    
    for (int i = 0; i < subjects; i++) {
        pre[i] = 0;
        int precnt;
        cin>>precnt;
        for (int j = 0; j < precnt; j++) {
            int tpre;
            cin>>tpre;
            pre[i] |= (1 << tpre);
        }
    }
    
    for (int i = 0; < termcnt; i++) {
        int scnt;
        cin>>scnt;
        term[i] = 0;
        for (int j = 0; j < scnt; j++) {
            
        }
    }
}

int main()
{
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }
	
	return 0;
}
