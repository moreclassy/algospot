#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

const double pi = 2.0 * acos(0);
int n;
double y[100], x[100], r[100];
pair<double, double> ranges[100];

void ConvertToRange()
{
	for (int i = 0; i < n; i++)
	{
		double loc = fmod(2*pi + atan2(y[i], x[i]), 2*pi);
		double range = 2.0 * asin(r[i] / 2.0 / 8.0);
		ranges[i] = make_pair(loc - range, loc + range);
	}
	sort(ranges, ranges + n);
}

const int INF = 987654321;

int SolveLinear(double begin, double end)
{
	int used = 0, idx = 0;

	while (begin < end)
	{
		double maxCover = -1;
		while (idx < n && ranges[idx].first <= begin)
		{
			maxCover = max(maxCover, ranges[idx].second);
			++idx;
		}

		if (maxCover <= begin) return INF;

		begin = maxCover;
		++used;
	}

	return used;
}

int SolveCircular()
{
	int ret = INF;

	for (int i = 0; i < n; i++) if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi)
	{
		double begin = fmod(ranges[i].second, 2*pi);
		double end = fmod(ranges[i].first + 2*pi, 2*pi);
		ret = min(ret, 1 + SolveLinear(begin, end));
	}

	return ret;
}

void Reset()
{
    
}

void GetInput()
{
    cin>>n;
	for (int i = 0; i < n; i++)
		cin>>y[i]>>x[i]>>r[i];
}

void Solve()
{
    Reset();
    GetInput();
    
	ConvertToRange();

	int ret = SolveCircular();

	if (ret < INF)
		cout<<ret<<endl;
	else
		cout<<"IMPOSSIBLE"<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
