template<typename T>
Circle<llf> MinCircleCover(const vector<PT>& pts){
	random_shuffle(ALL(pts));
	Circle<llf> c = {pts[0], 0};
	for(int i=0;i<SZ(pts);i++){
		if(pts[i].in(c)) continue;
		c = {pts[i], 0};
		for(int j=0;j<i;j++){
			if(pts[j].in(c)) continue;
			c.o = (pts[i] + pts[j]) / 2;
			c.r = pts[i].dis(c.o);
			for(int k=0;k<j;k++){
				if(pts[k].in(c)) continue;
				c = get_circum(pts[i], pts[j], pts[k]);
			}
		}
	}
	return c;
}