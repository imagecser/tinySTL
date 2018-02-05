#ifndef _ITERATOR_H_
#define _ITERATOR_H_

namespace sz {

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
		reverse_iterator_(): _cur(0) {}
		explicit reverse_iterator_(const Iterator& ite): _cur(ite - 1){}
		template<class Iter>
		reverse_iterator_(const reverse_iterator_<Iter>& rite) {
			_cur = rite._cur;
		}

		Iterator base() {
			return _cur + 1;
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
		reverse_iterator_& operator--() {
			++_cur;
			return *this;
		}
		reverse_iterator_& operator++(int) {
			reverse_iterator_ _trite = *this;
			++(*this);
			return _trite;
		}
		reverse_iterator_& operator--(int) {
			reverse_iterator_ _trite = *this;
			--(*this);
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

		friend constexpr bool operator == (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur == rhs._cur;
		}
		friend constexpr bool operator != (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur == rhs._cur;
		}
		friend constexpr bool operator < (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur < rhs._cur;
		}
		friend constexpr bool operator <= (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur <= rhs._cur;
		}
		friend constexpr bool operator > (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur > rhs._cur;
		}
		friend constexpr bool operator >= (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur >= rhs._cur;
		}
		friend reverse_iterator_<Iterator> operator + (typename reverse_iterator_<Iterator>::difference_type n, const reverse_iterator_<Iterator>& rite) {
			return rite + n;
		}
		friend typename reverse_iterator_<Iterator>::difference_type operator - (const reverse_iterator_<Iterator>& lhs, const reverse_iterator_<Iterator>& rhs) {
			return lhs._cur - rhs._cur;
		}
	};
}


#endif // !_ITERATOR_H_
