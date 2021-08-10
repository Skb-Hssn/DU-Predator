#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<
int ,
    null_type ,
    less < int > , // "less_equal<int>," for multiset
    rb_tree_tag,
    tree_order_statistics_node_update > ordered_set;
ordered_set OS;
/*
   OS.insert(1);
   OS.insert(2);
   OS.insert(4);
   OS.insert(8);
   OS.insert(16);
   cout << ( *OS.find_by_order(0) ) << endl; /// 1
   cout << ( *OS.find_by_order(2) ) << endl; /// 4
   cout << ( *OS.find_by_order(4) ) << endl; /// 16
   cout << ( end(OS) == OS.find_by_order(5) ) <<endl; /// true
   cout << OS.order_of_key(-5) << endl;  /// 0
   cout << OS.order_of_key(3) << endl;   /// 2
   cout << OS.order_of_key(400) << endl; /// 5
   */
