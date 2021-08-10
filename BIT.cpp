/* 1 - based indexing 
   bit range update, query*/
const int N=0;
int B1[N+3], B2[N+3];

void add(int b[], int idx, int val) {
 while(idx <= N) {
  b[idx] += val;
  idx += idx & -idx;
 }
}

void rangeAdd(int l, int r, int val) {
 add(B1, l, val);
 add(B1, r+1, -val);
 add(B2, l, val*(l-1));
 add(B2, r+1, -val*r);
}

int sum(int b[], int idx) {
 int ret = 0;
 while(idx > 0) {
  ret += b[idx];
  idx -= idx & -idx;
 }
 return ret;
}

int prefixSum(int idx) {
 return sum(B1, idx)*idx - sum(B2, idx);
}

int rangeSum(int l, int r) {
 return prefixSum(r) - prefixSum(l-1);
}
