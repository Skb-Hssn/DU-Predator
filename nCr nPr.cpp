int64_t bigMod(int64_t base, int64_t power, int64_t mod)
{
    if(!power) return 1;
    if(!base) return 0;

    int64_t res = 1;
    for(int64_t k = 1; k <= power; k <<= 1)
    {
        if(k & power) res = (res*base)%mod;
        base = (base*base)%mod;
    }
    if(res < 0) res += mod;
    return res;
}

int64_t modInverse(int64_t a, int64_t modp)
{
    return bigMod(a, modp - 2, modp);
}

const int64_t MOD = 1000000007LL;

const int MAX = 100069;
int64_t fac[MAX];
int64_t fac_inv[MAX];

void precalc()
{
    fac[0] = 1;
    for(int i = 1; i < MAX; i++)
    {
        fac[i] = (i*fac[i-1])%MOD;
    }
    fac_inv[MAX-1] = modInverse(fac[MAX-1],MOD);
    for(int i = MAX-2; i >= 0; i--)
    {
        fac_inv[i] = ((i+1)*fac_inv[i+1])%MOD;
    }
}

int64_t nCr(int n, int r)
{
    if(r > n) return 0;
    return (((fac[n]*fac_inv[n-r])%MOD)*fac_inv[r])%MOD;
}

int64_t nPr(int n, int r)
{
    if(r > n) return 0;
    return (fac[n]*fac_inv[n-r])%MOD;
}