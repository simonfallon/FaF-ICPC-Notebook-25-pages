// https://judge.yosupo.jp/problem/ordered_set

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  cin >> N >> Q;

  ordered_set st;
  for(int i = 0; i < N; i++){
    int x;
    cin >> x;
    st.insert(x);
  }

  while(Q--){
    int t, x;
    cin >> t >> x;

    if(t == 0){
      // Insert x if not present
      st.insert(x);
    }
    else if(t == 1){
      // Remove x if present
      st.erase(x);
    }
    else if(t == 2){
      // Output x-th smallest (1-indexed)
      if(x > (int)st.size()){
        cout << -1 << "\n";
      }
      else{
        // find_by_order is 0-indexed
        auto it = st.find_by_order(x - 1);
        cout << *it << "\n";
      }
    }
    else if(t == 3){
      // Count elements <= x
      // order_of_key(x) gives count < x
      // So count <= x is order_of_key(x+1)
      cout << st.order_of_key(x + 1) << "\n";
    }
    else if(t == 4){
      // Largest element <= x
      // upper_bound(x) gives first element > x
      auto it = st.upper_bound(x);
      if(it == st.begin()){
        cout << -1 << "\n";
      }
      else{
        --it;
        cout << *it << "\n";
      }
    }
    else if(t == 5){
      // Smallest element >= x
      // lower_bound(x) gives first element >= x
      auto it = st.lower_bound(x);
      if(it == st.end()){
        cout << -1 << "\n";
      }
      else{
        cout << *it << "\n";
      }
    }
  }
}
