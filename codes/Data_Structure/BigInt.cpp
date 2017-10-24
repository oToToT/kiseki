#include<algorithm>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<string>
#include<cmath>
using namespace std;
template<typename T>
inline string to_string(const T& x){
   stringstream ss;
   return ss<<x,ss.str();
}
typedef long long LL;
struct bigN:vector<LL>{
   const static int base=1000000000,width=log10(base);
   bool negative;
   bigN(const_iterator a,const_iterator b):vector<LL>(a,b){}
   bigN(string s){
      if(s.empty())return;
      if(s[0]=='-')negative=1,s=s.substr(1);
      else negative=0;
      for(int i=int(s.size())-1;i>=0;i-=width){
         LL t=0;
         for(int j=max(0,i-width+1);j<=i;++j)
            t=t*10+s[j]-'0';
         push_back(t);
      }
      trim();
   }
   template<typename T>
      bigN(const T &x):bigN(to_string(x)){}
   bigN():negative(0){}
   void trim(){
      while(size()&&!back())pop_back();
      if(empty())negative=0;
   }
   void carry(int _base=base){
      for(size_t i=0;i<size();++i){
         if(at(i)>=0&&at(i)<_base)continue;
         if(i+1u==size())push_back(0);
         int r=at(i)%_base;
         if(r<0)r+=_base;
         at(i+1)+=(at(i)-r)/_base;
         at(i)=r;
      }
   }
   int abscmp(const bigN &b)const{
      if(size()>b.size())return 1;
      if(size()<b.size())return -1;
      for(int i=int(size())-1;i>=0;--i){
         if(at(i)>b[i])return 1;
         if(at(i)<b[i])return -1;
      }
      return 0;
   }
   int cmp(const bigN &b)const{
      if(negative!=b.negative)return negative?-1:1;
      return negative?-abscmp(b):abscmp(b);
   }
   bool operator<(const bigN&b)const{return cmp(b)<0;}
   bool operator>(const bigN&b)const{return cmp(b)>0;}
   bool operator<=(const bigN&b)const{return cmp(b)<=0;}
   bool operator>=(const bigN&b)const{return cmp(b)>=0;}
   bool operator==(const bigN&b)const{return !cmp(b);}
   bool operator!=(const bigN&b)const{return cmp(b)!=0;}
   bigN abs()const{
      bigN res=*this;
      return res.negative=0, res;
   }
   bigN operator-()const{
      bigN res=*this;
      return res.negative=!negative, res;
   }
   bigN operator+(const bigN &b)const{
      if(negative)return -(-(*this)+(-b));
      if(b.negative)return *this-(-b);
      bigN res=*this;
      if(b.size()>size())res.resize(b.size());
      for(size_t i=0;i<b.size();++i)res[i]+=b[i];
      return res.carry(),res.trim(),res;
   }
   bigN operator-(const bigN &b)const{
      if(negative)return -(-(*this)-(-b));
      if(b.negative)return *this+(-b);
      if(abscmp(b)<0)return -(b-(*this));
      bigN res=*this;
      if(b.size()>size())res.resize(b.size());
      for(size_t i=0;i<b.size();++i)res[i]-=b[i];
      return res.carry(),res.trim(),res;
   }
   //operator* using karatsuba
   bigN convert_base(int old_width,int new_width)const{
      vector<long long> p(max(old_width,new_width)+1,1);
      for(size_t i=1;i<p.size();++i)p[i]=p[i-1]*10;
      bigN ans;
      long long cur=0;
      int cur_id=0;
      for(size_t i=0;i<size();++i){
         cur+=at(i)*p[cur_id];
         cur_id+=old_width;
         while(cur_id>=new_width){
            ans.push_back(cur%p[new_width]);
            cur/=p[new_width];
            cur_id-=new_width;
         }
      }
      return ans.push_back(cur),ans.trim(),ans;
   }
   bigN karatsuba(const bigN &b)const{
      bigN res;res.resize(size()*2);
      if(size()<=32){
         for(size_t i=0;i<size();++i)
            for(size_t j=0;j<size();++j)
               res[i+j]+=at(i)*b[j];
         return res;
      }
      size_t k=size()/2;
      bigN a1(begin(),begin()+k);
      bigN a2(begin()+k,end());
      bigN b1(b.begin(),b.begin()+k);
      bigN b2(b.begin()+k,b.end());

      bigN a1b1=a1.karatsuba(b1);
      bigN a2b2=a2.karatsuba(b2);

      for(size_t i=0;i<k;++i)a2[i]+=a1[i];
      for(size_t i=0;i<k;++i)b2[i]+=b1[i];

      bigN r=a2.karatsuba(b2);
      for(size_t i=0;i<a1b1.size();++i)r[i]-=a1b1[i];
      for(size_t i=0;i<a2b2.size();++i)r[i]-=a2b2[i];

      for(size_t i=0;i<r.size();++i)res[i+k]+=r[i];
      for(size_t i=0;i<a1b1.size();++i)res[i]+=a1b1[i];
      for(size_t i=0;i<a2b2.size();++i)res[i+size()]+=a2b2[i];
      return res;
   }
   bigN operator*(const bigN &b)const{
      const static int mul_base=1000000,mul_width=log10(mul_base);
      bigN A=convert_base(width,mul_width);
      bigN B=b.convert_base(width,mul_width);
      int n=max(A.size(),B.size());
      while(n&(n-1))++n;
      A.resize(n),B.resize(n);
      bigN res=A.karatsuba(B);
      res.negative=negative!=b.negative;
      res.carry(mul_base);
      res=res.convert_base(mul_width,width);
      return res.trim(),res;
   }
   bigN operator*(long long b)const{
      bigN res=*this;
      if(b<0)res.negative=!negative,b=-b;
      for(size_t i=0,is=0;i<res.size()||is;++i){
         if(i==res.size())res.push_back(0);
         long long a=res[i]*b+is;
         is=a/base;
         res[i]=a%base;
      }
      return res.trim(),res;
   }
   bigN operator/(const bigN &b)const{
      int norm=base/(b.back()+1);
      bigN x=abs()*norm;
      bigN y=b.abs()*norm;
      bigN q,r;
      q.resize(x.size());
      for(int i=int(x.size())-1;i>=0;--i){
         r=r*base+x[i];
         int s1=r.size()<=y.size()?0:r[y.size()];
         int s2=r.size()<y.size()?0:r[y.size()-1];
         int d=(LL(base)*s1+s2)/y.back();
         r=r-y*d;
         while(r.negative)r=r+y,--d;
         q[i]=d;
      }
      q.negative=negative!=b.negative;
      return q.trim(),q;
   }
   bigN operator%(const bigN &b)const{
      return *this-(*this/b)*b;
   }
   friend istream& operator>>(istream &ss,bigN &b){
      string s;
      return ss>>s, b=s, ss;
   }
   friend ostream& operator<<(ostream &ss,const bigN &b){
      if(b.negative)ss<<'-';
      ss<<(b.empty()?0:b.back());
      for(int i=int(b.size())-2;i>=0;--i)
         ss<<setw(width)<<setfill('0')<<b[i];
      return ss;
   }
   template<typename T>
      operator T(){
         stringstream ss;
         ss<<*this;
         T res;
         return ss>>res,res;
      }
};
