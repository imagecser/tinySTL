#ifndef _SZ_ALGORITHM_H_
#define _SZ_ALGORITHM_H_
#include <type_traits>
#include <random>
#include <ctime>
#include "iterator.h"
#include "functional.h"
#include "type_traits.h"
#include "utility.h"
namespace sz {

#ifndef _DEFINE_NAMESPACE
#define _DEFINE_NAMESPACE
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
	typename _SZ iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& val) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ count_if(first, last, [=](value_type _cur) {return _cur == val; });
	}
	template<class InputIterator, class UnaryPredicate>
	typename _SZ iterator_traits<InputIterator>::difference_type
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
	InputIterator find(InputIterator first, InputIterator last, const T& val) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ find_if(first, last, [=](value_type _cur) {return _cur == val; });
	}
	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate p) {
		for (; first != last; ++first)
			if (p(*first))
				return first;
		return last;
	}
	template<class InputIterator, class UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate p) {
		for (; first != last; ++first)
			if (!p(*first))
				return first;
		return last;
	}

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last) {
		typedef typename _SZ iterator_traits<ForwardIterator1>::value_type value_type;
		return _SZ find_end(first, last, s_first, s_last, _SZ equal_to<value_type>());
	}
	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate p) {
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
	InputIterator find_first_of(InputIterator first, InputIterator last, ForwardIterator s_first, ForwardIterator s_last) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ find_first_of(first, last, s_first, s_last, _SZ equal_to<value_type>());
	}
	template<class InputIterator, class ForwardIterator, class BinaryPredicate>
	InputIterator find_first_of(InputIterator first, InputIterator last, ForwardIterator s_first, ForwardIterator s_last, BinaryPredicate p) { //potential refactoring based on KMP
		for (; first != last; ++first)
			for (ForwardIterator it = s_first; it != s_last; ++it)
				if (p(*first, *it))
					return first;
		return last;
	}

	template<class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
		typedef typename _SZ iterator_traits<ForwardIterator>::value_type value_type;
		return _SZ adjacent_find(first, last, _SZ equal_to<value_type>());
	}
	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate p) {
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
	ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last) {
		typedef typename _SZ iterator_traits<ForwardIterator1>::value_type value_type;
		return _SZ search(first, last, s_first, s_last, equal_to<value_type>());
	}
	template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
	ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 s_first, ForwardIterator2 s_last, BinaryPredicate p) {
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
	ForwardIterator search(ForwardIterator first, ForwardIterator last, const Searcher& searcher) {
		return searcher(first, last).first;
	}

	template<class ForwardIterator, class Size, class T>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val) {
		typedef typename _SZ iterator_traits<ForwardIterator>::value_type value_type;
		return _SZ search_n(first, last, n, val, _SZ equal_to<value_type>());
	}
	template<class ForwardIterator, class Size, class T, class BinaryPredicate>
	ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val, BinaryPredicate p) {
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
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator d_first) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ copy_if(first, last, d_first, _SZ logical_true_1op<value_type>());
	}
	template<class InputIterator, class OutputIterator, class UnaryPredicate>
	OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator d_first, UnaryPredicate pred) {
		for (; first != last; ++first)
			if (pred(*first))
				*d_first++ = *first;
		return d_first;
	}
	template<class InputIterator, class Size, class OutputIterator>
	OutputIterator copy_n(InputIterator first, Size n, OutputIterator result) {
		if (n > 0) {
			*result++ = *first;
			for (Size i = 1; i < n; ++i)
				*result++ = *++first;
		}
		return result;
	}
	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 d_last) {
		while (first != last)
			*(--d_last) = *(--last);
		return d_last;
	}

	/*move*/

	template<class InputIterator, class OutputIterator>
	OutputIterator move(InputIterator first, InputIterator last, OutputIterator d_first) {
		while (first != last)
			*d_first++ = _SZ move(*first++);
		return d_first;
	}
	template<class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 d_last) {
		while (first != last)
			*(--d_last) = _SZ move(*(--last));
		return d_last;
	}

	/*fill*/

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

	/*transform*/

	template<class InputIterator, class OutputIterator, class UnaryOperation>
	OutputIterator transform(InputIterator first, InputIterator last, OutputIterator d_first, UnaryOperation unary_op) {
		while (first != last)
			*d_first++ = unary_op(*first++);
		return d_first;
	}
	template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator d_first, BinaryOperation binary_op) {
		while (first1 != last1)
			*d_first++ = binary_op(*first1++, *first2++);
		return d_first;
	}

	/*generate*/

	template<class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator g) {
		while (first != last)
			*first++ = g();
	}
	template<class OutputIterator, class Generator, class Size>
	OutputIterator generate_n(OutputIterator first, Size n, Generator g) {
		while (n--)
			*first++ = g();
		return first;
	}

	/*remove*/

	template<class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val) {
		typedef typename _SZ iterator_traits<ForwardIterator>::value_type value_type;
		return _SZ remove_if(first, last, [=](value_type _cur) {return _cur == val; });
	}
	template<class ForwardIterator, class UnaryPredicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
		first = _SZ find_if(first, last, p);
		if (first != last)
			for (ForwardIterator it = first; ++it != last;)
				if (!p(*it))
					*first++ = _SZ move(*it);
		return first;
	}

	/*remove_copy*/

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator d_first, const T& val) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ remove_copy_if(first, last, d_first, [=](value_type _cur) {return _cur == val; });
	}
	template<class InputIterator, class OutputIterator, class UnaryPredicate>
	OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator d_first, UnaryPredicate p) {
		for (; first != last; ++first)
			if (!p(*first))
				*d_first++ = *first;
		return d_first;
	}

	/*replace*/

	template<class ForwardIterator, class T>
	void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
		typedef typename _SZ iterator_traits<ForwardIterator>::value_type value_type;
		_SZ replace_if(first, last, [=](value_type _cur) {return _cur == old_value; }, new_value);
	}
	template<class ForwardIterator, class UnaryPredicate, class T>
	void replace_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p, const T& new_value) {
		for (; first != last; ++first)
			if (p(*first))
				*first = new_value;
	}

	/*replace_copy*/

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator d_first, const T& old_value, const T& new_value) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ replace_copy_if(first, last, d_first, [=](value_type _cur) {return _cur == old_value; }, new_value);
	}
	template<class InputIterator, class OutputIterator, class UnaryPredicate, class T>
	OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator d_first, UnaryPredicate p, const T& new_value) {
		for (; first != last; ++first)
			*d_first++ = p(*first) ? new_value : *first;
		return d_first;
	}

	/*swap*/

	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
		while (first1 != last1)
			_SZ iter_swap(first1++, first2++);
		return first2;
	}
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
		_SZ swap(*a, *b);
	}

	/*reverse*/

	template<class BidirectionalIterator>
	void reverse(BidirectionalIterator first, BidirectionalIterator last) {
		while (first != last && first != --last)
			_SZ iter_swap(first++, last);
	}
	template<class BidirectionalIterator, class OutputIterator>
	OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator d_first) {
		while (last != first)
			*d_first++ = *--last;
		return d_first;
	}

	/*rotate*/

	template<class ForwardIterator>
	ForwardIterator rotate(ForwardIterator first, ForwardIterator n_first, ForwardIterator last) {
		if (first == n_first) return last;
		if (n_first == last) return first;

		ForwardIterator next = n_first;
		do {
			_SZ iter_swap(first++, next++);
			if (first == n_first)
				n_first = next;
		} while (next != last);

		ForwardIterator ret = first;
		for (next = n_first; next != last;) {
			_SZ iter_swap(first++, next++);
			if (first == n_first)
				n_first = next;
			else if (next == last)
				next = n_first;
		}
		return ret;
	}
	template<class InputIterator, class OutputIterator>
	OutputIterator rotate_copy(InputIterator first, InputIterator n_first, InputIterator last, OutputIterator d_first) {
		d_first = _SZ copy(n_first, last, d_first);
		return _SZ copy(first, n_first, d_first);
	}

	/*shuffle*/

	template<class RandomAccessIterator>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
		std::srand((unsigned)time(NULL));
		typename _SZ iterator_traits<RandomAccessIterator>::difference_type i = n - 1, n = last - first;
		for (; i > 0; --i)
			_SZ swap(first[i], first[std::rand() % (i + 1)]);
	}
	template<class RandomAccessIterator, class RandomFunc>
	void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomFunc&& r) {
		typename _SZ iterator_traits<RandomAccessIterator>::difference_type i = n - 1, n = last - first;
		for (; i > 0; --i)
			_SZ swap(first[i], first[r(i + 1)]);
	}

	/*unique*/

	template<class ForwardIterator>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
		typedef typename _SZ iterator_traits<ForwardIterator>::value_type value_type;
		return _SZ unique(first, last, [](value_type lhs, value_type rhs) {return lhs == rhs; });
	}
	template<class ForwardIterator, class BinaryPredicate>
	ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate p) {
		if (first == last)
			return last;
		ForwardIterator res = first;
		while (++first != last)
			if (!p(*res, *first) && ++res != first)
				*res = _SZ move(*first);
		return ++res;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator d_first) {
		typedef typename _SZ iterator_traits<InputIterator>::value_type value_type;
		return _SZ unique_copy(first, last, d_first, equal_to<value_type>());
	}
	template<class InputIterator, class OutputIterator, class BinaryPredicate>
	OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator d_first, BinaryPredicate p) {
		if (first == last)
			return d_first;
		InputIterator prev = first, cur = first;
		for (; cur != last; ++cur) {
			if (prev == cur)
				*d_first++ = *prev;
			else if (*prev == *cur);
			else if(*prev != *cur) {
				*d_first++ = *cur;
				prev = cur;
			}
		}
		return d_first;
	}

	/*Partitioning operations*/ //no testcases

	template<class InputIterator, class UnaryPredicate>
	bool is_partitioned(InputIterator first, InputIterator last, UnaryPredicate p) {
		for (; first != last; ++first)
			if (!p(*first))
				break;
		for (; first != last; ++first)
			if (p(*first))
				return false;
		return true;
	}
	template<class ForwardIterator, class UnaryPredicate>
	ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
		first = _SZ find_if_not(first, last, p);
		if (first == last)
			return first;
		for (ForwardIterator it = _SZ next(first); it != last; ++it)
			if (p(*it)) {
				_SZ iter_swap(it, first);
				++first;
			}
		return first;
	}
	template<class InputIterator, class OutputIterator1, class OutputIterator2, class UnaryPredicate>
	_SZ pair<OutputIterator1, OutputIterator2>
		partition_copy(InputIterator first, InputIterator last, 
			OutputIterator1 d_first_true, OutputIterator2 d_first_false, UnaryPredicate p) {
		for (; first != last; ++first) {
			if (p(*first))
				*d_first_true++ = *first;
			else
				*d_first_false++ = *first;
		}
		return _SZ pair<OutputIterator1, OutputIterator2>(d_first_true, d_first_false);
	}
	// stable partition to do 

	template<class ForwardIterator, class UnaryPredicate>
	ForwardIterator partition_point(ForwardIterator first, ForwardIterator last, UnaryPredicate p) {
		return _SZ find_if_not(first, last, p);
	}
	
}

#endif // !_SZ_ALGORITHM_H_
