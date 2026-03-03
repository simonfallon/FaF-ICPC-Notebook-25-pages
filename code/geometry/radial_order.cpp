#include "../template.h"
#include "point.cpp"

int cuad(pt p){
  if(p.x > 0 && p.y >= 0) return 0;
  if(p.x <= 0 && p.y > 0) return 1;
  if(p.x < 0 && p.y <= 0) return 2;
  if(p.x >= 0 && p.y < 0) return 3;
  return -1; // x == 0 && y == 0
}
// Around Origin(0, 0):  -->  sort(all(pts), cmp); 
bool cmp(pt p1, pt p2){ 
  int c1 = cuad(p1), c2 = cuad(p2);
  return c1 == c2 ? p1.y*p2.x < p1.x*p2.y : c1 < c2; 
} 
// Around const pt O(x, y):
//  -->  sort(all(pts), [&](pt& pi, pt& pj){ 
// return cmp(pi - O, pj - O); 
// });