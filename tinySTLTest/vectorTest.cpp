#include "pch.h"
#include "../tinySTL/vector.h"
#include <vector>

template<class T>
using stdvec = std::vector<T>;
template<class T>
using szvec = sz::vector<T>;
const char* ptr = "hello world";

TEST(vector, constructor) {
    stdvec<int> v1;
    szvec<int> v2;
    CONTAINER_ITER_EQ(v1, v2);

    stdvec<int> v3(10);
    szvec<int> v4(10);
    EXPECT_EQ(v3.capacity(), v4.capacity());

    stdvec<int> v5(10, 2);
    szvec<int> v6(10, 2);
    CONTAINER_ITER_EQ(v5, v6);

    stdvec<int> v7(ptr, ptr + 6);
    szvec<int> v8(ptr, ptr + 6);
    CONTAINER_ITER_EQ(v7, v8);

    stdvec<int> v9(v7);
    szvec<int> v10(v8);
    CONTAINER_ITER_EQ(v9, v10);

    v1 = v5;
    v2 = v6;
    CONTAINER_ITER_EQ(v1, v2);

    stdvec<int> v11 = { 1, 2, 3, 4 };
    szvec<int> v12 = { 1, 2, 3, 4 };
    CONTAINER_ITER_EQ(v11, v12);
}

TEST(vector, iterator) {
    stdvec<int> v1(ptr, ptr + 9);
    szvec<int> v2(v1.begin(), v1.end());
    for (size_t i = 0; i < 9; i++)
        EXPECT_TRUE(*(v1.begin() + i) == *(v2.begin() + i));
    for (size_t i = 0; i < 9; ++i)
        EXPECT_TRUE(*(v1.rbegin() + i) == *(v2.rbegin() + i));
}

TEST(vector, capacity) {
    stdvec<int> d(ptr, ptr + 10);
    szvec<int> z(ptr, ptr + 10);
    d.reserve(40);
    z.reserve(40);
    EXPECT_EQ(d.capacity(), z.capacity());

    d.shrink_to_fit();
    z.shrink_to_fit();
    EXPECT_EQ(d.capacity(), z.capacity());

    d.resize(25, 13);
    z.resize(25, 13);
    CONTAINER_ITER_EQ(d, z);

    d.resize(3, 222);
    z.resize(3, 222);
    CONTAINER_ITER_EQ(d, z);

    d.resize(50, 3);
    z.resize(50, 3);
    CONTAINER_ITER_EQ(d, z);
}

TEST(vector, modifier) {
    stdvec<int> d(ptr, ptr + 11);
    szvec<int> z(ptr, ptr + 11);

    z.insert(z.begin() + 3, z.begin(), z.begin() + 4);
    d.insert(d.begin() + 3, d.begin(), d.begin() + 4);
    CONTAINER_ITER_EQ(d, z);

    z.insert(z.begin() + 3, z.begin(), z.begin() + 1);
    d.insert(d.begin() + 3, d.begin(), d.begin() + 1);
    CONTAINER_ITER_EQ(d, z);

    z.insert(z.begin(), 1, 2);
    d.insert(d.begin(), 1, 2);
    CONTAINER_ITER_EQ(d, z);

    z.insert(z.end(), 20, 3123);
    d.insert(d.end(), 20, 3123);
    CONTAINER_ITER_EQ(d, z);

    z.insert(z.begin() + 30, 3);
    d.insert(d.begin() + 30, 3);
    CONTAINER_ITER_EQ(d, z);

    z.push_back(231);
    d.push_back(231);
    CONTAINER_ITER_EQ(d, z);

    z.erase(z.begin() + 10, z.begin() + 15);
    d.erase(d.begin() + 10, d.begin() + 15);
    CONTAINER_ITER_EQ(d, z);

    z.erase(z.begin() + 20);
    d.erase(d.begin() + 20);
    CONTAINER_ITER_EQ(d, z);

    z.pop_back();
    d.pop_back();
    CONTAINER_ITER_EQ(d, z);
}