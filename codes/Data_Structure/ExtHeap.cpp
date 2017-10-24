#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using std::less;
using std::greater;
using __gnu_pbds::priority_queue;
using __gnu_pbds::pairing_heap_tag;
using __gnu_pbds::binary_heap_tag;
using __gnu_pbds::binomial_heap_tag;
using __gnu_pbds::rc_binomial_heap_tag;
using __gnu_pbds::thin_heap_tag;

int main(){
	priority_queue<int,less<int>,pairing_heap_tag> pq1, pq2;
	pq1.push(1);
	pq2.push(2);
	pq1.join(pq2);
	assert(pq2.size()==0);
	auto it = pq1.push(87);
	pq1.modify(it, 19);
	while(!pq1.empty()){
		pq1.top();
		pq1.pop();
	}
	return 0;
}