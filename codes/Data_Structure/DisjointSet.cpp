class DJS{
	private:
		vector<int> fa, sz, sv;
		vector<pair<int*, int>> opt;
		inline void assign(int *k, int v){
			opt.PB({k, *k});
			*k = v;
		}
	public:
		inline void init(int n){
			fa.resize(n);
			sz.resize(n);
			for(int i=0;i<n;i++){
				fa[i] = i;
				sz[i] = 1;
			}
			opt.clear();
		}
		int query(int x){
			if(fa[x] == x) return x;
			return query(fa[x]);
		}
		inline void merge(int a, int b){
			int af = query(a), bf = query(b);
			if(af == bf) return;
			if(sz[af] < sz[bf]) swap(af, bf);
			assign(&fa[bf], fa[af]);
			assign(&sz[af], sz[af]+sz[bf]);
		}
		inline void save(){sv.PB(SZ(opt));}
		inline void undo(){
			int ls = sv.back(); sv.pop_back();
			while(SZ(opt) > ls){
				pair<int*, int> cur=opt.back();
				*cur.FF = cur.SS;
				opt.pop_back();
			}
		}
}