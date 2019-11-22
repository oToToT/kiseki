struct DLX {
	const static int maxn=210;
	const static int maxm=210;
	const static int maxnode=210*210;
	int n, m, size, row[maxnode], col[maxnode];
	int U[maxnode], D[maxnode], L[maxnode], R[maxnode];
	int H[maxn], S[maxm], ansd, ans[maxn];
	void init(int _n, int _m) {
		n = _n, m = _m;
		for(int i = 0; i <= m; ++i) {
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i-1, R[i] = i+1;
		}
		R[L[0] = size = m] = 0;
		for(int i = 1; i <= n; ++i) H[i] = -1;
	}
	void Link(int r, int c) {
		++S[col[++size] = c];
		row[size] = r; D[size] = D[c];
		U[D[c]] = size; U[size] = c; D[c] = size;
		if(H[r] < 0) H[r] = L[size] = R[size] = size;
		else {
			R[size] = R[H[r]];
			L[R[H[r]]] = size;
			L[size] = H[r];
			R[H[r]] = size;
		}
	}
	void remove(int c) {
		L[R[c]] = L[c]; R[L[c]] = R[c];
		for(int i = D[c]; i != c; i = D[i])
			for(int j = R[i]; j != i; j = R[j]) {
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[col[j]];
			}
	}
	void resume(int c) {
		L[R[c]] = c; R[L[c]] = c;
		for(int i = U[c]; i != c; i = U[i])
			for(int j = L[i]; j != i; j = L[j]) {
				U[D[j]] = j;
				D[U[j]] = j;
				++S[col[j]];
		}
	}
	void dance(int d) {
		if(d>=ansd) return;
		if(R[0] == 0) {
			ansd = d;
			return;
		}
		int c = R[0];
		for(int i = R[0]; i; i = R[i])
			if(S[i] < S[c]) c = i;
		remove(c);
		for(int i = D[c]; i != c; i = D[i]) {
			ans[d] = row[i];
			for(int j = R[i]; j != i; j = R[j])
				remove(col[j]);
			dance(d+1);
			for(int j = L[i]; j != i; j = L[j])
				resume(col[j]);
		}
		resume(c);
	}
} sol;