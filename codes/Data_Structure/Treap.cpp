#include <cstdlib>

class Treap{
	private:
		struct node{
			node* l;
			node* r;
			int pri,size,val;
			node(){l=NULL;r=NULL;pri=rand();size=0;}
			node(int x){l=NULL;r=NULL;pri=rand();size=1;val=x;}
			~node(){if(l)delete l;if(r)delete r;l=NULL;r=NULL;}
		};
		node* root;
		inline int gSize(node* x){return (x==NULL)?0:(x->size);}
		node* merge(node* x,node* y){
			if(x==NULL||y==NULL)return x?x:y;
			else if(x->pri > y->pri){
				x->r = merge(x->r,y);
				x->size = gSize(x->l)+gSize(x->r)+1;
				return x;
			}else{
				y->l = merge(x,y->l);
				y->size = gSize(y->l)+gSize(y->r)+1;
				return y;
			}
		}
		void split(node* rr, int x, node*& l, node*& r){
			if(rr==NULL)r=l=NULL;
			else if(rr->val <= x){
				l=rr;
				split(rr->r, x, l->r, r);
				l->size = gSize(l->r)+gSize(l->l)+1;
			}else{
				r=rr;
				split(rr->l, x, l, r->l);
				r->size = gSize(r->r)+gSize(r->l)+1;
			}
		}
		int oOk(node* rr, int x){
			if(rr==NULL)return 0;
			if((rr->val) < x)return gSize(rr->l)+oOk(rr->r, x)+1;
			else return oOk(rr->l, x);
		}
	public:
		Treap(){root=NULL;}
		~Treap(){delete root;root=NULL;}
		void insert(int x){
			node *a, *b;
			split(root, x, a, b);
			root = merge(merge(a, new node(x)), b);
			root->size = gSize(root->l)+gSize(root->r)+1;
		}
		void remove(int x){
			//need debug may contain bugs
			node *a, *b, *c, *d;
			split(root, x, a, b);
			a->size = gSize(a->l)+gSize(a->r);
			split(a, x-1, c, d);
			root = merge(b, c);
			root->size = gSize(root->l)+gSize(root->r);
			delete d;
		}
		int order_of_key(int x){return oOk(root,x);}
};

int main(){

	return 0;
}