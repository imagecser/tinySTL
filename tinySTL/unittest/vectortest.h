#ifndef _SZ_VECTOR_TEST_H_
#define _SZ_VECTOR_TEST_H_
#include "../vector.h"
#include "testUtil.h"
#include <cassert>
#include <vector>
namespace sz {
	namespace vectorTest {
		template<class T>
		using stdvec = std::vector<T>;
		template<class T>
		using szvec = sz::vector<T>;
		void allTestcases();

	}
}

#endif // !_SZ_VECTOR_TEST_H_
