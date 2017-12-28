#include "tinySTL\type_traits.h"
#include "tinySTL\construct.h"

int main() {
	int a = 5;
	a.~int();
	return 0;
}