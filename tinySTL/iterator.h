#ifndef _SZ_ITERATOR_H_
#define _SZ_ITERATOR_H_
#include <cassert>
namespace sz {

#ifndef _DEFINE_NAMESPACE
#define _SZ ::sz::
#endif // !_DEFINE_NAMESPACE

	typedef int ptrdiff_t;
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };


	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};
	template<class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};
	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag		iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};
	template<class Iterator>
	class reverse_iterator_ {
	public:
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef const pointer											const_pointer;
		typedef const reference											const_reference;
	private:
		Iterator _cur;

		void add_aux(difference_type n, random_access_iterator_tag) {
			_cur -= n;
		}
		void add_aux(difference_type n, bidirectional_iterator_tag) {
			for (difference_type i = 0; i < n; ++i)
				--_cur;
		}
		void minus_aux(difference_type n, random_access_iterator_tag) {
			_cur += n;
		}
		void minus_aux(difference_type n, bidirectional_iterator_tag) {
			for (difference_type i = 0; i < n; ++i)
				++_cur;
		}
	public:
		reverse_iterator_() : _cur(0) {}
		explicit reverse_iterator_(const Iterator& ite) {
			Iterator _tmp = ite;
			_tmp--;
			_cur = _tmp;
		}
		template<class Iter>
		reverse_iterator_(const reverse_iterator_<Iter>& rite) {
			_cur = rite._cur;
		}

		Iterator base() {
			Iterator _tmp = _cur;
			_tmp++;
			return _tmp;
		}
		reference operator*() {
			return *_cur;
		}
		const_reference operator*() const {
			return *_cur;
		}
		pointer operator->() {
			return &(operator*());
		}
		const_pointer operator->() const {
			return &(operator*());
		}
		reverse_iterator_& operator++() {
			--_cur;
			return *this;
		}
		reverse_iterator_ operator--(int) {
			reverse_iterator_ _trite = *this;
			--(*this);
			return _trite;
		}
		reverse_iterator_& operator--() {
			++_cur;
			return *this;
		}
		reverse_iterator_ operator++(int) {
			reverse_iterator_ _trite = *this;
			++(*this);
			return _trite;
		}
		reference operator[](difference_type n) {
			return base()[-n - 1];
		}
		reverse_iterator_& operator+= (difference_type n) {
			add_aux(n, iterator_category());
			return *this;
		}
		reverse_iterator_& operator-= (difference_type n) {
			minus_aux(n, iterator_category());
			return *this;
		}
		reverse_iterator_ operator+ (difference_type n) const {
			reverse_iterator_<Iterator> res = *this;
			res += n;
			return res;
		}
		reverse_iterator_ operator- (difference_type n) const {
			reverse_iterator_<Iterator> res = *this;
			res -= n;
			return res;
		}

		friend bool operator == (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur == rhs._cur;
		}
		friend bool operator != (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur == rhs._cur;
		}
		friend bool operator < (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur < rhs._cur;
		}
		friend bool operator <= (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur <= rhs._cur;
		}
		friend bool operator > (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur > rhs._cur;
		}
		friend bool operator >= (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur >= rhs._cur;
		}
		friend reverse_iterator_<Iterator> operator + (typename reverse_iterator_<Iterator>::difference_type n, const reverse_iterator_<Iterator>& rite) {
			return rite + n;
		}
		friend typename reverse_iterator_<Iterator>::difference_type operator - (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur - rhs._cur;
		}
	};

	/*operations*/

	template<class InputIterator, class Distance>
	void _advance_aux(InputIterator& it, Distance n, input_iterator_tag) {
		assert(n >= 0);
		while (n--)
			++it;
	}
	template<class BidirectionIterator, class Distance>
	void _advance_aux(BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
		if (n < 0)
			while (n++)
				--it;
		else
			while (n--)
				++it;
	}
	template<class RandomIterator, class Distance>
	void _advance_aux(RandomIterator& it, Distance n, random_access_iterator_tag) {
		if (n < 0)
			it -= (-n);
		else
			it += n;
	}
	template<class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n) {
		_SZ _advance_aux(it, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance_aux(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type ret = 0;
		for (; first != last; ++first)
			++ret;
		return ret;
	}
	template<class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		_distance_aux(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
		return last - first;
	}
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		return _SZ _distance_aux(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}

	template<class ForwardIterator>
	ForwardIterator next(ForwardIterator it, typename iterator_traits<ForwardIterator>::difference_type n = 1) {
		_SZ advance(it, n);
		return it;
	}

	template<class BidrectionalIterator>
	BidrectionalIterator prev(BidrectionalIterator it, typename iterator_traits<BidrectionalIterator>::difference_type n = 1) {
		_SZ advance(it, -n);
		return it;
	}

	/*range*/

	template<class Container>
	constexpr auto begin(Container& c) ->decltype(c.begin()) {
		return c.begin();
	}
	template<class Container>
	constexpr auto begin(const Container& c) ->decltype(c.begin()) {
		return c.begin();
	}
	template<class Container>
	constexpr auto end(Container& c) ->decltype(c.end()) {
		return c.end();
	}
	template<class Container>
	constexpr auto end(const Container& c) ->decltype(c.end()) {
		return c.end();
	}
	template<class T, size_t size>
	constexpr T *begin(T(&_Array)[size]) {
		return _Array;
	}
	template<class T, size_t size>
	constexpr T *end(T(&_Array)[size]) {
		return _Array + size;
	}

	template<class Container>
	constexpr auto cbegin(const Container& c) ->decltype(_SZ begin(c)) {
		return _SZ begin(c);
	}
	template<class Container>
	constexpr auto cend(const Container& c) ->decltype(_SZ end(c)) {
		return _SZ end(c);
	}

	template<class Container>
	constexpr auto rbegin(Container& c) ->decltype(c.rbegin()) {
		return c.rbegin();
	}
	template<class Container>
	constexpr auto rbegin(const Container& c) ->decltype(c.rbegin()) {
		return c.rbegin();
	}
	template<class Container>
	constexpr auto rend(Container& c) ->decltype(c.rend()) {
		return c.rend();
	}
	template<class Container>
	constexpr auto rend(const Container& c) ->decltype(c.rend()) {
		return c.rend();
	}
	template<class T, size_t size>
	constexpr _SZ reverse_iterator_<T*> rbegin(T(&_Array)[size]) {
		return _SZ reverse_iterator_<T*>(_Array + size);
	}
	template<class T, size_t size>
	constexpr _SZ reverse_iterator_<T*> rend(T(&_Array)[size]) {
		return _SZ reverse_iterator_<T*>(_Array);
	}

	template<class Container>
	constexpr auto crbegin(const Container& c) ->decltype(_SZ rbegin(c)) {
		return _SZ rbegin(c);
	}
	template<class Container>
	constexpr auto crend(const Container& c) ->decltype(_SZ rend(c)) {
		return _SZ rend(c);
	}

	template<class Container>
	constexpr auto size(const Container& c) ->decltype(c.size()) {
		return c.size();
	}
	template<class T, size_t _size>
	constexpr size_t size(const T(&_Arrray)[_size]) {
		return size;
	}

	template<class Container>
	constexpr auto empty(const Container& c) ->decltype(c.empty()) {
		return c.empty();
	}
	template<class T>
	constexpr bool empty(const T(&_Array)[size]) {
		return false;
	}
}


#endif // !_SZ_ITERATOR_H_
