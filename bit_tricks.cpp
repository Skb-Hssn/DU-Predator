//1. check odd:
if(x&1) cout << "odd\n";

//2. check even:
if(x&1^1) cout << "even\n";

//3. Diveide by 2:
x >>= 1;

//4. Multiply by 2:
x <<= 1;

//5. Flip the i-th bit: (0-based)
x ^= (1<<i);

//7. least bit position value: 13-1, 12-4, 14-2, 16-16
x & -x;


//6. remove trailing zeros:
while(x&1^1)  x >>= 1;
// or,
x/(-x&x);     //divide by least set bit

//?. reset(0) the least bit:
x &= x-1

//8. check a number if power of two or not: (least bit value == value)
if(x && (x&-x) == x)  cout << "power of two\n";
//((x-1)&x) == 0  //it does not work for 0
//(-x&x)==x     //best, but it does not work for 0

//9. the next number after x with the same number of set bits:
int c = x&-x;
int r = x + c;
(((r^x) >> 2)/c) | r;
//Or,
//next permutation
int next_perm(int n) {
  int l = -n&n;    //least set bit value
  int nn = n+l;
  return ((nn^n)/(4*l)) | nn;
}
//Tested: https://binarysearch.com/problems/Next-Binary-Permutation/submissions/5434840

//count number of set bit:
int popcount(int n) {
  int ret = 0;
  while(n) {
    ret++;
    n &= n-1;   //resetting least set bit
  }
  return ret;
}

/*
__builtin_ffs(x) find first(least) set bit index(1-based)
__builtin_clz(x) count leading zero
__builtin_ctz(x) count trailing zero
__builtin_popcount(x) count set bits
/*