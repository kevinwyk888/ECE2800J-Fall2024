#include <cassert>
#include <iostream>
#include "p2.h"
#include "recursive.h"
using namespace std;
void assert_lists_equal(list_t l1, list_t l2) {
    while (!list_isEmpty(l1) && !list_isEmpty(l2)) {
        assert(list_first(l1) == list_first(l2));
        l1 = list_rest(l1);
        l2 = list_rest(l2);
    }
    // 确保两个列表都为空，以保证长度相等
    assert(list_isEmpty(l1) && list_isEmpty(l2));
}
void test_tree_sum() {
    cout << "Testing tree_sum..." << endl;
    
    // Test empty tree
    tree_t empty_tree = tree_make();
    assert(tree_sum(empty_tree) == 0);
    
    // Test single node
    tree_t single_node = tree_make(10, tree_make(), tree_make());
    assert(tree_sum(single_node) == 10);
    
    // Test deeper tree
    /*
           10
          /   \
         7     15
        / \   /  \
       3   8 12   18
         \
          5
    */
    tree_t leaf5 = tree_make(5, tree_make(), tree_make());
    tree_t node3 = tree_make(3, tree_make(), leaf5);
    tree_t node8 = tree_make(8, tree_make(), tree_make());
    tree_t node7 = tree_make(7, node3, node8);
    tree_t node12 = tree_make(12, tree_make(), tree_make());
    tree_t node18 = tree_make(18, tree_make(), tree_make());
    tree_t node15 = tree_make(15, node12, node18);
    tree_t root = tree_make(10, node7, node15);
    
    assert(tree_sum(root) == 78); // Sum of all nodes
    
    cout << "tree_sum tests passed!" << endl;
}

void test_tree_search() {
    cout << "Testing tree_search..." << endl;
    
    // Test empty tree
    tree_t empty_tree = tree_make();
    assert(!tree_search(empty_tree, 15));
    
    // Test multiple nodes with various depths
    /*
           10
          /   \
         5     15
        / \   /  \
       3   7 12   18
         \
          4
    */
    tree_t leaf4 = tree_make(4, tree_make(), tree_make());
    tree_t node3 = tree_make(3, tree_make(), leaf4);
    tree_t node7 = tree_make(7, tree_make(), tree_make());
    tree_t node5 = tree_make(5, node3, node7);
    tree_t node12 = tree_make(12, tree_make(), tree_make());
    tree_t node18 = tree_make(18, tree_make(), tree_make());
    tree_t node15 = tree_make(15, node12, node18);
    tree_t root = tree_make(10, node5, node15);
    
    assert(tree_search(root, 10));  // root
    assert(tree_search(root, 4));   // deeper node
    assert(tree_search(root, 18));  // rightmost leaf
    assert(!tree_search(root, 20)); // non-existent
    
    cout << "tree_search tests passed!" << endl;
}

void test_depth() {
    cout << "Testing depth..." << endl;
    
    // Test empty tree
    tree_t empty_tree = tree_make();
    assert(depth(empty_tree) == 0);
    
    // Test unbalanced tree
    /*
           5
          /
         3
        /
       2
      /
     1
    */
    tree_t node1 = tree_make(1, tree_make(), tree_make());
    tree_t node2 = tree_make(2, node1, tree_make());
    tree_t node3 = tree_make(3, node2, tree_make());
    tree_t root = tree_make(5, node3, tree_make());
    
    assert(depth(root) == 4);  // depth of unbalanced tree
    
    // Test balanced tree
    /*
           5
          / \
         3   7
    */
    tree_t node7 = tree_make(7, tree_make(), tree_make());
    tree_t balanced_root = tree_make(5, node3, node7);
    
    assert(depth(balanced_root) == 4);  // depth of balanced tree
    
    cout << "depth tests passed!" << endl;
}

void test_tree_max() {
    cout << "Testing tree_max..." << endl;
    
    // Test tree with negative and positive values
    /*
           -10
           /  \
        -20    5
              / \
             0   12
    */
    tree_t node0 = tree_make(0, tree_make(), tree_make());
    tree_t node12 = tree_make(12, tree_make(), tree_make());
    tree_t node5 = tree_make(5, node0, node12);
    tree_t root = tree_make(-10, tree_make(-20, tree_make(), tree_make()), node5);
    
    assert(tree_max(root) == 12); // Max value in mixed tree
    
    cout << "tree_max tests passed!" << endl;
}

void test_traversal() {
    cout << "Testing traversal..." << endl;
    
    // Test full binary tree
    /*
           10
          /   \
         5     15
        / \   /  \
       2   7 12   18
    */
    tree_t node2 = tree_make(2, tree_make(), tree_make());
    tree_t node7 = tree_make(7, tree_make(), tree_make());
    tree_t node5 = tree_make(5, node2, node7);
    tree_t node12 = tree_make(12, tree_make(), tree_make());
    tree_t node18 = tree_make(18, tree_make(), tree_make());
    tree_t node15 = tree_make(15, node12, node18);
    tree_t root = tree_make(10, node5, node15);
    
    list_t expected = list_make(2, list_make(5, list_make(7, list_make(10, list_make(12, list_make(15, list_make(18, list_make())))))));
    assert_lists_equal(traversal(root), expected);
    
    cout << "traversal tests passed!" << endl;
}

void test_tree_hasMonotonicPath() {
    cout << "Testing tree_hasMonotonicPath..." << endl;
    
    // Complex mixed tree with monotonic path
    /*
           10
          /   \
         7     12
        /       \
       3         15
        \
         5
    */
    tree_t leaf5 = tree_make(5, tree_make(), tree_make());
    tree_t node3 = tree_make(3, tree_make(), leaf5);
    tree_t node7 = tree_make(7, node3, tree_make());
    tree_t node15 = tree_make(15, tree_make(), tree_make());
    tree_t node12 = tree_make(12, tree_make(), node15);
    tree_t root = tree_make(10, node7, node12);
    
    assert(tree_hasMonotonicPath(root));  // There exists a monotonic path
    
    cout << "tree_hasMonotonicPath tests passed!" << endl;
}

void test_tree_allPathSumGreater() {
    cout << "Testing tree_allPathSumGreater..." << endl;
    
    // Complex tree with various paths
    /*
           8
          / \
         4   12
        /     \
       2       16
    */
    tree_t node2 = tree_make(2, tree_make(), tree_make());
    tree_t node16 = tree_make(16, tree_make(), tree_make());
    tree_t node4 = tree_make(4, node2, tree_make());
    tree_t node12 = tree_make(12, tree_make(), node16);
    tree_t root = tree_make(8, node4, node12);
    
    assert(tree_allPathSumGreater(root, 9));  // Path sums are all greater than 9
    assert(!tree_allPathSumGreater(root, 20)); // Path 8->4->2 < 20
    
    cout << "tree_allPathSumGreater tests passed!" << endl;
}

void test_covered_by() {
    cout << "Testing covered_by..." << endl;
    
    // Larger subtree coverage test
    /*
    Tree A:
           3
          /
         2
    
    Tree B:
           5
          / \
         3   8
        /
       2
    */
    tree_t node2_A = tree_make(2, tree_make(), tree_make());
    tree_t A = tree_make(3, node2_A, tree_make());
    
    tree_t node2_B = tree_make(2, tree_make(), tree_make());
    tree_t node3_B = tree_make(3, node2_B, tree_make());
    tree_t B = tree_make(5, node3_B, tree_make(8, tree_make(), tree_make()));
    
    assert(!covered_by(A, B)); // A is covered by B
    
    cout << "covered_by tests passed!" << endl;
}

void test_contained_by() {
    cout << "Testing contained_by..." << endl;
    
    // Large containment test
    /*
    Tree A:
           4
          / \
         2   3
    
    Tree B:
           10
          /  \
         4    15
        / \
       2   3
    */
    tree_t node2_A = tree_make(2, tree_make(), tree_make());
    tree_t node3_A = tree_make(3, tree_make(), tree_make());
    tree_t A = tree_make(4, node2_A, node3_A);
    
    tree_t node2_B = tree_make(2, tree_make(), tree_make());
    tree_t node3_B = tree_make(3, tree_make(), tree_make());
    tree_t node4_B = tree_make(4, node2_B, node3_B);
    tree_t B = tree_make(10, node4_B, tree_make(15, tree_make(), tree_make()));
    
    assert(contained_by(A, B));  // A is contained by B
    
    cout << "contained_by tests passed!" << endl;
}

void test_insert_tree() {
    cout << "Testing insert_tree..." << endl;
    
    // Insert in larger tree with complex structure
    /*
    Original tree:
           8
          / \
         4   12
        /
       2
    */
    tree_t node2 = tree_make(2, tree_make(), tree_make());
    tree_t node4 = tree_make(4, node2, tree_make());
    tree_t node12 = tree_make(12, tree_make(), tree_make());
    tree_t root = tree_make(8, node4, node12);
    
    tree_t new_tree = insert_tree(10, root);
    list_t expected = list_make(2, list_make(4, list_make(8, list_make(10, list_make(12, list_make())))));
    assert_lists_equal(traversal(new_tree), expected);  // Verify in-order traversal after insertion
    
    cout << "insert_tree tests passed!" << endl;
}

int main() {
    test_tree_sum();
    test_tree_search();
    test_depth();
    test_tree_max();
    test_traversal();
    test_tree_hasMonotonicPath();
    test_tree_allPathSumGreater();
    test_covered_by();
    test_contained_by();
    test_insert_tree();
    
    cout << "All tests passed!" << endl;
    return 0;
}
