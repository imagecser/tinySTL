#ifndef _SZ_MEMORY_H_
#define _SZ_MEMORY_H_
#include "type_traits.h"
#include "iterator.h"
#include "construct.h"
#include "algorithm.h"

namespace sz {
    template<class InIt, class FwdIt>
    FwdIt _uninitialized_copy_aux(InIt first, InIt last, FwdIt ptr, _true_type) {
        for (; first < last; ++first, ++ptr)
            *ptr = *first;
        return ptr;
    }
    template<class InIt, class FwdIt>
    FwdIt _uninitialized_copy_aux(InIt first, InIt last, FwdIt ptr, _false_type) {
        for (; first < last; ++first, ++ptr)
            construct(ptr, *first);
        return ptr;
    }
    template<class InIt, class FwdIt>
    FwdIt uninitialized_copy(InIt first, InIt last, FwdIt ptr) {
        typedef _type_traits<iterator_traits<InIt>::value_type>::is_POD_type is_POD_type;
        return _uninitialized_copy_aux(first, last, ptr, is_POD_type());
    }


    template<class FwdIt, class T>
    void _uninitialized_fill_aux(FwdIt first, FwdIt last, const T& val, _true_type) {
        fill(first, last, val);
    }
    template<class FwdIt, class T>
    void _uninitialized_fill_aux(FwdIt first, FwdIt last, const T& val, _false_type) {
        for (; first < last; ++first)
            construct(first, val);
    }
    template<class FwdIt, class T>
    void uninitialized_fill(FwdIt first, FwdIt last, const T& val) {
        typedef _type_traits<iterator_traits<FwdIt>::value_type>::is_POD_type is_POD_type;
        _uninitialized_fill_aux(first, last, val, is_POD_type());
    }

    template<class FwdIt, class Size, class T>
    FwdIt _uninitialized_fill_n_aux(FwdIt first, Size n, const T& val, _true_type) {
        return fill_n(first, n, val);
    }
    template<class FwdIt, class Size, class T>
    FwdIt _uninitialized_fill_n_aux(FwdIt first, Size n, const T& val, _false_type) {
        for (Size i = 0; i != n; ++i)
            construct(first + i, val);
        return first + n;
    }
    template<class FwdIt, class Size, class T>
    FwdIt uninitialized_fill_n(FwdIt first, Size n, const T& val) {
        typedef _type_traits<iterator_traits<FwdIt>::value_type>::is_POD_type is_POD_type;
        return _uninitialized_fill_n_aux(first, n, val, is_POD_type());
    }
}

#endif // !_SZ_MEMORY_H_
