struct palindromic_tree{
  struct node{
    int next[26],f,len;
    int cnt,num,st,ed;
    node(int l=0):f(0),len(l),cnt(0),num(0){
      memset(next, 0, sizeof(next));
    }
  };
  vector<node> state;
  vector<char> s;
  int last,n;
  void init(){
    state.clear();s.clear();last=1; n=0;
    state.push_back(0);state.push_back(-1);
    state[0].f=1;s.push_back(-1);
  }
  int getFail(int x){
    while(s[n-state[x].len-1]!=s[n])x=state[x].f;
    return x;
  }
  void add(int c){
    s.push_back(c-='a'); ++n;
    int cur=getFail(last);
    if(!state[cur].next[c]){
      int now=state.size();
      state.push_back(state[cur].len+2);
      state[now].f=state[getFail(state[cur].f)].next[c];
      state[cur].next[c]=now;
      state[now].num=state[state[now].f].num+1;
    }
    last=state[cur].next[c];
    ++state[last].cnt;
  }
  int size(){
    return state.size()-2;
  }
} pt;
int main() {
  string s; cin >> s; pt.init();
  for (int i=0; i<SZ(s); i++) {
    int prvsz = pt.size(); pt.add(s[i]);
    if (prvsz != pt.size()) {
      int r = i, l = r - pt.state[pt.last].len + 1;
      // pal @ [l,r]: s.substr(l, r-l+1)
    }
  }
  return 0;
}