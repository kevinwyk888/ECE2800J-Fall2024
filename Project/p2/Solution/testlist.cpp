#include <cassert>
#include <iostream>
#include "p2.h"
#include "recursive.h"
/*
// 使用基本函数实现size
int size(list_t list) {
    if (list_isEmpty(list)) return 0;
    return 1 + size(list_rest(list));
}

// 使用基本函数实现memberOf
bool memberOf(list_t list, int val) {
    if (list_isEmpty(list)) return false;
    if (list_first(list) == val) return true;
    return memberOf(list_rest(list), val);
}
*/
void test_size() {
    std::cout << "Testing size()..." << std::endl;
    
    // 测试空列表
    assert(size(list_make()) == 0);
    
    // 测试单元素列表
    list_t single = list_make(1, list_make());
    assert(size(single) == 1);
    
    // 测试多元素列表
    list_t multi = list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, list_make())))));
    assert(size(multi) == 5);
    
    std::cout << "size() tests passed!" << std::endl;
}

void test_memberOf() {
    std::cout << "Testing memberOf()..." << std::endl;
    
    // 测试空列表
    assert(!memberOf(list_make(), 1));
    
    // 测试单元素列表
    list_t single = list_make(1, list_make());
    assert(memberOf(single, 1));
    assert(!memberOf(single, 2));
    
    // 测试多元素列表包含重复值
    list_t multi = list_make(1, list_make(2, list_make(3, list_make(1, list_make(4, list_make())))));
    assert(memberOf(multi, 1));
    assert(memberOf(multi, 2));
    assert(memberOf(multi, 4));
    assert(!memberOf(multi, 5)); // 不存在的元素
    
    std::cout << "memberOf() tests passed!" << std::endl;
}

void test_dot() {
    std::cout << "Testing dot()..." << std::endl;
    
    // 测试零向量
    list_t v1 = list_make(0, list_make(0, list_make(0, list_make())));
    list_t v2 = list_make(0, list_make(0, list_make(0, list_make())));
    assert(dot(v1, v2) == 0);

    // 测试混合正负向量
    list_t mixed1 = list_make(-1, list_make(2, list_make(-3, list_make(4, list_make()))));
    list_t mixed2 = list_make(5, list_make(-6, list_make(7, list_make(-8, list_make()))));
    assert(dot(mixed1, mixed2) == -70);
    
    std::cout << "dot() tests passed!" << std::endl;
}

void test_isIncreasing() {
    std::cout << "Testing isIncreasing()..." << std::endl;
    
    // 测试空列表
    assert(isIncreasing(list_make()));
    
    // 测试递增和严格递增的列表
    list_t inc = list_make(1, list_make(1, list_make(2, list_make(3, list_make(3, list_make())))));
    list_t strict_inc = list_make(1, list_make(2, list_make(3, list_make(4, list_make()))));
    assert(isIncreasing(inc));
    assert(isIncreasing(strict_inc));

    // 测试包含负数的递增列表
    list_t neg_inc = list_make(-3, list_make(-1, list_make(0, list_make(2, list_make(3, list_make())))));
    assert(isIncreasing(neg_inc));

    std::cout << "isIncreasing() tests passed!" << std::endl;
}

void test_reverse() {
    std::cout << "Testing reverse()..." << std::endl;
    
    // 测试带负数和零的列表
    list_t mixed = list_make(0, list_make(-1, list_make(2, list_make(-3, list_make()))));
    list_t rev_mixed = reverse(mixed);
    assert(list_first(rev_mixed) == -3);
    assert(list_first(list_rest(rev_mixed)) == 2);
    
    std::cout << "reverse() tests passed!" << std::endl;
}

void test_append() {
    std::cout << "Testing append()..." << std::endl;
    
    // 测试两个大列表的拼接
    list_t l1 = list_make(1, list_make(2, list_make(3, list_make(4, list_make()))));
    list_t l2 = list_make(5, list_make(6, list_make(7, list_make(8, list_make()))));
    list_t result = append(l1, l2);
    assert(size(result) == 8);

    std::cout << "append() tests passed!" << std::endl;
}

void test_isArithmeticSequence() {
    std::cout << "Testing isArithmeticSequence()..." << std::endl;
    
    // 测试复杂的等差数列
    list_t large_arith = list_make(5, list_make(10, list_make(15, list_make(20, list_make(25, list_make())))));
    assert(isArithmeticSequence(large_arith));
    
    // 测试复杂的非等差数列
    list_t not_arith = list_make(1, list_make(2, list_make(4, list_make(7, list_make()))));
    assert(!isArithmeticSequence(not_arith));
    
    std::cout << "isArithmeticSequence() tests passed!" << std::endl;
}

void test_filter_odd() {
    std::cout << "Testing filter_odd()..." << std::endl;
    
    // 测试偶数和奇数混合列表
    list_t mixed = list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, list_make())))));
    list_t odd_result = filter_odd(mixed);
    assert(size(odd_result) == 3);

    std::cout << "filter_odd() tests passed!" << std::endl;
}
bool is_positive(int x) { 
    return x > 0; 
}
void test_filter() {
    std::cout << "Testing filter()..." << std::endl;
    
    // 测试带负数和正数的混合列表
    list_t mixed = list_make(-10, list_make(20, list_make(-30, list_make(40, list_make()))));
    list_t positive_filtered = filter(mixed, is_positive);
    assert(size(positive_filtered) == 2);
    
    std::cout << "filter() tests passed!" << std::endl;
}

void test_unique() {
    std::cout << "Testing unique()..." << std::endl;
    
    // 测试带有大量重复值的列表
    list_t with_many_dups = list_make(1, list_make(1, list_make(2, list_make(3, list_make(3, list_make(2, list_make()))))));
    list_t unique_result = unique(with_many_dups);
    assert(size(unique_result) == 3);

    std::cout << "unique() tests passed!" << std::endl;
}

void test_insert_list() {
    std::cout << "Testing insert_list()..." << std::endl;
    
    // 测试在列表末尾插入
    list_t first = list_make(1, list_make(2, list_make(3, list_make())));
    list_t second = list_make(4, list_make(5, list_make()));
    list_t result3 = insert_list(first, second, 3);
    assert(size(result3) == 5);
    assert(list_first(list_rest(list_rest(list_rest(result3)))) == 4);

    std::cout << "insert_list() tests passed!" << std::endl;
}

void test_chop() {
    std::cout << "Testing chop()..." << std::endl;
    
    // 测试删除所有元素的情况
    list_t list = list_make(1, list_make(2, list_make(3, list_make(4, list_make()))));
    list_t result3 = chop(list, 4);
    assert(size(result3) == 0);  // 结果应为空

    std::cout << "chop() tests passed!" << std::endl;
}

int main() {
    test_size();
    test_memberOf();
    test_dot();
    test_isIncreasing();
    test_reverse();
    test_append();
    test_isArithmeticSequence();
    test_filter_odd();
    test_filter();
    test_unique();
    test_insert_list();
    test_chop();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}