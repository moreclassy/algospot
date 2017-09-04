#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

const int MAX_N = 10000;
int n, m[MAX_N], e[MAX_N];

void Reset()
{
    
}

void GetInput()
{
    cin>>n;
	for (int i = 0; i < n; i++)
		cin>>m[i];
	for (int i = 0; i < n; i++)
		cin>>e[i];
}

void Solve()
{
    Reset();
    GetInput();
    
	vector<pair<int,int> > boxes;

	for (int i = 0; i < n; i++)
		boxes.push_back(pair<int,int>(e[i], m[i]));

	sort(boxes.rbegin(), boxes.rend());

	int total = 0, extra = 0;

	for (int i = 0; i < boxes.size(); i++)
	{
		total += boxes[i].second;
		extra = max(extra - boxes[i].second, boxes[i].first);
	}

	cout<<total + extra<<endl;
}

int main() {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
