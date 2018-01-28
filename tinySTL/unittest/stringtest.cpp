#include "stringtest.h"
using sz::test::containerEqual;
using sz::test::printContainer;
using sz::test::printEqual;
using sz::test::printItem;
namespace sz {
	namespace stringTest {
		void construct() {
			const char* ptr = "hello world";
			stdstring stdstr1;
			szstring szstr1;
			assert(printEqual(stdstr1, szstr1));
			assert(containerEqual(stdstr1, szstr1));

			stdstring stdstr2(ptr);
			szstring szstr2(ptr);
			assert(printEqual(stdstr2, szstr2));
			assert(containerEqual(stdstr2, szstr2));


		}

		void allTestcases() {
			construct();
		}
	}

}
