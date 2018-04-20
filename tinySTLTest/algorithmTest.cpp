#include "pch.h"
#include "../tinySTL/algorithm.h"
#include <cctype>

TEST(algorithm, non_modify_for_each) {
    std::vector<int> vec = { 10, 20, 30 };
    std::vector<int> res = { 11, 21, 31 }, res2 = { 22, 42, 62 };
    sz::for_each(vec.begin(), vec.end(), [&vec](int& i) {
        ++i;
    });
    CONTAINER_ITER_EQ(vec, res);

    sz::for_each_n(vec.begin(), 3, [&vec](int& i) {
        i *= 2;
    });
    CONTAINER_ITER_EQ(vec, res2);
}

TEST(algorithm, non_modify_find) {
    std::vector<int> vec = { 10, 20, 30, 10, 20, 17, 18, 20, 10, 40 };
    EXPECT_EQ(sz::count(vec.begin(), vec.end(), 10), 3);
    auto res1 = sz::count_if(vec.begin(), vec.end(), [](int i) {return i % 5 == 0; });
    EXPECT_EQ(res1, 8);

    EXPECT_EQ(sz::find(vec.begin(), vec.end(), 20) - vec.begin(), 1);
    EXPECT_EQ(sz::find(vec.begin(), vec.end(), 11), vec.end());
    auto res2 = sz::find_if(vec.begin(), vec.end(), [](int i) {return i > 39; });
    EXPECT_EQ(res2, vec.end() - 1);
    res2 = sz::find_if_not(vec.begin(), vec.end(), [](int i) {return i < 30; });
    EXPECT_EQ(res2, vec.begin() + 2);

    int myints[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
    std::vector<int> v(myints, myints + 10);
    int needle1[] = { 1, 2, 3 };
    auto it = sz::find_end(v.begin(), v.end(), needle1, needle1 + 3);
    EXPECT_EQ(it, v.begin() + 5);

    int needle2[] = { 4, 5, 1 };
    it = sz::find_end(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
    EXPECT_EQ(it, v.begin() + 3);

    int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
    std::vector<char> v1(mychars, mychars + 6);
    int needle[] = { 'A', 'B', 'C' };
    auto it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3);
    EXPECT_EQ(*it1, 'A');

    it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3,
        [](char ch1, char ch2) {return std::tolower(ch1) == std::tolower(ch2); });
    EXPECT_EQ(*it1, 'a');

    int myints1[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
    std::vector<int> v2(myints1, myints1 + 8);
    auto it2 = sz::adjacent_find(v2.begin(), v2.end());
    EXPECT_EQ(*it2, 30);

    it2 = sz::adjacent_find(++it2, v2.end(), [](int i, int j) {return i == j; });
    EXPECT_EQ(*it2, 10);
}

TEST(algorithm, non_modify_search) {
    std::vector<int> v;
    for (int i = 1; i<10; i++) v.push_back(i * 10);
    int needle1[] = { 40, 50, 60, 70 };
    auto it = sz::search(v.begin(), v.end(), needle1, _SZ end(needle1));
    EXPECT_EQ(it, v.begin() + 3);

    int needle2[] = { 20, 30, 50 };
    it = sz::search(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
    EXPECT_EQ(it, v.end());

    std::vector<char> ve = { 1, 0, 0, 0, 1, 1, 3, 0, 0, 0, 1, 1, 1, 1 };
    EXPECT_EQ(true, sz::search_n(ve.begin(), ve.end(), 4, 0) == ve.end());
    EXPECT_EQ(true, sz::search_n(ve.begin(), ve.end(), 3, 0) != ve.end());
}

TEST(algorithm, modify_copy) {
    std::vector<int> v1 = { 9, 6, 3, 6, 4, 10 }, v2(6);
    std::vector<int> v3 = { 9, 6, 6, 10 }, v4(4);
    std::vector<int> v5 = { 9, 6, 3, 6 }, v6(4);
    sz::copy(v1.begin(), v1.end(), v2.begin());
    EXPECT_EQ(v1, v2);
    sz::copy_if(v1.begin(), v1.end(), v4.begin(), [](int i) {return i > 5; });
    EXPECT_EQ(v3, v4);
    sz::copy_n(v1.begin(), 4, v6.begin());
    EXPECT_EQ(v5, v6);
    v2.clear();
    v2.resize(6, 0);
    sz::copy_backward(v1.begin(), v1.end(), v2.end());
    EXPECT_EQ(v1, v2);
}

TEST(algorithm, modify_transform_generate) {
    std::string s1("hello"), s2(5, 0), s3("ifmmp"), s4("aaaaa");
    sz::transform(sz::begin(s1), sz::end(s1), sz::begin(s2), [](unsigned char c) {return c + 1; });
    EXPECT_EQ(s2, s3);
    sz::transform(sz::begin(s2), sz::end(s2), sz::begin(s3), sz::begin(s1), [](unsigned char lhs, unsigned char rhs) { return lhs == rhs ? 'a' : 'b'; });
    CONTAINER_ITER_EQ(s1, s4);

    std::vector<int> v1(5), v2 = { 2, 3, 4, 5, 6 }, v3 = { 10, 9, 8, 7, 6 };
    sz::generate(v1.begin(), v1.end(), [n = 2]() mutable{ return n++; });
    CONTAINER_ITER_EQ(v1, v2);

    sz::generate_n(v1.begin(), 5, [n = 10]() mutable {return n--; });
    CONTAINER_ITER_EQ(v1, v3);
}

TEST(algorithm, modify_remove_replace) {
    std::string s1("h e llo , worl d"), s2("hello,world"), s3("h\tello\t \t ,\twor ld"), s5(11, 0), s6(11, 0), s7("heqqo,worqd"), s10("hell.,w?rld"), s8(11, 0), s9(11, 0);
    sz::remove_copy(s1.begin(), s1.end(), s5.begin(), ' ');
    CONTAINER_ITER_EQ(s2, s5);

    sz::remove_copy_if(s3.begin(), s3.end(), s6.begin(), [](unsigned char c) {return c == ' ' || c == '\t'; });
    CONTAINER_ITER_EQ(s2, s6);

    s1.erase(sz::remove(s1.begin(), s1.end(), ' '), s1.end());
    CONTAINER_ITER_EQ(s1, s2);

    s3.erase(sz::remove_if(s3.begin(), s3.end(), [](unsigned char c) {return c == ' ' || c == '\t'; }), s3.end());
    CONTAINER_ITER_EQ(s3, s2);

    sz::replace_copy(s7.begin(), s7.end(), s8.begin(), 'q', 'l');
    CONTAINER_ITER_EQ(s8, s2);

    sz::replace_copy_if(s10.begin(), s10.end(), s9.begin(), [](unsigned char c) {return c == '.' || c == '?'; }, 'o');
    CONTAINER_ITER_EQ(s9, s2);

    sz::replace(s7.begin(), s7.end(), 'q', 'l');
    CONTAINER_ITER_EQ(s7, s2);

    sz::replace_if(s10.begin(), s10.end(), [](unsigned char c) {return c == '.' || c == '?'; }, 'o');
    CONTAINER_ITER_EQ(s10, s2);
}

TEST(algorithm, modify_swap) {
    std::string s1("hello, world"), s2("world, hello");
    std::string d1("world, world"), d2("hello, hello");
    sz::swap_ranges(s1.begin(), s1.begin() + 5, s2.begin());
    CONTAINER_ITER_EQ(s1, d1);
    CONTAINER_ITER_EQ(s2, d2);

    char ca[13] = "hello, world", cb[13] = "world, hello";
    char cc[13] = "world, hello", cd[13] = "hello, world";
    sz::swap(ca, cb);
    CONTAINER_ITER_EQ(ca, cc);
    CONTAINER_ITER_EQ(cb, cd);
}

TEST(algorithm, modify_reverse) {
    std::string s1("hello, world"), s2(12, 0);
    std::string d1("dlrow ,olleh");
    sz::reverse_copy(s1.begin(), s1.end(), s2.begin());
    EXPECT_EQ(s2, d1);

    sz::reverse(s1.begin(), s1.end());
    EXPECT_EQ(s1, d1);
}

TEST(algorithm, modify_rotate_sort_unique) {
    std::string s1("0123456789"), s2(10, 0);
    std::string d1("6789012345");
    sz::rotate_copy(s1.begin(), s1.begin() + 6, s1.end(), s2.begin());
    CONTAINER_ITER_EQ(s2, d1);

    sz::rotate(s1.begin(), s1.begin() + 6, s1.end());
    CONTAINER_ITER_EQ(s1, d1);

    std::vector<int> v{ 1,2,3,1,2,3,3,4,5,4,5,6,7 }, v1(7);
    std::vector<int> d2{ 1, 2, 3, 4, 5, 6, 7 };
    std::sort(v.begin(), v.end());
    sz::unique_copy(v.begin(), v.end(), v1.begin());
    CONTAINER_ITER_EQ(v1, d2);

    v.erase(sz::unique(v.begin(), v.end()), v.end());
    CONTAINER_ITER_EQ(v, d2);
}