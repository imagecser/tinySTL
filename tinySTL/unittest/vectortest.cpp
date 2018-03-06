#include "vectortest.h"

namespace sz {
	namespace vectorTest {
		const char* ptr = "hello world";
		template<class T>
		void unittest(stdvec<T> src, szvec<T> dest, const char *s, bool islast = true, bool condition = true) {
			if (sz::test::containerEqual(dest, src) && condition) {
				if (islast)
					sz::test::unitpass(s);
			}
			else
				sz::test::unitfail(s);
		}
		
		void func1() {
			stdvec<int> v1;
			szvec<int> v2;
			unittest(v1, v2, "vector();");

			stdvec<int> v3(10);
			szvec<int> v4(10);
			unitassert(v3.capacity(), v4.capacity(), "explicit vector(const size_type n);");

			stdvec<int> v5(10, 2);
			szvec<int> v6(10, 2);
			unittest(v5, v6, "vector(const size_type n, value_type val);");

			const char* ptr = "hello world";
			stdvec<int> v7(ptr, ptr + 6);
			szvec<int> v8(ptr, ptr + 6);
			unittest(v7, v8, "vector(InputIterator first, InputIterator last);");

			stdvec<int> v9(v7);
			szvec<int> v10(v8);
			unittest(v9, v10, "vector(const vector& vec);");

			v1 = v5;
			v2 = v6;
			unittest(v1, v2, "vector& operator=(const vector& vec);");

			stdvec<int> v11 = { 1, 2, 3, 4 };
			szvec<int> v12 = { 1, 2, 3, 4 };
			unittest(v11, v12, "vector(std::initializer_list<value_type> ilist);");
		}

		void func2() {
			stdvec<int> v1(ptr, ptr + 9);
			szvec<int> v2(v1.begin(), v1.end());
			for (size_t i = 0; i < 9; i++)
				assert(*(v1.begin() + i) == *(v2.begin() + i));
			for (size_t i = 0; i < 9; ++i)
				assert(*(v1.rbegin() + i) == *(v2.rbegin() + i));
		}

		void func3() {
			stdvec<int> d(ptr, ptr + 10);
			szvec<int> z(ptr, ptr + 10);
			d.reserve(40);
			z.reserve(40);
			unitassert(d.capacity(), z.capacity(), "void reserve(size_type n);");

			d.shrink_to_fit();
			z.shrink_to_fit();
			unitassert(d.capacity(), z.capacity(), "void shrink_to_fit();");

			d.resize(25, 13);
			z.resize(25, 13);
			unittest(d, z, "void resize(size_type n, value_type val = value_type())", false);

			d.resize(3, 222);
			z.resize(3, 222);
			unittest(d, z, "void resize(size_type n, value_type val = value_type())", false);

			d.resize(50, 3);
			z.resize(50, 3);
			unittest(d, z, "void resize(size_type n, value_type val = value_type())");
		}

		void func4() {
			stdvec<int> d(ptr, ptr + 11);
			szvec<int> z(ptr, ptr + 11);

			z.insert(z.begin() + 3, z.begin(), z.begin() + 4);
			d.insert(d.begin() + 3, d.begin(), d.begin() + 4);
			unittest(d, z, "iterator insert(iterator pos, InputIterator first, InputIterator last);", false);
			
			z.insert(z.begin() + 3, z.begin(), z.begin() + 1);
			d.insert(d.begin() + 3, d.begin(), d.begin() + 1);
			unittest(d, z, "iterator insert(iterator pos, InputIterator first, InputIterator last);");

			z.insert(z.begin(), 1, 2);
			d.insert(d.begin(), 1, 2);
			unittest(d, z, "iterator insert(iterator pos, const size_type& n, const_reference val);", false);

			z.insert(z.end(), 20, 3123);
			d.insert(d.end(), 20, 3123);
			unittest(d, z, "iterator insert(iterator pos, const size_type& n, const_reference val);");

			z.insert(z.begin() + 30, 3);
			d.insert(d.begin() + 30, 3);
			unittest(d, z, "iterator insert(iterator pos, const_reference val);");

			z.push_back(231);
			d.push_back(231);
			unittest(d, z, "void push_back(const_reference val);");

			z.erase(z.begin() + 10, z.begin() + 15);
			d.erase(d.begin() + 10, d.begin() + 15);
			unittest(d, z, "iterator erase(iterator first, iterator last);");

			z.erase(z.begin() + 20);
			d.erase(d.begin() + 20);
			unittest(d, z, "iterator erase(iterator pos);");

			z.pop_back();
			d.pop_back();
			unittest(d, z, "void pop_back();");
		}


		void allTestcases(){
			func1();
			func2();
			func3();
			func4();
			std::cout << std::endl;
		}
	}
}