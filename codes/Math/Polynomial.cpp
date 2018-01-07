#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using std::vector;
using std::max;
using std::ostream;
const llf EPS = 1e-9;
class Poly{
    typedef long double llf;
    typedef vector<llf> vlf;
    private:
        vlf arr;
        inline void trim(){
            while(!arr.empty() and fabsl(arr.back())<=EPS) arr.pop_back();
        }
    public:
        Poly():arr(vlf()){}
        Poly(vlf a): arr(a){trim();}
        Poly operator=(const Poly& a){
            arr = a.arr;
            return *this;
        }
        Poly operator+(const Poly& a) const {
            vlf ret;
            ret.resize(max(a.arr.size(), arr.size()), 0);
            for(size_t i=0;i<arr.size();i++) ret[i] += arr[i];
            for(size_t i=0;i<a.arr.size();i++) ret[i] += a.arr[i];
            Poly retret = Poly(ret);
            retret.trim();
            return retret;
        }
        Poly operator+=(const Poly& a) {
            arr.resize(max(arr.size(), a.arr.size()), 0);
            for(size_t i=0;i<a.arr.size();i++) arr[i]+=a.arr[i];
            trim();
            return *this;
        }
        Poly operator*(const Poly& a) const {
            Poly ret;
            for(size_t i=0;i<a.arr.size();i++){
                vlf tmp;
                tmp.resize(i, 0);
                for(auto j: arr) tmp.push_back(j*a.arr[i]);
                ret += Poly(tmp);
            }
            ret.trim();
            return ret;
        }
        Poly operator*=(const Poly& a){
            *this = *this * a;
            return *this;
        }
        Poly operator-(const Poly& a) const {
            return *this + Poly({-1})*a;
        }
        Poly operator-=(const Poly& a) {
            arr.resize(max(arr.size(), a.arr.size()), 0);
            for(size_t i=0;i<a.arr.size();i++) arr[i]-=a.arr[i];
            trim();
            return *this;
        }
        Poly operator/(const Poly& a) const {
            vlf tmp1 = arr, tmp2 = a.arr;
            reverse(tmp1.begin(), tmp1.end());
            reverse(tmp2.begin(), tmp2.end());
            Poly ret;
            for(size_t i=0;i<=tmp1.size()-tmp2.size();i++){
                llf ratio = tmp1[i] / tmp2[0];
                ret = ret * Poly({0, 1}) + Poly({ratio});
                for(size_t j = 0;j<tmp2.size();j++){
                    tmp1[i+j] -= ratio * tmp2[j];
                }
            }
            return ret;
        }
        Poly operator/=(const Poly& a){
            *this = *this / a;
            return *this;
        }
        Poly operator%(const Poly& a) const {
            vlf tmp1 = arr, tmp2 = a.arr;
            reverse(tmp1.begin(), tmp1.end());
            reverse(tmp2.begin(), tmp2.end());
            for(size_t i=0;i<=tmp1.size()-tmp2.size();i++){
                llf ratio = tmp1[i] / tmp2[0];
                for(size_t j = 0;j<tmp2.size();j++){
                    tmp1[i+j] -= ratio * tmp2[j];
                }
            }
            reverse(tmp1.begin(), tmp1.end());
            return Poly(tmp1);
        }
        Poly operator%=(const Poly& a){
            vlf &tmp1 = arr, tmp2 = a.arr;
            reverse(tmp1.begin(), tmp1.end());
            reverse(tmp2.begin(), tmp2.end());
            for(size_t i=0;i<=tmp1.size()-tmp2.size();i++){
                llf ratio = tmp1[i] / tmp2[0];
                for(size_t j = 0;j<tmp2.size();j++){
                    tmp1[i+j] -= ratio * tmp2[j];
                }
            }
            reverse(tmp1.begin(), tmp1.end());
            trim();
            return *this;
        }
        vlf get_coefficients(){return arr;}
        inline bool empty() const {return arr.empty();}
        friend ostream& operator<<(ostream& ss, const Poly &x){
            for(size_t i=0;i<x.arr.size();i++){
                ss << x.arr[i] << "x^" << i << (i==x.arr.size()-1?"":" + ");
            }
            return ss;
        }
};