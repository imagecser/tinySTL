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
    template<class T, class K>
    using pair = std::pair<T, K>;

    template<class T, class K>
    _SZ pair<T, K> make_pair(T&& _left, K&& _right) {
        return std::pair<T, K>(_left, _right);
    }

}
#endif // !_SZ_UTILITY_H_

