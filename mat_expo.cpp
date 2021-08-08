using ll = long long;
using row = vector<ll>;
using matrix = vector<row>;

const int mod = ?;

matrix unit_mat(int n) {
  matrix I(n, row(n));
  for (int i = 0; i < n; ++i){
    I[i][i] = 1;
  }
  return I;
}

matrix mat_mult(matrix a, matrix b) {
  int m = a.size(), n = a[0].size();
  int p = b.size(), q = b[0].size();
  matrix res(m, row(q));
  for (int i = 0; i < m; ++i){
    for (int j = 0; j < q; ++j){
      for (int k = 0; k < n; ++k){
        res[i][j] = (res[i][j] + a[i][k]*b[k][j]) % mod;
      }
    }
  }
  return res;
}

matrix mat_expo(matrix a, int p) {
  int m = a.size(), n = a[0].size();
  matrix res = unit_mat(m);
  while (p) {
    if (p&1)  res = mat_mult(a, res);
    a = mat_mult(a, a);
    p >>= 1;
  }
  return res;
}