#ifndef _SZ_TEST_UTIL_H_
#define _SZ_TEST_UTIL_H_
#include <iostream>
#include <sstream>
#include "rang.hpp"
namespace sz {
	namespace test {
		inline void unitpass(const char* s) {
			std::cout << "[ " << rang::fg::green << "pass" << rang::style::reset << " ] " << s << std::endl;
		}
		inline void unitfail(const char* s) {
			std::cout << "[ " << rang::fg::red << "fail" << rang::style::reset << " ] " << s << std::endl;
		}
		template<class T>
		void printContainer(T& container, const char* name = "") {
			std::cout << "Container: " << name << std::endl;
			for (auto val : container)
				std::cout << val << std::endl;
		}
		template<class T>
		void printItem(T& container, const char* name = "") {
			std::cout << "Container: " << name << std::endl;
			std::cout << container << std::endl;
		}

		template<class T, class K>
		bool printEqual(const T dest, const K src) {
			std::stringstream ssd, sss;
			ssd << dest;
			sss << src;
			return !ssd.str().compare(sss.str());
		}

		template<class T, class K>
		bool containerEqual(T& dest, K&src){
			auto first1 = std::begin(dest), last1 = std::end(dest);
			auto first2 = std::begin(src), last2 = std::end(src);
			for (; first1 != last1 && first2 != last2; ++first1, ++first2)
				if (*first1 != *first2)
					return false;
			return (first1 == last1 && first2 == last2);
		}

		/*void unitPass(const char* s) {
			std::cout << str << rang::fg::green << " ok\n";
		}*/
	}
}
#endif
