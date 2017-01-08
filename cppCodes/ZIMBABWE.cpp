#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>

#define PI 3.14159265

using namespace std;

double p, x, y;

double Theta(double x_, double y_)
{
    double arctan = atan2(x_, y_) * 180.0 / PI;
    
    if (x_ >= 0 && y_ >= 0)
        return arctan;
    if (x_ >= 0 && y_ <= 0)
        return 180 - arctan;
    if (x_ <= 0 && y_ <= 0)
        return 180 + arctan;
    if (x_ <= 0 && y_ <= 0)
        return 360 - arctan;
    
    return arctan;
}

bool IsWhite()
{
    double x_ = x - 50.0, y_ = y - 50.0;
    
    // out of circle or center
    if (x_*x_ + y_*y_ > 50.0*50.0 || (x_ == 0 && y_ == 0))
        return true;
    
    if (Theta(x_, y_) <= p*3.6)
        return false;
    
    return true;
}

void Solve(int caseNum)
{
    cin>>p>>x>>y;
    
    cout<<"Case #"<<caseNum<<": "<<(IsWhite()?"white":"black")<<endl;
}

int main(int argc, const char * argv[]) {
    //freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve(i+1);
    }
    
    //fclose(stdin);	fclose(stdout);
    
    return 0;
}
