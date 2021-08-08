const int N=?;
const int LGN=?;
 
int n;
vector<int> adj[N];
int tin[N], tout[N], sz[N], par[N][LGN];
vector<int> hc(N, -1), cno(N), hd(N, -1), idx(N);
int tt=0, ccnt=0, id=0;
 
void dfs(int u=0, int p=0) {
  tin[u] = tt++, sz[u] = 1, par[u][0] = p;
  for (int j = 1; j < LGN; ++j) {
    par[u][j] = par[par[u][j-1]][j-1];
  }
  int mx = 0;
  for (int &v: adj[u]) {
    if (v!=p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > mx) {
        mx = sz[v];
        hc[u] = v;
      }
    }
  }
  tout[u] = tt-1;
}
 
void hld(int u=0, int p=0) {
  if(hd[ccnt]==-1) hd[ccnt] = u;
  cno[u] = ccnt, idx[u] = id++;
  if(hc[u] != -1)  hld(hc[u], u);
  for (int &v: adj[u]) {
    if (v!=p and v!=hc[u]) {
      ccnt++;
      hld(v, u);
    }
  }
}
 
bool is_anc(int u, int v) {
  return (tin[u]<=tin[v] and tout[u]>=tout[v]);
}
 
int get_lca(int u, int v) {
  if(is_anc(u, v))  return u;
  if(is_anc(v, u))  return v;
  for (int j = LGN-1; j >= 0; --j) {
    if(!is_anc(par[u][j], v)) {
      u = par[u][j];
    }
  }
  return par[u][0];
}
 
int t[3*N];
 
void assign(int i, int x, int u=1, int s=0, int e=n-1){
 if(s>i or e<i)  return ;
 if(s==e){
   t[u]=x;
   return ;
 }
 int v=2*u, w=2*u+1, m=(s+e)/2;
 assign(i,x,v,s,m);
 assign(i,x,w,m+1,e);
 t[u] = max(t[v],t[w]);
}
 
int rmx(int l, int r, int u=1, int s=0, int e=n-1){
 if(l>e or r<s)  return 0;
 if(l<=s and e<=r) return t[u];
 int v=2*u, w=2*u+1, m=(s+e)/2;
 return max(rmx(l,r,v,s,m),rmx(l,r,w,m+1,e));
}
 
 
void upd(int u, int x) {
  assign(idx[u], x);
}
 
//path max only for up
int pmx_up(int u, int anc) {
  if(cno[u]==cno[anc]) {
    return rmx(idx[anc], idx[u]);
  }
  int ret = rmx(idx[hd[cno[u]]], idx[u]);
  u = hd[cno[u]];
  u = par[u][0];
  return max(ret, pmx_up(u, anc));
}
 
//path max
int pmx(int u, int v) {
  int l = get_lca(u, v);
  return max(pmx_up(u, l), pmx_up(v, l));
}

//dfs()
//hld()

/*
hc: heavy child of a node
cno: chain no of a node
hd: head of a chain
idx: idx of a node in plain array
ccnt: chain count
*/