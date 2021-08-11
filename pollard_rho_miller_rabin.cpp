//O(lgn)
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

//O(lgn)
ll bigmod(ll a, ll b, ll m){
  a%=m;
  ll res = 1;
  while(b > 0){
    if(b&1) res = mulmod(res, a, m);
    a = mulmod(a, a, m);
    b >>= 1;
  }
  return res;
}

bool isp(ll n){
  if(n==2 || n == 3)  return 1;
  if(n<=1 || n%2==0)  return 0;
  for (int k = 0; k < 5; ++k){
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

ll f(ll x, ll c, ll n){
  return (mulmod(x,x,n)+c)%n;
}

ll pollard_rho(ll n){
  if(n == 1)  return 1;
  if(n%2 == 0)  return 2;
  ll x = rand()%(n-2)+2;
  ll y = x;
  ll c = rand()%(n-1)+1;
  ll g = 1;
  while (g == 1){
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(y, c, n);
    g = __gcd(abs(x-y), n);
  }
  return g;
}

vector<ll> factorize(ll n){
  if(n<=1)  return vector<ll>();
  if(isp(n))  return vector<ll> ({n});
  ll d = pollard_rho(n);
  vector<ll> v = factorize(d);
  vector<ll> w = factorize(n/d);
  v.insert(v.end(), w.begin(), w.end());
  sort(v.begin(), v.end());
  return v;
}


// auto pf = factorize(n);