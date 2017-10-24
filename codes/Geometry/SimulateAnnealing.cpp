#include <random>
#include <functional>
#include <utility>
#include <algorithm>
using namespace std;

double getY(double);

int main(){
    int rr, ll;
    default_random_engine rEng(time(NULL));
	uniform_real_distribution<double> Range(-1,1);
	uniform_real_distribution<double> expR(0,1);
	auto Random=bind(Range,rEng);
	auto expRand=bind(expR,rEng);
	int step=0;
	double pace=rr-ll, mini=0.95; // need to search for it
	double x=max(min(Random()*pace+ll, rr), ll), y=getY(x);
	while(pace>=1e-7){
		double newX = max(min(x + Random()*pace, rr), ll);
		double newY = getY(newX);
		if(newY < y || expRand() < exp(-step))
			x=newX, y=newY;
		step++;
		pace*=mini;
	}
}

double getY(double x){
    // get y using x
    return x;
}