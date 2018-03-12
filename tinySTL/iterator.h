#ifndef _SZ_ITERATOR_H_
#define _SZ_ITERATOR_H_
#include <cassert>
#include <iterator>

namespace sz {
#ifndef _DEFINE_NAMESPACE
#define _DEFINE_NAMESPACE
#define _SZ ::sz::
#endif // !_DEFINE_NAMESPACE

    /*
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    */
    typedef int ptrdiff_t;
    typedef std::input_iterator_tag                input_iterator_tag;
    typedef std::output_iterator_tag            output_iterator_tag;
    typedef std::forward_iterator_tag            forward_iterator_tag;
    typedef std::bidirectional_iterator_tag        bidirectional_iterator_tag;
    typedef std::random_access_iterator_tag        random_access_iterator_tag;
    

    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::difference_type        difference_type;
        typedef typename Iterator::pointer                pointer;
        typedef typename Iterator::reference            reference;
    };
    template<class T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag        iterator_category;
        typedef T                                value_type;
        typedef ptrdiff_t                        difference_type;
        typedef T*                                pointer;
        typedef T&                                reference;
    };
    template<class T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag        iterator_category;
        typedef T                                value_type;
        typedef ptrdiff_t                        difference_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
    };
    template<class Iterator>
    class reverse_iterator_ {
    public:
        typedef typename iterator_traits<Iterator>::value_type            value_type;
        typedef typename iterator_traits<Iterator>::iterator_category    iterator_category;
        typedef typename iterator_traits<Iterator>::difference_type        difference_type;
        typedef typename iterator_traits<Iterator>::pointer                pointer;
        typedef typename iterator_traits<Iterator>::reference            reference;
        typedef const pointer                                            const_pointer;
        typedef const reference                                            const_reference;
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

    template<class InIt, class Distance>
    void _advance_aux(InIt& it, Distance n, input_iterator_tag) {
        assert(n >= 0);
        while (n--)
            ++it;
    }
    template<class BidIt, class Distance>
    void _advance_aux(BidIt& it, Distance n, bidirectional_iterator_tag) {
        if (n < 0)
            while (n++)
                --it;
        else
            while (n--)
                ++it;
    }
    template<class RanIt, class Distance>
    void _advance_aux(RanIt& it, Distance n, random_access_iterator_tag) {
        if (n < 0)
            it -= (-n);
        else
            it += n;
    }
    template<class InIt, class Distance>
    void advance(InIt& it, Distance n) {
        _SZ _advance_aux(it, n, typename iterator_traits<InIt>::iterator_category());
    }

    template<class InIt>
    typename iterator_traits<InIt>::difference_type
        _distance_aux(InIt first, InIt last, input_iterator_tag) {
        typename iterator_traits<InIt>::difference_type ret = 0;
        for (; first != last; ++first)
            ++ret;
        return ret;
    }
    template<class RanIt>
    typename iterator_traits<RanIt>::difference_type
        _distance_aux(RanIt first, RanIt last, random_access_iterator_tag) {
        return last - first;
    }
    template<class InIt>
    typename iterator_traits<InIt>::difference_type
        distance(InIt first, InIt last) {
        return _SZ _distance_aux(first, last, typename iterator_traits<InIt>::iterator_category());
    }

    template<class FwdIt>
    FwdIt next(FwdIt it, typename iterator_traits<FwdIt>::difference_type n = 1) {
        _SZ advance(it, n);
        return it;
    }

    template<class BidIt>
    BidIt prev(BidIt it, typename iterator_traits<BidIt>::difference_type n = 1) {
        _SZ advance(it, -n);
        return it;
    }

    /*range*/

    template<class Container>
    auto begin(Container& c) ->decltype(c.begin()) {
        return c.begin();
    }
    template<class Container>
    auto begin(const Container& c) ->decltype(c.begin()) {
        return c.begin();
    }
    template<class Container>
    auto end(Container& c) ->decltype(c.end()) {
        return c.end();
    }
    template<class Container>
    auto end(const Container& c) ->decltype(c.end()) {
        return c.end();
    }
    template<class T, size_t size>
    T *begin(T(&_Array)[size]) {
        return _Array;
    }
    template<class T, size_t size>
    T *end(T(&_Array)[size]) {
        return _Array + size;
    }

    template<class Container>
    auto cbegin(const Container& c) ->decltype(_SZ begin(c)) {
        return _SZ begin(c);
    }
    template<class Container>
    auto cend(const Container& c) ->decltype(_SZ end(c)) {
        return _SZ end(c);
    }

    template<class Container>
    auto rbegin(Container& c) ->decltype(c.rbegin()) {
        return c.rbegin();
    }
    template<class Container>
    auto rbegin(const Container& c) ->decltype(c.rbegin()) {
        return c.rbegin();
    }
    template<class Container>
    auto rend(Container& c) ->decltype(c.rend()) {
        return c.rend();
    }
    template<class Container>
    auto rend(const Container& c) ->decltype(c.rend()) {
        return c.rend();
    }
    template<class T, size_t size>
    _SZ reverse_iterator_<T*> rbegin(T(&_Array)[size]) {
        return _SZ reverse_iterator_<T*>(_Array + size);
    }
    template<class T, size_t size>
    _SZ reverse_iterator_<T*> rend(T(&_Array)[size]) {
        return _SZ reverse_iterator_<T*>(_Array);
    }

    template<class Container>
    auto crbegin(const Container& c) ->decltype(_SZ rbegin(c)) {
        return _SZ rbegin(c);
    }
    template<class Container>
    auto crend(const Container& c) ->decltype(_SZ rend(c)) {
        return _SZ rend(c);
    }

    template<class Container>
    auto size(const Container& c) ->decltype(c.size()) {
        return c.size();
    }
    template<class T, size_t _size>
    size_t size(const T(&_Arrray)[_size]) {
        return size;
    }

    template<class Container>
    auto empty(const Container& c) ->decltype(c.empty()) {
        return c.empty();
    }
    template<class T>
    bool empty(const T(&_Array)[size]) {
        return false;
    }
}


#endif // !_SZ_ITERATOR_H_
