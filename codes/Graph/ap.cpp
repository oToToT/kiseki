#include <bits/stdc++.h>
using namespace std;
#define N 1000000+5

class AP{
	private:
		vector<int> graph[N];
		bitset<N> visited, result;
		int low[N], lv[N];	
		void dfs(int x, int f, int cnt){
			low[x]=cnt;
			lv[x]=cnt;
			visited[x]=1;
			int child=0;
			for(auto i:graph[x]){
				if(i!=f){
					if(visited[i]){
						low[x] = min(low[x], low[i]);
					}else{
						child++;
						dfs(i,x,cnt+1);
						low[x] = min(low[x], low[i]);
						if(low[i] >= lv[x]) result[x]=1;
					}
				}
			}
			if(lv[x]==1 && child <= 1)
				result[x]=0;
		}
	public:
		void init(int sz){
			for(int i=0;i<sz;i++) graph[i].clear();
			visited.reset(); result.reset();
		}
		void AddEdge(int u, int v){
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		void solve(){
			dfs(1, 1, 1);
		}
		bool isAP(int x){
			return result[x];
		}
} ap;

int main(){
	int n,m;cin>>n>>m;
	ap.init(n+2);
	for(int i=0;i<m;i++){
		int st,ed;cin>>st>>ed;
		ap.AddEdge(st, ed);
	}
	ap.solve();
	for(int i=1;i<=n;i++) if(ap.isAP(i)) cout<<i<<'\n';
	return 0;
}
