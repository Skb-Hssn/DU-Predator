//Tested: https://codeforces.com/gym/100753/submission/85265606
//O(n^1/3)

typedef long long ll;
 
const int N = 1e6+6;
vector<int> isp(N, 1);
 
void seive(){
  for (int i = 2; i*i < N; ++i){
    if(isp[i]){
      for (int j = i*i; j < N; j+=i){
        isp[j] = 0;
      }
    }
  }
}
 
ll mulmod(ll a, ll b, ll m){
  a%=m;
  ll res = 0;
  while(b > 0){
    if(b&1) res=(res+a)%m;
    a=(a<<1)%m;
    b>>=1;
  }
  return res;
}
 
ll bigmod(ll a, ll b, ll m){
  a%=m;
  ll res = 1;
  while(b > 0){
    if(b&1) res = mulmod(res,a,m);
    a = mulmod(a,a,m);
    b >>= 1;
  }
  return res;
}
 
int isprime(ll n){
  if(n==2 || n == 3)  return 1;
  if(n<=1 || n%2==0)  return 0;
  for (int k = 0; k < 10; ++k){
    ll a = 2+rand()%(n-2);
    ll s = n-1;
    while(!(s&1)) s>>=1;
    if(bigmod(a, s, n) == 1)  continue;
    int iscomp = 1;
    while(s!=n-1){
      if(bigmod(a, s, n)==n-1){
        iscomp = 0;
        break;
      }
      s=s<<1;
    }
    if(iscomp) return 0;
  }
  return 1;
}
 
int nod(ll n){
  seive();
  int ret = 1;
  for (int i = 2; 1LL*i*i*i <= n; ++i){
    if(isp[i]){
      int e = 0;
      while(n%i == 0){
        e++;
        n /= i;
      }
      ret *= e+1;
    }
  }
  ll sq = sqrt(1.0L*n);
  if(isprime(n))  ret *= 2;
  else if(n == sq*sq and isprime(sq))  ret *= 3;
  else if(n!=1) ret *= 4;
  return ret;
}