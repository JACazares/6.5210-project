#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator<=(P p) const { return tie(x,y) <= tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	bool operator!=(P p) const { return tie(x,y)!=tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point <long long> IntPoint;
typedef Point <double> RealPoint;
using P = Point<double>;
const double pi = acos(-1);
/// Hull points are taken from the eclipse x^2/a^2 + y^2/b^2 = 1
/// Can also be used for circles with a = b = 1
vector <Point <double>> elipse(int n, int h, int seed, double a, double b) {
    mt19937 generator (seed);
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    while(points.size() < h) {
        double theta = unif(generator) * pi;
        double x = a*cos(theta);
        double y = b*sin(theta);
        points.insert(Point <double> (x, y));
    }
    while(points.size() < n) {
         double x = unif(generator) * a;
         double y = unif(generator) * b;
         if((x/a)*(x/a) + (y/b)*(y/b) <= 1) {
            points.insert(Point <double> (x, y));
         }
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}

// Most points will be on the curve y = 4ax^2
// Other points will be on the curve y = 4ax^2 + 100 which is strictly above 4ax^2
// So most points will be very close to the curve
vector <Point <double>> parabola(int n, int h, int seed, double a) {     
    mt19937 generator (seed);
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    double maxCoord = sqrt(5e8/(4*a));
    while(points.size() < h) {
        double x = unif(generator) * maxCoord;
        double y = 4*a*x*x;
        points.insert(Point <double> (x, y));
    }
    while(points.size() < n) {
        double x = unif(generator) * maxCoord;
        double y = 4*a*x*x + 100;
        points.insert(Point <double> (x, y));
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}

vector <Point <double>> elipse_border(int n, int h, int seed, double a, double b) {
    mt19937 generator (seed);
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    while(points.size() < h) {
        double theta = unif(generator) * pi;
        double x = a*cos(theta);
        double y = b*sin(theta);
        points.insert(Point <double> (x, y));
    }
    while(points.size() < n) {
         double x = unif(generator) * a;
         double y = unif(generator) * b;
         double val = (x/a)*(x/a) + (y/b)*(y/b);
         if(0.9 <= val && val <= 1) {
            points.insert(Point <double> (x, y));
         }
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}

vector <Point <double>> uniCircle(int n, int seed, double radius) {
    return elipse(n, n, seed, radius, radius);
}

/// points enclosed by line mx + c and mx - c
vector <Point <double>> line(int n, int seed, double m, double c) {
    mt19937 generator (seed);
    double maxCoord = (1e9 - c) / m;
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    while(points.size() < n) {
        double x = unif(generator) * maxCoord;
        double y = m * x + unif(generator) * c;
        points.insert(Point <double> (x, y));
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}

vector <Point <double>> randSquare(int n, int seed, double width) {
    mt19937 generator (seed);
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    while(points.size() < n) {
        double x = unif(generator) * (width/2);
        double y = unif(generator) * (width/2);
        points.insert(Point <double> (x, y));
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}

vector <Point <double>> randCircle(int n, int seed, double radius) {
    return elipse(n, 0, seed, radius, radius);
}

vector <Point <double>> sortArray(int n, int seed) {
    return parabola(n, n, seed, 0.25);
}

vector <Point <double>> cluster(int n, int k, int seed) {
    int sz = n / k;
    mt19937 generator (seed);
    uniform_real_distribution <> unif (-1, 1);
    set <Point <double>> points;
    const double maxCoord = 1e5;
    while(points.size() < n) {
        auto block = randSquare(n / k, seed, 1e2);
        double dx = unif(generator) * maxCoord;
        double dy = unif(generator) * maxCoord;
        for(auto [x, y] : block) points.insert(P(x + dx, y + dy));
    }
    vector <Point <double>> dataset (points.begin(), points.end());
    random_shuffle(dataset.begin(), dataset.end());
    return dataset;
}


template <class T> 
int orientation(Point <T> &a, Point <T> &b, Point <T> &c) {
  return sgn((b - a).cross(c - a));
}

template <class T> 
void print_points(vector <Point <T>> points) {
  for(auto pt : points) cout << pt << " ";
  cout << endl;
}
template <class T>
vector <Point <T>> remove_duplicates(vector <Point <T>> points) {
	set <Point <T>> tmp (points.begin(), points.end());
	return vector <Point <T>> (tmp.begin(), tmp.end());
}
template <class T> 
void monotone_chain(vector <Point <T>> &points, vector <Point <T>> &lower, vector <Point <T>> &upper) {
  sort(points.begin(), points.end());
  int n = points.size();
  if(n <= 2) {
    lower = upper = points;
    return ;
  }
  lower = {points[0], points[1]};
  lower.reserve(n);
  for(int i = 2; i < n; i++) {
    auto pt = points[i];
    while(lower.size() >= 2 && orientation(lower[lower.size() - 2], lower[lower.size() - 1], pt) == -1) {
      lower.pop_back();
    }
    lower.push_back(pt);
  }
  upper = {points[n-1], points[n-2]};
  upper.reserve(n);
  for(int i = n-3; i >= 0; i--) { 
    auto pt = points[i];
    while(upper.size() >= 2 && orientation(upper[upper.size() - 2], upper[upper.size() - 1], pt) == -1) {
      upper.pop_back();
    }
    upper.push_back(pt);
  }
}
template <class T> 
vector <Point <T>> monotone_chain(vector <Point <T>> points) {
  vector <Point <T>> lower, upper; 
  monotone_chain(points, lower, upper);
  for(int i = 1; i + 1 < upper.size(); i++) {
    lower.emplace_back(upper[i]);
  }
  return lower;
}

template <class T>
inline bool on_segment(Point <T> A, Point <T> B, Point <T> C) {
	return orientation(A, B, C) == 0 && (B - A).dot(C - A) >= 0 && (B - A).dist2() >= (C - A).dist2();
}

inline double seg_to_point_dist(RealPoint A, RealPoint B, RealPoint C) {
	auto seg = (B - A).unit();
	double dist = fabs(seg.cross(C - A));
	if((B - A).dot(C - A) < 0 || (A - B).dot(C - B) < 0) {
		return min((C - A).dist(), (C - B).dist());
	} else {
		return dist;
	}
}

template <class T>
bool inside(vector <Point <T>> &hull, Point <T> point) {
	int n = hull.size();
	int l = 1, r = n - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(orientation(hull[0], hull[mid], point) == 1) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	if(l == 1) return on_segment(hull[0], hull[1], point); 
	auto A = hull[0];
	auto B = hull[l - 1];
	auto C = hull[l];
	int ab = orientation(A, B, point);
	int bc = orientation(B, C, point);
	int ca = orientation(C, A, point);
	return min({ab, bc, ca}) >= 0;
}

template <class T>
vector <Point <T>> heuristics_quad(vector <Point <T>> points) {
	Point <T> A, B, C, D;
	A = B = C = D = points[0];
	for(auto point : points) {
		if(A.x > point.x) A = point;
		if(B.x < point.x) B = point;
		if(C.y > point.y) C = point;
		if(D.y < point.y) D = point;
	}
	// cout << A << " " << B << " " << C << " " << D << endl;
	// order A -> C -> B -> D
	vector <Point <T>> remaining;
	for(auto i : points) {
		if(i == A || i == B || i == C || i == D) continue;
		auto ac = orientation(A, C, i);
		auto cb = orientation(C, B, i);
		auto bd = orientation(B, D, i);
		auto da = orientation(D, A, i);
		// cout << ac << " " << cb << " " << bd << " " << da << endl;
		if(min({ac, cb, bd, da}) >= 0) continue;
		remaining.emplace_back(i);
	}
	return remaining;
}

template <class T>
vector <Point <T>> heuristics_poly(vector <Point <T>> points, vector <Point <T>> cands) {
	set <Point <T>> cont (cands.begin(), cands.end());
	auto hull = monotone_chain(vector <Point <T>> (cont.begin(), cont.end()));
	vector <Point <T>> rem;
	for(auto i : points) {
		if(cont.find(i) != cont.end()) continue;
		if(inside(hull, i)) continue;
		rem.emplace_back(i);
	}
	return rem;
}

void test_square_on_random_points() {
	int w = 10000;
	int inc = 1000;
	for(int x = 1; x <= 100; x++) {
		int i = x * inc;
		auto dataset = randSquare(i, 29, w);
		auto pruned_1 = heuristics_quad(dataset);
		auto pruned_2 = heuristics_quad(dataset);
		cout << i << " " << pruned_1.size() << " " << pruned_2.size() << " " << (100.0 * pruned_1.size() / i) << endl;
	}
}

void test_circle_on_random_points() {
	int w = 10000;
	for(int x = 1; x <= 6; x++) {
		int i = round(pow(10, x));
		auto dataset = randSquare(i, 212, 1); // elipse(i, 0.05 * i, 29, 4, 13);
		auto actualHull = monotone_chain(dataset);
		P avg (0, 0);
    for(auto pt : dataset) avg = avg + pt;
    avg = avg / i;
    sort(dataset.begin(), dataset.end(), [avg] (auto i, auto j) {
			return i.dist2() > j.dist2(); });
		int k = 1 + log2(i);
		auto select = dataset;
		select.resize(k);
		dataset = heuristics_poly(dataset, select);
		cout << i << " & " << actualHull.size() << " & " << dataset.size() << "\\\\"  << endl;
	}
	/*
	for(int x = 1; x <= 6; x++) {
		int i = round(pow(10, x));
		auto dataset = randCircle(i, 31, 1);

		// sort(dataset.begin(), dataset.end(), [] (auto i, auto j) {
		// 	return i.dist2() > j.dist2(); });
		auto actualHull = monotone_chain(dataset);
		int k = min(i, (int) (i / (1 + log2(i))));
		auto select = dataset;
		select.resize(k);
		auto hull = monotone_chain(select);
		k = hull.size();
		double rad = w;
		for(int j = 0; j < k; j++) {
			auto pt1 = RealPoint(hull[j].x, hull[j].y);
			auto pt2 = RealPoint(hull[(j + 1) % k].x, hull[(j + 1) % k].y);
			rad = min(rad, seg_to_point_dist(pt1, pt2, RealPoint(0, 0)));
		}
		vector <IntPoint> remaining;
		for(auto [x, y] : dataset) {
			if(RealPoint(x, y).dist() < rad) continue;
			remaining.push_back(IntPoint(x, y));
		}
		cout << setprecision(4) << i << " & " << rad << " & " << actualHull.size() << " & " << remaining.size()  << "\\\\" << endl;
  }
  cout << endl;
  */
}

int main() {
	test_circle_on_random_points();
	return 0;
}
