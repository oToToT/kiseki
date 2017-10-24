/************************ 
 n為分子，d為分母 
 若分數為0則n=0,d=1
 若為負數則負號加在分子 
 必定約到最簡分數 
************************/
#ifndef SUNMOON_FRACTION
#define SUNMOON_FRACTION 
#include<algorithm> 
template<typename T>
struct fraction{
	T n,d;
	fraction(const T &_n=0,const T &_d=1):n(_n),d(_d){
		T t=std::__gcd(n,d);
		n/=t,d/=t;
		if(d<0)n=-n,d=-d;
	}
	fraction operator-()const{
		return fraction(-n,d);
	}
	fraction operator+(const fraction &b)const{
		return fraction(n*b.d+b.n*d,d*b.d);
	}
	fraction operator-(const fraction &b)const{
		return fraction(n*b.d-b.n*d,d*b.d);
	}
	fraction operator*(const fraction &b)const{
		return fraction(n*b.n,d*b.d);
	}
	fraction operator/(const fraction &b)const{
		return fraction(n*b.d,d*b.n);
	}
	fraction operator+=(const fraction &b){
		return *this=fraction(n*b.d+b.n*d,d*b.d);
	}
	fraction operator-=(const fraction &b){
		return *this=fraction(n*b.d-b.n*d,d*b.d);
	}
	fraction operator*=(const fraction &b){
		return *this=fraction(n*b.n,d*b.d);
	}
	fraction operator/=(const fraction &b){
		return *this=fraction(n*b.d,d*b.n);
	}
	bool operator <(const fraction &b)const{
		return n*b.d<b.n*d;
	}
	bool operator >(const fraction &b)const{
		return n*b.d>b.n*d;
	}
	bool operator ==(const fraction &b)const{
		return n*b.d==b.n*d;
	}
	bool operator <=(const fraction &b)const{
		return n*b.d<=b.n*d;
	}
	bool operator >=(const fraction &b)const{
		return n*b.d>=b.n*d;
	}
};
#endif