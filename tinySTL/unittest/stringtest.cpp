#include "stringtest.h"
namespace sz {
	namespace stringTest {
		bool stringEqual(stdstring src, szstring dest) {
			return sz::test::printEqual(src, dest) && sz::test::containerEqual(src, dest);
		}
		void unittest(stdstring src, szstring dest, const char * str, bool condition = true) {
			if (stringEqual(src, dest) && condition)
				sz::test::unitpass(str);
			else
				sz::test::unitfail(str);
		}

		void construct() {
			const char* ptr = "hello world";
			stdstring st1;
			szstring sz1;
			unittest(st1, sz1, "string();");

			stdstring st2(ptr);
			szstring sz2(ptr);
			unittest(st2, sz2, "string(const char* str);");

			stdstring st3(st2);
			szstring sz3(sz2);
			unittest(st3, sz3, "string(const string& str);");

			stdstring st4(st2, 6, 3);
			szstring sz4(sz2, 6, 3);
			unittest(st4, sz4, "string(const string& str, size_t pos, size_t len);");

			stdstring st5(st2, 6);
			szstring sz5(sz2, 6);
			unittest(st5, sz5, "string(const string& str, size_t pos, size_t len = npos);");

			stdstring st6(st2.begin(), st2.end());
			szstring sz6(sz2.begin(), sz2.end());
			unittest(st6, sz6, "string(InputIterator first, InputIterator last);");

			stdstring st7(5, 'a');
			szstring sz7(5, 'a');
			unittest(st7, sz7, "string(size_t n, char ch);");
		}

		void operate() {
			const char *ptr = "hello world";
			stdstring stdstr(ptr);
			szstring szstr(ptr);

			stdstring s1 = stdstr;
			szstring z1 = szstr;
			unittest(s1, z1, "string& operator= (const string& str);");

			s1 = ptr;
			z1 = ptr;
			unittest(s1, z1, "string& operator= (const char* str);");


			s1 = 'c';
			z1 = 'c';
			unittest(s1, z1, "string& operator= (char ch);");
			
		}

		void func1() {
			const char *ptr = "hello world";
			stdstring stdstr(ptr);
			szstring szstr(ptr);

			stdstring s1(stdstr);
			szstring z1(szstr);
			bool flag1 = s1.empty() == z1.empty();
			s1.clear();
			z1.clear();
			unittest(s1, z1, "bool empty(); void clear();", flag1 && s1.empty() == z1.empty());

			s1 = ptr;
			z1 = ptr;
			s1.resize(s1.size() + 5);
			z1.resize(z1.size() + 5);
			bool flag2 = stringEqual(s1, z1);
			s1.resize(s1.size());
			z1.resize(z1.size());
			bool flag3 = stringEqual(s1, z1);
			s1.resize(s1.size() - 5);
			z1.resize(z1.size() - 5);
			unittest(s1, z1, "void resize(size_t n, const char ch = '\\000');", flag2 && flag3);
			

		}

		void allTestcases() {
			construct();
			operate();
			func1();
		}
	}
}
