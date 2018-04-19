class BCC{
private:
    int low[N], dfn[N], cnt;
    bool bcc[N];
    vector<PII> G[N];
    void dfs(int w, int f){
        dfn[w] = cnt++;
        low[w] = dfn[w];
        for(auto i: G[w]){
            int u = i.FF, t = i.SS;
            if(u == f) continue;
            if(dfn[u]!=0){
                low[w] = min(low[w], dfn[u]);
            }else{
                dfs(u, w);
                low[w] = min(low[w], low[u]);
                if(low[u] > dfn[w]) bcc[t] = true;
            }
        }
    }
public:
    void init(int n, int m){
        for(int i=0;i<n;i++) G[i].clear();
        fill(bcc, bcc+m, false);
        cnt = 0;
    }
    void add_edge(int u, int v){
        G[u].PB({v, cnt});
        G[v].PB({u, cnt});
        cnt++;
    }
    void solve(){cnt = 1;dfs(0, 0);}
    // the id will be same as insert order, 0-base
    bool is_bcc(int x){return bcc[x];}
} bcc;
