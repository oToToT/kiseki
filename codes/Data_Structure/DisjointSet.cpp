class DJS{
private:
  vector<int> fa, sz, sv;
  vector<pair<int*, int>> opt;
  inline void assign(int *k, int v){
    opt.emplace_back(k, *k);
    *k = v;
  }
public:
  inline void init(int n){
    fa.resize(n); iota(fa.begin(), fa.end(), 0);
    sz.resize(n); fill(sz.begin(), sz.end(), 1);
    opt.clear();
  }
  int query(int x){
    if(fa[x] == x) return x;
    return query(fa[x]);
  }
  inline void merge(int a, int b){
    int af = query(a), bf = query(b);
    if(af == bf) return;
    if(sz[af] < sz[bf]) swap(af, bf);
    assign(&fa[bf], fa[af]);
    assign(&sz[af], sz[af]+sz[bf]);
  }
  inline void save(){sv.push_back((int)opt.size());}
  inline void undo(){
    int ls = sv.back(); sv.pop_back();
    while((int)opt.size() > ls){
      pair<int*, int> cur=opt.back();
      *cur.first = cur.second;
      opt.pop_back();
    }
  }
};