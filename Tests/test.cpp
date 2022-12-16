#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using namespace std;

#include "../Algorithms/Kactl/Point.h"
#include "../Algorithms/Kactl/Convex.h"
#include "../Algorithms/Kirkpatrick-Seidel/kirkpatrick-seidel.h"
#include "../Algorithms/Algorithms_A/Convex_Hull_A.h"

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
		
		vector<P> points_aux;
		copy(points.begin(), points.end(), back_inserter(points_aux));
		//vector<P> hull_jarvis_march = jarvis_march(points_aux);
		points_aux.clear();
		copy(points.begin(), points.end(), back_inserter(points_aux));
		vector<P> hull_monotone_chain = monotone_chain(points_aux);
		points_aux.clear();
		copy(points.begin(), points.end(), back_inserter(points_aux));
		vector<P> hull_graham_scan = graham_scan(points_aux);
		points_aux.clear();
		copy(points.begin(), points.end(), back_inserter(points_aux));
		//vector<P> hull_divide_and_conquer = divide_and_conquer(points_aux);
		points_aux.clear();
		copy(points.begin(), points.end(), back_inserter(points_aux));
		//vector<P> hull_kirkpatrick_seidel = kirkpatrick_seidel(points_aux);
		points_aux.clear();

		//cout << hull_jarvis_march.size() << "\n";
		cout << hull_monotone_chain.size() << "\n";
		cout << hull_graham_scan.size() << "\n";
		//cout << hull_divide_and_conquer.size() << "\n";
		//cout << hull_kirkpatrick_seidel.size() << "\n";
		
		cin >> N;
	}
	return 0;
}
