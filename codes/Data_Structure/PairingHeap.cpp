template<typename T, typename cmp=less<T>>
class PairingHeap{
private:
  struct PairingNode{
    T x;
    queue<PairingNode*> cld;
    PairingNode(T a=0):x(a), cld(queue<PairingNode*>()){}
  } *root;
  cmp CMP_;
  size_t count;
  PairingNode* Merge(PairingNode*& a, PairingNode*& b){
    if(!a or !b) return a?a:b;
    if(CMP_(a->x, b->x)) swap(a, b);
    a->cld.push(b); b=nullptr;
    return a;
  }
  void clear(PairingNode*& a){
    if(!a) return;
    while(!(a->cld.empty())){
      auto c = a->cld.front(); a->cld.pop();
      clear(c);
    }
    delete a; a = nullptr;
  }
public:
  PairingHeap(): root(nullptr), count(0){}
  bool empty(){return count==0;}
  size_t size(){return count;}
  T top(){return root->x;}
  void clear(){clear(root);count = 0;}
  void push(const T& x){
    PairingNode* a = new PairingNode(x);
    count += 1;
    root = Merge(root, a);
  }
  void join(PairingHeap& a){
    count += a.count; a.count = 0;
    root = Merge(root, a.root);
  }
  void pop(){
    count -= 1;
    auto& chld = root->cld;
    while(chld.size() > 1){
      PairingNode* a = chld.front(); chld.pop();
      PairingNode* b = chld.front(); chld.pop();
      chld.push(Merge(a, b));
    }
    PairingNode* res = chld.empty()?nullptr:chld.front();
    delete root; root = res;
  }
  friend void swap(PairingHeap& a, PairingHeap& b){
    swap(a.root, b.root);
  }
};
