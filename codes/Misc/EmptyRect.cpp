int max_empty_rect(int n, int m, bool blocked[N][N]){
    static int mxu[2][N], me=0,he=1,ans=0;
    for(int i=0;i<m;i++) mxu[he][i]=0;
    for(int i=0;i<n;i++){
        stack<PII,vector<PII>> stk;
        for(int j=0;j<m;++j){
            if(blocked[i][j]) mxu[me][j]=0;
            else mxu[me][j]=mxu[he][j]+1;
            int la = j;
            while(!stk.empty()&&stk.top().FF>mxu[me][j]){
                int x1 = i - stk.top().FF, x2 = i;
                int y1 = stk.top().SS, y2 = j;
                la = stk.top().SS; stk.pop();
                ans=max(ans,(x2-x1)*(y2-y1));
            }
            if(stk.empty()||stk.top().FF<mxu[me][j])
                stk.push({mxu[me][j],la});
        }
        while(!stk.empty()){
            int x1 = i - stk.top().FF, x2 = i;
            int y1 = stk.top().SS-1, y2 = m-1;
            stk.pop();
            ans=max(ans,(x2-x1)*(y2-y1));
        }
        swap(me,he);
    }
    return ans;
}