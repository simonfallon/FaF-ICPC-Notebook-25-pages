#include "../template.h"

struct custom_hash {
  static ll splitmix64(ll x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(ll x) const { 
    using clock = chrono::steady_clock;
    auto cur_time = clock::now().time_since_epoch().count();
    return splitmix64(x + cur_time);
  }
};
unordered_map<ll,int, custom_hash> mapa;
