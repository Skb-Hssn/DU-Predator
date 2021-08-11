struct Node
{
  int bk, hk; //binary key, heap key
  int sz, sum;
  Node *l, *r;
  Node(){}
  Node(int bk):bk(bk),hk(rand()),sz(1), sum(0),l(0),r(0){}
}*root;
typedef Node* pnode;

int get_sz(pnode t){
  return t?t->sz:0;
}

int get_sum(pnode t){
  return t?t->sum:0;
}

void upd(pnode &t){
  if(!t)  return ;
  t->sz = get_sz(t->l)+1+get_sz(t->r);
  t->sum = t->bk;
  t->sum += get_sum(t->l);
  t->sum += get_sum(t->r);
}

void split(int key, pnode t, pnode &l, pnode &r){
  if(!t)  l=r=0;
  else if(key > t->bk) split(key, t->r, t->r, r), l=t;
  else  split(key, t->l, l, t->l), r=t; 
  upd(l);
  upd(r);
}

void merge(pnode &t, pnode l, pnode r){
  if(!l or !r)  t=l?l:r;
  else if(l->hk > r->hk)  merge(l->r, l->r, r), t=l;
  else  merge(r->l, l, r->l), t=r;
  upd(t);
}

void insert(pnode v, pnode &t=root){
  if(!t)  t=v;
  else if(v->hk > t->hk)  split(v->bk, t, v->l, v->r),  t=v;
  else  insert(v, v->bk <= t->bk? t->l: t->r);
  upd(t);
}

void erase(int key, pnode &t=root){
  if(!t)  return ;
  if(t->bk==key)  merge(t, t->l, t->r);
  else  erase(key, key < t->bk? t->l: t->r);
  upd(t);
}

pnode find(int key, pnode t=root){
  if(!t)  return 0;
  if(key == t->bk)  return t;
  if(key < t->bk) return find(key, t->l);
  else  return find(key, t->r);
}

int sumltk(int key, pnode t=root){  //sum less than k
  if(!t)  return 0;
  if(t->bk < key) return t->bk+get_sum(t->l)+sumltk(key, t->r);
  return sumltk(key, t->l);
}

int ltk(int key, pnode t=root){ //count less than k
  if(!t)  return 0;
  if(t->bk < key) return get_sz(t->l)+1+ltk(key, t->r);
  return ltk(key, t->l);
}

int kth(int k, pnode t=root){   //kth BST key
  if(get_sz(t)<k) return INT_MIN; //k is larger than tree size
  if(get_sz(t->l)==k-1) return t->bk;
  if(get_sz(t->l)>k-1)  return kth(k, t->l);
  return kth(k-get_sz(t->l)-1, t->r);
}