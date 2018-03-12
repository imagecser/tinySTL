#include "listtest.h"
namespace sz {
    namespace listTest {
        const char* ptr = "hello world";
        template<class T>
        void unittest(stdlist<T> src, szlist<T> dest, const char *s, bool islast = true, bool condition = true) {
            if (sz::test::containerEqual(dest, src) && condition) {
                if (islast)
                    sz::test::unitpass(s);
            }
            else
                sz::test::unitfail(s);
        }
        void func1() {
            stdlist<int> d;
            szlist<int> z;
            unittest(d, z, "list();");

            stdlist<int> d1(5, 123);
            szlist<int> z1(5, 123);
            unittest(d1, z1, "list(size_type n, const_reference val = value_type());");

            stdlist<char> d2(ptr, ptr + 12);
            szlist<char> z2(ptr, ptr + 12);
            //sz::test::printContainer(d2);
            //sz::test::printContainer(z2);
            unittest(d2, z2, "list(InIt first, InIt last);", false);

            stdlist<char> d3(d2);
            szlist<char> z3(z2);
            unittest(d3, z3, "list(const list& src);");

            stdlist<int> d4(d3.begin(), d3.end());
            szlist<int> z4(z3.begin(), z3.end());
            unittest(d2, z2, "list(InIt first, InIt last);");

            stdlist<int> d5 = { 1, 2, 3, 4, 5 };
            szlist<int> z5 = { 1, 2, 3, 4, 5 };
            unittest(d5, z5, "list(std::initializer_list<value_type> ilist);");
        }

        void func2() {
            stdlist<char> d(ptr, ptr + 12);
            szlist<char> z(ptr, ptr + 12);
            auto id = d.begin();
            auto iz = z.begin();
            for (; id != d.end() && iz != z.end(); id++, iz++)
                assert(*id == *iz);
            auto rd = d.rbegin();
            auto rz = z.rbegin();
            for (; rd != d.rend() && rz != z.rend(); rd++, rz++)
                assert(*rd == *rz);
        }

        void func3() {
            stdlist<char> d(ptr, ptr + 10);
            szlist<char> z(ptr, ptr + 10);
            d.pop_back();
            z.pop_back();
            unittest(d, z, "void pop_back();");
            unittest(d, z, "size_type size() const;", false);

            d.pop_front();
            z.pop_front();
            unittest(d, z, "void pop_front();");
            unittest(d, z, "size_type size() const;", false);

            d.push_front(123);
            z.push_front(123);
            unittest(d, z, "void push_front(const_reference val);");
            unittest(d, z, "size_type size() const;", false);

            d.push_back(34);
            z.push_back(34);
            unittest(d, z, "void push_back(const_reference val);");
            unittest(d, z, "size_type size() const;", false);
            unitassert(d.empty(), z.empty(), "bool empty() const;", false);
            d.clear();
            z.clear();
            unitassert(d.empty(), z.empty(), "bool empty() const;");
            unittest(d, z, "void clear();");

            d.insert(d.begin(), ptr, ptr + 3);
            z.insert(z.begin(), ptr, ptr + 3);
            unittest(d, z, "iterator insert(iterator pos, InIt first, InIt last);");

            d.insert(d.end(), 3, 'c');
            z.insert(z.end(), 3, 'c');
            unittest(d, z, "iterator insert(iterator pos, size_type n, const_reference val);");

            d.insert(d.begin(), 'h');
            z.insert(z.begin(), 'h');
            unittest(d, z, "iterator insert(iterator pos, const_reference val);");

            d.erase(--d.end());
            z.erase(--z.end());
            unittest(d, z, "iterator erase(iterator pos);");
        }

        bool isn3(int i) {
            return i == 3;
        }
        void func4() {
            stdlist<int> d1(ptr, ptr + 5), d2(ptr + 7, ptr + 10);
            szlist<int> z1(ptr, ptr + 5), z2(ptr + 7, ptr + 10);
            auto di = d1.begin();
            auto zi = z1.begin();
            ++(++di);
            ++(++zi);
            d1.splice(di, d2);
            z1.splice(zi, z2);
            unittest(d1, z1, "void splice(iterator pos, list& other);", false);
            unittest(d2, z2, "void splice(iterator pos, list& other);");

            d2.splice(d2.begin(), d1, di, d1.end());
            z2.splice(z2.begin(), z1, zi, z1.end());
            unittest(d1, z1, "void splice(iterator pos, list&, iterator first, iterator last);", false);
            unittest(d2, z2, "void splice(iterator pos, list&, iterator first, iterator last);");

            di = d1.begin(); ++di;
            zi = z1.begin(); ++zi;
            d2.splice(d2.begin(), d1, di);
            z2.splice(z2.begin(), z1, zi);
            unittest(d1, z1, "void splice(iterator pos, list&, iterator it);", false);
            unittest(d2, z2, "void splice(iterator pos, list&, iterator it);");

            d1.push_back(*(++d1.begin()));
            z1.push_back(*(++z1.begin()));
            d1.remove(*(++d1.begin()));
            z1.remove(*(++z1.begin()));
            unittest(d1, z1, "void remove(const_reference val);");

            for (size_t i = 0; i < 4; ++i) {
                d1.push_back(3);
                z1.push_back(3);
            }
            d1.remove_if(isn3);
            z1.remove_if(isn3);
            unittest(d1, z1, "void remove_if(Predicate pred);");


            for (size_t i = 0; i < 4; ++i) {
                d1.push_back(3);
                z1.push_back(3);
            }
            d1.unique();
            z1.unique();
            unittest(d1, z1, "void unique();");

            for (size_t i = 0; i < 4; ++i) {
                d1.push_back(i);
                z1.push_back(i);
            }
            d1.unique(less<int>());
            z1.unique(less<int>());
            unittest(d1, z1, "void unique(BiPr pred);");
        }

        void func5() {
            int arr[6] = { 1, 2, 3, 6, 7, 8 };
            stdlist<int> d(arr, arr + 6), d1(arr + 2, arr + 4), d2(arr, arr + 3);
            szlist<int> z(arr, arr + 6), z1(arr + 2, arr + 4), z2(arr, arr + 3);

            d.merge(d1);
            z.merge(z1);
            unittest(d, z, "void merge(list& other);", false);
            unittest(d1, z1, "void merge(list& other);");

            d.merge(d2, less<int>());
            z.merge(z2, less<int>());
            unittest(d, z, "void merge(list& other, Compare comp);", false);
            unittest(d2, z2, "void merge(list& other, Compare comp);");

            stdlist<int> d3(ptr, ptr + 12);
            szlist<int> z3(ptr, ptr + 12);
            d3.sort();
            z3.sort();
            unittest(d3, z3, "void sort();", false);

            d3.reverse();
            z3.reverse();
            unittest(d3, z3, "void reverse();");

            d3.sort(greater<int>());
            z3.sort(greater<int>());
            unittest(d3, z3, "void sort();");

            unitassert(true, z3 == z3, "friend bool operator== (const list<T>& lhs, const list<T>& rhs);", false);
            unitassert(false, z3 != z3, "friend bool operator!= (const list<T>& lhs, const list<T>& rhs);", false);

            szlist<int> z4(z3);
            z4.push_back(3);
            unitassert(false, z3 == z4, "friend bool operator== (const list<T>& lhs, const list<T>& rhs);");
            unitassert(true, z3 != z4, "friend bool operator!= (const list<T>& lhs, const list<T>& rhs);");
            
        }

        void allTestcases() {
            func1();
            func2();
            func3();
            func4();
            func5();
            std::cout << std::endl;
        }
    }
}
