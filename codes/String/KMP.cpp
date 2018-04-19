int F[N<<1];
void KMP(char s1[], char s2[], int n, int m){
    // make F[] for s1+'\0'+s2;
    char ss[N<<1];
    int len = n+m+1;
    for(int i=0;i<n;i++) ss[i] = s1[i];
    ss[n] = '\0';
    for(int i=0;i<m;i++) ss[i+1+n] = s2[i];
    F[0] = F[1] = 0;
    for(int i=1;i<len;i++){
        int j = F[i];
        while(j > 0 and ss[i]!=ss[j]) j = F[j];
        F[i+1] = (ss[i]==ss[j]?j+1:0);
    }
    // just find (F[len2+i] == len2), i from 1 to len+1 for matching
}
