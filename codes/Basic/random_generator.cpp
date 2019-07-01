template<class T,T x1,T x2,T x3,int y1,int y2,int y3>
struct PRNG {
  using S = typename std::make_signed<T>::type;
  T s;
  PRNG(T _s = 0) : s(_s) {}
  T next() {
    T z = (s += x1);
    z = (z ^ (z >> y1)) * x2;
    z = (z ^ (z >> y2)) * x3;
    return z ^ (z >> y3);
  }
  T next(T n) { return next() % n; }
  S next(S l, S r){return l+next(r-l+1);}
  T operator()() { return next(); }
  T operator()(T n) { return next(n); }
  S operator()(S l, S r) { return next(l, r); }
  static T gen(T s) { return PRNG(s)(); }
  template<class U>
  void shuffle(U first,U last){
    size_t n=last-first;
    for(size_t i=0;i<n;i++)
      swap(first[i],first[next(i+1)]);
  }
};
using R32=PRNG<uint32_t,0x9E3779B1,0x85EBCA6B,
0xC2B2AE35,16,13,16>;
R32 r32;
using R64=PRNG<uint64_t,0x9E3779B97F4A7C15,
0xBF58476D1CE4E5B9,0x94D049BB133111EB,30,27,31>;
R64 r64;
