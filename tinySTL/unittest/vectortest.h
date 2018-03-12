#ifndef _SZ_VECTOR_TEST_H_
#define _SZ_VECTOR_TEST_H_
#include "../vector.h"
#include "testUtil.h"
#include <vector>
namespace sz {
    namespace vectorTest {
        using sz::test::unitassert;
        template<class T>
        using stdvec = std::vector<T>;
        template<class T>
        using szvec = sz::vector<T>;
        void func1();
        void func2();
        void func3();
        void func4();
        void allTestcases();

    }
}

#endif // !_SZ_VECTOR_TEST_H_
