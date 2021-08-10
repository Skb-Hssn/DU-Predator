/*
   0 - based Indexing of Array
*/
const int MAXN = 5e5+5;
const int K = 24;

int st[MAXN][K];
int arr[MAXN];
int Log[MAXN];
int N;

void build()
{
 Log[1] = 0;
 for(int i = 2; i < MAXN; i++) {
  Log[i] = Log[i/2] + 1;
 }

 for(int i = 0; i < N; i++) {
  st[i][0] = arr[i];
 }

 for(int j = 1; j <= K; j++) {
  for(int i = 0; i + (1<<j) <= N; i++) {
   st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
  }
 }
}

long long sum(int L, int R)
{
 long long ret = 0;
 for(int j = K; j >= 0; j--) {
  if((1<<j) <= R-L+1) {
   ret += st[L][j];
   L += (1 << j);
  }
 }
 return ret;
}

int min_query(int L, int R)
{
 int j = Log[R-L+1];
 int minimum = min(st[L][j], st[R-(1<<j)+1][j]);
 return minimum;
}


