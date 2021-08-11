const int N=4e5+5;
const int LGN=20;
const int A=28;
 
string s;
int c[LGN][N], sa[N], lcp[N];
 
//O(nlgn)
void build_sa(){
  s += '`';
  int n = s.size();
  vector<int> cnt(max(n, A));
  for (int i = 0; i < n; ++i) cnt[s[i]-'`']++;
  for (int i = 1; i < A; ++i) cnt[i] += cnt[i-1];
  for (int i = n-1; i >=0; --i) sa[--cnt[s[i]-'`']] = i;
  int cls = 1;
  for (int i = 1; i < n; ++i){
    if(s[sa[i]] != s[sa[i-1]])  cls++;
    c[0][sa[i]] = cls-1;
  }
 
  vector<int> pn(n);
  for (int k = 0; (1<<k) < n; ++k){
    for (int i = 0; i < n; ++i){
      pn[i] = sa[i] - (1<<k);
      if(pn[i] < 0) pn[i] += n;
    }
    fill(cnt.begin(), cnt.begin()+cls, 0);
    for (int i = 0; i < n; ++i) cnt[c[k][pn[i]]]++;
    for (int i = 1; i < cls; ++i) cnt[i] += cnt[i-1];
    for (int i = n-1; i >= 0; --i) sa[--cnt[c[k][pn[i]]]] = pn[i];
 
    c[k+1][sa[0]]=0;
    cls = 1;
    for (int i = 1; i < n; ++i){
      pair<int, int> cur = {c[k][sa[i]], c[k][(sa[i] + (1 << k)) % n]};
      pair<int, int> prev = {c[k][sa[i-1]], c[k][(sa[i-1] + (1 << k)) % n]};
      if(cur != prev) cls++;
      c[k+1][sa[i]] = cls-1;
    }
  }
  s.pop_back();
  for (int i = 0; i <= n; ++i)  sa[i] = sa[i+1];
}
 
void build_lcp(){
  int n = s.size();
  int idx[n];
  for (int i = 0; i < n; ++i) idx[sa[i]] = i;
  int k = 0;
  for (int i = 0; i < n; ++i){
    if(idx[i]==n-1) {
      k = 0;
      continue;
    }
    int j = sa[idx[i]+1];
    while(i+k<n and j+k<n and s[i+k]==s[j+k]) k++;
    lcp[idx[i]] = k;
    if(k) k--;
  }
}
 
int get_lcp(int i, int j){
  int ret = 0, n = s.size();
  int k = log2(n);
  while (k>=0){
    if(c[k][i]==c[k][j]){
      ret += 1<<k;
      i += 1<<k;
      j += 1<<k;
    }
    k--;
  }
  return ret;
}