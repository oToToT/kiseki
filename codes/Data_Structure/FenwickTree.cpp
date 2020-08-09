template<typename T>
class BIT{
#define ALL(x) begin(x), end(x)
private:
  vector<T> arr;
  int n;
  inline int lowbit(int x){return x & (-x);}
  T query(int x){
    T ret = 0;
    while(x > 0){
      ret += arr[x];
      x -= lowbit(x);
    }
    return ret;
  }
public:
  void init(int n_){
    n = n_;
    arr.resize(n);
    fill(arr.begin(), arr.end(), 0);
  }
  void modify(int pos, T v){
    while(pos < n){
      arr[pos] += v;
      pos += lowbit(pos);
    }
  }
  T query(int l, int r){
    // 1-base (l, r]
    return query(r) - query(l);
  }
#undef ALL
};

template<typename T>
class BIT{
#define ALL(x) begin(x), end(x)
private:
  vector<T> arr;
  int n;
  inline int lowbit(int x){return x & (-x);}
  void add(int s, int v){
    while(s){
      arr[s]+=v;
      s-=lowbit(s);
    }
  }
public:
  void init(int n_){
    n = n_;
    arr.resize(n);
    fill(ALL(arr), 0);
  }
  void add(int l, int r, T v){
    //1-base (l, r]
    add(l, -v);
    add(r, v);
  }
  T query(int x){
    T r=0;
    while(x<size){
      r+=arr[x];
      x+=lowbit(x);
    }
    return r;
  }
#undef ALL
};
