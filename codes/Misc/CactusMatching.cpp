const int maxn=200010;
vector<int> init_g[maxn],g[maxn*2];
int dfn[maxn],low[maxn],par[maxn],dfs_idx,bcc_id;
int n;
void tarjan(int u){
  dfn[u]=low[u]=++dfs_idx;
  for(int i=0;i<(int)init_g[u].size();i++){
    int v=init_g[u][i];
    if(v==par[u]) continue;
    if(!dfn[v]){
      par[v]=u;
      tarjan(v);
      low[u]=min(low[u],low[v]);
      if(dfn[u]<low[v]){
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }else{
      low[u]=min(low[u],dfn[v]);
      if(dfn[v]<dfn[u]){
        int temp_v=u;
        bcc_id++;
        while(temp_v!=v){
          g[bcc_id+n].push_back(temp_v);
          g[temp_v].push_back(bcc_id+n);
          temp_v=par[temp_v];
        }
        g[bcc_id+n].push_back(v);
        g[v].push_back(bcc_id+n);
        reverse(g[bcc_id+n].begin(),g[bcc_id+n].end());
      }
    }
  }
}
int dp[maxn][2],min_dp[2][2],tmp[2][2],tp[2];
void dfs(int u,int fa){
  if(u<=n){
    for(int i=0;i<(int)g[u].size();i++){
      int v=g[u][i];
      if(v==fa) continue;
      dfs(v,u);
      memset(tp,0x8f,sizeof tp);
      if(v<=n){
        tp[0]=dp[u][0]+max(dp[v][0],dp[v][1]);
        tp[1]=max(
          dp[u][0]+dp[v][0]+1,
          dp[u][1]+max(dp[v][0],dp[v][1])
        );
      }else{
        tp[0]=dp[u][0]+dp[v][0];
        tp[1]=max(dp[u][0]+dp[v][1],dp[u][1]+dp[v][0]);
      }
      dp[u][0]=tp[0],dp[u][1]=tp[1];
    }
  }else{
    for(int i=0;i<(int)g[u].size();i++){
      int v=g[u][i];
      if(v==fa) continue;
      dfs(v,u);
    }
    min_dp[0][0]=0;
    min_dp[1][1]=1;
    min_dp[0][1]=min_dp[1][0]=-0x3f3f3f3f;
    for(int i=0;i<(int)g[u].size();i++){
      int v=g[u][i];
      if(v==fa) continue;
      memset(tmp,0x8f,sizeof tmp);
      tmp[0][0]=max(
        min_dp[0][0]+max(dp[v][0],dp[v][1]),
        min_dp[0][1]+dp[v][0]
      );
      tmp[0][1]=min_dp[0][0]+dp[v][0]+1;
      tmp[1][0]=max(
        min_dp[1][0]+max(dp[v][0],dp[v][1]),
        min_dp[1][1]+dp[v][0]
      );
      tmp[1][1]=min_dp[1][0]+dp[v][0]+1;
      memcpy(min_dp,tmp,sizeof tmp);
    }
    dp[u][1]=max(min_dp[0][1],min_dp[1][0]);
    dp[u][0]=min_dp[0][0];
  }
}
int main(){
  int m,a,b;
  scanf("%d%d",&n,&m);
  for(int i=0;i<m;i++){
    scanf("%d%d",&a,&b);
    init_g[a].push_back(b);
    init_g[b].push_back(a);
  }
  par[1]=-1;
  tarjan(1);
  dfs(1,-1);
  printf("%d\n",max(dp[1][0],dp[1][1]));
  return 0;
}