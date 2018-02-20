#ifndef _SZ_MEMORY_H_
#define _SZ_MEMORY_H_
#include "type_traits.h"
#include "iterator.h"
#include "construct.h"
#include "algorithm.h"

namespace sz {
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator ptr, _true_type) {
		for (; first < last; ++first, ++ptr)
			*ptr = *first;
		return ptr;
	}
	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator ptr, _false_type) {
		for (; first < last; ++first, ++ptr)
			construct(ptr, *first);
		return ptr;
	}
	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator ptr) {
		typedef _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
		return _uninitialized_copy_aux(first, last, ptr, is_POD_type());
	}


	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& val, _true_type) {
		fill(first, last, val);
	}
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& val, _false_type) {
		for (; first < last; ++first)
			construct(first, val);
	}
	template<class ForwardIterator, class T>
	void unintialized_fill(ForwardIterator first, ForwardIterator last, const T& val) {
		typedef _type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
		_uninitialized_copy_aux(first, last, val, is_POD_type());
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& val, _true_type) {
		return fill_n(first, n, val);
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& val, _false_type) {
		for (Size i = 0; i != n; ++i)
			construct(first + i, val);
		return first + n;
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& val) {
		typedef _type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type is_POD_type;
		return _uninitialized_fill_n_aux(first, n, val, is_POD_type());
	}
}

#endif // !_SZ_MEMORY_H_
