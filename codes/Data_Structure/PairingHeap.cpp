#include <vector>
using std::vector;

template<class __type, class __cmp=less<__type>>
class pairingHeap{
	private:
	    struct pairingNode{
    	    __type val;
            vector<pairingNode*> child;
            pairingNode(){
                val = 0;
                child.clear();
            }
            pairingNode(int x): val(x){
                child.clear();
            }
	    };
		pairingNode* root;
		int count;
		__cmp _cp;
		void remove(pairingNode* cur){
		    if(cur==nullptr) return;
		    for(auto i: cur->child) remove(i);
		    delete cur;
		}
	public:
		pairingHeap(){root=nullptr;count=0;}
		inline bool empty(){return count==0;}
		inline __type top(){return root->val;}
		inline int size(){return count;}
		inline void clear(){remove(root);root=nullptr;count=0;}
		inline void push(__type a){
			count++;
			auto mynode = new pairingNode(a);
			if(root==nullptr) root = mynode;
			else{
				if(_cp(root->val, mynode->val)) swap(root, mynode);
				root->child.push_back(mynode);
			}
		}
		inline void pop(){
			count--;
			queue<pairingNode*> que;
			for(auto i:root->child) que.push(i);
			delete root;
			while(que.size() > 1){
				auto tp1=que.front();que.pop();
				auto tp2=que.front();que.pop();
				if(_cp(tp1->val, tp2->val)) swap(tp1, tp2);
				tp1->child.push_back(tp2);
				que.push(tp1);
			}
			if(que.empty()) root=nullptr;
			else root = que.front();
		}
		inline void join(pairingHeap<__type, __cmp>& pq2){
		    if(_cp(root->val, pq2.root->val)) swap(root, pq2.root);
		    root->child.push_back(pq2.root);
			count += pq2.count;
		    pq2.root = nullptr;
		    pq2.count = 0;
		}
};

int main(){
	pairingHeap<int> pq1, pq2;
	for(int i=0;i<1e5;i++) pq1.push(i);
	for(int i=1e5;i<2e5;i++) pq2.push(i);
	pq1.join(pq2);
	while(!pq1.empty()){
		// cout<<pq1.top()<<" ";
		pq1.pop();
	}
	return 0;
}