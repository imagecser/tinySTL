#ifndef _SZ_UTILITY_H_
#define _SZ_UTILITY_H_
#include "type_traits.h"
#include <utility>
namespace sz {

#ifndef _DEFINE_NAMESPACE
#define _DEFINE_NAMESPACE
#define _SZ ::sz::
#endif // !_DEFINE_NAMESPACE

    /*swap*/

    template<class T>
    void swap(T& a, T& b) {
        T tmp = _SZ move(a);
        a = _SZ move(b);
        b = _SZ move(tmp);
    }
    template<class T, size_t _size>
    void swap(T(&_left)[_size], T(&_right)[_size]) {
        if (&_left != &_right) {
            T *first1 = _left, *last1 = _left + _size, *first2 = _right;
            for (; first1 != last1; ++first1, ++first2)
                _SZ iter_swap(first1, first2);
        }
    }

    /*move*/

    template<class T>
    typename _SZ remove_reference_t<T>&& move(T&& param) noexcept {
        using returnType = _SZ remove_reference_t<T>&&;
        return static_cast<returnType>(param);
    }

    /*pair*/

    template<class T1, class T2>
    struct pair {
        typedef T1    first_type;
        typedef T2    second_type;

        first_type first;
        second_type second;
        pair() :first(first_type()), second(second_type()) { }
        pair(const first_type& a, const second_type& b) : first(a), second(b) { }
        template<class _T1, class _T2>
        pair(const _SZ pair<_T1, _T2>& p) : first(p.first), second(p.second) { }

        void swap(_SZ pair<T1, T2>& p) {
            if (this != &p) {
                _SZ swap(first, p.first);
                _SZ swap(second, p.second);
            }
        }

        template<class _T1, class _T2>
        pair& operator=(const _SZ pair<_T1, _T2>& p) : first(p.first), second(p.second) { }
    };

    /*pair operator*/

    template<class _T1, class _T2>
    bool operator==(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return _left.first == _right.first && _left.second == _right.second;
    }
    template<class _T1, class _T2>
    bool operator!=(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return !(_left == _right);
    }
    template<class _T1, class _T2>
    bool operator<(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return _left.first < _right.first || (!(_right.first < _left.first) && _left.second < _right.second);
    }
    template<class _T1, class _T2>
    bool operator>(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return _right < _left;
    }
    template<class _T1, class _T2>
    bool operator<=(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return !(_left > _right);
    }
    template<class _T1, class _T2>
    bool operator>=(const _SZ pair<_T1, _T2>& _left, const _SZ pair<_T1, _T2>& _right) {
        return !(_left < _right);
    }

    /*pair: swap specialization*/

    template<class T1, class T2>
    void swap(_SZ pair<T1, T2>& lhs, _SZ pair<T1, T2>& rhs) {
        lhs.swap(rhs);
    }

}
#endif // !_SZ_UTILITY_H_

