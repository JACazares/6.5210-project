#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int main()
{
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(-10000, 10000);
    uniform_int_distribution<> unif_N(5000, 10000);
	
	int T = 2;
	while(T--)
	{
		int N = unif_N(rd);
		cout << N << "\n";
		for(int i = 0; i < N; i++)
			cout << distrib(rd) << " " << distrib(rd) << "\n";
	}
	cout << "0\n";
	return 0;
}
