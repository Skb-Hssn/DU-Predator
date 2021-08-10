/*
   -Find the number of path of length K.
*/
#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
const int N = 2e5;
vector<vector<int>> G(N+3);
vector<bool> dead(N+3);
vector<int> sz(N+3);
int oneCentroid(int root)
{
 function<void(int, int)> get_size = [&] (int cur, int p) {
  sz[cur] = 1;
  for(int to : G[cur]) {
   if(!dead[to] && to != p) {
    get_size(to, cur);
    sz[cur] += sz[to];
   }
  }
 };
 get_size(root, -1);

 int tot_sz = sz[root];
 tot_sz /= 2;

 function<int(int, int)> get_centroid = [&] (int cur, int p) {
  for(int to : G[cur]) {
   if(!dead[to] && to != p) {
    if(sz[to] > tot_sz) {
     return get_centroid(to, cur);
    }
   }
  }
  return cur;
 };
 return get_centroid(root, -1);
}
i64 ans = 0;
int K;
int cnt[N+5];
void decompose(int root)
{
 int mx_height = 0;
 function<void(int, int, int, int)> add_cnt = [&] (int cur, int p, int h, int val) {
  if(h > K) return;
  mx_height = max(mx_height, h);
  cnt[h] += val;
  for(int to : G[cur]) {
   if(!dead[to] && to != p) {
    add_cnt(to, cur, h+1, val);
   }
  }
 };
 function<void(int, int, int)> calc = [&] (int cur, int p, int h) { 
  if(h > K) return;
  ans += cnt[K-h]; 
  mx_height = max(mx_height, h);
  for(int to : G[cur]) { 
   if(!dead[to] && to != p) {
    calc(to, cur, h+1);
   }
  }
 };
 function<void(int, int)> dfs = [&] (int cur, int p) {
  int cntrd = oneCentroid(cur);
  dead[cntrd] = true;
  for(int to : G[cntrd]) {
   if(!dead[to] && to != p) {
    dfs(to, cntrd);
   }
  }
  mx_height = 0;
  cnt[0] = 1;
  add_cnt(cntrd, -1, 0, 1);
  for(int to : G[cntrd]) {
   if(to != p && !dead[to]) {
    add_cnt(to, cntrd, 1, -1);
    calc(to, cntrd, 1);
    add_cnt(to, cntrd, 1, 1);
   }
  }
  for(int i = 0; i <= mx_height; i++) {
   cnt[i] = 0;
  }
  dead[cntrd] = false;
 };
 dfs(root, -1);
}
int main()
{
 int n;
 scanf("%d", &n);
 for(int i = 1; i < n; i++) {
  int u, v;
  scanf("%d%d", &u, &v);
  G[u].push_back(v);
  G[v].push_back(u);
 }
 decompose(1);
}

