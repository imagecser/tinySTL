#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_
#include "type_traits.h"
#include <new>

namespace stl {
	template<typename T1, typename T2>
	inline void construct(T1* p, const T2& value) {
		new (p) T1(value);
	}

	template<typename T>
	inline void destroy(T *ptr) {
		ptr->~T();
	}

	template<typename ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type){}

	template<typename ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
		for(; first < last; ++first)
			destroy(&*first);
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
		_destroy(first, last, is_POD_type());
	}
}

#endif // !_CONSTRUCT_H_
