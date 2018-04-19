class Treap{
private:
    const int MEM = 500000 + 5;
    unsigned seed;
    inline unsigned myrand(){
        static unsigned seed = time(NULL);
        seed = seed*seed*127 + seed*227 + 2147483587;
        seed ^= seed*97;
        seed /= 7123;
        return seed;
    }
    struct node{
        node *lc, *rc;
        int pri, size, val;
        node(){}
        node(int x): 
            lc(nullptr), 
            rc(nullptr),
            pri(myrand()),
            size(1), 
            val(x)
        {}
        inline void pull(){
            size = 1;
            if(lc) size += lc->size;
            if(rc) size += rc->size;
        }
    } *root, pool[MEM];
    int mem_;
    inline node* new_node(int x){
        static int mem_ = 0;
        assert(mem_ < MEM);
        pool[mem_]=node(x);
        return &pool[mem_++];
    }
    inline int sz(node* x){return x?x->size:0;}
    node* merge(node *a, node *b){
        if(!a or !b) return a?a:b;
        if(a->pri > b->pri){
            a->rc = merge(a->rc, b);
            a->pull();
            return a;
        }else{
            b->lc = merge(a, b->lc);
            b->pull();
            return b;
        }
    }
    void split(Treap* t, int k, Treap*& a, Treap*& b){
        if(!t) a=b=nullptr;
        else if(sz(t->lc) < k){
            a = t;
            split(t->rc, k - sz(t->lc) - 1 , a->rc, b);
            a->pull();
        }else{
            b = t;
            split(t->lc, k, a, b->lc);
            b->pull();
        }
    }
    int oOk(node* rr, int x){
        if(rr==NULL)return 0;
        if((rr->val) < x)return gSize(rr->l)+oOk(rr->r, x)+1;
        else return oOk(rr->l, x);
    }
public:
    Treap(){root=nullptr;seed=time(NULL);mem_=0;}
    void do_something_at(int l, int r){
        // 1-base [l, r]
        split(root, l-1, tl, root);
        split(root, r-l+1, root, tr);
        root = merge(tl, merge(root, tr));
    }
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
