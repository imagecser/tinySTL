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
			unittest(d2, z2, "list(InputIterator first, InputIterator last);", false);

			stdlist<char> d3(d2);
			szlist<char> z3(z2);
			unittest(d3, z3, "list(const list& src);");

			stdlist<int> d4(d3.begin(), d3.end());
			szlist<int> z4(z3.begin(), z3.end());
			unittest(d2, z2, "list(InputIterator first, InputIterator last);");
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
			unittest(d, z, "iterator insert(iterator _pos, InputIterator first, InputIterator last);");

			d.insert(d.end(), 3, 'c');
			z.insert(z.end(), 3, 'c');
			unittest(d, z, "iterator insert(iterator _pos, size_type n, const_reference val);");

			d.insert(d.begin(), 'h');
			z.insert(z.begin(), 'h');
			unittest(d, z, "iterator insert(iterator _pos, const_reference val);");

			d.erase(d.end());
			z.erase(z.end());
			unittest(d, z, "iterator erase(iterator _pos);");
		}

		void allTestcases() {
			func1();
			func2();
			func3();
		}
	}
}
