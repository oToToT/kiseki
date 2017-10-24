#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
#define PB push_back
const int N = 1000 + 5;

vector<int> X[N], Y[N];
bitset<N> visited;
int arr[N], matchX[N], matchY[N];
bool DFS(int);

int main(){
    int n; cin>>n;
    // read graph... for(int i=0;i<n;i++)
	fill(matchX, matchX+n+1, -1);
	fill(matchY, matchY+n+1, -1);
	for(int i=1;i<=n;i++){
		visited.reset();
		DFS(i);
	}
	return 0;
}

bool DFS(int x){
	for(auto y:X[x]){
		if(visited[y]) continue;
		visited[y]=1;
		if(matchY[y]==-1||DFS(matchY[y])){
			matchY[y]=x;
			matchX[x]=y;
			return 1;
		}
	}
	return 0;
}