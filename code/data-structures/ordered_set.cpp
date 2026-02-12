#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef tree<int, null_type, less<int>, rb_tree_tag,

tree_order_statistics_node_update> ordered_set;
int main(){
  // -------- CONSTRUCTOR -------- //
  ordered_set st;
  // 1. For MAX ordering: change less<int> to greater<int>
  // 2. For multiset: Use pairs {value, time}

  // -------- METHODS --------- //
  int k, x;
  st.find_by_order(k); // returns pointer to the k-th smallest element
  st.order_of_key(x);  // returns how many elements are smaller than x
  st.find_by_order(k) == st.end(); // true, if element does not exist
  auto it = st.upper_bound(x); // first element > x
}
