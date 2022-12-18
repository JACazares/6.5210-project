#include <bits/stdc++.h>
#include "../../Algorithms/Kactl/Point.h"
using namespace std;
const double pi = acos(-1);
typedef Point <double> P;

/// Hull points are taken from the eclipse x^2/a^2 + y^2/b^2 = 1
/// Can also be used for circles with a = b = 1
vector <Point <double>> eclipse(int n, int h, int seed, double a, double b) {
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
    return eclipse(n, 0, seed, radius, radius);
}

vector <Point <double>> sortArray(int n, int seed) {
    return parabola(n, n, seed, 0.25);
}

int main() {
    cout.precision(10);
    auto dataset = randCircle(1e6, 14, 5);
    cout << dataset[1221] << endl;
}
