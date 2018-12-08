#include <ext/pb_ds/assoc_container.hpp>
using __gnu_pbds::tree;
using __gnu_pbds::rb_tree_tag;
using __gnu_pbds::ov_tree_tag;
using __gnu_pbds::splay_tree_tag;
using __gnu_pbds::null_type;
using __gnu_pbds::tree_order_statistics_node_update;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename A, B>
using ordered_map = tree<A, B, less<A>, rb_tree_tag, tree_order_statistics_node_update>;
int main(){
  ordered_set<int> ss;
  ordered_map<int,int> mm;
  ss.insert(1);
  ss.insert(5);
  assert(*ss.find_by_order(0)==1);
  assert(ss.order_of_key(-1)==0);
  assert(ss.order_of_key(87)==2);
  return 0;
}
