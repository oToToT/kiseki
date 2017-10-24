class DJS{
	private:
		int arr[N];
	public:
		int query(int x){
			while(arr[x]!=x) x=arr[x];
			return x;
		}
		int merge(int a, int b){
			arr[query(a)]=query(b);
		}
};