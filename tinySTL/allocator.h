#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cassert>
#include <new>

namespace sz {
	template<typename T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		static T *allocate();
		static T *allocate(size_t n);
		static void deallocate(T *ptr);
		static void deallocate(T *ptr, size_t n);

		static void construct(T *ptr);
		static void construct(T *ptr, const T& value);
		static void destroy(T *ptr);
		static void destroy(T *first, T *last);
	};

	template<typename T>
	T *allocator::allocate() {
		return malloc(sizeof(T));
	}
	template<typename T>
	T *allocator::allocate(size_t n) {
		return malloc(sizeof(T) * n);
	}
	template<typename T>
	T *allocator::deallocate(T *ptr) {
		free(ptr);
	}
	template<typename T>
	T *allocator::deallocate(T *ptr, size_t n) {
		free(ptr);
	}
	template<typename T>
	void allocator::construct(T *ptr) {
		new(ptr)T();
	}
	template<typename T>
	void allocator::construct(T *ptr, const T& value) {
		new(ptr)T(value);
	}
	template<typename T>
	void allocator::destroy(T *ptr) {
		ptr->~T();
	}
	template<typename T>
	void allocator::destroy(T *first, T *last) {
		for(; first != last; ++first)
			first->~T();
	}

}
#endif // !_allocator_H_
