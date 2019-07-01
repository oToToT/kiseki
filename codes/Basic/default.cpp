#include <bits/stdc++.h>
using namespace std;
using lld = int64_t;
using llu = uint64_t;
using llf = long double;
using PII = pair<int,int>;
using PIL = pair<int,lld>;
using PLI = pair<lld,int>;
using PLL = pair<lld,lld>;
template<typename T>
using maxHeap = priority_queue<T,vector<T>,less<T>>;
template<typename T>
using minHeap = priority_queue<T,vector<T>,greater<T>>;
#define FF first
#define SS second
#define SZ(x) (int)((x).size())
#define ALL(x) begin(x), end(x)
#define PB push_back
#define WC(x) while((x)--)
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
  s<<"[";
  for(auto it=b;it!=e;it++)s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}
template<typename A, typename B>
ostream& operator<<(ostream &s,const pair<A,B>&p)
{return s<<"("<<p.FF<<","<<p.SS<<")";}
template<typename T>
ostream& operator<<(ostream &s,const vector<T>&c)
{return _out(s,ALL(c));}
bool debug = 0;
#define DUMP(x) if(debug)cerr<<__PRETTY_FUNCTION__<<\
           ":"<<__LINE__<<" - "<<(#x)<<"="<<(x)<<'\n'
template<typename T>
void DEBUG(const T& x){if(debug)cerr<<x;}
template<typename T,typename...Args>
void DEBUG(const T&head,const Args&...tail){
  if(debug){cerr<<head;DEBUG(tail...);}
}
int main(int argc,char* argv[]){
  if(argc>1&&string(argv[1])=="-D")debug=1;
  if(!debug){ios_base::sync_with_stdio(0);cin.tie(0);}
  return 0;
}
