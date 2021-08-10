#include<bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
i64 rnd(i64 l, i64 r) {
 return uniform_int_distribution<i64>(l, r) (rng);
}

void __print(int x) {cout << x;}
void __print(i64 x) {cout << x;}
void __print(u64 x) {cout << x;}
void __print(double x) {cout << x;}
void __print(long double x) {cout << x;}
void __print(char x) {cout << x;}
void __print(const char* x) {cout << x;}
void __print(string x) {cout << x;}
void __print(bool x) {cout << x;}

template<typename T, typename V>
void __print(const pair<T, V> x) {
 __print(x.first);
 cout << " ";
 __print(x.second);
}

template<typename T>
void __print(const T x) {
 int f = 0;
 for(auto i : x) {
  if(f++) {
   cout << " ";
  }
  __print(i);
 }
}

void _print() {
 cout << '\n';
}

template<typename T, typename... V>
void _print(T t, V... v) {
 __print(t);
 if(sizeof...(v)) cout << " ";
 _print(v...);
}

#define pr(x...) _print(x)

void pr_vec(int sz, int lower, int upper)
{
 if(lower > upper) swap(lower, upper);
 vector<int> v;
 for(int i = 0; i < sz; i++) {
  v.push_back(rnd(lower, upper));
 }
 if(rnd(1, 400) == 1) {
  sort(v.begin(), v.end());
 }
 pr(v);
}

void pr_str(int sz, char lower, char upper)
{
 if(lower>upper) swap(lower, upper);
 string s;
 while(sz--) {
  s += lower + rnd(0, upper-lower);
 }
 if(rnd(1, 400) == 1) {
  sort(s.begin(), s.end());
 }
 pr(s);
}

struct Graph {
 Graph() {}
 Graph(int _n, int _m) : n(_n), m(_m) {
 }

 void pr_graph(int nodes, int edges)
 {
  init(nodes, edges);
  if(edges == 0) return;
  if(edges > (nodes*nodes-nodes)/2) {
   cerr << "Edges limit excedeed.\n";
   return;
  }
  if(edges < nodes - 1) {
   disconnected_graph(nodes, edges);
   return;
  }
  set<pair<int, int>> E;
  while((int)E.size() < nodes-1) {
   int u = rnd(1, nodes);
   int v = rnd(1, nodes);
   if(combine(u, v)) {
    E.insert({u-1, v-1});
   }
  }
  while((int)E.size() < edges) {
   int u = rnd(1, nodes);
   int v = rnd(1, nodes);
   if(u == v) continue;
   E.insert({u, v});
  }
  vector<pair<int, int>> EE(E.begin(), E.end());
  shuffle(EE.begin(), EE.end(), default_random_engine(rnd(1, 1000)));
  for(auto it : EE) {
   pr(it.first + 1, it.second+1, rnd(0, 1000));
  }
 }

 private :

 int n, m;
 vector<int> par;
 vector<int> sz;

 void init(int nodes, int edges)
 {
  n = nodes;
  m = edges;

  par = vector<int> (n+3);
  sz = vector<int> (n+3, 1);
  for(int i = 1; i <= n; i++) par[i] = i;
 }

 void disconnected_graph(int nodes, int edges)
 {
  if(edges == 0) return;
  vector<pair<int, int>> V;
  while((int)V.size() < edges) {
   int u = rnd(1, nodes);
   int v = rnd(1, nodes);
   V.push_back({u, v});
  }
  for(auto it : V) {
   pr(it);
  }
 }

 int find_set(int u)
 {
  return u == par[u] ? u : par[u] = find_set(par[u]);
 }

 bool combine(int u, int v)
 {
  int pu = find_set(u);
  int pv = find_set(v);
  if(pu == pv) return false;
  par[pu] = pv;
  return true;
 }
};

int main() 
{
 int n = rnd(1, 1000);
 int k = rnd(1, 10000);
 pr(n, k);
}

