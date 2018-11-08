class SCC{
private:
    int n, num_;
    vector<vector<int>> G, rG;
    vector<int> ord, num;
    bool vis[N];
    void dfs(int u){
        if(vis[u]) return;
        vis[u]=1;
        for(auto v: G[u]) dfs(v);
        ord.PB(u);
    }
    void rdfs(int u){
        if(vis[u]) return;
        num[u] = num_;
        vis[u] = 1;
        for(auto v: rG[u]) rdfs(v);
    }
public:
    inline void init(int n_){
        G.resize(n); rG.resize(n);
        n=n_, num_=0;
        num.resize(n);
        for(int i=0;i<n;i++) G[i].clear();
        for(int i=0;i<n;i++) rG[i].clear();
    }
    inline void add_edge(int st, int ed){
        G[st].PB(ed);
        rG[ed].PB(st);
    }
    void solve(){
        memset(vis, 0, sizeof(vis));
        for(int i=0;i<n;i++){
            if(!vis[i]) dfs(i);
        }
        reverse(ALL(ord));
        memset(vis, 0, sizeof(vis));
        for(auto i: ord){
            if(!vis[i]){
                rdfs(i);
                num_++;
            }
        }
    }
    inline int get_id(int x){return num[x];}
    inline int count(){return num_;}
} scc;
