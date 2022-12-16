#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
 
int main()
{
	random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(-10000, 10000);
    uniform_int_distribution<> unif_N(5000, 10000);
	
	int T = 2;
	while(T--)
	{
		int N = unif_N(rd);
		double r = 10;
		cout << N << "\n";
		for(int i = 0; i < N; i++)
		{
			int x = distrib(rd);
			int y = distrib(rd);
			if(x*x + y*y <= r*r)
				cout << x << " " << y << "\n";
		}
	}
	cout << "0\n";
	return 0;
}
