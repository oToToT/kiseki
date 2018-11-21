class MiniCostMaxiFlow{
    using CapT = int;
    using WeiT = lld;
    using PCW = pair<CapT, WeiT>;
    static const CapT INF_CAP = 1<<30;
    static const WeiT INF_WEI = 1LL<<60;
    static const int MAXV = N;
private:
    struct Edge{
        int to, back;
        WeiT wei;
        CapT cap;
        Edge(){}
        Edge(int a, int b, WeiT c, CapT d): to(a), back(b), wei(c), cap(d) {}
    };
    int ori, edd, V;
    vector<Edge> G[MAXV];
    int fa[MAXV], wh[MAXV];
    bool inq[MAXV];
    WeiT dis[MAXV];
    PCW SPFA(){
        for(int i=0;i<V;i++) inq[i]=0;
        for(int i=0;i<V;i++) dis[i]=INF_WEI;
        queue<int> qq;
        qq.push(ori);
        dis[ori]=0;
        while(!qq.empty()){
            int u = qq.front(); qq.pop();
            inq[u]=0;
            for(int i=0;i<SZ(G[u]);i++){
                Edge e = G[u][i];
                int v = e.to;
                WeiT d = e.wei;
                if(e.cap > 0 and dis[v] > dis[u]+d){
                    dis[v]=dis[u]+d;
                    fa[v]=u;
                    wh[v] = i;
                    if(inq[v]) continue;
                    qq.push(v);
                    inq[v]=1;
                }
            }
        }
        if(dis[edd]==INF_WEI) return {-1, -1};
        CapT mw=INF_CAP;
        for(int i=edd;i!=ori;i=fa[i]){
            mw = min(mw, G[fa[i]][wh[i]].cap);
        }
        for(int i=edd;i!=ori;i=fa[i]){
            auto &eg = G[fa[i]][wh[i]];
            eg.cap -= mw;
            G[eg.to][eg.back].cap += mw;
        }
        return {mw, dis[edd]};
    }
public:
    void init(int a, int b, int n=MAXV){
        V=n;
        ori = a;
        edd = b;
        for(int i=0;i<n;i++) G[i].clear();
    }
    void addEdge(int st, int ed, WeiT w, CapT c){
        G[st].PB(Edge(ed, SZ(G[ed]), w, c));
        G[ed].PB(Edge(st, SZ(G[st])-1, -w, 0));
    }
    PCW solve(){
        CapT cc=0; WeiT ww=0;
        while(true){
            PCW ret = SPFA();
            if(ret.FF==-1) break;
            cc += ret.FF;
            ww += ret.SS;
        }
        return {cc, ww};
    }
} mcmf;