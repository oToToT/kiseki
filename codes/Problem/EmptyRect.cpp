int largest_empty_rectangle(){
    int max_area = 0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j)
            if (array[i][j]) wl[j] = wl[j-1] + 1;
            else wl[j] = 0;
        for (int j=n; j>=1; --j)
            if (array[i][j]) wr[j] = wr[j+1] + 1;
            else wr[j] = 0;
        for (int j=1; j<=n; ++j)
            if (array[i][j]) h[j] = h[j] + 1;
            else h[j] = 0;
         for (int j=1; j<=n; ++j)
            if (l[j] == 0) l[j] = wl[j];
            else l[j] = min(wl[j], l[j]);
        for (int j=1; j<=n; ++j)
            if (r[j] == 0) r[j] = wr[j];
            else r[j] = min(wr[j], r[j]);
        for (int j=1; j<=n; ++j)
            max_area = max(max_area, (l[j] + r[j] - 1) * h[j]);
    }
    return max_area;
}