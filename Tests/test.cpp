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

template <class DT = std::chrono::milliseconds,
          class ClockT = std::chrono::steady_clock>
class Timer
{
    using timep_t = decltype(ClockT::now());
    
    timep_t _start = ClockT::now();
    timep_t _end = {};

public:
    void tick() { 
        _end = timep_t{};
        _start = ClockT::now(); 
    }
    
    void tock() {
        _end = ClockT::now(); 
    }
    
    template <class duration_t = DT>
    auto duration() const { 
        // Use gsl_Expects if your project supports it.
        assert(_end != timep_t{} && "Timer must toc before reading the time"); 
        return std::chrono::duration_cast<duration_t>(_end - _start); 
    }
};

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
vector <Point <double>> parabola(int n, int h, int seed, int a) {     
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

vector <Point <double>> elipse_border(int n, int h, int seed, int a, int b) {
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

double chan_time(vector <Point <double>> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    chan(points);
    clock.tock();
    return clock.duration().count();
}
double grahan_time(vector <P> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    graham_scan(points);
    clock.tock();
    return clock.duration().count();
}
double monotone_chain_time(vector <P> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    monotone_chain(points);
    clock.tock();
    return clock.duration().count();
}

double jarvis_time(vector <P> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    jarvis_march(points);
    clock.tock();
    return clock.duration().count();
}

double divide_and_conquer_time(vector <P> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    divide_and_conquer(points);
    clock.tock();
    return clock.duration().count();
}

double kirkpatrick_seidel_time(vector <P> points) {
    Timer clock; // Timer<milliseconds, steady_clock>
    clock.tick();
    kirkpatrick_seidel(points);
    clock.tock();
    return clock.duration().count();
}

int main() {
    vector <P> points = elipse(100000, 1000, 12, 1, 1);
    cout << chan_time(points) << endl;
    cout << monotone_chain_time(points) << endl;
    cout << grahan_time(points) << endl;
    cout << jarvis_time(points) << endl;
    cout << divide_and_conquer_time(points) << endl;
    cout << kirkpatrick_seidel_time(points) << endl;
}

