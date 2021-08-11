#define eb emplace_back
 
struct AC{
  const int A = 26;
  vector<vector<int>> nxt, idx, rev_ed;
  vector<int> lnk, otlnk, vis, cnt;
  AC(){newNode();}
 
  int newNode(){
    nxt.eb(A, 0), idx.eb(0), rev_ed.eb(0);
    lnk.eb(0),  otlnk.eb(0), vis.eb(0);
    return nxt.size()-1;
  }
 
  void clear(){
    nxt.clear(), idx.clear(), rev_ed.clear();
    lnk.clear(), otlnk.clear(), vis.clear(), cnt.clear();
  }
 
  //O(|p|)
  void add(string p, int i){
    int v=0;
    for(char c: p){
      if(!nxt[v][c-'a'])  nxt[v][c-'a'] = newNode();
      v = nxt[v][c-'a'];
    }
    idx[v].eb(i);
    cnt.eb(0);
  }
 
  //O(|p1+p2+p3+..|)
  void build(){
    queue<int> q; q.push(0);
    while (!q.empty()){
      int u=q.front();  q.pop();
      for (int i = 0; i < A; ++i){
        int v = nxt[u][i];
        if (!v) {
          nxt[u][i] = nxt[lnk[u]][i];
          continue;
        }
        if (u) {
          int x = lnk[u];
          while(x and !nxt[x][i])  x = lnk[x];
          lnk[v] = nxt[x][i];
          if (!idx[lnk[v]].empty())  otlnk[v] = lnk[v];
          else otlnk[v] = otlnk[lnk[v]];
        }
        q.push(v);
        rev_ed[lnk[v]].eb(v);
      }
    }
  }
 
  void dfs(int u) {
    for (int &v: rev_ed[u]) {
      dfs(v);
      vis[u] += vis[v];
    }
    for (int &i: idx[u]) {
      cnt[i] = vis[u];
    }
  }
 
  void trav(string &t){
    int u = 0;
    for (char &c: t) {
      u = nxt[u][c-'a'];
      vis[u]++;
    }
    dfs(0);
  }
};
/*
nxt[u][i] is the ended node number of the edge that goes from u by char i+'a'
idx[u] is the list of index of the pattern which end on node u (if patter are unique it should be 1D vector)
rev_ed[u] means reverse edge of suffix link
*/
