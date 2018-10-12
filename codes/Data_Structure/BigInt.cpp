class BigInt{
	private:
		using lld = int_fast64_t;
		#define PRINTF_ARG PRIdFAST64
		#define LOG_BASE_STR "9"
		static constexpr lld BASE = 1000000000;
		static constexpr int LOG_BASE = 9;
		vector<lld> dig;
		bool neg;
		inline int len()const{return (int)dig.size();}
		inline int cmp_minus(const BigInt& a) const {
			if(len() == 0 and a.len() == 0) return 0;
			if(neg ^ a.neg) return (int)a.neg*2 - 1;
			if(len() != a.len()) return neg?a.len()-len():len()-a.len();
			for(int i=len()-1;i>=0;i--) if(dig[i] != a.dig[i]) {
				return neg?a.dig[i]-dig[i]:dig[i]-a.dig[i];
			}
			return 0;
		}
		inline void trim(){
			while(!dig.empty() and dig.back()==0) dig.pop_back();
			if(dig.empty()) neg = false;
		}
	public:
		BigInt(): dig(vector<lld>()), neg(false){}
		BigInt(lld a): dig(vector<lld>()){
			neg = a<0; dig.push_back(abs(a));
			trim();
		}
		BigInt(const string& a): dig(vector<lld>()){
			assert(!a.empty()); neg = (a[0]=='-');
			for(int i=((int)(a.size()))-1;i>=neg;i-=LOG_BASE){
				lld cur = 0;
				for(int j=min(LOG_BASE-1, i-neg);j>=0;j--) cur = cur*10+a[i-j]-'0';
				dig.push_back(cur);
			} trim();
		}
		inline bool operator<(const BigInt& a)const{return cmp_minus(a)<0;}
		inline bool operator<=(const BigInt& a)const{return cmp_minus(a)<=0;}
		inline bool operator==(const BigInt& a)const{return cmp_minus(a)==0;}
		inline bool operator!=(const BigInt& a)const{return cmp_minus(a)!=0;}
		inline bool operator>(const BigInt& a)const{return cmp_minus(a)>0;}
		inline bool operator>=(const BigInt& a)const{return cmp_minus(a)>=0;}
		BigInt operator-() const {
			BigInt ret = *this;
			ret.neg ^= 1;
			return ret;
		}
		BigInt operator+(const BigInt& a) const {
			if(neg) return -(-(*this)+(-a));
			if(a.neg) return (*this)-(-a);
			int n = max(a.len(), len());
			BigInt ret; ret.dig.resize(n);
			lld pro = 0;
			for(int i=0;i<n;i++) {
				ret.dig[i] = pro;
				if(i < a.len()) ret.dig[i] += a.dig[i];
				if(i < len()) ret.dig[i] += dig[i];
				pro = 0;
				if(ret.dig[i] >= BASE) pro = ret.dig[i]/BASE;
				ret.dig[i] -= BASE*pro;
			}
			if(pro != 0) ret.dig.push_back(pro);
			return ret;
		}
		BigInt operator-(const BigInt& a) const {
			if(neg) return -(-(*this) - (-a));
			if(a.neg) return (*this) + (-a);
			int diff = cmp_minus(a);
			if(diff < 0) return -(a - (*this));
			if(diff == 0) return 0;
			BigInt ret; ret.dig.resize(len(), 0);
			for(int i=0;i<len();i++) {
				ret.dig[i] += dig[i];
				if(i < a.len()) ret.dig[i] -= a.dig[i];
				if(ret.dig[i] < 0){
					ret.dig[i] += BASE;
					ret.dig[i+1]--;
				}
			}
			ret.trim();
			return ret;
		}
		BigInt operator*(const BigInt& a) const {
			if(len()==0 or a.len()==0) return 0;
			BigInt ret; ret.dig.resize(len()+a.len()+1);
			ret.neg = neg ^ a.neg;
			for(int i=0;i<len();i++) for(int j=0;j<a.len();j++){
				ret.dig[i+j] += dig[i] * a.dig[j];
				if(ret.dig[i+j] >= BASE) {
					lld x = ret.dig[i+j] / BASE;
					ret.dig[i+j+1] += x;
					ret.dig[i+j] -= x * BASE;
				}
			}
			ret.trim();
			return ret;
		}
		BigInt operator/(const BigInt& a) const {
			assert(a.len());
			if(len() < a.len()) return 0;
			BigInt ret; ret.dig.resize(len()-a.len()+1);
			ret.neg = a.neg;
			for(int i=len()-a.len();i>=0;i--){
				lld l = 0, r = BASE;
				while(r-l > 1){
					lld mid = (l+r)>>1;
					ret.dig[i] = mid;
					if(ret*a <= (neg?-(*this):(*this))) l = mid;
					else r = mid;
				}
				ret.dig[i] = l;
			}
			ret.neg ^= neg; ret.trim();
			return ret;
		}
		BigInt operator%(const BigInt& a) const {
			return (*this) - (*this) / a * a;
		}
		friend BigInt abs(BigInt a){
			a.neg ^= 1; return a;
		}
		friend void swap(BigInt& a, BigInt& b){
			swap(a.dig, b.dig); swap(a.neg, b.neg);
		}
		friend istream& operator>>(istream& ss, BigInt& a){
			string s; ss >> s;
			a = s;
			return ss;
		}
		friend ostream& operator<<(ostream& ss, const BigInt& a){
			if(a.len() == 0) return ss << '0';
			if(a.neg) ss << '-';
			ss << a.dig.back();
			for(int i=a.len()-2;i>=0;i--) ss << setw(LOG_BASE) << setfill('0') << a.dig[i];
			return ss;
		}
		inline void print() const {
			if(len() == 0){putchar('0');return;}
			if(neg) putchar('-');
			printf("%" PRINTF_ARG, dig.back());
			for(int i=len()-2;i>=0;i--) printf("%0" LOG_BASE_STR PRINTF_ARG, dig[i]);
		}
		#undef PRINTF_ARG
		#undef LOG_BASE_STR
};
