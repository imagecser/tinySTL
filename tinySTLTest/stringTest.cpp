#include "pch.h"
#include "../tinySTL/string.h"
#include <string>

using stdstring = std::string;
using szstring = sz::string;


TEST(string, constructor) {
    const char* ptr = "hello world";
    stdstring st1;
    szstring sz1;
    CONTAINER_ITER_EQ(st1, sz1);

    stdstring st2(ptr);
    szstring sz2(ptr);
    CONTAINER_ITER_EQ(st2, sz2);

    stdstring st3(st2);
    szstring sz3(sz2);
    CONTAINER_ITER_EQ(st3, sz3);

    stdstring st4(st2, 6, 3);
    szstring sz4(sz2, 6, 3);
    CONTAINER_ITER_EQ(st4, sz4);

    stdstring st5(st2, 6);
    szstring sz5(sz2, 6);
    CONTAINER_ITER_EQ(st5, sz5);

    stdstring st6(st2.begin(), st2.end());
    szstring sz6(sz2.begin(), sz2.end());
    CONTAINER_ITER_EQ(st6, sz6);

    stdstring st7(5, 'a');
    szstring sz7(5, 'a');
    CONTAINER_ITER_EQ(st7, sz7);

    stdstring st8 = { '1', '2', '3' };
    szstring sz8 = { '1', '2', '3' };
    CONTAINER_ITER_EQ(st8, sz8);
}

TEST(string, element_access) {
    const char* ptr = "hello world";

    stdstring s1(ptr);
    szstring z1(ptr);
    struct _pos {
        bool operator()(stdstring s1, szstring z1) {
            for (size_t i = 0; i < z1.size(); ++i)
                if (z1[i] != s1[i])
                    return false;
            return true;
        }
    }pos;
    EXPECT_TRUE(pos(s1, z1));
    EXPECT_TRUE(s1.front() == z1.front() && s1.back() && z1.back());
}

TEST(string, capacity) {
    const char *ptr = "hello world";
    stdstring stdstr(ptr);
    szstring szstr(ptr);

    CONTAINER_ITER_EQ(stdstr, szstr);

    stdstring s1(stdstr);
    szstring z1(szstr);
    CONTAINER_ITER_EQ(s1, z1);
    s1.clear();
    z1.clear();
    CONTAINER_ITER_EQ(s1, z1);

    s1 = ptr;
    z1 = ptr;
    s1.resize(s1.size() + 5, 'z');
    z1.resize(z1.size() + 5, 'z');
    CONTAINER_ITER_EQ(s1, z1);
    s1.resize(s1.size());
    z1.resize(z1.size());
    CONTAINER_ITER_EQ(s1, z1);
    s1.resize(s1.size() - 5);
    z1.resize(z1.size() - 5);
    CONTAINER_ITER_EQ(s1, z1);

    stdstring s2;
    szstring z2;
    s2.reserve(20);
    z2.reserve(20);
    CONTAINER_ITER_EQ(s2, z2);

    s2 = ptr;
    z2 = ptr;
    s2.reserve(20);
    z2.reserve(20);
    s2.shrink_to_fit();
    z2.shrink_to_fit();
    CONTAINER_ITER_EQ(s2, z2);


    szstring rz1("hello world");
    sz::reverse_iterator_<char*> rite;
    size_t i;
    for (i = rz1.size() - 1, rite = rz1.rbegin(); i != -1; --i, ++rite)
        EXPECT_TRUE(rz1[i] == *rite);
}

TEST(string, insert) {
    const char* ptr = "hello world";

    stdstring s1;
    szstring z1;
    s1.push_back('?');
    z1.push_back('?');
    CONTAINER_ITER_EQ(s1, z1);

    s1.insert(1, ptr);
    z1.insert(1, ptr);
    CONTAINER_ITER_EQ(s1, z1);

    s1.insert(0, ptr, 3);
    z1.insert(0, ptr, 3);
    CONTAINER_ITER_EQ(s1, z1);

    s1.insert(1, s1);
    z1.insert(1, z1);
    CONTAINER_ITER_EQ(s1, z1);

    s1.insert(0, s1, 1);
    z1.insert(0, z1, 1);
    CONTAINER_ITER_EQ(s1, z1);
    s1.insert(13, s1, 4, 2);
    z1.insert(13, z1, 4, 2);
    CONTAINER_ITER_EQ(s1, z1);

    s1.insert(1, 3, 'c');
    z1.insert(1, 3, 'c');
    CONTAINER_ITER_EQ(s1, z1);
}

TEST(string, append) {
    const char* ptr = "hello world";
    stdstring s1;
    szstring z1;
    s1.append(ptr, 2);
    z1.append(ptr, 2);
    CONTAINER_ITER_EQ(s1, z1);

    s1.append(ptr);
    z1.append(ptr);
    CONTAINER_ITER_EQ(s1, z1);

    s1.append(s1);
    z1.append(z1);
    CONTAINER_ITER_EQ(s1, z1);

    s1.append(s1, 3);
    z1.append(z1, 3);
    CONTAINER_ITER_EQ(s1, z1);
    s1.append(s1, 3, 3);
    z1.append(z1, 3, 3);
    CONTAINER_ITER_EQ(s1, z1);

    s1.append(10, 'c');
    z1.append(10, 'c');
    CONTAINER_ITER_EQ(s1, z1);

    s1.append(z1.begin(), z1.end());
    z1.append(z1.begin(), z1.end());
    CONTAINER_ITER_EQ(s1, z1);
    z1.append(s1.begin(), s1.end());
    s1.append(s1.begin(), s1.end());
    CONTAINER_ITER_EQ(s1, z1);

    s1 += ptr;
    z1 += ptr;
    CONTAINER_ITER_EQ(s1, z1);

    s1 += s1;
    z1 += z1;
    CONTAINER_ITER_EQ(s1, z1);

    s1 += 'c';
    z1 += 'c';
    CONTAINER_ITER_EQ(s1, z1);
}

TEST(string, erase) {
    const char* ptr = "hello world";
    stdstring s1(ptr);
    szstring z1(ptr);

    s1.pop_back();
    z1.pop_back();
    CONTAINER_ITER_EQ(s1, z1);

    s1.erase();
    z1.erase();
    CONTAINER_ITER_EQ(s1, z1);
    s1 = ptr;
    z1 = ptr;
    s1.erase(1, 4);
    z1.erase(1, 4);
    CONTAINER_ITER_EQ(s1, z1);

    s1.erase(s1.begin());
    z1.erase(z1.begin());
    CONTAINER_ITER_EQ(s1, z1);
}

TEST(string, replace) {
    stdstring s1("zouxiaohang"), t1("I Love C++");
    szstring s2("zouxiaohang"), t2("I Love C++");

    s1.replace(0, 3, t1);
    s2.replace(0, 3, t2);
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(s1.begin(), s1.begin() + s1.size() / 2, t1);
    s2.replace(s2.begin(), s2.begin() + s2.size() / 2, t2);
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(0, s1.size(), t1, 0, t1.size());
    s2.replace(0, s2.size(), t2, 0, t2.size());
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(0, s1.size(), "123456789");
    s2.replace(0, s2.size(), "123456789");
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(s1.begin(), s1.end(), "hubei");
    s2.replace(s2.begin(), s2.end(), "hubei");
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(0, s1.size(), "wuhan", 5);
    s2.replace(0, s2.size(), "wuhan", 5);
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(s1.begin(), s1.end(), "hongshanqu", 10);
    s2.replace(s2.begin(), s2.end(), "hongshanqu", 10);
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(0, s1.size(), 10, 'Z');
    s2.replace(0, s2.size(), 10, 'Z');
    CONTAINER_ITER_EQ(s1, s2);
    s1.replace(s1.begin(), s1.end(), 10, 'A');
    s2.replace(s2.begin(), s2.end(), 10, 'A');
    CONTAINER_ITER_EQ(s1, s2);

    s1.replace(s1.begin(), s1.end(), t1.begin(), t1.end());
    s2.replace(s2.begin(), s2.end(), t2.begin(), t2.end());
    CONTAINER_ITER_EQ(s1, s2);
}

TEST(string, find){
    szstring s1("There are two needles in this haystack with needles.");
    szstring s2("needle");

    EXPECT_EQ(14, s1.find(s2));
    EXPECT_EQ(44, s1.find("needles are small", 15, 6));
    EXPECT_EQ(s1.npos, s1.find(szstring("sunzhi")));
    EXPECT_EQ(30, s1.find("haystack"));
    EXPECT_EQ(51, s1.find('.'));

    s1 = "The sixth sick sheik's sixth sheep's sick.";
    s2 = "sixth";

    EXPECT_EQ(23, s1.rfind(s2));
    EXPECT_EQ(23, s1.rfind(s2, 24));
    EXPECT_EQ(s1.size() - 1, s1.rfind('.'));
    EXPECT_EQ(0, s1.rfind("The"));
    EXPECT_EQ(10, s1.rfind("sick111", 10, 4));

    const char* root_ptr = "hello world";
    const char* child_ptr = "godboye";
    stdstring d1 = root_ptr, d2 = child_ptr;
    szstring z1 = root_ptr, z2 = child_ptr;

    EXPECT_EQ(d1.find_first_of(child_ptr), z1.find_first_of(child_ptr));
    EXPECT_EQ(d1.find_first_of(child_ptr, 2), z1.find_first_of(child_ptr, 2));
    EXPECT_EQ(d1.find_first_of(d2, 1), z1.find_first_of(z2, 1));
    EXPECT_EQ(d1.find_first_of(child_ptr, 0, 1), z1.find_first_of(child_ptr, 0, 1));
    EXPECT_EQ(d1.find_first_of('l', 3), z1.find_first_of('l', 3));

    EXPECT_EQ(d1.find_first_not_of(child_ptr), z1.find_first_not_of(child_ptr));
    EXPECT_EQ(d1.find_first_not_of(child_ptr, 2), z1.find_first_not_of(child_ptr, 2));
    EXPECT_EQ(d1.find_first_not_of(d2, 1), z1.find_first_not_of(z2, 1));
    EXPECT_EQ(d1.find_first_not_of(child_ptr, 0, 1), z1.find_first_not_of(child_ptr, 0, 1));
    EXPECT_EQ(d1.find_first_not_of('l', 3), z1.find_first_not_of('l', 3));

    EXPECT_EQ(d1.find_last_of(child_ptr), z1.find_last_of(child_ptr));
    EXPECT_EQ(d1.find_last_of(child_ptr, 2), z1.find_last_of(child_ptr, 2));
    EXPECT_EQ(d1.find_last_of(d2, 1), z1.find_last_of(z2, 1));
    EXPECT_EQ(d1.find_last_of(child_ptr, 0, 1), z1.find_last_of(child_ptr, 0, 1));
    EXPECT_EQ(d1.find_last_of('l', 3), z1.find_last_of('l', 3));

    EXPECT_EQ(d1.find_last_not_of(child_ptr), z1.find_last_not_of(child_ptr));
    EXPECT_EQ(d1.find_last_not_of(child_ptr, 2), z1.find_last_not_of(child_ptr, 2));
    EXPECT_EQ(d1.find_last_not_of(d2, 1), z1.find_last_not_of(z2, 1));
    EXPECT_EQ(d1.find_last_not_of(child_ptr, 0, 1), z1.find_last_not_of(child_ptr, 0, 1));
    EXPECT_EQ(d1.find_last_not_of('l', 3), z1.find_last_not_of('l', 3));
}

TEST(string, compare) {
    szstring s1("apple green");
    szstring s2("green apple");
    EXPECT_EQ(-1, s1.compare("apple green "));
    EXPECT_EQ(1, s1.compare("apple"));
    EXPECT_EQ(0, s1.compare("apple green"));
    EXPECT_EQ(-1, s1.compare(s2));
    EXPECT_EQ(-1, s1.compare(6, 5, s2));
    EXPECT_EQ(0, s1.compare(0, 5, s2, 6));
    EXPECT_EQ(0, s1.compare(6, 5, "green"));
    EXPECT_EQ(0, s1.compare(6, 5, "green4", 5));
}

TEST(string, overload) {
    const char *ptr = "beta";
    stdstring stdstr(ptr);
    szstring szstr(ptr);

    stdstring s1 = stdstr;
    szstring z1 = szstr;
    CONTAINER_ITER_EQ(s1, z1);

    s1 = ptr;
    z1 = ptr;
    CONTAINER_ITER_EQ(s1, z1);

    s1 = 'c';
    z1 = 'c';
    CONTAINER_ITER_EQ(s1, z1);

    stdstr = s1 + stdstr;
    szstr = z1 + szstr;
    CONTAINER_ITER_EQ(stdstr, szstr);
   /* CONTAINER_ITER_EQ(s1 + ptr, z1 + ptr);
    CONTAINER_ITER_EQ(ptr + s1, ptr + z1);
    CONTAINER_ITER_EQ(s1 + 'c', z1 + 'c');
    CONTAINER_ITER_EQ('c' + s1, 'c' + z1);*/

    szstring z2("alpha"), z3 = ("beta");
    EXPECT_EQ(z2 == z3, false);
    EXPECT_EQ(ptr == z2, false);
    EXPECT_EQ(z2 == ptr, false);
    EXPECT_EQ(z3 == z3 || z3 <= z3 || z3 >= z3, true);
    EXPECT_EQ(ptr == z3 || ptr <= z3 || ptr >= z3, true);
    EXPECT_EQ(z3 == ptr || z3 <= ptr || z3 >= ptr, true);
    EXPECT_EQ(z2 != z3, true);
    EXPECT_EQ(ptr != z2, true);
    EXPECT_EQ(z2 != ptr, true);
    EXPECT_EQ(z2 < z3 && z2 <= z3, true);
    EXPECT_EQ(ptr < z2 || ptr <= z2, false);
    EXPECT_EQ(z2 < ptr && z2 <= ptr, true);
    EXPECT_EQ(z2 > z3 || z2 >= z3, false);
    EXPECT_EQ(ptr > z2 && ptr >= z2, true);
    EXPECT_EQ(z2 > ptr || z2 >= ptr, false);
}
