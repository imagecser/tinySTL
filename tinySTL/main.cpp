#include "unittest\stringtest.h"
#include "unittest\vectortest.h"
#include <vector>
#include <string>
int main() {
	sz::stringTest::allTestcases();
	sz::vectorTest::allTestcases();
	std::vector<int> vec;

	system("pause");
	return 0;
}
