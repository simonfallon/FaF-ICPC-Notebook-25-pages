// https://codeforces.com/gym/104252/problem/G

#include <bits/stdc++.h>

#define forn(i, n) for(int i = 0; i < n; ++i)
#define pb push_back
#define sz(x) (int32_t)(x.size())
#define el '\n'
#define ford(i, n) for(int i = n - 1; i >= 0; --i)
 
#define for1(i, n) for(int i = 1; i <= n; ++i)
#define fore(i, l, r) for(int i = l ; i <= r; ++i)
#define fored(i, l, r) for(int i = r ; i >= l; --i)
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef long long ld;
 
typedef __int128_t i128;
typedef array<ll,2> v2;
typedef array<int, 3> v3;
typedef array<int, 4> v4;
typedef array<string, 2> vs2;

const int inf = 2e9;
const int mod = 998244353;
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
  mink_sum(vector<pt>& p1, vector<pt>& p2, bool inter=0){
    if(inter) for(auto& [x, y] : p2) x = -x, y = -y;
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
  bool has(pt q){
    int cnt = 0;
    forn(i, sz(p))
      cnt += q.side(p[i], p[(i+1) % sz(p)]) >= 0;
    return cnt == sz(p);
  }
  bool intersect(pt shift = pt(0, 0)){ 
    return has(shift); 
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
      // 
      int m = (l+r) / 2;
      if(!q.left(p[0], p[m])) l = m;
      else r = m;
    }
    return !q.left(p[l], p[l+1]);
  }
};


void sol(){
    int m1, m2, n;
    cin >> m1;
    vector<pt> p1(m1);
    forn(i, m1){
        cin >> p1[i].x >> p1[i].y;
        p1[i] = p1[i] * 2;
    } 
    cin >> m2;
    vector<pt> p2(m2);
    forn(i, m2){
        cin >> p2[i].x >> p2[i].y;
        p2[i] = p2[i] * 2;
    }
    cin >> n;
    vector<pt> pts(n);
    forn(i, n){
        cin >> pts[i].x >> pts[i].y;
        pts[i] = pts[i] * 2;
    }

    string ans(n, 'N');
    auto tp1 = p1, tp2 = p2;
    for(auto &p: tp1) p = p / 2;
    for(auto &p: tp2) p = p / 2;

    auto ms = mink_sum(tp1, tp2);
    forn(i, n) if(ms.has_log(pts[i])) ans[i] = 'Y';

    // p1 + 2*(p2 - p1)
    // 2*p2 - p1
    tp1 = p1, tp2 = p2;
    for(auto &p: tp1) p = p * (-1);
    for(auto &p: tp2) p = p * 2;
    ms = mink_sum(tp1, tp2);
    forn(i, n) if(ms.has_log(pts[i])) ans[i] = 'Y';

    tp1 = p2, tp2 = p1;
    for(auto &p: tp1) p = p * (-1);
    for(auto &p: tp2) p = p * 2;
    ms = mink_sum(tp1, tp2);
    forn(i, n) if(ms.has_log(pts[i])) ans[i] = 'Y';

    cout << ans << el;
}

int main(){
    ios_base::sync_with_stdio(false);
    cout << setprecision(20) << fixed;
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--){
        sol();
    }
}