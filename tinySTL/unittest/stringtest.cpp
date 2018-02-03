#include "stringtest.h"
namespace sz {
	namespace stringTest {
		bool stringEqual(stdstring src, szstring dest) {
			return sz::test::printEqual(src, dest) && sz::test::containerEqual(src, dest);
		}
		void unittest(stdstring src, szstring dest, const char * str, bool islast = true, bool condition = true) {
			if (stringEqual(src, dest) && condition) {
				if (islast)
					sz::test::unitpass(str);
			}
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
			unittest(s1, z1, "bool empty(); void clear();", false, s1.empty() == z1.empty());
			s1.clear();
			z1.clear();
			unittest(s1, z1, "bool empty(); void clear();", true, s1.empty() == z1.empty());

			s1 = ptr;
			z1 = ptr;
			s1.resize(s1.size() + 5, 'z');
			z1.resize(z1.size() + 5, 'z'); 
			unittest(s1, z1, "void resize(size_t n, const char ch = '\\000');", false);
			s1.resize(s1.size());
			z1.resize(z1.size()); 
			unittest(s1, z1, "void resize(size_t n, const char ch = '\\000');", false);
			s1.resize(s1.size() - 5);
			z1.resize(z1.size() - 5);
			unittest(s1, z1, "void resize(size_t n, const char ch = '\\000');");
			
			stdstring s2;
			szstring z2;
			s2.reserve(20);
			z2.reserve(20);
			unittest(s2, z2, "void reserve(size_t n);", true, 20 == z2.capacity());

			s2 = ptr;
			z2 = ptr;
			s2.reserve(20);
			z2.reserve(20);
			s2.shrink_to_fit();
			z2.shrink_to_fit();
			unittest(s2, z2, "void shrink_to_fit();", true, 11 == z2.capacity());
		}
		void func2() {
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
			unittest(s1, z1, "char& operator[](size_t pos);", true, pos(s1, z1));
			unittest(s1, z1, "char& back(); char& front();", true, s1.front() == z1.front() && s1.back() == z1.back());
		}

		void insert() {
			const char* ptr = "hello world";

			stdstring s1;
			szstring z1;
			s1.push_back('?');
			z1.push_back('?');
			unittest(s1, z1, "void push_back(char ch);");

			s1.insert(1, ptr);
			z1.insert(1, ptr);
			unittest(s1, z1, "string& insert(size_t pos, const char* str);");

			s1.insert(0, ptr, 3);
			z1.insert(0, ptr, 3);
			unittest(s1, z1, "string& insert(size_t pos, const char* str, size_t n);");

			s1.insert(1, s1);
			z1.insert(1, z1);
			unittest(s1, z1, "string& insert(size_t pos, const string& str);");
			
			s1.insert(0, s1, 1);
			z1.insert(0, z1, 1);
			unittest(s1, z1, "string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);", false);
			s1.insert(1, s1, 4, 2);
			z1.insert(1, z1, 4, 2);
			unittest(s1, z1, "string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);");

			s1.insert(1, 3, 'c');
			z1.insert(1, 3, 'c');
			unittest(s1, z1, "string& insert(size_t pos, size_t n, char ch);");

		}

		void allTestcases() {
			construct();
			operate();
			func1();
			func2();
			insert();
		}
	}
}
