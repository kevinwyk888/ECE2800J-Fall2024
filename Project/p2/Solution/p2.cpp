#include<iostream>
#include<cstdlib>
#include "recursive.h"
int size(list_t list) {
    if (list_isEmpty(list)) return 0;
    return 1 + size(list_rest(list));
}
bool memberOf(list_t list, int val) {
    if (list_isEmpty(list)) return false;
    if (list_first(list) == val) return true;
    else return memberOf(list_rest(list),val);
}
int dot(list_t v1, list_t v2) {
    if (list_isEmpty(v1) || list_isEmpty(v2) ) return 0;
    return list_first(v1)*list_first(v2) + dot (list_rest(v1), list_rest(v2));
}
bool isIncreasing(list_t v) {
    if (size(v)<2) return true;
    if (list_first(v)> list_first(list_rest(v))) return false;
    return isIncreasing(list_rest(v));
}
static int list_last(list_t list) {
    if (size(list) == 1) return list_first(list);
    return list_last(list_rest(list));
}
static list_t list_lrest(list_t list) {
    if (size(list) == 1) return list_make();
    return list_make(list_first(list), list_lrest(list_rest(list)));
}
list_t reverse(list_t list) {
    if (list_isEmpty(list)) return list_make();
    return list_make(list_last(list),reverse(list_lrest(list)));
}
list_t append(list_t first, list_t second) {
    if (list_isEmpty(first) && list_isEmpty(second)) return list_make();
    if (list_isEmpty(first)) return list_make(list_first(second), append(first, list_rest(second)));
    return list_make(list_first(first), append(list_rest(first), second));
}
bool isArithmeticSequence(list_t v) {
    if (size(v)<3) return true;
    if (list_first(v) + list_first(list_rest(list_rest(v))) != 2* list_first(list_rest(v)) ) return false;
    return isArithmeticSequence(list_rest(v));
}
list_t filter_odd(list_t list) {
    if (list_isEmpty(list)) return list_make();
    if (list_first(list) % 2 == 0) return filter_odd(list_rest(list));
    return list_make(list_first(list),filter_odd(list_rest(list)));
}
list_t filter(list_t list, bool (*fn)(int)) {
    if (list_isEmpty(list)) return list_make();
    if (fn(list_first(list)) == false ) return filter(list_rest(list),(*fn));
    return list_make(list_first(list),filter(list_rest(list),(*fn)));
}
static list_t filter_unique(list_t list, int val) {
    if (list_isEmpty(list)) return list_make();
    if (list_first(list) == val) return filter_unique(list_rest(list),val);
    return list_make(list_first(list),filter_unique(list_rest(list),val));
}
list_t unique(list_t list) {
    if (list_isEmpty(list)) return list_make();
    if (memberOf(list_rest(list),list_first(list))) 
        return list_make(list_first(list), unique(filter_unique(list_rest(list), list_first(list))));
    else 
        return list_make(list_first(list), unique(list_rest(list)));
}
list_t insert_list(list_t first, list_t second, unsigned int n) {
    if (list_isEmpty(first) && list_isEmpty(second)) return list_make();

    if ( n>0 ) 
        return list_make(list_first(first), insert_list(list_rest(first), second, n-1));
    else if (list_isEmpty(second)) 
        return list_make(list_first(first), insert_list(list_rest(first), second, 0));
    return list_make(list_first(second), insert_list(first, list_rest(second), 0));
}
list_t chop(list_t list, unsigned int n) {
    if ((unsigned int)size(list) == n) return list_make();
    return list_make(list_first(list),chop(list_rest(list),n));
}


int tree_sum(tree_t tree) {
    if (tree_isEmpty(tree)) return 0;
    return tree_elt(tree) + tree_sum( tree_left(tree))+ tree_sum(tree_right(tree));
}
bool tree_search(tree_t tree, int val) {
    if (tree_isEmpty(tree)) return false;
    if (tree_elt(tree) == val) return true;
    return tree_search(tree_left(tree),val) || tree_search(tree_right(tree),val);
}
static int maxx(int x,int y) {
    return x>y?x:y;
}
int depth(tree_t tree) {
    if (tree_isEmpty(tree)) return 0;
    return maxx(depth(tree_left(tree)) + 1, depth(tree_right(tree)) + 1);
}
int tree_max(tree_t tree) {
    if (tree_isEmpty(tree)) return 0;
    int max_value= maxx(tree_max(tree_left(tree)),tree_max(tree_right(tree)));
    return maxx(max_value,tree_elt(tree));
}

list_t traversal(tree_t tree) {
    if (tree_isEmpty(tree)) return list_make();
    list_t list1 = append(traversal(tree_left(tree)), list_make(tree_elt(tree),list_make()));
    return append(list1, traversal(tree_right(tree)));
}
static bool tree_hasMonotonicPath_helper(tree_t tree, int prev, bool increasing) {
    if (tree_isEmpty(tree)) return true;
    int current = tree_elt(tree);
    if ((increasing && current < prev) || (!increasing && current > prev)) {
        return false;
    }
    return tree_hasMonotonicPath_helper(tree_left(tree), current, increasing) &&
           tree_hasMonotonicPath_helper(tree_right(tree), current, increasing);

}
bool tree_hasMonotonicPath(tree_t tree) {
    if (tree_isEmpty(tree)) return false;
    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) return true; 
    bool flag1=false, flag2=false;
    if (!tree_isEmpty(tree_left(tree))) 
        flag1= tree_hasMonotonicPath_helper(tree_left(tree), tree_elt(tree), true)
            || tree_hasMonotonicPath_helper(tree_left(tree), tree_elt(tree), false);
    if  (!tree_isEmpty(tree_right(tree))) 
        flag2= tree_hasMonotonicPath_helper(tree_right(tree), tree_elt(tree), true)
            || tree_hasMonotonicPath_helper(tree_right(tree), tree_elt(tree), false);
    return flag1 || flag2;
}


bool tree_allPathSumGreater(tree_t tree, int sum) {
    if (tree_isEmpty(tree)) return sum<0;
    return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree)) && tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree)); 
}
bool covered_by(tree_t A, tree_t B) {
    if (tree_isEmpty(B) && !tree_isEmpty(A)) return false;
    if (tree_isEmpty(B) || tree_isEmpty(A)) return true; 
    if (tree_elt(A)!=tree_elt(B)) return false;
    
    return (covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A),tree_right(B)));
}

bool contained_by(tree_t A, tree_t B) {
    if (tree_isEmpty(A) && tree_isEmpty(B)) return true;
    if (tree_isEmpty(B)) return false;
    if (covered_by(A,B)) return true;
    return (contained_by(A,tree_left(B)) || contained_by(A,tree_right(B)) );
}

tree_t insert_tree(int elt, tree_t tree) {
    if (tree_isEmpty(tree)) return tree_make(elt, tree_make(),tree_make());
    int val = tree_elt(tree);
    if (elt<val) return tree_make(val, insert_tree(elt, tree_left(tree)), tree_right(tree));
    return tree_make(val, tree_left(tree), insert_tree(elt, tree_right(tree)));
}
