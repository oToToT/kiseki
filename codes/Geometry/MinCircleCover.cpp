template<typename T>
Circle<llf> MinCircleCover(const vector<Point<T>>& pts){
    random_shuffle(ALL(pt));
    Circle<llf> c = {pt[0], 0};
    int n = SZ(pts);
    for(int i=0;i<n;i++){
        if(pt[i].in(c)) continue;
        c = {pt[i], 0};
        for(int j=0;j<i;j++){
            if(pt[j].in(c)) continue;
            c.o = (pt[i] + pt[j]) / 2;
            c.r = pt[i].dis(c.o);
            for(int k=0;k<j;k++){
                if(pt[k].in(c)) continue;
                c = get_circum(pt[i], pt[j], pt[k]);
            }
        }
    }
    return c;
}