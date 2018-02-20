#ifndef _SZ_STRING_TEST_H_
#define _SZ_STRING_TEST_H_
#include "../string.h"
#include "testUtil.h"
#include <cassert>
#include <string>
namespace sz {
	namespace stringTest {
		using stdstring = std::string;
		using szstring = sz::string;
		void construct();
		void operate();
		void func1();
		void func2();
		void insert();
		void append();
		void erase();
		void find();
		void allTestcases();
	}
}
#endif
