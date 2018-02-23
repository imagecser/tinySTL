#ifndef _SZ_LIST_TEST_H_
#define _SZ_LIST_TEST_H_
#include "../list.h"
#include "testUtil.h"
#include <list>
namespace sz {
	namespace listTest {
		template<class T>
		using stdlist = std::list<T>;
		void allTestcases();
	}
}
#endif // !_SZ_LIST_TEST_H_
