#ifndef _SZ_ALLOCATOR_H_
#define _SZ_ALLOCATOR_H_
#include <cassert>
#include <new>
#include "memory.h"

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

		static T *allocate() {
			return (T*)malloc(sizeof(T));
		}
		static T *allocate(size_t n) {
			return (T*)malloc(sizeof(T) * n);
		}
		static void deallocate(T *ptr) {
			free(ptr);
		}
		static void deallocate(T *ptr, size_t n){
			free(ptr);
		}
		static void construct(T *ptr){
			new(ptr) T();
		}
		static void construct(T *ptr, const T& value){
			new(ptr) T(value);
		}
		static void destroy(T *ptr){
			ptr->~T();
		}
		static void destroy(T *first, T *last){
			for (; first != last; ++first)
				first->~T();
		}
	};
}
#endif // !_SZ_allocator_H_
