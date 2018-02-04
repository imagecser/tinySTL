#include "stringtest.h"
namespace sz {
	namespace stringTest {
		bool stringEqual(stdstring src, szstring dest) {
			return sz::test::printEqual(src, dest) && sz::test::containerEqual(src, dest);
		}
		void unittest(stdstring src, szstring dest, const char *s, bool islast = true, bool condition = true) {
			if (stringEqual(src, dest) && condition) {
				if (islast)
					sz::test::unitpass(s);
			}
			else
				sz::test::unitfail(s);
		}
		template<class T, class K>
		void unitassert(T src, K dest, const char* s, bool islast = true, bool condition = true) {
			if (src == dest) {
				if (islast)
					sz::test::unitpass(s);
			}
			else
				sz::test::unitfail(s);
		}

		void construct() {
			const char* ptr = "hello world";
			stdstring st1;
			szstring sz1;
			unittest(st1, sz1, "string();");

			stdstring st2(ptr);
			szstring sz2(ptr);
			unittest(st2, sz2, "string(const char* s);");

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
			unittest(s1, z1, "string& operator= (const char* s);");


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
			unittest(s1, z1, "string& insert(size_t pos, const char* s);");

			s1.insert(0, ptr, 3);
			z1.insert(0, ptr, 3);
			unittest(s1, z1, "string& insert(size_t pos, const char* s, size_t n);");

			s1.insert(1, s1);
			z1.insert(1, z1);
			unittest(s1, z1, "string& insert(size_t pos, const string& str);");
			
			s1.insert(0, s1, 1);
			z1.insert(0, z1, 1);
			unittest(s1, z1, "string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);", false);
			s1.insert(13, s1, 4, 2);
			z1.insert(13, z1, 4, 2);
			unittest(s1, z1, "string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);");

			s1.insert(1, 3, 'c');
			z1.insert(1, 3, 'c');
			unittest(s1, z1, "string& insert(size_t pos, size_t n, char ch);");
		}

		void append() {
			const char* ptr = "hello world";
			stdstring s1;
			szstring z1;
			s1.append(ptr, 2);
			z1.append(ptr, 2);
			unittest(s1, z1, "string& append(const char* s, size_t n);");

			s1.append(ptr);
			z1.append(ptr);
			unittest(s1, z1, "string& append(const char* s);");

			s1.append(s1);
			z1.append(z1);
			unittest(s1, z1, "string& append(const string& str);");

			s1.append(s1, 3);
			z1.append(z1, 3);
			unittest(s1, z1, "string& append(const string& str, size_t subpos, size_t sublen = npos);", false);
			s1.append(s1, 3, 3);
			z1.append(z1, 3, 3);
			unittest(s1, z1, "string& append(const string& str, size_t subpos, size_t sublen = npos);");

			s1.append(10, 'c');
			z1.append(10, 'c');
			unittest(s1, z1, "string& append(size_t n, char c);");

			s1.append(z1.begin(), z1.end());
			z1.append(z1.begin(), z1.end());
			unittest(s1, z1, "string& append(InputIterator first, InputIterator last);", false);
			z1.append(s1.begin(), s1.end());
			s1.append(s1.begin(), s1.end());
			unittest(s1, z1, "string& append(InputIterator first, InputIterator last);");

			s1 += ptr;
			z1 += ptr;
			unittest(s1, z1, "string& operator+= (const char* s);");

			s1 += s1;
			z1 += z1;
			unittest(s1, z1, "string& operator+= (const string& str);");

			s1 += 'c';
			z1 += 'c';
			unittest(s1, z1, "string& operator+= (char c);");
		}

		void erase() {
			const char* ptr = "hello world";
			stdstring s1(ptr);
			szstring z1(ptr);

			s1.pop_back();
			z1.pop_back();
			unittest(s1, z1, "void pop_back();");

			s1.erase();
			z1.erase();
			unittest(s1, z1, "string& erase(size_t pos = 0, size_t len = npos);", false);
			s1 = ptr;
			z1 = ptr;
			s1.erase(1, 4);
			z1.erase(1, 4);
			unittest(s1, z1, "string& erase(size_t pos = 0, size_t len = npos);");

			s1.erase(s1.begin());
			z1.erase(z1.begin());
			unittest(s1, z1, "iterator erase(iterator p);");
		}

		void replace() {
			stdstring s1("zouxiaohang"), t1("I Love C++");
			szstring s2("zouxiaohang"), t2("I Love C++");

			s1.replace(0, 3, t1);
			s2.replace(0, 3, t2);
			unittest(s1, s2, "string& replace(size_t pos, size_t len, const string& str);");

			s1.replace(s1.begin(), s1.begin() + s1.size() / 2, t1);
			s2.replace(s2.begin(), s2.begin() + s2.size() / 2, t2);
			unittest(s1, s2, "string& replace(iterator first, iterator last, const string& str);");

			s1.replace(0, s1.size(), t1, 0, t1.size());
			s2.replace(0, s2.size(), t2, 0, t2.size());
			unittest(s1, s2, "string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);");

			s1.replace(0, s1.size(), "123456789");
			s2.replace(0, s2.size(), "123456789");
			unittest(s1, s2, "string& replace(size_t pos, size_t len, const char* s);");

			s1.replace(s1.begin(), s1.end(), "hubei");
			s2.replace(s2.begin(), s2.end(), "hubei");
			unittest(s1, s2, "string& replace(iterator first, iterator last, const char* s);");

			s1.replace(0, s1.size(), "wuhan", 5);
			s2.replace(0, s2.size(), "wuhan", 5);
			unittest(s1, s2, "string& replace(size_t pos, size_t len, const char* s, size_t n);");

			s1.replace(s1.begin(), s1.end(), "hongshanqu", 10);
			s2.replace(s2.begin(), s2.end(), "hongshanqu", 10);
			unittest(s1, s2, "string& replace(iterator first, iterator last, const char* s, size_t n);");

			s1.replace(0, s1.size(), 10, 'Z');
			s2.replace(0, s2.size(), 10, 'Z');
			unittest(s1, s2, "string& replace(size_t pos, size_t len, size_t n, char ch);");
			s1.replace(s1.begin(), s1.end(), 10, 'A');
			s2.replace(s2.begin(), s2.end(), 10, 'A');
			unittest(s1, s2, "string& replace(iterator first, iterator last, size_t n, char ch);");

			s1.replace(s1.begin(), s1.end(), t1.begin(), t1.end());
			s2.replace(s2.begin(), s2.end(), t2.begin(), t2.end());
			unittest(s1, s2, "string& replace(iterator first, iterator last, InputIterator inputfirst, InputIterator inputlast);");
		}

		void find() {
			szstring s1("There are two needles in this haystack with needles.");
			szstring s2("needle");

			unitassert(14, s1.find(s2), "size_t find(const string& str, size_t pos = 0) const;", false);
			unitassert(44, s1.find("needles are small", 15, 6), "size_t find(const char* s, size_t pos, size_t n) const;");
			unitassert(s1.npos, s1.find(szstring("sunzhi")), "size_t find(const string& str, size_t pos = 0) const;");
			unitassert(30, s1.find("haystack"), "size_t find(const char* s, size_t pos = 0) const;");
			unitassert(51, s1.find('.'), "size_t find(char c, size_t pos = 0) const;");

			s1 = "The sixth sick sheik's sixth sheep's sick.";
			s2 = "sixth";

			unitassert(23, s1.rfind(s2), "size_t rfind(const string& str, size_t pos = npos) const;", false);
			unitassert(23, s1.rfind(s2, 24), "size_t rfind(const string& str, size_t pos = npos) const;");
			unitassert(s1.size() - 1, s1.rfind('.'), "size_t rfind(char c, size_t pos = npos) const;");
			unitassert(0, s1.rfind("The"), "size_t rfind(const char* s, size_t pos = npos) const;");
			unitassert(10, s1.rfind("sick111", 10, 4), "size_t rfind(const char* s, size_t pos, size_t n) const;");
		}

		void allTestcases() {
			construct();
			operate();
			func1();
			func2();
			insert();
			append();
			erase();
			replace();
			find();
		}
	}
}
