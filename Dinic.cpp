typedef long long ll;
const ll INF = 1e15;

struct Dinic{
  struct Edge{
    int to, idxf;
    ll c, f; //idxf stands for idx for from node
  };
  int n;
  vector<vector<Edge>> ed;
  vector<int> l, nxt;

  Dinic(int n):n(n){
    ed.assign(n, vector<Edge>());
  }

  void add_edge(int u, int v, ll c){
    ed[u].push_back({v,(int)ed[v].size(),c,0});
    ed[v].push_back({u,(int)ed[u].size()-1,0,0});
  }

  bool bfs(int s, int t){
    l.assign(n,-1); l[s]=0;
    queue<int> q; q.push(s);
    while(!q.empty()){
      int at=q.front();  q.pop();
      for(auto& e: ed[at]){
        if(l[e.to]==-1 and e.c>e.f){
          l[e.to]=l[at]+1;
          q.push(e.to);
        }
      }
    }
    return l[t]!=-1;
  }

  ll dfs(int at, int t,ll fl=INF){
    if(at==t) return fl;
    for( ; nxt[at]<ed[at].size(); nxt[at]++){
      Edge &e=ed[at][nxt[at]];
      if(e.c>e.f && l[e.to]==l[at]+1){
        ll bn = dfs(e.to,t,min(fl,e.c-e.f));   //bn for bottleneck
        if(bn>0){
          e.f+=bn;
          ed[e.to][e.idxf].f-=bn;
          return bn;
        }
      }
    }
    return 0;
  }

  ll mxflow(int s, int t){
    ll ret=0;
    while(bfs(s,t)){
      nxt.assign(n,0);
      while(ll fl=dfs(s,t)){
        ret += fl;
      }
    }
    return ret;
  }
};