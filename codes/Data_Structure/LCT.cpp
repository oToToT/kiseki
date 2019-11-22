struct Node{
  Node *par,*ch[2];
  int xor_sum,v;
  bool is_rev;
  Node(int _v){
    v=xor_sum=_v;is_rev=false;
    par=ch[0]=ch[1]=nullptr;
  }
  inline void set_rev(){is_rev^=1;swap(ch[0],ch[1]);}
  inline void down(){
    if(is_rev){
      if(ch[0]!=nullptr) ch[0]->set_rev();
      if(ch[1]!=nullptr) ch[1]->set_rev();
      is_rev=false;
    }
  }
  inline void up(){
    xor_sum=v;
    if(ch[0]!=nullptr){
      xor_sum^=ch[0]->xor_sum;
      ch[0]->par=this;
    }
    if(ch[1]!=nullptr){
      xor_sum^=ch[1]->xor_sum;
      ch[1]->par=this;
    }
  }
  inline bool is_root(){
    return par==nullptr ||\
      (par->ch[0]!=this && par->ch[1]!=this);
  }
  bool is_rch(){return !is_root() && par->ch[1]==this;}
} *node[maxn],*stk[maxn];
int top;
void to_child(Node* p,Node* c,bool dir){
  p->ch[dir]=c;
  p->up();
}
inline void rotate(Node* node){
  Node* par=node->par;
  Node* par_par=par->par;
  bool dir=node->is_rch();
  bool par_dir=par->is_rch();
  to_child(par,node->ch[!dir],dir);
  to_child(node,par,!dir);
  if(par_par!=nullptr && par_par->ch[par_dir]==par)
    to_child(par_par,node,par_dir);
  else node->par=par_par;
}
inline void splay(Node* node){
  Node* tmp=node;
  stk[top++]=node;
  while(!tmp->is_root()){
    tmp=tmp->par;
    stk[top++]=tmp;
  }
  while(top) stk[--top]->down();
  for(Node *fa=node->par;
   !node->is_root();
   rotate(node),fa=node->par)
    if(!fa->is_root())
      rotate(fa->is_rch()==node->is_rch()?fa:node);
}
inline void access(Node* node){
  Node* last=nullptr;
  while(node!=nullptr){
    splay(node);
    to_child(node,last,true);
    last=node;
    node=node->par;
  }
}
inline void change_root(Node* node){
  access(node);splay(node);node->set_rev();
}
inline void link(Node* x,Node* y){
  change_root(x);splay(x);x->par=y;
}
inline void split(Node* x,Node* y){
  change_root(x);access(y);splay(x);
  to_child(x,nullptr,true);y->par=nullptr;
}
inline void change_val(Node* node,int v){
  access(node);splay(node);node->v=v;node->up();
}
inline int query(Node* x,Node* y){
  change_root(x);access(y);splay(y);
  return y->xor_sum;
}
inline Node* find_root(Node* node){
  access(node);splay(node);
  Node* last=nullptr;
  while(node!=nullptr){
    node->down();last=node;node=node->ch[0];
  }
  return last;
}
set<pii> dic;
inline void add_edge(int u,int v){
  if(u>v) swap(u,v);
  if(find_root(node[u])==find_root(node[v])) return;
  dic.insert(pii(u,v));
  link(node[u],node[v]);
}
inline void del_edge(int u,int v){
  if(u>v) swap(u,v);
  if(dic.find(pii(u,v))==dic.end()) return;
  dic.erase(pii(u,v));
  split(node[u],node[v]);
}