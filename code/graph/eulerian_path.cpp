#include "../template.h"

int n;
int edges = 0;
int out[nax], in[nax];

struct edge {
  int v, id;
//  list<edge>::iterator rev;          
  edge(int v, int id):v(v),id(id){}
};
list<edge> g[nax];
void add_edge(int a, int b, int id){
  out[a]++;
  in[b]++;
  ++edges;
  g[a].push_front(edge(b,id)); //auto ia=g[a].begin();
//  g[b].push_front(edge(a,id)); auto ib=g[b].begin();
//  ia->rev=ib; ib->rev=ia;                          
}
vi p, pe; // pe = edge ids (judge wants edge indices, not nodes)
void go(int u){
  while(sz(g[u])){
    int v=g[u].front().v;
    int id=g[u].front().id;
//    g[v].erase(g[u].front().rev);
    g[u].pop_front();
    go(v);
    pe.push_back(id);
  }
  p.push_back(u);
}
vi get_path(int u){
  p.clear(); pe.clear();
  go(u);
  reverse(all(p)); reverse(all(pe));
  return p;
}

pair<bool, int> check_directed() {
  int start = -1, plus = 0, minus = 0, bad = 0;
  forn(i, n){
    if (out[i] && start == -1) start = i;
    int d = out[i] - in[i];
    if (d == 1){ plus++; start = i; }
    else if (d == -1) minus++;
    else if (d) bad++;
  }
  return {(bad == 0 && plus == minus && plus <= 1), start};
}

pair<bool, int> check_undirected() {
  int start = -1, odd = 0;
  forn(i, n){
    int deg = out[i] + in[i];
    if (deg && start == -1) start = i;
    if (deg & 1) { odd++; start = i; }
  }
  return {(odd == 0 || odd == 2), start};
}

// For undirected -> Use check_undirected, uncomment lines above
bool eulerian(vi& tour){
  auto [ok, start] = check_directed();
  if (ok && start != -1) {
    tour = get_path(start);
    if (sz(tour) == edges + 1) return true; 
  } // Remove + 1 if pe is returned (edge indices)
  return false;
}