class BCC{
	private:
		int n, m, cnt, bcnt;
		vector<vector<PII>> G;
		vector<int> low, dfn, ids, sz;
		stack<int> stk;
		void dfs(int w, int f){
			dfn[w] = cnt++;
			low[w] = dfn[w];
			for(auto i: G[w]){
				int u = i.FF, t = i.SS;
				if(u == f) continue;
				if(dfn[u] == -1){
					stk.push(t);
					dfs(u, w);
					if(low[u] >= dfn[w]){
						while(stk.top() != t){
							assert(!stk.empty());
							ids[stk.top()] = bcnt;
							sz[bcnt]++;
							stk.pop();
						}
						ids[stk.top()] = bcnt;
						sz[bcnt]++;
						stk.pop();
						bcnt++;
					}
					low[w] = min(low[w], low[u]);
				}else{
					if(dfn[u] < dfn[w]) stk.push(t);
					low[w] = min(low[w], dfn[u]);
				}
			}
		}
	public:
		void init(int n_, int m_){
			n = n_, m = m_, cnt = 0;
			G.resize(n); fill(ALL(G), vector<PII>());
			low.resize(n);
			dfn.resize(n); fill(ALL(dfn), -1);
			ids.resize(m); sz.resize(m);
		}
		void add_edge(int u, int v){
			assert(0 <= u and u < n);
			assert(0 <= v and v < n);
			G[u].PB({v, cnt});
			G[v].PB({u, cnt});
			cnt++;
		}
		void solve(){
			assert(cnt == m);
			cnt = 1, bcnt = 0;
			for(int i=0;i<n;i++){
				if(dfn[i] != -1) continue;
				while(!stk.empty()) stk.pop();
				dfs(i, i);
			}
		}
		int count(){return bcnt;}
		// get bcc_id of edges, same as inserting order (0-base)
		int get_id(int t){return ids[t];}
		int get_size(int x){return sz[x];}
} bcc;