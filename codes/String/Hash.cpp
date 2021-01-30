class Hash {
  private:
    static constexpr int P = 127, Q = 1051762951;
    vector<int> h, p;
  public:
    void init(const string &s){
      h.assign(s.size()+1, 0); p.resize(s.size()+1);
      for (size_t i = 0; i < s.size(); ++i)
        h[i + 1] = add(mul(h[i], P), s[i]);
      generate(p.begin(), p.end(),[x=1,y=1,this]()
          mutable{y=x;x=mul(x,P);return y});
    }
    int query(int l, int r){ // 1-base (l, r]
      return sub(h[r], mul(h[l], p[r-l]));}
};
