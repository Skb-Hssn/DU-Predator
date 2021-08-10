/*
- 0 based indexing.
Problem :
Find the number of distinct element in a given range.
*/

#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;

const int BLOCK_SZ = 200;
const int N = 30'005;
const int MAXN = 1'000'005;

struct Query {
 int L, R, idx, bn;
 Query() {}
 Query(int _L, int _R, int _idx) : L(_L), R(_R), idx(_idx), bn(_L/BLOCK_SZ) {}
 bool operator<(const Query& other) const {
  if(bn != other.bn) return bn < other.bn;
  return (bn & 1) ? (R < other.R) : (R > other.R);
 }
};

int a[N];
int freq[MAXN];
int res[MAXN];
int ans = 0;
vector<Query> queries;

void add(int idx)
{
 freq[a[idx]]++;
 if(freq[a[idx]] == 1) ans++;
}

void remove(int idx)
{
 freq[a[idx]]--;
 if(freq[a[idx]] == 0) ans--;
}

void Mo(int q)
{
 sort(queries.begin(), queries.end());

 int cur_L = 0;
 int cur_R = -1;

 for(auto it : queries) {
  int l = it.L;
  int r = it.R;
  while(cur_L > l) {
   --cur_L;
   add(cur_L);
  }

  while(cur_R < r) {
   ++cur_R;
   add(cur_R);
  }

  while(cur_L < l) {
   remove(cur_L);
   ++cur_L;
  }

  while(cur_R > r) {
   remove(cur_R);
   --cur_R;
  }

  res[it.idx] = ans;
 }

}

