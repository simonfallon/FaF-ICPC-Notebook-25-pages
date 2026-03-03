#include "../template.h"

struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  // Polar unit point: ang(randians)
  pt(ld ang): x(cos(ang)), y(sin(ang)) {}  

  // ------- BASIC OPERATORS -------  //        
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
  pt operator-(pt p){ return pt(x-p.x, y-p.y); }
  pt operator*(ld t){ return pt(x*t, y*t); }
  pt operator/(ld t){ return pt(x/t, y/t); }
  ld operator*(pt p){ return x*p.x + y*p.y; }
  ld operator%(pt p){ return x*p.y - y*p.x; }

  // ------- COMPARISON OPERATORS -------  // 
  bool operator==(pt p){ 
    return abs(x - p.x) <= eps && abs(y - p.y) <= eps;
  }
  // for sort, convex hull/set/map
  bool operator<(pt p)const{ 
    return x < p.x - eps || 
      (abs(x - p.x) <= eps && y < p.y - eps); 
  }
  bool operator!=(pt p){ return !operator==(p); }

  // -------------- NORMS --------------  // 
  ld norm2(){ return *this**this; }
  ld norm(){ return sqrt(norm2()); }
  pt unit(){ return *this/norm(); }

  // ------------ SIDE, LEFT------------ //
  // C is: >0 L, ==0 on AB, <0 R
  ld side(pt p, pt q){ return (q-p) % (*this-p); }
  // Left of directed line PQ? (eps == 0 if integer)
  bool left(pt p, pt q){ 
    // ( >= -eps to accept collinear)
    return side(p, q) > eps; 
  } 

  // -------------- ANGLES -------------- //
  // Angle from origin, in [-pi, pi]
  ld angle(){ return atan2(y, x); } 
  ld min_angle(pt p){ // In [0, pi]
    return acos(*this*p / (norm()*p.norm())); 
  } 
  // Angle< AB(*this) > in direction CW
  ld angle(pt a, pt b, bool CW){ 
    ld ma = (a - b).min_angle(*this - b);
    return side(a, b) * (CW ? -1 : 1) <= 0 ?
      ma : 2*pi - ma; 
  }
  // Is pt inside infinite angle ABC 
  bool in_angle(pt a, pt b, pt c, bool CW = 1){ 
    //From BA to BC in CW direction
    return angle(a, b, CW) <= c.angle(a, b, CW); 
  } 

  // -------------- ROTATIONS -------------- //
  // use ccw90(1,0), cw90(-1,0) for 90 degree rotations
  pt rot(pt p){ return pt(*this % p,*this * p); }
  // CCW, ang (radians)
  pt rot(ld ang){ return rot(pt(sin(ang), cos(ang))); }
  pt rot_around(ld ang, pt p){ 
    return p + (*this - p).rot(ang); 
  }
  pt perp(){ return rot(pt(1, 0)); }

  // -------------- SEGMENTS -------------- //
  bool in_disk(pt p, pt q){ 
    return (p - *this) * (q - *this) <= 0; 
  }
  bool on_segment(pt p, pt q){ 
    return side(p, q) == 0 && in_disk(p, q); 
  }
};

int sgn(ld x){
  if(x < 0) return -1;
  return x == 0 ? 0 : 1;
}
// Segment intersection between AB & CD
void seg_inter(pt a, pt b, pt c, pt d, vector<pt>& out){
  ld sa = a.side(c, d), sb = b.side(c, d);
  ld sc = c.side(a, b), sd = d.side(a, b); // proper cut
  if(sgn(sa) * sgn(sb) < 0 && sgn(sc) * sgn(sd) < 0){
    out.pb((a * sb - b * sa) / (sb - sa)); 
  }
  for(pt p : {c, d}) if(p.on_segment(a, b)) out.pb(p);
  for(pt p : {a, b}) if(p.on_segment(c, d)) out.pb(p);
}
