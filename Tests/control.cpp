#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using namespace std;

#include "../Algorithms/Kactl/Point.h"
#include "../Algorithms/Kactl/Convex.h"
#include "../Algorithms/Kirkpatrick-Seidel/kirkpatrick-seidel.h"

using P = Point<double>;

int main()
{
	int N;
	cin >> N;
	while(N != 0)
	{
		vector<P> points;
		points.clear();
		for(int i = 0; i < N; i++)
		{
			double x, y;
			cin >> x >> y;
			points.push_back(P(x, y));
		}
		
		vector<P> hull = kactl_convex_hull(points);
					
		cout << hull.size() << "\n";
		for(auto i : hull)
			cout << i.x << " " << i.y << "\n";
		
		cin >> N;
	}
	return 0;
}

