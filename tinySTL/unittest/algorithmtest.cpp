#include "algorithmtest.h"
#include <vector>
namespace sz {
	namespace algorithmTest {
		void func1() {
			std::vector<int> vec = { 10, 20, 30 };
			std::vector<int> res = { 11, 21, 31 }, res2 = { 22, 42, 62 };
			sz::for_each(vec.begin(), vec.end(), [&vec](int& i) {
				++i;
			});
			unitassert(containerEqual(vec, res), true, "UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);");

			sz::for_each_n(vec.begin(), 3, [&vec](int& i) {
				i *= 2;
			});
			unitassert(containerEqual(vec, res2), true, "InputIterator for_each_n(InputIterator first, Size n, UnaryFunction f)");

		}

		void func2() {
			std::vector<int> vec = { 10, 20, 30, 10, 20, 17, 18, 20, 10, 40 };
			unitassert(sz::count(vec.begin(), vec.end(), 10), 3, "count(InputIterator first, InputIterator last, const T& val);");
			unitassert(sz::count_if(vec.begin(), vec.end(), [](int i) {return i % 5 == 0; }), 8, "count_if(InputIterator first, InputIterator last, UnaryPredicate p);");
		}

		void allTestcases() {
			func1();
			func2();
		}
	}
}