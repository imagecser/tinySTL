#ifndef _SZ_ALGORITHM_H_
#define _SZ_ALGORITHM_H_
#include <type_traits>
#include "iterator.h"
#include "functional.h"
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
	constexpr typename sz::iterator_traits<InputIterator>::difference_type 
		count(InputIterator first, InputIterator last, const T& val) {
		typename sz::iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (*first == val)
				ret++;
		return ret;
	}
	template<class InputIterator, class UnaryPredicate>
	constexpr typename sz::iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, UnaryPredicate p) {
		typename sz::iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			if (p(*first))
				ret++;
		return ret;
	}

	//mismatch function

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
		return sz::find_end(first, last, s_first, s_last, sz::equal_to<typename sz::iterator_traits<ForwardIterator1>::value_type>());
	}
	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	constexpr ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate p = sz::equal_to<typename sz::iterator_traits<ForwardIterator1>::value_type>()) {
		if (s_first == s_last)
			return last;
		ForwardIterator1 res = last;
		while (true) {
			ForwardIterator1 new_res = sz::search(first, last, s_first, s_last, p);
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
		return sz::find_first_of(first, last, s_first, s_last, sz::equal_to<typename sz::iterator_traits<InputIterator>::value_type>());
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
		return sz::adjacent_find(first, last, sz::equal_to<typename sz::iterator_traits<ForwardIterator>::value_type>());
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

	template<class ForwardIterator1, class ForwardIterator2>
	constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last) {
		return sz::search(first, last, s_first, s_last, equal_to<typename sz::iterator_traits<ForwardIterator1>::value_type>());
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
		return sz::search_n(first, last, n, val, sz::equal_to<typename sz::iterator_traits<ForwardIterator>::value_type>());
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
