#ifndef _SZ_ALGORITHM_H_
#define _SZ_ALGORITHM_H_

namespace sz {
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
}

#endif // !_SZ_ALGORITHM_H_
