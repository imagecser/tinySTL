#include "stringtest.h"
using sz::test::containerEqual;
using sz::test::printContainer;
using sz::test::printEqual;
using sz::test::printItem;
using sz::test::unitpass;
namespace sz {
	namespace stringTest {
		void construct() {
			const char* ptr = "hello world";
			stdstring st1;
			szstring sz1;
			assert(printEqual(st1, sz1));
			assert(containerEqual(st1, sz1));
			unitpass("string();");

			stdstring st2(ptr);
			szstring sz2(ptr);
			assert(printEqual(st2, sz2));
			assert(containerEqual(st2, sz2));
			unitpass("string(const char* str);");

			stdstring st3(st2);
			szstring sz3(sz2);
			assert(printEqual(st3, sz3));
			assert(containerEqual(st3, sz3));
			unitpass("string(const string& str);");

			stdstring st4(st2, 6, 3);
			szstring sz4(sz2, 6, 3);
			assert(printEqual(st4, sz4));
			assert(containerEqual(st4, sz4));
			unitpass("string(const string& str, size_t pos, size_t len);");

			stdstring st5(st2, 6);
			szstring sz5(sz2, 6);
			assert(printEqual(st5, sz5));
			assert(containerEqual(st5, sz5));
			unitpass("string(const string& str, size_t pos, size_t len = npos);");

			stdstring st6(st2.begin(), st2.end());
			szstring sz6(sz2.begin(), sz2.end());
			assert(printEqual(st6, sz6));
			assert(containerEqual(st6, sz6));
			unitpass("string(InputIterator first, InputIterator last);");

			stdstring st7(5, 'a');
			szstring sz7(5, 'a');
			assert(printEqual(st7, sz7));
			assert(containerEqual(st7, sz7));
			unitpass("string(size_t n, char ch);");
		}

		void operate() {
			const char *ptr = "hello world";
			stdstring stdstr(ptr);
			szstring szstr(ptr);

			stdstring s1 = stdstr;
			szstring z1 = szstr;
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			unitpass("string& operator= (const string& str);");

			s1 = ptr;
			z1 = ptr;
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			unitpass("string& operator= (const char* str);");


			s1 = 'c';
			z1 = 'c';
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			unitpass("string& operator= (char ch);");
			
		}

		void func1() {
			const char *ptr = "hello world";
			stdstring stdstr(ptr);
			szstring szstr(ptr);

			stdstring s1(stdstr);
			szstring z1(szstr);
			assert(s1.empty() == z1.empty());
			s1.clear();
			z1.clear();
			assert(s1.empty() == z1.empty());
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			unitpass("void clear();");
			unitpass("bool empty();");

			s1 = ptr;
			z1 = ptr;
			s1.resize(s1.size() + 5);
			z1.resize(z1.size() + 5);
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			s1.resize(s1.size());
			z1.resize(z1.size());
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			s1.resize(s1.size() - 5);
			z1.resize(z1.size() - 5);
			assert(printEqual(s1, z1));
			assert(containerEqual(s1, z1));
			unitpass("void resize(size_t n, const char ch = '\\000');");

		}

		void allTestcases() {
			construct();
			operate();
			func1();
		}
	}
}
