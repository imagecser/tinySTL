#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cassert>
#include <new>

namespace stl {
	template<typename T>
	class Allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
	};

}
#endif // !_ALLOCATOR_H_
