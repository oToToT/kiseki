int F[N];
int match(const std::string& A, const std::string& B) {
	F[0] = -1, F[1] = 0;
	for (int i=1, j=0; i < B.size()-1; F[++i] = ++j) { // calculate failure function
		if (B[i] == B[j]) F[i] = F[j]; // optimization by Knuth, may not need this
		while (j != -1 && B[i] != B[j]) j = F[j];
	}
	for (int i=0, j=0; i-j+B.size() <= A.size(); i++, j++) { // match
		while (j != -1 && A[i] != B[j]) j = F[j];
		if (j == B.size() - 1) return i - j; // match successfully at string B's end return result
	}
	return -1;
}
