// https://codeforces.com/gym/104252/problem/G

#include <bits/stdc++.h>

#define forn(i, n) for(int i = 0; i < n; ++i)
#define pb push_back
#define sz(x) (int32_t)(x.size())
#define el '\n'
#define all(a) a.begin(), a.end()
 
using namespace std;

typedef long long ld;
typedef pair<int, int> ii;

const ld eps = 0;

struct pt{
    ld x, y;
    pt(){}
    pt(ld xx, ld yy): x(xx), y(yy){}
    auto tie() const {return std::tie(x, y);}
    // Polar unit point: ang(randians)
    pt(ld ang): x(cos(ang)), y(sin(ang)) {}
    auto operator<=>(const pt&) const = default;

    // ------- BASIC OPERATORS -------  //        
    pt operator+(pt p){ return pt(x+p.x, y+p.y); }
    pt operator-(pt p){ return pt(x-p.x, y-p.y); }
    ld operator*(pt p){ return x*p.x + y*p.y; }
    pt operator*(ld t){ return pt(x*t, y*t); }
    pt operator/(ld t){ return pt(x/t, y/t); }
    ld operator%(pt p){ return x*p.y - y*p.x; }
    ld side(pt p, pt q){ return (q-p) % (*this-p); }
    bool in_disk(pt p, pt q){ 
        return (p - *this) * (q - *this) <= 0; 
    }
    bool on_segment(pt p, pt q){ 
        return side(p, q) == 0 && in_disk(p, q); 
    }
    bool left(pt p, pt q){ 
        // ( >= -eps to accept collinear)
        return side(p, q) > eps; 
    } 
};

struct mink_sum{
    int normal=-1, n;
  vector<pt> p;
  mink_sum(){}
  mink_sum(vector<pt>& p1, vector<pt>& p2){
    p.reserve(sz(p1) + sz(p2));
    reorder(p1),  reorder(p2);
    forn(i, 2) p1.pb(p1[i]), p2.pb(p2[i]);
    int i = 0, j = 0;
    while(i+2 < sz(p1) || j+2 < sz(p2)){
      p.pb(p1[i] + p2[j]);
      auto cro = (p1[i+1] - p1[i]) % (p2[j+1] - p2[j]);
      i += cro >= -eps;
      j += cro <= eps;
    }
    n = sz(p);
  }
  void reorder(vector<pt> &pol){
    if(pol[2].side(pol[0], pol[1]) < 0) reverse(all(pol));
    int j = 0;
    forn(i, sz(pol)) 
      if(ii{pol[i].y, pol[i].x} < ii{pol[j].y, pol[j].x}) j = i;
    rotate(pol.begin(), pol.begin() + j, pol.end());
  }
  void remove_col(){ // helper 
    vector<pt> s;
    forn(i, n) 
      if(!p[i].on_segment(p[(i-1+n) % n], p[(i+1) % n]))
        s.pb(p[i]);
    p.swap(s);  n = sz(p);
  }
  void normalize(){  // helper 
    remove_col();
    if(p[2].left(p[0], p[1])) reverse(all(p));
    int pi = min_element(all(p)) - p.begin();
    vector<pt> s(n);
    forn(i, n) s[i] = p[(pi+i) % n];
    p.swap(s);  n = sz(p);
  }
  bool has_log(pt q){ /// O(log(n)) only CONVEX.
    if(normal == -1) normal = 1, normalize();
    if(q.left(p[0], p[1]) || q.left(p[n-1], p[0])) 
      return false;
    // returns true if point on boundary 
    // (change sign of EPS in left to return false)
    int l = 1, r = n-1; 
    while(l+1 < r){
      int m = (l+r) / 2;
      if(!q.left(p[0], p[m])) l = m;
      else r = m;
    }
    return !q.left(p[l], p[l+1]);
  }
};


void sol(){
    auto read = [&](){
        int n; cin >> n;
        vector<pt> p(n);
        forn(i, n){
            cin >> p[i].x >> p[i].y;
            p[i] = p[i] * 2; // Avoid double when / 2
        }  
        return make_pair(n, p);
    };
    auto [m1, p1] = read();
    auto [m2, p2] = read();
    auto [n, pts] = read();

    string ans(n, 'N');
    // (p1 + p2) / 2git
    auto tp1 = p1, tp2 = p2;
    for(auto &p: tp1) p = p / 2;
    for(auto &p: tp2) p = p / 2;
    auto ms = mink_sum(tp1, tp2);
    forn(i, n) if(ms.has_log(pts[i])) ans[i] = 'Y';

    // p1 + 2*(p2 - p1)
    // 2*p2 - p1
    auto diff = [&](){
        for(auto &p: tp1) p = p * (-1);
        for(auto &p: tp2) p = p * 2;
        ms = mink_sum(tp1, tp2);
        forn(i, n) if(ms.has_log(pts[i])) ans[i] = 'Y';
    };
    tp1 = p1, tp2 = p2, diff();
    tp1 = p2, tp2 = p1, diff();
    cout << ans << el;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sol();
}