#include "vectortest.h"

namespace sz {
	namespace vectorTest {
		template<class T>
		void unittest(stdvec<T> src, szvec<T> dest, const char *s, bool islast = true, bool condition = true) {
			if (sz::test::containerEqual(dest, src) && condition) {
				if (islast)
					sz::test::unitpass(s);
			}
			else
				sz::test::unitfail(s);
		}
		
		void func1() {


		}
		void allTestcases(){
			func1();
		}
	}
}