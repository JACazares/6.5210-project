#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using namespace std;

#include "../Algorithms/Kactl/Point.h"
#include "../Algorithms/Kactl/Convex.h"
#include "../Algorithms/Kirkpatrick-Seidel/kirkpatrick-seidel.h"
#include "../Algorithms/Algorithms_A/Convex_Hull_A.h"
#include "../Algorithms/Chan/chan.h"

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

double chan_time(vector <Point <double>> points) {
    clock_t start = clock();
    chan(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}
double graham_time(vector <P> points) {
    clock_t start = clock();
    graham_scan(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}
double monotone_chain_time(vector <P> points) {
    clock_t start = clock();
    monotone_chain(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

double jarvis_time(vector <P> points) {
    clock_t start = clock();
    jarvis_march(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

double divide_and_conquer_time(vector <P> points) {
    clock_t start = clock();
    divide_and_conquer(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

double kirkpatrick_seidel_time(vector <P> points) {
    clock_t start = clock();
    kirkpatrick_seidel(points);
    clock_t end = clock();
    return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

const string algos[] = {"GS", "MCA", "JM", "DNQ", "KSA", "CA"};
map <string, double> get_times(vector <P> points) {
    map <string, double> time;
    time["GS"] = graham_time(points);
    time["MCA"] = monotone_chain_time(points);
    // time["JM"] = jarvis_time(points);
    time["DNQ"] = divide_and_conquer_time(points);
    // time["KSA"] = kirkpatrick_seidel_time(points);
    time["CA"] = chan_time(points);
    return time;
}

// keeps n = 2^19. 
// changes h from 2^4 to 
void vary_h() {
    int n = 1 << 19;
    int a = 21;
    int b = 13;
    int seed = 10;
    for(int h = 1 << 10; h <= n; h <<= 1) {
        auto points = elipse(n, h, seed++, a, b);
        auto actual_h = kactl_convex_hull(points); 
        cout << actual_h.size() * 100.0 / n  << endl;
    }
    cout << endl;
    
    seed = 10;
    for(int h = 1 << 10; h <= n; h <<= 1) {
        auto points = elipse(n, h, seed++, a, b);
        int iter = 5;
        int tmp = iter;
        double sum = 0;
        while(tmp--) {
            double t = graham_time(points);
            sum += t;
            if(t >= 60000) {
                sum = LLONG_MAX;
                break;
            }
        }
        if(sum >= 60000) break;
        cout << (sum / iter) << endl;
    }
    return ;
}

void benchmark() {
    int n = 1<<19;
    int h = 0.50 * n;
    auto points = randCircle(n, 97, 1e8);
    int iter = 5;
    int tmp = iter;
    double sum = 0;
    while(tmp--) {
        double t = kirkpatrick_seidel_time(points);
        sum += t;
        cout << t << endl;
        if(t >= 60000) {
            sum = LLONG_MAX;
            break;
        }
    }
    cout << (sum / iter) << endl;
}

int main() {
    benchmark();
    return 0;
}

