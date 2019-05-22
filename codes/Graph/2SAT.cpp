class TwoSat{
  private:
    int n;
    vector<vector<int>> rG,G,sccs;
    vector<int> ord,idx;
    vector<bool> vis,result;
    void dfs(int u){
      vis[u]=true;
      for(int v:G[u])
        if(!vis[v])
          dfs(v);
      ord.push_back(u);
    }
    void rdfs(int u){
      vis[u]=false;
      idx[u]=sccs.size()-1;
      sccs.back().push_back(u);
      for(int v:rG[u])
        if(vis[v])
          rdfs(v);
    }
  public:
    void init(int n_){
      n=n_;
      G.clear();
      G.resize(n);
      rG.clear();
      rG.resize(n);
      sccs.clear();
      ord.clear();
      idx.resize(n);
      result.resize(n);
    }
    void add_edge(int u,int v){
      G[u].push_back(v);
      rG[v].push_back(u);
    }
    void orr(int x,int y){
      if ((x^y)==1)return;
      add_edge(x^1,y);
      add_edge(y^1,x);
    }
    bool solve(){
      vis.clear();
      vis.resize(n);
      for(int i=0;i<n;++i)
        if(not vis[i])
          dfs(i);
      reverse(ord.begin(),ord.end());
      for (int u:ord){
        if(!vis[u])
          continue;
        sccs.push_back(vector<int>());
        rdfs(u);
      }
      for(int i=0;i<n;i+=2)
        if(idx[i]==idx[i+1])
          return false;
      vector<bool> c(sccs.size());
      for(size_t i=0;i<sccs.size();++i){
        for(size_t j=0;j<sccs[i].size();++j){
          result[sccs[i][j]]=c[i];
          c[idx[sccs[i][j]^1]]=!c[i];
        }
      }
      return true;
    }
    bool get(int x){return result[x];}
    inline int get_id(int x){return idx[x];}
    inline int count(){return sccs.size();}
} sat2;