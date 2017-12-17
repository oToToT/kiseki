// Incorrect and Contain Lots of Bug...
class MaxClique{
	private:
		typedef bitset<N> bits;
		bool poped[N];
		bits G[N], ans;
		int deg[N], deo[N], n;
		void sort_by_degree(){
			memset(poped, 0, sizeof(poped));
			for(int i=0;i<n;i++) deg[i]=G[i].count();
			for(int i=0;i<n;i++){
				int mi = N, id = -1;
				for(int j=0;j<n;j++){
					if(poped[j]) continue;
					if(deg[j] < mi){
						mi = deg[j];
						id = j;
					}
				}
				deo[i] = id;
				// DUMP(deo[i]);
				poped[id] = 1;
				for(int u=G[i]._Find_first();u<n;u=G[i]._Find_next(u)){
					deg[u]--;
				}
			}
			for(int i=0;i<n;i++) deg[i]=G[i].count();
		}
		void BronKerbosch(bits R, bits P, bits X){
			// DEBUG("R: ", R, ", P: ", P, ", X: ", X, '\n');
			if(P.count()==0 and X.count()==0){
				if(R.count() > ans.count()) ans = R;
				return;
			}
			bits cur = P|X; int pivot = -1, sz = -1;
			for(int u=cur._Find_first();u<n;u=cur._Find_next(u)){
				if(deg[u] > sz){
					sz = deg[u];
					pivot = u;
				}
			}
			cur = P&(~G[pivot]), sz = 0;
			for(int u=cur._Find_first();u<n;u=cur._Find_next(u)){
				int pre=R[u]; R[u]=1;
				BronKerbosch(R, P&G[u], X&G[u]);
				R[u]=pre;
				P[u]=0;
				X[u]=1;
			}
		}
	public:
		void init(int n_){
			n = n_;
			for(int i=0;i<n;i++) G[i].reset();
			ans.reset();
		}
		void add_edges(int u, bits S){
			G[u] = S;
		}
		void add_edge(int u, int v){
			G[u][v]=1;
			G[v][u]=1;
		}
		int solve(){
			sort_by_degree();
			bits pob = (1<<n)-1, nob = 0;
			for(int i=0;i<n;i++){
				int v = deo[i];
				BronKerbosch(bits(1<<v), pob&G[v], nob&G[v]);
				pob[v] = 0;
				nob[v] = 1;
			}
			return ans.count();
		}
} cli;