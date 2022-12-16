#include <bits/stdc++.h>
#include "../Kactl/Point.h"

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

using P = Point<double>;

vector<P> find_upper_bridge(vector<P> points, int lft, int rgt, double median)
{
	/*
	for(int i = lft; i <= rgt; i++)
		cerr << points[i] << ", ";
	cerr << "\n";
	// */
	
	if(lft+1 == rgt)
	{
		if(points[lft] < points[rgt])
			return {points[rgt], points[lft]};
		else
			return {points[lft], points[rgt]};
	}
		
	vector<P> candidates;
	if((rgt-lft+1)%2 == 1)
		candidates.push_back(points[rgt]);
	
	vector<pair<P, P>> slopes;
	for(int i = lft; i <= rgt; i += 2)
	{
		if(i == rgt)
			break;
		if(points[i].x == points[i+1].x)
		{
			if(points[i].y > points[i+1].y)
				candidates.push_back(points[i]);
			else
				candidates.push_back(points[i+1]);
		}
		else
		{
			if(points[i].x < points[i+1].x)
				slopes.push_back({points[i], points[i+1]});
			else
				slopes.push_back({points[i+1], points[i]});
		}
	}
	
	if(!slopes.empty())
	{
		auto slope_cmp = [](pair<P, P> _a, pair<P, P> _b)
		{
			return (_a.second.y - _a.first.y) * (_b.second.x - _b.first.x) < 
					(_b.second.y - _b.first.y) * (_a.second.x - _a.first.x);
		};
		int mid = slopes.size() / 2;
		nth_element(slopes.begin(), slopes.begin() + mid, slopes.end(), slope_cmp);
		pair<P, P> k = slopes[mid];
		
		auto pnt_slope_cmp = [k](P _a, P _b)
		{
			double dy = k.second.y - k.first.y;
			double dx = k.second.x - k.first.x;
			
			return dx*_a.y - dy*_a.x < dx*_b.y - dy*_b.x;
		};
		P max_k = *max_element(next(points.begin(), lft), next(points.begin(), rgt+1), pnt_slope_cmp);
		
		vector<P> sup_line;
		auto max_pnt_slope_cmp = [k, max_k](P _a)
		{
			double dy = k.second.y - k.first.y;
			double dx = k.second.x - k.first.x;
			
			return dx*_a.y - dy*_a.x == dx*max_k.y - dy*max_k.x;
		};
		copy_if(next(points.begin(), lft), next(points.begin(), rgt+1), back_inserter(sup_line), max_pnt_slope_cmp);
		
		auto [minim, maxim] = minmax_element(begin(sup_line), end(sup_line),
			[](P _a, P _b) {return _a.x < _b.x;});
		
		if(minim -> x <= median && maxim -> x > median)
			return {*maxim, *minim};
		else if(maxim -> x <= median)
		{
			for(auto i : slopes)
			{
				double slp1 = (i.second.y - i.first.y) * (k.second.x - k.first.x);
				double slp2 = (k.second.y - k.first.y) * (i.second.x - i.first.x);
				
				if(slp1 >= slp2)
					candidates.push_back(i.second);
				else
				{
					candidates.push_back(i.first);
					candidates.push_back(i.second);
				}
			}
		}
		else
		{
			for(auto i : slopes)
			{
				double slp1 = (i.second.y - i.first.y) * (k.second.x - k.first.x);
				double slp2 = (k.second.y - k.first.y) * (i.second.x - i.first.x);
				
				if(slp1 <= slp2)
					candidates.push_back(i.first);
				else
				{
					candidates.push_back(i.first);
					candidates.push_back(i.second);
				}
			}
		}
	}
	
	return find_upper_bridge(candidates, 0, candidates.size() - 1, median);
}

vector<P> find_lower_bridge(vector<P> points, int lft, int rgt, double median)
{
	/*
	for(int i = lft; i <= rgt; i++)
		cerr << points[i] << ", ";
	cerr << "\n";
	// */
	if(lft+1 == rgt)
	{
		if(points[lft] < points[rgt])
			return {points[lft], points[rgt]};
		else
			return {points[rgt], points[lft]};
	}
		
	vector<P> candidates;
	if((rgt-lft+1)%2 == 1)
		candidates.push_back(points[rgt]);
	
	vector<pair<P, P>> slopes;
	for(int i = lft; i <= rgt; i += 2)
	{
		if(i == rgt)
			break;
		if(points[i].x == points[i+1].x)
		{
			if(points[i].y > points[i+1].y)
				candidates.push_back(points[i+1]);
			else
				candidates.push_back(points[i]);
		}
		else
		{
			if(points[i].x < points[i+1].x)
				slopes.push_back({points[i], points[i+1]});
			else
				slopes.push_back({points[i+1], points[i]});
		}
	}
	
	if(!slopes.empty())
	{
		auto slope_cmp = [](pair<P, P> _a, pair<P, P> _b)
		{
			return (_a.second.y - _a.first.y) * (_b.second.x - _b.first.x) < 
					(_b.second.y - _b.first.y) * (_a.second.x - _a.first.x);
		};
		int mid = slopes.size() / 2;
		nth_element(slopes.begin(), slopes.begin() + mid, slopes.end(), slope_cmp);
		pair<P, P> k = slopes[mid];
		
		auto pnt_slope_cmp = [k](P _a, P _b)
		{
			double dy = k.second.y - k.first.y;
			double dx = k.second.x - k.first.x;
			
			return dx*_a.y - dy*_a.x < dx*_b.y - dy*_b.x;
		};
		P min_k = *min_element(next(points.begin(), lft), next(points.begin(), rgt+1), pnt_slope_cmp);
		
		vector<P> sup_line;
		auto min_pnt_slope_cmp = [k, min_k](P _a)
		{
			double dy = k.second.y - k.first.y;
			double dx = k.second.x - k.first.x;
			
			return dx*_a.y - dy*_a.x == dx*min_k.y - dy*min_k.x;
		};
		copy_if(next(points.begin(), lft), next(points.begin(), rgt+1), back_inserter(sup_line), min_pnt_slope_cmp);
		
		auto [minim, maxim] = minmax_element(begin(sup_line), end(sup_line),
			[](P _a, P _b) {return _a.x < _b.x;});
		
		if(minim -> x <= median && maxim -> x > median)
			return {*minim, *maxim};
		else if(maxim -> x <= median)
		{
			for(auto i : slopes)
			{
				double slp1 = (i.second.y - i.first.y) * (k.second.x - k.first.x);
				double slp2 = (k.second.y - k.first.y) * (i.second.x - i.first.x);
				
				if(slp1 <= slp2)
					candidates.push_back(i.second);
				else
				{
					candidates.push_back(i.first);
					candidates.push_back(i.second);
				}
			}
		}
		else
		{
			for(auto i : slopes)
			{
				double slp1 = (i.second.y - i.first.y) * (k.second.x - k.first.x);
				double slp2 = (k.second.y - k.first.y) * (i.second.x - i.first.x);
				
				if(slp1 >= slp2)
					candidates.push_back(i.first);
				else
				{
					candidates.push_back(i.first);
					candidates.push_back(i.second);
				}
			}
		}
	}
	return find_lower_bridge(candidates, 0, candidates.size() - 1, median);
}

vector<P> find_upper_hull(vector<P> points, int lft, int rgt)
{
	if(lft == rgt)
		return {points[lft]};
	else if(lft + 1 == rgt)
	{
		if(points[lft].x == points[rgt].x)
		{
			if(points[lft].y < points[rgt].y)
				return {points[rgt]};
			else
				return {points[lft]};
		}
		else if(points[lft] < points[rgt])
			return {points[rgt], points[lft]};
		else
			return {points[lft], points[rgt]};
	}
	
	auto minim = min_element(next(points.begin(), lft), next(points.begin(), rgt+1),
		[](P _a, P _b) {return (_a.x == _b.x ? _a.y > _b.y : _a.x < _b.x); });
	swap(points[lft], *minim);
	auto maxim = max_element(next(points.begin(), lft), next(points.begin(), rgt+1),
		[](P _a, P _b) {return (_a.x == _b.x ? _a.y < _b.y : _a.x < _b.x); });
	swap(points[lft+1], *maxim);
	
	for(int i = lft + 2; i <= rgt; i++)
		while(i <= rgt && (points[i].x == points[lft].x || points[i].x == points[lft+1].x))
			swap(points[i], points[rgt--]);
		
	if(lft == rgt)
		return {points[lft]};
	else if(lft + 1 == rgt)
	{
		if(points[lft].x == points[rgt].x)
		{
			if(points[lft].y < points[rgt].y)
				return {points[rgt]};
			else
				return {points[lft]};
		}
		else if(points[lft] < points[rgt])
			return {points[rgt], points[lft]};
		else
			return {points[lft], points[rgt]};
	}
	
	int mid = lft + (rgt-lft)/2;
	nth_element(points.begin()+lft, points.begin()+mid, points.begin()+rgt+1);
	vector<P> bridge = find_upper_bridge(points, lft, rgt, points[mid].x);
	
	/*
	for(int i = lft; i <= rgt; i++)
		cerr << points[i] << ", ";
	cerr << "BRIDGE: " << bridge[0] << ", " << bridge[1] << "\n";
	// */
	
	int lcnt = lft;
	for(int i = lft; i <= rgt; i++)
		if(points[i].x < bridge[1].x || points[i] == bridge[1])
			swap(points[lcnt++], points[i]);

	int rcnt = lcnt;
	for(int i = lcnt; i <= rgt; i++)
		if(points[i].x > bridge[0].x || points[i] == bridge[0])
			swap(points[rcnt++], points[i]);
	
	vector<P> lft_hull, rgt_hull;
	lft_hull = find_upper_hull(points, lft, lcnt-1);
	rgt_hull = find_upper_hull(points, lcnt, rcnt-1);
	
	vector<P> hull;
	hull.insert(hull.end(), rgt_hull.begin(), rgt_hull.end());
	hull.insert(hull.end(), lft_hull.begin(), lft_hull.end());
	
	return hull;
}

vector<P> find_lower_hull(vector<P> points, int lft, int rgt)
{
	if(lft == rgt)
		return {points[lft]};
	else if(lft + 1 == rgt)
	{
		if(points[lft].x == points[rgt].x)
		{
			if(points[lft].y < points[rgt].y)
				return {points[lft]};
			else
				return {points[rgt]};
		}
		else if(points[lft] < points[rgt])
			return {points[lft], points[rgt]};
		else
			return {points[rgt], points[lft]};
	}
	
	auto minim = min_element(next(points.begin(), lft), next(points.begin(), rgt+1),
		[](P _a, P _b) {return (_a.x == _b.x ? _a.y < _b.y : _a.x < _b.x); });
	swap(points[lft], *minim);
	auto maxim = max_element(next(points.begin(), lft), next(points.begin(), rgt+1),
		[](P _a, P _b) {return (_a.x == _b.x ? _a.y > _b.y : _a.x < _b.x); });
	swap(points[lft+1], *maxim);
	
	for(int i = lft + 2; i <= rgt; i++)
		while(i <= rgt && (points[i].x == points[lft].x || points[i].x == points[lft+1].x))
			swap(points[i], points[rgt--]);
	
	if(lft == rgt)
		return {points[lft]};
	else if(lft + 1 == rgt)
	{
		if(points[lft].x == points[rgt].x)
		{
			if(points[lft].y < points[rgt].y)
				return {points[lft]};
			else
				return {points[rgt]};
		}
		else if(points[lft] < points[rgt])
			return {points[lft], points[rgt]};
		else
			return {points[rgt], points[lft]};
	}
	
	int mid = lft + (rgt-lft)/2;
	nth_element(points.begin()+lft, points.begin()+mid, points.begin()+rgt+1);
	vector<P> bridge = find_lower_bridge(points, lft, rgt, points[mid].x);
	
	/*
	for(int i = lft; i <= rgt; i++)
		cerr << points[i] << ", ";
	cerr << "BRIDGE: " << bridge[0] << ", " << bridge[1] << "\n";
	// */
	
	int lcnt = lft;
	for(int i = lft; i <= rgt; i++)
		if(points[i].x < bridge[0].x || points[i] == bridge[0])
			swap(points[lcnt++], points[i]);

	int rcnt = lcnt;
	for(int i = lcnt; i <= rgt; i++)
		if(points[i].x > bridge[1].x || points[i] == bridge[1])
			swap(points[rcnt++], points[i]);
	
	vector<P> lft_hull, rgt_hull;
	lft_hull = find_lower_hull(points, lft, lcnt-1);
	rgt_hull = find_lower_hull(points, lcnt, rcnt-1);
	
	vector<P> hull;
	hull.insert(hull.end(), lft_hull.begin(), lft_hull.end());
	hull.insert(hull.end(), rgt_hull.begin(), rgt_hull.end());
	
	return hull;
}

vector<P> kirkpatrick_seidel(vector<P> points)
{
	vector<P> lower_hull = find_upper_hull(points, 0, points.size() - 1);
	vector<P> upper_hull = find_lower_hull(points, 0, points.size() - 1);
	vector<P> hull;
	hull.clear();
	hull.insert(hull.end(), upper_hull.begin(), upper_hull.end());
	
	int lshift = 0, rshift = 0;
	if(lower_hull[0] == upper_hull[upper_hull.size() - 1])
		lshift = 1;
	if(lower_hull[lower_hull.size() - 1] == upper_hull[0])
		rshift = 1;
	hull.insert(hull.end(), lower_hull.begin() + lshift, lower_hull.end() - rshift);
	
	return hull;
}
