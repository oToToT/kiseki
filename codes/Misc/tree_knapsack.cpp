int dp[N][K];PII obj[N];
vector<int> G[N];
void dfs(int u, int mx){
  for(int s: G[u]) {
    if(mx < obj[s].first) continue;
    for(int i=0;i<=mx-obj[s].FF;i++)
      dp[s][i] = dp[u][i];
    dfs(s, mx - obj[s].first);
    for(int i=obj[s].FF;i<=mx;i++)
      dp[u][i] = max(dp[u][i], 
        dp[s][i - obj[s].FF] + obj[s].SS);
  }
}
int main(){
  int n, k; cin >> n >> k;
  for(int i=1;i<=n;i++){
    int p; cin >> p;
    G[p].push_back(i);
    cin >> obj[i].FF >> obj[i].SS;
  }
  dfs(0, k); int ans = 0;
  for(int i=0;i<=k;i++) ans = max(ans, dp[0][i]);
  cout << ans << '\n';
  return 0;
}