static inline int gc() {
  static char buf[1 << 20], *p = buf, *end = buf;
  if (p == end) {
    if ((end = buf + fread(buf, 1, 1 << 20, stdin)) == buf) return EOF;
    p = buf;
  }
  return *p++;
}
template<typename T>
static inline bool gn(T &_){
  register int c = gc(); register T __ = 1; _ = 0;
  while(!isdigit(c) and c!=EOF and c!='-') c = gc();
  if(c == '-') { __ = -1; c = gc(); }
  if(c == EOF) return false;
  while(isdigit(c)) _ = _ * 10 + c - '0', c = gc();
  _ *= __;
  return true;
}
template <typename T, typename ...Args>
static inline bool gn(T &x, Args& ...args){return gn(x) and gn(args...);}
