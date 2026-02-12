#include "../template.h"

/// Complexity: O(|N+Q|*sqrt(|N|)*|ADD/DEL|)
/// Requires add(), delete() and get_ans()
struct query {
  int l, r, idx;
};
vector<query> q;
vi ans;
int S, n; // s = sqrt(n)
bool cmp (query a, query b) {
  int x = a.l / S;
  if (x != b.l / S) return x < b.l / S;
  return (x&1 ? a.r < b.r : a.r > b.r);
}
void add(int i){}
void del(int i){}
int get_ans(){}
void solve(){
  S = sqrt(n); // n = size of array
  sort(all(q), cmp);
  int l = 0, r = -1;
  forn(i, sz(q)){
    while (r < q[i].r) add(++r);
    while (l > q[i].l) add(--l);
    while (r > q[i].r) del(r--);
    while (l < q[i].l) del(l++);
    ans[q[i].idx] = get_ans();
  }
}
