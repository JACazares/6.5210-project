#include<bits/stdc++.h>

#include "../Kactl/Point.h"

using namespace std;

typedef Point<double> P;


int isright(P p, P q, P r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    return val > 0 || val == 0 && (q.x - p.x) * (r.x - q.x) > 0;
}
int orientation(P p, P q, P r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: -1; // clock or counterclock wise
}

vector<P> jarvis_march(vector<P> v){
    int n = v.size();
    if(n <= 2) return v;

    P X = *min_element(v.begin(),v.end());  //leftmost P
    vector<P> ans;
    while(1){
        ans.push_back(X);
        P enp = v[0];
        for (int j = 0; j < n; j++)
            if (enp == X || isright(X, enp, v[j]))
                enp = v[j];
        X = enp;
        if(X == ans[0]) return ans;
    }
}

vector<P> monotone_chain(vector<P> A)
{
    int n = A.size(), k = 0;

    if (n <= 2)
        return A;

    vector<P> ans(2 * n);

    // Sort points lexicographically
    sort(A.begin(), A.end());

    //Lower Hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && isright(ans[k - 2],
                          ans[k - 1], A[i]) >= 0)
            k--;
        ans[k++] = A[i];
    }

    // Upper hull
    for (size_t i = n - 1, t = k + 1; i > 0; --i) {
        while (k >= t && isright(ans[k - 2],
                           ans[k - 1], A[i - 1]) >= 0)
            k--;
        ans[k++] = A[i - 1];
    }
    ans.resize(k - 1);

    return ans;
}

P p0;

bool compare(P &p1, P &p2)
{
   int o = orientation(p0, p1, p2);
   if (o == 0)
     return ((p0-p2).dist2() >= (p0-p1).dist2()) ? true : false;

   return (o == -1)? true: false;
}
vector<P> graham_scan(vector<P> A)
{
   int n = A.size();
   double xmin = A[0].x;
   int min = 0;
   for (int i = 1; i < n; i++)
   {
     int x = A[i].x;
     if ((x < xmin) || (xmin == x &&
         A[i].y < A[min].y))
        xmin = A[i].x, min = i;
   }

   swap(A[0], A[min]);

   p0 = A[0];
   sort(A.begin()+1, A.end(), compare);
   int m = 1;
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(p0, A[i],
                                    A[i+1]) == 0)
          i++;
       A[m] = A[i];
       m++;
   }
    while(A.size() > m) A.pop_back();
    if(m <= 2) {
        return A;
    }
   vector<P> S;
   S.push_back(A[0]);
   S.push_back(A[1]);
   S.push_back(A[2]);
   for (int i = 3; i < m; i++)
   {
      while (S.size()>1 && orientation(S[S.size()-2], S.back(), A[i]) != -1)
         S.pop_back();
      S.push_back(A[i]);
   }
    return S;
}
P mid;

int quad(P p)
{
    if (p.x >= 0 && p.y >= 0)
        return 1;
    if (p.x <= 0 && p.y >= 0)
        return 2;
    if (p.x <= 0 && p.y <= 0)
        return 3;
    return 4;
}


bool compare_1(P p1, P q1)
{
    P p = p1-mid;
    P q = q1-mid;

    int one = quad(p);
    int two = quad(q);

    if (one != two)
        return (one < two);
    return (p.y*q.x < q.y*p.x);
}

vector<P> merger(vector<P> a,
                              vector<P > b)
{
    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;
    for (int i=1; i<n1; i++)
        if (a[i].x > a[ia].x)
            ia = i;

    for (int i=1; i<n2; i++)
        if (b[i].x < b[ib].x)
            ib=i;

    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >=0)
            inda = (inda + 1) % n1;

        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <=0)
        {
            indb = (n2+indb-1)%n2;
            done = 0;
        }
    }


    int uppera = inda, upperb = indb;
    inda = ia, indb=ib;
    done = 0;
    int g = 0;
    while (!done)
    {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb+1)%n2])>=0)
            indb=(indb+1)%n2;

        while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1])<=0)
        {
            inda=(n1+inda-1)%n1;
            done=0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<P> ret;

    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera)
    {
        ind = (ind+1)%n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind+1)%n2;
        ret.push_back(b[ind]);
    }
    return ret;

}
vector<P> bruteHull(vector<P> a)
{
    return jarvis_march(a);
}

vector<P> divide(vector<P> a)
{
    if (a.size() <= 5)
        return bruteHull(a);
    vector<P>left, right;
    for (int i=0; i<a.size()/2; i++)
        left.push_back(a[i]);
    for (int i=a.size()/2; i<a.size(); i++)
        right.push_back(a[i]);

    vector<P>left_hull = divide(left);
    vector<P>right_hull = divide(right);

    return merger(left_hull, right_hull);
}
vector<P> divide_and_conquer(vector<P> A)
{
    sort(A.begin(),A.end());
    return divide(A);
}
