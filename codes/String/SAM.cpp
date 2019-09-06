struct Node{
  Node *green, *edge[26];
  int max_len;
  Node(const int _max_len)
    : green(NULL), max_len(_max_len){
    memset(edge,0,sizeof(edge));
  }
} *ROOT, *LAST;
void Extend(const int c) {
  Node *cursor = LAST;
  LAST = new Node((LAST->max_len) + 1);
  for(;cursor&&!cursor->edge[c]; cursor=cursor->green)
    cursor->edge[c] = LAST;
  if (!cursor)
    LAST->green = ROOT;
  else {
    Node *potential_green = cursor->edge[c]; 
    if((potential_green->max_len)==(cursor->max_len+1))
      LAST->green = potential_green;
    else {
//assert(potential_green->max_len>(cursor->max_len+1));
      Node *wish = new Node((cursor->max_len) + 1);
      for(;cursor && cursor->edge[c]==potential_green;
           cursor = cursor->green)
        cursor->edge[c] = wish;
      for (int i = 0; i < 26; i++)
        wish->edge[i] = potential_green->edge[i];
      wish->green = potential_green->green;         
      potential_green->green = wish;                
      LAST->green = wish;                           
    }
  }
}
char S[10000001], A[10000001];
int N;
int main(){
  scanf("%d%s", &N, S);
  ROOT = LAST = new Node(0);
  for (int i = 0; S[i]; i++)
    Extend(S[i] - 'a');
  while (N--){
    scanf("%s", A);
    Node *cursor = ROOT;
    bool ans = true;
    for (int i = 0; A[i]; i++){
      cursor = cursor->edge[A[i] - 'a'];
      if (!cursor) {
        ans = false;
        break;
      }
    }
    puts(ans ? "Yes" : "No");
  }
  return 0;
}