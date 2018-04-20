#include "pch.h"
#include "../tinySTL/list.h"
#include <list>

template<class T>
using stdlist = std::list<T>;
template<class T>
using szlist = sz::list<T>;


const char* list_ptr = "hello world";

TEST(list, constructor) {
    stdlist<int> d;
    szlist<int> z;
    CONTAINER_ITER_EQ(d, z);

    stdlist<int> d1(5, 123);
    szlist<int> z1(5, 123);
    CONTAINER_ITER_EQ(d1, z1);

    stdlist<char> d2(list_ptr, list_ptr + 12);
    szlist<char> z2(list_ptr, list_ptr + 12);
    //sz::test::printContainer(d2);
    //sz::test::printContainer(z2);
    CONTAINER_ITER_EQ(d2, z2);

    stdlist<char> d3(d2);
    szlist<char> z3(z2);
    CONTAINER_ITER_EQ(d3, z3);

    stdlist<int> d4(d3.begin(), d3.end());
    szlist<int> z4(z3.begin(), z3.end());
    CONTAINER_ITER_EQ(d2, z2);

    stdlist<int> d5 = { 1, 2, 3, 4, 5 };
    szlist<int> z5 = { 1, 2, 3, 4, 5 };
    CONTAINER_ITER_EQ(d5, z5);
}

TEST(list, iterator) {
    stdlist<char> d(list_ptr, list_ptr + 12);
    szlist<char> z(list_ptr, list_ptr + 12);
    auto id = d.begin();
    auto iz = z.begin();
    for (; id != d.end() && iz != z.end(); id++, iz++)
        EXPECT_TRUE(*id == *iz);
    auto rd = d.rbegin();
    auto rz = z.rbegin();
    for (; rd != d.rend() && rz != z.rend(); rd++, rz++)
        EXPECT_TRUE(*rd == *rz);
}

TEST(list, modifier) {
    stdlist<char> d(list_ptr, list_ptr + 10);
    szlist<char> z(list_ptr, list_ptr + 10);
    d.pop_back();
    z.pop_back();
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d, z);

    d.pop_front();
    z.pop_front();
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d, z);

    d.push_front(123);
    z.push_front(123);
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d, z);

    d.push_back(34);
    z.push_back(34);
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d, z);
    EXPECT_EQ(d.empty(), z.empty());
    d.clear();
    z.clear();
    EXPECT_EQ(d.empty(), z.empty());
    CONTAINER_ITER_EQ(d, z);

    d.insert(d.begin(), list_ptr, list_ptr + 3);
    z.insert(z.begin(), list_ptr, list_ptr + 3);
    CONTAINER_ITER_EQ(d, z);

    d.insert(d.end(), 3, 'c');
    z.insert(z.end(), 3, 'c');
    CONTAINER_ITER_EQ(d, z);

    d.insert(d.begin(), 'h');
    z.insert(z.begin(), 'h');
    CONTAINER_ITER_EQ(d, z);

    d.erase(--d.end());
    z.erase(--z.end());
    CONTAINER_ITER_EQ(d, z);
}

bool isn3(int i) {
    return i == 3;
}

TEST(list, list_operation1) {
    stdlist<int> d1(list_ptr, list_ptr + 5), d2(list_ptr + 7, list_ptr + 10);
    szlist<int> z1(list_ptr, list_ptr + 5), z2(list_ptr + 7, list_ptr + 10);
    auto di = d1.begin();
    auto zi = z1.begin();
    ++(++di);
    ++(++zi);
    d1.splice(di, d2);
    z1.splice(zi, z2);
    CONTAINER_ITER_EQ(d1, z1);
    CONTAINER_ITER_EQ(d2, z2);

    d2.splice(d2.begin(), d1, di, d1.end());
    z2.splice(z2.begin(), z1, zi, z1.end());
    CONTAINER_ITER_EQ(d1, z1);
    CONTAINER_ITER_EQ(d2, z2);

    di = d1.begin(); ++di;
    zi = z1.begin(); ++zi;
    d2.splice(d2.begin(), d1, di);
    z2.splice(z2.begin(), z1, zi);
    CONTAINER_ITER_EQ(d1, z1);
    CONTAINER_ITER_EQ(d2, z2);

    d1.push_back(*(++d1.begin()));
    z1.push_back(*(++z1.begin()));
    d1.remove(*(++d1.begin()));
    z1.remove(*(++z1.begin()));
    CONTAINER_ITER_EQ(d1, z1);

    for (size_t i = 0; i < 4; ++i) {
        d1.push_back(3);
        z1.push_back(3);
    }
    d1.remove_if(isn3);
    z1.remove_if(isn3);
    CONTAINER_ITER_EQ(d1, z1);


    for (size_t i = 0; i < 4; ++i) {
        d1.push_back(3);
        z1.push_back(3);
    }
    d1.unique();
    z1.unique();
    CONTAINER_ITER_EQ(d1, z1);

    for (size_t i = 0; i < 4; ++i) {
        d1.push_back(i);
        z1.push_back(i);
    }
    d1.unique(sz::less<int>());
    z1.unique(sz::less<int>());
    CONTAINER_ITER_EQ(d1, z1);
}

TEST(list, list_operation2) {
    int arr[6] = { 1, 2, 3, 6, 7, 8 };
    stdlist<int> d(arr, arr + 6), d1(arr + 2, arr + 4), d2(arr, arr + 3);
    szlist<int> z(arr, arr + 6), z1(arr + 2, arr + 4), z2(arr, arr + 3);

    d.merge(d1);
    z.merge(z1);
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d1, z1);

    d.merge(d2, sz::less<int>());
    z.merge(z2, sz::less<int>());
    CONTAINER_ITER_EQ(d, z);
    CONTAINER_ITER_EQ(d2, z2);

    stdlist<int> d3(list_ptr, list_ptr + 12);
    szlist<int> z3(list_ptr, list_ptr + 12);
    d3.sort();
    z3.sort();
    CONTAINER_ITER_EQ(d3, z3);

    d3.reverse();
    z3.reverse();
    CONTAINER_ITER_EQ(d3, z3);

    d3.sort(sz::greater<int>());
    z3.sort(sz::greater<int>());
    CONTAINER_ITER_EQ(d3, z3);

    EXPECT_EQ(true, z3 == z3);
    EXPECT_EQ(false, z3 != z3);

    szlist<int> z4(z3);
    z4.push_back(3);
    EXPECT_EQ(false, z3 == z4);
    EXPECT_EQ(true, z3 != z4);
}