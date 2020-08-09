template<typename T>
class ConvexHull_2D{
private:
  typedef Point<T> PT;
  vector<PT> d;
  struct myhash{
    uint64_t operator()(const PT& a) const {
      uint64_t xx=0, yy=0;
      memcpy(&xx, &a.x, sizeof(a.x));
      memcpy(&yy, &a.y, sizeof(a.y));
      uint64_t ret = xx*17+yy*31;
      ret = (ret ^ (ret >> 16))*0x9E3779B1;
      ret = (ret ^ (ret >> 13))*0xC2B2AE35;
      ret = ret ^ xx;
      return (ret ^ (ret << 3)) * yy;
    }	
  };
  unordered_set<PT, myhash> in_hull;
public:
  void init(){in_hull.clear();d.clear();}
  void insert(const PT& x){d.PB(x);}
  void solve(){
    sort(ALL(d), [](const PT& a, const PT& b){
      return tie(a.x, a.y) < tie(b.x, b.y);});
    vector<PT> s(SZ(d)<<1); int o = 0;
    for(auto p: d) {
      while(o>=2 && cross(p-s[o-2],s[o-1]-s[o-2])<=0)
        o--;
      s[o++] = p;
    }
    for(int i=SZ(d)-2, t = o+1;i>=0;i--){
      while(o>=t&&cross(d[i]-s[o-2],s[o-1]-s[o-2])<=0)
        o--;
      s[o++] = d[i];
    }
    s.resize(o-1); swap(s, d);
    for(auto i: s) in_hull.insert(i);
  }
  vector<PT> get(){return d;}
  bool in_it(const PT& x){
    return in_hull.find(x)!=in_hull.end();}
};
