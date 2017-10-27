#include <string>
typedef long long lld;
const int N = 1000000;
class Hash{
    private:
        const lld p = 127, q = 1208220623;
        int sz;
        lld prefix[N], power[N];
    public:
        void init(const std::string &x){
            sz = x.size();
            prefix[0]=0;
            for(int i=1;i<=sz;i++) prefix[i]=((prefix[i-1]*p)%q+x[i-1])%q;
            power[0]=1;
            for(int i=1;i<=sz;i++) power[i]=(power[i-1]*p)%q;
        }
        lld query(int l, int r){
            // 1-base (l, r]
            return (prefix[r] - (prefix[l]*power[r-l])%q + q)%q;
        }
};