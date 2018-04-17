#include "algorithmtest.h"
#include <algorithm>
namespace sz {
    namespace algorithmTest {
        void func1() {
            std::vector<int> vec = { 10, 20, 30 };
            std::vector<int> res = { 11, 21, 31 }, res2 = { 22, 42, 62 };
            sz::for_each(vec.begin(), vec.end(), [&vec](int& i) {
                ++i;
            });
            unitassert(containerEqual(vec, res), true, "UnFn for_each(InIt first, InIt last, UnFn f);");

            sz::for_each_n(vec.begin(), 3, [&vec](int& i) {
                i *= 2;
            });
            unitassert(containerEqual(vec, res2), true, "InIt for_each_n(InIt first, Size n, UnFn f)");

        }

        void func2() {
            std::vector<int> vec = { 10, 20, 30, 10, 20, 17, 18, 20, 10, 40 };
            unitassert(sz::count(vec.begin(), vec.end(), 10), 3, "count(InIt first, InIt last, const T& val);");
            unitassert(sz::count_if(vec.begin(), vec.end(), [](int i) {return i % 5 == 0; }), 8, "count_if(InIt first, InIt last, UnPr p);");

            unitassert(sz::find(vec.begin(), vec.end(), 20) - vec.begin(), 1, "InIt find(InIt first, InIt last, const T& val);", false);
            unitassert(sz::find(vec.begin(), vec.end(), 11), vec.end(), "InIt find(InIt first, InIt last, const T& val);");

            unitassert(sz::find_if(vec.begin(), vec.end(), [](int i) {return i > 39; }), vec.end() - 1, "InIt find_if(InIt first, InIt last, UnPr p);");
            unitassert(sz::find_if_not(vec.begin(), vec.end(), [](int i) {return i < 30; }), vec.begin() + 2, "InIt find_if_not(InIt first, InIt last, UnPr p);");

            int myints[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
            std::vector<int> v(myints, myints + 10);
            int needle1[] = { 1, 2, 3 };
            auto it = sz::find_end(v.begin(), v.end(), needle1, needle1 + 3);
            unitassert(it, v.begin() + 5, "FwdIt1 find_end(FwdIt1 first, FwdIt1 last, ...);");

            int needle2[] = { 4, 5, 1 };
            it = sz::find_end(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
            unitassert(it, v.begin() + 3, "FwdIt1 find_end(..., BiPr p);");

            int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
            std::vector<char> v1(mychars, mychars + 6);
            int needle[] = { 'A', 'B', 'C' };
            auto it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3);
            unitassert(*it1, 'A', "InIt find_first_of(InIt first, InIt last, ...);");

            it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3,
                [](char ch1, char ch2) {return std::tolower(ch1) == std::tolower(ch2); });
            unitassert(*it1, 'a', "InIt find_first_of(..., BiPr p);");

            int myints1[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
            std::vector<int> v2(myints1, myints1 + 8);
            auto it2 = sz::adjacent_find(v2.begin(), v2.end());
            unitassert(*it2, 30, "FwdIt adjacent_find(FwdIt first, FwdIt last);");

            it2 = sz::adjacent_find(++it2, v2.end(), [](int i, int j) {return i == j; });
            unitassert(*it2, 10, "FwdIt adjacent_find(..., BiPr p);");
        }

        void func3() {
            std::vector<int> v;
            for (int i = 1; i<10; i++) v.push_back(i * 10);
            int needle1[] = { 40, 50, 60, 70 };
            auto it = sz::search(v.begin(), v.end(), needle1, _SZ end(needle1));
            unitassert(it, v.begin() + 3, "FwdIt1 search(FwdIt1 first, FwdIt1 last, ...);");
            
            int needle2[] = { 20, 30, 50 };
            it = sz::search(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
            unitassert(it, v.end(), "FwdIt1 search(..., BiPr p);");

            std::vector<char> ve = {1, 0, 0, 0, 1, 1, 3, 0, 0, 0, 1, 1, 1, 1};
            unitassert(true, sz::search_n(ve.begin(), ve.end(), 4, 0) == ve.end(), "FwdIt search_n(FwdIt first, FwdIt last, Size n, const T& val);", false);
            unitassert(true, sz::search_n(ve.begin(), ve.end(), 3, 0) != ve.end(), "FwdIt search_n(FwdIt first, FwdIt last, Size n, const T& val);");

        }

        void func4() {
            std::vector<int> v1 = { 9, 6, 3, 6, 4, 10 }, v2(6);
            std::vector<int> v3 = { 9, 6, 6, 10 }, v4(4);
            std::vector<int> v5 = { 9, 6, 3, 6 }, v6(4);
            sz::copy(v1.begin(), v1.end(), v2.begin());
            unitassert(v1, v2, "OutIt copy(InIt first, InIt last, OutIt d_first);");
            sz::copy_if(v1.begin(), v1.end(), v4.begin(), [](int i) {return i > 5; });
            unitassert(v3, v4, "OutIt copy_if(..., UnPr pred);");
            sz::copy_n(v1.begin(), 4, v6.begin());
            unitassert(v5, v6, "OutIt copy_n(InIt first, Size n, OutIt result);");
            v2.clear();
            v2.resize(6, 0);
            sz::copy_backward(v1.begin(), v1.end(), v2.end());
            unitassert(v1, v2, "BidIt2 copy_backward(BidIt1 first, ...);");
        }

        void func5() {
            std::string s1("hello"), s2(5, 0), s3("ifmmp"), s4("aaaaa");
            sz::transform(sz::begin(s1), sz::end(s1), sz::begin(s2), [](unsigned char c) {return c + 1; });
            unitassert(s2, s3, "OutIt transform(..., UnFn unary_op);");
            sz::transform(sz::begin(s2), sz::end(s2), sz::begin(s3), sz::begin(s1), [](unsigned char lhs, unsigned char rhs) { return lhs == rhs ? 'a' : 'b'; });
            unitassert(containerEqual(s1, s4), true, "OutIt transform(..., BinaryOperation binary_op);");

            std::vector<int> v1(5), v2 = { 2, 3, 4, 5, 6 }, v3 = { 10, 9, 8, 7, 6 };
            sz::generate(v1.begin(), v1.end(), [n = 2]() mutable{ return n++; });
            unitassert(containerEqual(v1, v2), true, "void generate(FwdIt first, FwdIt last, Fn g);");

            sz::generate_n(v1.begin(), 5, [n = 10]() mutable {return n--; });
            unitassert(containerEqual(v1, v3), true, "OutIt generate_n(OutIt first, Size n, Fn g);");
        }

        void func6() {
            std::string s1("h e llo , worl d"), s2("hello,world"), s3("h\tello\t \t ,\twor ld"), s5(11, 0), s6(11, 0), s7("heqqo,worqd"), s10("hell.,w?rld"), s8(11, 0), s9(11, 0);
            sz::remove_copy(s1.begin(), s1.end(), s5.begin(), ' ');
            unitassert(containerEqual(s2, s5), true, "OutIt remove_copy(InIt first, ..., OutIt d_first, const T& val);");

            sz::remove_copy_if(s3.begin(), s3.end(), s6.begin(), [](unsigned char c) {return c == ' ' || c == '\t'; });
            unitassert(containerEqual(s2, s6), true, "OutIt remove_copy_if(..., UnPr p);");

            s1.erase(sz::remove(s1.begin(), s1.end(), ' '), s1.end());
            unitassert(containerEqual(s1, s2), true, "FwdIt remove(FwdIt first, FwdIt last, const T& val);");

            s3.erase(sz::remove_if(s3.begin(), s3.end(), [](unsigned char c) {return c == ' ' || c == '\t'; }), s3.end());
            unitassert(containerEqual(s3, s2), true, "FwdIt remove_if(FwdIt first, FwdIt last, UnPr p);");

            sz::replace_copy(s7.begin(), s7.end(), s8.begin(), 'q', 'l');
            unitassert(containerEqual(s8, s2), true, "OutIt replace_copy(..., OutIt d_first, const T& old_value, const T& new_value);");

            sz::replace_copy_if(s10.begin(), s10.end(), s9.begin(), [](unsigned char c) {return c == '.' || c == '?'; }, 'o');
            unitassert(containerEqual(s9, s2), true, "OutIt replace_copy_if(..., UnPr p, const T& new_value);");

            sz::replace(s7.begin(), s7.end(), 'q', 'l');
            unitassert(containerEqual(s7, s2), true, "void replace(FwdIt first, FwdIt last, const T& old_value, const T& new_value)");

            sz::replace_if(s10.begin(), s10.end(), [](unsigned char c) {return c == '.' || c == '?'; }, 'o');
            unitassert(containerEqual(s10, s2), true, "void replace_if(FwdIt first, FwdIt last, UnPr p, const T& new_value);");
        }

        void func7() {
            std::string s1("hello, world"), s2("world, hello");
            std::string d1("world, world"), d2("hello, hello");
            sz::swap_ranges(s1.begin(), s1.begin() + 5, s2.begin());
            unitassert(containerEqual(s1, d1), true, "FwdIt2 swap_ranges(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2);", false);
            unitassert(containerEqual(s2, d2), true, "FwdIt2 swap_ranges(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2);");

            char ca[13] = "hello, world", cb[13] = "world, hello";
            char cc[13] = "world, hello", cd[13] = "hello, world";
            sz::swap(ca, cb);
            unitassert(containerEqual(ca, cc), true, "void swap(T(&a)[n], T(&b)[n]);", false);
            unitassert(containerEqual(cb, cd), true, "void swap(T(&a)[n], T(&b)[n]);");
        }

        void func8() {
            std::string s1("hello, world"), s2(12, 0);
            std::string d1("dlrow ,olleh");
            sz::reverse_copy(s1.begin(), s1.end(), s2.begin());
            unitassert(s2, d1, "OutIt reverse_copy(..., OutIt d_first);");

            sz::reverse(s1.begin(), s1.end());
            unitassert(s1, d1, "void reverse(BidIt first, BidIt last);");
        }

        void func9() {
            std::string s1("0123456789"), s2(10, 0);
            std::string d1("6789012345");
            sz::rotate_copy(s1.begin(), s1.begin() + 6, s1.end(), s2.begin());
            unitassert(containerEqual(s2, d1), true, "OutIt rotate_copy(..., InIt last, OutIt d_first);");

            sz::rotate(s1.begin(), s1.begin() + 6, s1.end());
            unitassert(containerEqual(s1, d1), true, "FwdIt rotate(FwdIt first, FwdIt n_first, FwdIt last);");

            std::vector<int> v{ 1,2,3,1,2,3,3,4,5,4,5,6,7 }, v1(7);
            std::vector<int> d2{ 1, 2, 3, 4, 5, 6, 7 };
            std::sort(v.begin(), v.end());
            sz::unique_copy(v.begin(), v.end(), v1.begin());
            unitassert(containerEqual(v1, d2), true, "OutIt unique_copy(InIt first, InIt last, OutIt d_first);");

            v.erase(sz::unique(v.begin(), v.end()), v.end());
            unitassert(containerEqual(v, d2), true, "FwdIt unique(FwdIt first, FwdIt last);");
        }

        void func10() {
            std::string s1("0123456789"), s2(5, 0), s3(5, 0);
            auto f = [](unsigned char c) {return c % 2; };
            sz::partition_copy(s1.begin(), s1.end(), s2.begin(), s3.begin(), f);
            sz::partition(s1.begin(), s1.end(), f);
            bool ret = sz::is_partitioned(s1.begin(), s1.end(), f);

        }

        void func11() {
            std::string s1("1122233344445");
            unitassert(_SZ binary_search(s1.begin(), s1.end(), '6'), false,
                "bool binary_search(FwdIt first, FwdIt last, const T& val);", false);
            unitassert(_SZ binary_search(s1.begin(), s1.end(), '5'), true,
                "bool binary_search(FwdIt first, FwdIt last, const T& val);");

            unitassert(_SZ equal_range(s1.begin(), s1.end(), '4'),
                std::equal_range(s1.begin(), s1.end(), '4'),
                "pair<FwdIt, FwdIt equal_range(FwdIt first, FwdIt last, const T& val);");

        }

        void func12() {
            std::string s1("456"), s2("1234"), s3(10, 0);
            _SZ set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());
            s3.clear();
            s3.resize(10);
            _SZ set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());
            s3.clear();
            s3.resize(10);
            _SZ set_symmetric_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());
            s3.clear();
            s3.resize(10);
            _SZ set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), s3.begin());
            s3.clear();
        }

        void allTestcases() {
            func1();
            func2();
            func3();
            func4();
            func5();
            func6();
            func7();
            func8();
            func9();
            func10();
            func11();
            func12();
        }
    }
}