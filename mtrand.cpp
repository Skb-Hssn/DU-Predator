mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
i64 rnd(i64 l, i64 r) {
 return uniform_int_distribution<i64>(l, r) (rng);
}

