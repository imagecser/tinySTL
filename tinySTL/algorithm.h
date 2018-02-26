#ifndef _SZ_ALGORITHM_H_
#define _SZ_ALGORITHM_H_
#include <type_traits>
#include "iterator.h"
namespace sz {
	/*Non-modifying sequence operations*/

	/*
	template<class InputIterator, class UnaryFunction>
	UnaryFunction _for_each_aux(InputIterator first, InputIterator last, UnaryFunction f, std::false_type) {
		for (; first != last; ++first)
			f(*first);
		return f;
	}
	template<class InputIterator, class Size, class UnaryFunction>
	InputIterator _for_each_aux(InputIterator first, Size n, UnaryFunction f, std::true_type) {
		for (Size i = 0; i != n; ++first, (void)++i)
			f(*first);
		return first;
	}
	*/

	template<class InputIterator, class UnaryFunction>
	UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f) {
		for (; first != last; ++first)
			f(*first);
		return f;
		//return _for_each_aux(first, last, f, std::is_integral<last>::type());
	}
	template<class InputIterator, class Size, class UnaryFunction>
	InputIterator for_each_n(InputIterator first, Size n, UnaryFunction f) {
		for (Size i = 0; i != n; ++first, (void)++i)
			f(*first);
		return first;
		//return _for_each_aux(first, n, f, std::is_integral<Size>::type());
	}

	template<class InputIterator, class T>
	constexpr typename iterator_traits<InputIterator>::difference_type 
		count(InputIterator first, InputIterator last, const T& val) {
		typename iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (*first == val)
				ret++;
		return ret;
	}
	template<class InputIterator, class UnaryPredicate>
	constexpr typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, UnaryPredicate p) {
		typename iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (p(*first))
				ret++;
		return ret;
	}

	/*Modifying sequence operations*/

	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val) {
		for (; first != last; ++first)
			*first = val;
	}
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& val) {
		for (; n > 0; ++first, --n)
			*first = val;
		return first;
	}
	template<class T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

#endif // !_SZ_ALGORITHM_H_
