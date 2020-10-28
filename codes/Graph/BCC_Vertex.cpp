class BCC {
	private:
		int n, t, ecnt;
		vector<vector<pair<int, int>>> G;
		vector<int> low, tin, st, bcc;
		vector<bool> ap, ins;
		void dfs(int x, int p) {
			tin[x] = low[x] = ++t;
			int ch = 0;
			for (auto u: G[x]) {
				if (u.first == p) continue;
				if (not ins[u.second]) {
					st.push_back(u.second);
					ins[u.second] = true;
				}
				if (tin[u.first]) {
					low[x] = min(low[x], tin[u.first]);
					continue;
				}
				++ch; dfs(u.first, x);
				low[x] = min(low[x], low[u.first]);
				if (low[u.first] >= tin[x]) {
					ap[x] = true; ++ecnt;
					while (true) {
						int e = st.back(); st.pop_back();
						bcc[e] = ecnt;
						if (e == u.second) break;
					}
				}
			}
			if (ch == 1 and p == x) ap[x] = false;
		}
	public:
		void init(int n_) {
			n = n_, ecnt = 0; st.clear();
			G.clear(); G.resize(n);
			low.clear(); tin.clear();
			ap.assign(n, false);
		}
		void add_edge(int u, int v) {
			G[u].emplace_back(v, ecnt);
			G[v].emplace_back(u, ecnt++);
		}
		void solve() {
			ecnt = 0; bcc.resize(t);
			ins.assign(t, false);
			for (int i = 0; i < n; ++i)
				if (low[i] == 0) dfs(i, i);
		}
		int get_id(int x) { return bcc[x];; }
		int count() { return ecnt; }
		bool is_ap(int x) { return ap[x]; }
};

