struct palindromic_tree{
  struct node{
    int next[26],f,len;
    int cnt,num,st,ed;
    node(int l=0):f(0),len(l),cnt(0),num(0) {
      memset(next, 0, sizeof(next)); }
  };
  vector<node> st;
  vector<char> s;
  int last,n;
  void init(){
    st.clear();s.clear();last=1; n=0;
    st.push_back(0);st.push_back(-1);
    st[0].f=1;s.push_back(-1); }
  int getFail(int x){
    while(s[n-st[x].len-1]!=s[n])x=st[x].f;
    return x;}
  void add(int c){
    s.push_back(c-='a'); ++n;
    int cur=getFail(last);
    if(!st[cur].next[c]){
      int now=st.size();
      st.push_back(st[cur].len+2);
      st[now].f=st[getFail(st[cur].f)].next[c];
      st[cur].next[c]=now;
      st[now].num=st[st[now].f].num+1;
    }
    last=st[cur].next[c];
    ++st[last].cnt;}
  int size(){ return st.size()-2;}
} pt;
int main() {
  string s; cin >> s; pt.init();
  for (int i=0; i<SZ(s); i++) {
    int prvsz = pt.size(); pt.add(s[i]);
    if (prvsz != pt.size()) {
      int r = i, l = r - pt.st[pt.last].len + 1;
      // pal @ [l,r]: s.substr(l, r-l+1)
    }
  }
  return 0;
}