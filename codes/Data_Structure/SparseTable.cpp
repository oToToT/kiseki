template<typename T, typename Cmp_=std::less<T>>
class SparseTable{
	private:
		vector<vector<T>> table;
		vector<int> lg;
		T cmp_(T a, T b){
		    return Cmp_()(a, b)?a:b;
		}
	public:
		void init(T arr[], int n){
			// 0-base
			lg.resize(n+1);
			lg[0] = -1, lg[1] = 0;
			for(int i=2;i<=n;i++) lg[i] = lg[i>>1]+1;
			table.resize(lg[n]+1);
			table[0].resize(n);
			for(int i=0;i<n;i++) table[0][i] = arr[i];
			for(int i=1;i<=lg[n];i++){
				int len = 1<<(i-1), sz = 1<<i;
				table[i].resize(n-sz+1);
				for(int j=0;j<=n-sz;j++){
					table[i][j] = cmp_(table[i-1][j], table[i-1][j+len]);
				}
			}
		}
		T query(int l, int r){
			// 0-base [l, r)
			int wh = lg[r-l], len=1<<wh;
			return cmp_(table[wh][l], table[wh][r-len]);
		}
};