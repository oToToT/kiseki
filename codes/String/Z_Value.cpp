char s[MAXN];
int len,z[MAXN];
void Z_value() {
  int i,j,left,right;
  z[left=right=0]=len;
  for(i=1;i<len;i++) {
    j=max(min(z[i-left],right-i),0);
    for(;i+j<len&&s[i+j]==s[j];j++);
    if(i+(z[i] = j)>right) {
      right=i+z[i];
      left=i;
    }
  }
}
