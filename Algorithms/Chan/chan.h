#include <bits/stdc++.h>
#include "../Kactl/Point.h"

using namespace std;

#define orientation orientation_chan

template <class T> 
int orientation(Point <T> &a, Point <T> &b, Point <T> &c) {
  return sgn((b - a).cross(c - a));
}

template <class T>
void negate_points(vector <Point <T>> &points) {
  for(auto &point : points) {
    point = point * -1;
  }
}

// returns the lower hull
template <class T> 
vector <Point <T>> get_lower_hull(vector <Point <T>> &points) {
  int n = points.size();
  if(n <= 2) {
    return points;
  }
  vector <Point <T>> lower;
  lower = {points[0], points[1]};
  lower.reserve(n);
  for(int i = 2; i < n; i++) {
    auto pt = points[i];
    while(lower.size() >= 2 && orientation(lower[lower.size() - 2], lower[lower.size() - 1], pt) == -1) {
      lower.pop_back();
    }
    lower.push_back(pt);
  }
  return lower;
}

template <class T>
vector <Point <T>> chan_lower_hull(vector <Point <T>> &points, int m) {
  vector <vector <Point <T>>> blocks;
  int N = points.size();
  int K = (N - 1) / m + 1;
  for(int i = 0; i < K; i++) {
    vector <Point <T>> subBlock;
    for(int j = i*m; j < (i + 1) * m && j < N; j++) {
      subBlock.push_back(points[j]);
    }
    blocks.emplace_back(get_lower_hull(subBlock));
  }
  auto start = *min_element(points.begin(), points.end());
  auto current = start;
  vector <int> pt (K);
  vector <Point <T>> hull;
  hull.emplace_back(start);
  while(hull.size() <= m) {
    for(int i = 0; i < K; i++) {
      while(pt[i] < blocks[i].size() && blocks[i][pt[i]] <= current) {
        ++pt[i];
      }
      while(pt[i] + 1 < blocks[i].size() && orientation(current, blocks[i][pt[i]], blocks[i][pt[i] + 1]) == -1) {
        ++pt[i];
      }
    }
    auto nextPoint = current;
    bool firstCand = true;
    for(int i = 0; i < K; i++) {
      if(pt[i] < blocks[i].size()) {
        auto cand = blocks[i][pt[i]];
        int ori = orientation(current, nextPoint, cand);
        if(firstCand) {
          nextPoint = cand;
          firstCand = false;
        } else if (ori == -1) {
          nextPoint = cand;
        } else if (ori == 0 && (current - nextPoint).dist2() > (current - cand).dist2()) {
          nextPoint = cand;
        }
      }
    }
    if(!firstCand) {
      current = nextPoint;
      hull.emplace_back(nextPoint);
    } else {
      break; 
    }
  }
  return hull;
}

template <class T>
vector <Point <T>> chan(vector <Point <T>> &points, int m) {
  int N = points.size();
  int K = (N-1)/m + 1;
  for(int i = 0; i < K; i++) {
    int l = i*m;
    int r = min(N, (i+1)*m);
    sort(points.begin() + l, points.begin() + r);
  }
  vector <Point <T>> lower_hull = chan_lower_hull(points, m);
  negate_points(points);
  for(int i = 0; i < K; i++) {
    int l = i*m;
    int r = min(N, (i+1)*m);
    reverse(points.begin() + l, points.begin() + r);
  }
  vector <Point <T>> upper_hull = chan_lower_hull(points, m);
  negate_points(upper_hull);
  negate_points(points);
  bool isSame = (upper_hull.size() == lower_hull.size());
  for(int i = 0; isSame && i < upper_hull.size(); i++) {
    isSame &= upper_hull[i] == lower_hull[lower_hull.size() - i - 1];
  }
  if(isSame) return lower_hull;
  for(int i = 1; i + 1 < upper_hull.size(); i++) {
    lower_hull.emplace_back(upper_hull[i]);
  }
  return lower_hull;
}

template <class T>
vector <Point <T>> chan(vector <Point <T>> points) {
  int n = points.size();
  for(int m = 2; m <= n; m = min(1LL * m * m, 1LL * n)) {
    auto hull = chan(points, m);
    if(hull.size() <= m) {
      return hull;
    }
  }
  return points;
}

#undef orientation
