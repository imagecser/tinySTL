#ifndef _STRING_TEST_H_
#define _STRING_TEST_H_
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
		void allTestcases();
	}
}
#endif
