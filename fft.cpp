//Tested: https://www.spoj.com/status/POLYMUL,fahimcp495/

typedef long long ll;
typedef long double ld;


struct cplx {
  ld a, b;
  cplx(ld a=0, ld b=0):a(a), b(b) {}
  const cplx operator + (const cplx &z) const { return cplx(a+z.a, b+z.b); }
  const cplx operator - (const cplx &z) const { return cplx(a-z.a, b-z.b); }
  const cplx operator * (const cplx &z) const { return cplx(a*z.a-b*z.b, a*z.b+b*z.a); }
  const cplx operator / (const ld &k) const { return cplx(a/k, b/k); }
};

const ld PI=acos(-1);
vector<int> rev;

void pre(int sz){
  if(rev.size()==sz)  return ;
  rev.resize(sz);
  rev[0]=0;
  int lg_n = __builtin_ctz(sz);
  for (int i = 1; i < sz; ++i)  rev[i] = (rev[i>>1] >> 1) | ((i&1)<<(lg_n-1));
}


void fft(vector<cplx> &a, bool inv){
  int n = a.size();
  
  for (int i = 1; i < n-1; ++i) if(i<rev[i])  swap(a[i], a[rev[i]]);


  for (int len = 2; len <= n; len <<= 1){
    ld t = 2*PI/len*(inv? -1: 1);
    cplx wlen = {cosl(t), sinl(t)};
    for (int st = 0; st < n; st += len){
      cplx w(1);
      for (int i = 0; i < len/2; ++i){
        cplx ev = a[st+i];
        cplx od = a[st+i+len/2]*w;
        a[st+i] = ev+od;
        a[st+i+len/2] = ev-od;
        w = w*wlen;
      }
    }
  }

  if(inv){
    for(cplx &z: a){
      z = z/n;
    }
  }
}

vector<ll> mul(vector<ll> &a, vector<ll> &b){
  int n = a.size(), m = b.size(), sz = 1;
  while (sz < n+m-1)  sz <<= 1;
  vector<cplx> x(sz), y(sz), z(sz);
  for (int i = 0; i < sz; ++i){
    x[i] = cplx(i<n? a[i]: 0, 0);
    y[i] = cplx(i<m? b[i]: 0, 0);
  }
  pre(sz);
  fft(x, 0);
  fft(y, 0);
  for (int i = 0; i < sz; ++i){
    z[i] = x[i] * y[i];
  }
  fft(z, 1);
  vector<ll> c(n+m-1);
  for (int i = 0; i < n+m-1; ++i){
    c[i] = round(z[i].a);
  }
  return c;
}