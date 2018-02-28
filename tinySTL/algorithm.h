#ifndef _SZ_ALGORITHM_H_
#define _SZ_ALGORITHM_H_
#include <type_traits>
#include "iterator.h"
#include "functional.h"
#include "type_traits.h"
namespace sz {

#ifndef _DEFINE_NAMESPACE
#define _SZ ::sz::
#endif // !_DEFINE_NAMESPACE


	/*Non-modifying sequence operations*/

	/*for_each*/

	template<class InputIterator, class UnaryFunction>
	UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f) {
		for (; first != last; ++first)
			f(*first);
		return f;
	}
	template<class InputIterator, class Size, class UnaryFunction>
	InputIterator for_each_n(InputIterator first, Size n, UnaryFunction f) {
		for (Size i = 0; i != n; ++first, (void)++i)
			f(*first);
		return first;
	}

	template<class InputIterator, class T>
	constexpr typename _SZ iterator_traits<InputIterator>::difference_type 
		count(InputIterator first, InputIterator last, const T& val) {
		typename _SZ iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (*first == val)
				ret++;
		return ret;
	}
	template<class InputIterator, class UnaryPredicate>
	constexpr typename _SZ iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, UnaryPredicate p) {
		typename _SZ iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (p(*first))
				ret++;
		return ret;
	}

	//mismatch function

	/*find*/

	template<class InputIterator, class T>
	constexpr InputIterator find(InputIterator first, InputIterator last, const T& val) {
		for (; first != last; ++first)
			if (*first == val)
				return first;
		return last;
	}
	template<class InputIterator, class UnaryPredicate>
	constexpr InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate p) {
		for (; first != last; ++first)
			if (p(*first))
				return first;
		return last;
	}
	template<class InputIterator, class UnaryPredicate>
	constexpr InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate p) {
		for (; first != last; ++first)
			if (!p(*first))
				return first;
		return last;
	}

	template<class ForwardIterator1, class ForwardIterator2>
	constexpr ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last) {
		return _SZ find_end(first, last, s_first, s_last, _SZ equal_to<typename _SZ iterator_traits<ForwardIterator1>::value_type>());
	}
	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	constexpr ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate p = _SZ equal_to<typename _SZ iterator_traits<ForwardIterator1>::value_type>()) {
		if (s_first == s_last)
			return last;
		ForwardIterator1 res = last;
		while (true) {
			ForwardIterator1 new_res = _SZ search(first, last, s_first, s_last, p);
			if (new_res == last)
				return res;
			else {
				res = new_res;
				first = res;
				++first;
			}
		}
		return res;
	}

	template<class InputIterator, class ForwardIterator>
	constexpr InputIterator find_first_of(InputIterator first, InputIterator last, ForwardIterator s_first, ForwardIterator s_last) {
		return _SZ find_first_of(first, last, s_first, s_last, _SZ equal_to<typename _SZ iterator_traits<InputIterator>::value_type>());
	}
	template<class InputIterator, class ForwardIterator, class BinaryPredicate>
	constexpr InputIterator find_first_of(InputIterator first, InputIterator last, ForwardIterator s_first, ForwardIterator s_last, BinaryPredicate p) { //potential refactoring based on KMP
		for (; first != last; ++first)
			for (ForwardIterator it = s_first; it != s_last; ++it)
				if (p(*first, *it))
					return first;
		return last;
	}

	template<class ForwardIterator>
	constexpr ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
		return _SZ adjacent_find(first, last, _SZ equal_to<typename _SZ iterator_traits<ForwardIterator>::value_type>());
	}
	template<class ForwardIterator, class BinaryPredicate>
	constexpr ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate p) {
		if (first == last)
			return last;
		ForwardIterator next = first;
		next++;
		for (; next != last; ++first, ++next)
			if (p(*first, *next))
				return first;
		return last;
	}

	/*search*/

	template<class ForwardIterator1, class ForwardIterator2>
	constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last) {
		return _SZ search(first, last, s_first, s_last, equal_to<typename _SZ iterator_traits<ForwardIterator1>::value_type>());
	}
	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate p) {
		for (;; ++first) {
			ForwardIterator1 it = first;
			for (ForwardIterator2 s_it = s_first; ; ++it, ++s_it) {
				if (s_it == s_last)
					return first;
				else if (it == last)
					return last;
				else if (!p(*it, *s_it))
					break;
			}
		}
	}
	template<class ForwardIterator, class Searcher>
	constexpr ForwardIterator search(ForwardIterator first, ForwardIterator last, const Searcher& searcher) {
		return searcher(first, last).first;
	}

	template<class ForwardIterator, class Size, class T>
	constexpr ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val) {
		return _SZ search_n(first, last, n, val, _SZ equal_to<typename _SZ iterator_traits<ForwardIterator>::value_type>());
	}
	template<class ForwardIterator, class Size, class T, class BinaryPredicate>
	constexpr ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val, BinaryPredicate p) {
		for (; first != last; ++first) {
			if (!p(*first, val))
				continue;
			ForwardIterator candicate = first;
			Size cur_count = 0;
			while (true) {
				++cur_count;
				if (cur_count == n)
					return candicate;
				++first;
				if (first == last)
					return last;
				if (!p(*first, val))
					break;
			}
		}
		return last;
	}

	/*Modifying sequence operations*/

	/*copy*/

	template<class InputIterator, class OutputIterator>
	constexpr OutputIterator copy(InputIterator first, InputIterator last, OutputIterator d_first) {
		return _SZ copy_if(first, last, d_first, _SZ logical_true_1op<typename _SZ iterator_traits<InputIterator>::value_type>());
	}
	template<class InputIterator, class OutputIterator, class UnaryPredicate>
	constexpr OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator d_first, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first))
				*d_first++ = *first;
		return d_first;
	}
	template<class InputIterator, class Size, class OutputIterator>
	constexpr OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {
		if (n > 0) {
			*result++ = *first;
			for (Size i = 1; i < n; ++i)
				*result++ = *++first;
		}
		return result;
	}
	template<class BidirectionalIterator1, class BidirectionalIterator2>
	constexpr BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 d_last) {
		while (first != last)
			*(--d_last) = *(--last);
		return d_last;
	}

	/*move*/

	template<class T>
	constexpr typename _SZ remove_reference_t<T>&& move(T&& param) noexcept {
		using returnType = _SZ remove_reference_t<T>&&;
		return static_cast<returnType>(param);
	}

	template<class InputIterator, class OutputIterator>
	constexpr OutputIterator move(InputIterator first, InputIterator last, OutputIterator d_first) {
		while (first != last)
			*d_first++ = _SZ move(*first++);
		return d_first;
	}
	template<class BidirectionalIterator1, class BidirectionalIterator2>
	constexpr BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 d_last) {
		while (first != last)
			*(--d_last) = _SZ move(*(--last));
		return d_last;
	}

	/*fill*/
    
	template<class ForwardIterator, class T>
	constexpr void fill(ForwardIterator first, ForwardIterator last, const T& val) {
		for (; first != last; ++first)
			*first = val;
	}
	template<class OutputIterator, class Size, class T>
	constexpr OutputIterator fill_n(OutputIterator first, Size n, const T& val) {
		for (; n > 0; ++first, --n)
			*first = val;
		return first;
	}

	/*transform*/

	template<class InputIterator, class OutputIterator, class UnaryOperation>
	constexpr OutputIterator transform(InputIterator first, InputIterator last, OutputIterator d_first, UnaryOperation unary_op) {
		while (first != last)
			*d_first++ = unary_op(*first++);
		return d_first;
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
	constexpr OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator d_first, BinaryOperation binary_op) {
		while (first1 != last1)
			*d_first++ = binary_op(*first1++, *first2++);
		return d_first;
	}

	/*generate*/

	template<class ForwardIterator, class Generator>
	constexpr void generate(ForwardIterator first, ForwardIterator last, Generator g) {
		while (first != last)
			*first++ = g();
	}
	template<class OutputIterator, class Generator, class Size>
	constexpr OutputIterator generate_n(OutputIterator first, Size n, Generator g) {
		while (n--)
			*first++ = g();
		return first;
	}

	/*remove*/

	template<class ForwardIterator, class T>
	constexpr ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val) {
		first = _SZ find(first, last, val);
		if (first != last)
			for (ForwardIterator it = first; ++it != last;)
				if (!(*it == val))
					*first++ = _SZ move(*it);
		return first;
	}
	template<class ForwardIterator, class UnaryPredicate>
	constexpr ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
		first = _SZ find_if(first, last, p);
		if (first != last)
			for (ForwardIterator it = first; ++it != last;)
				if (!p(*it))
					*first++ = _SZ move(*it);
		return first;
	}

	/*swap*/

	template<class T>
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

#endif // !_SZ_ALGORITHM_H_
