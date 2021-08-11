// “count the number of ways to partition a set of n labelled objects into k nonempty unlabelled subsets.”
// S(n, k) = S(n-1, k-1) + k * S(n-1, k)
// S(n, 1) = 1
// S(n, n) = 1

// More shortly, 
// S(0, 0) = 1
// S(>0, 0) = 0
// S(0, >0) = 0

const int N=1e3+3;
const int mod=1e9+7;

ll sn2[N][N];

void pc_sn2() {
  sn2[0][0] = 1;
  for (int i = 1; i < N; ++i){
    for (int j = 1; j <= i; ++j){
      sn2[i][j] = (sn2[i-1][j-1] + j*sn2[i-1][j]%mod ) % mod;
    }
  }
}

