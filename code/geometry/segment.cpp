#include "../template.h"

#include "point.cpp"
#include "line.cpp"

int sgn(ld x){
  if(x < 0) return -1;
  return x == 0 ? 0 : 1;
}
// Proper intersection of AB & CD (strictly opposite sides), into out
bool proper_inter(pt a, pt b, pt c, pt d, pt& out){
  ld sa = a.side(c, d), sb = b.side(c, d);
  ld sc = c.side(a, b), sd = d.side(a, b);
  if(sgn(sa) * sgn(sb) < 0 && sgn(sc) * sgn(sd) < 0){
    out = (a * sb - b * sa) / (sb - sa);
    return true;
  }
  return false;
}
// All intersection points of segments AB & CD
set<pt> seg_inter(pt a, pt b, pt c, pt d){
  pt out;
  if(proper_inter(a, b, c, d, out)) return {out};
  set<pt> s;
  if(a.on_segment(c, d)) s.insert(a);
  if(b.on_segment(c, d)) s.insert(b);
  if(c.on_segment(a, b)) s.insert(c);
  if(d.on_segment(a, b)) s.insert(d);
  return s;
}
// Distance from point P to segment AB
ld seg_point(pt a, pt b, pt p){
  if(a != b){
    line l(a, b);
    if(l.cmp_proj(a, p) && l.cmp_proj(p, b)) // P projects onto AB
      return l.dist(p);                       // distance to line
  }
  return min((p - a).norm(), (p - b).norm()); // else distance to A or B
}
// Distance between segments AB & CD
ld seg_seg(pt a, pt b, pt c, pt d){
  pt out;
  if(proper_inter(a, b, c, d, out)) return 0;
  return min({seg_point(a, b, c), seg_point(a, b, d),
              seg_point(c, d, a), seg_point(c, d, b)});
}
