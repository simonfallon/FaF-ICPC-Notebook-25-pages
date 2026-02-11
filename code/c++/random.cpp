#include "../template.h"

// Declare random number generator
mt19937_64 rng(0); // 64 bit, seed = 0
// 32 bit with random seed
using clock = chrono::steady_clock;
auto cur_time = clock::now().time_since_epoch().count();
mt19937 rng(cur_time); 

// Use it to shuffle a vector
int rd(int l, int r) { 
    return uniform_int_distribution<int>(l, r)(rng);
}
ld rd(ld l, ld r) { 
    return uniform_real_distribution<ld>(l, r)(rng);
}

int main(){
    vi vec(100);
    iota(all(vec), 0);
    shuffle(all(vec), rng);
}