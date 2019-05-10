// x: 1-base, p[]: 0-base
template<size_t N>
vector<llf> BM(llf x[N],size_t n){
	size_t f[N]={0},t=0;llf d[N];
	vector<llf> p[N];
	for(size_t i=1,b=0;i<=n;++i) {
		for(size_t j=0;j<p[t].size();++j)
			d[i]+=x[i-j-1]*p[t][j];
		if(abs(d[i]-=x[i])<=EPS)continue;
		f[t]=i;if(!t){p[++t].resize(i);continue;}
		vector<llf> cur(i-f[b]-1);
		llf k=-d[i]/d[f[b]];cur.PB(-k);
		for(size_t j=0;j<p[b].size();j++)
			cur.PB(p[b][j]*k);
		if(cur.size()<p[t].size())cur.resize(p[t].size());
		for(size_t j=0;j<p[t].size();j++)cur[j]+=p[t][j];
		if(i-f[b]+p[b].size()>=p[t].size()) b=t;
		p[++t]=cur;
	}
	return p[t];
}