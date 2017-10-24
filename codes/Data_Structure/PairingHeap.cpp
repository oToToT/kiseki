#include <vector>
using std::vector;

template<typename T>
class pairingHeap{
	private:
		struct pairingNode{
			T val;
			vector<pairingNode*> child;
		};
		pairingNode* root;
		size_t count=0;
	public:
		pairingHeap(){root=NULL;count=0;}
		inline bool empty(){return count==0;}
		inline T top(){return root->val;}
		inline size_t size(){return count;}
		inline void push(T a){
			count++;
			if(root==NULL){
				root = new pairingNode;
				root->val=a;
			}else{
				auto temp = new pairingNode;
				temp->val=a;
				if(root->val>=temp->val)
					root->child.push_back(temp);
				else{
					temp->child.push_back(root);
					swap(temp,root);
				}
			}
		}
		inline void join(pairingHeap& a){
			count+=a.size();
			auto temp = a.root;
			if(root->val>=temp->val){
				root->child.push_back(temp);
			}else{
				temp->child.push_back(root);
				swap(temp,root);
			}
			a.root=nullptr;
			a.count=0;
		}
		inline void pop(){
			count--;
			queue<pairingNode*> QQ;
			for(auto i:root->child) QQ.push(i);
			delete root;
			while(QQ.size()>1){
				pairingNode* tp1=QQ.front();QQ.pop();
				pairingNode* tp2=QQ.front();QQ.pop();
				if(tp1->val>tp2->val){
					tp1->child.push_back(tp2);
					QQ.push(tp1);
				}else{
					tp2->child.push_back(tp1);
					QQ.push(tp2);
				}
			}
			if(QQ.empty()) root=NULL;
			else root = QQ.front();
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