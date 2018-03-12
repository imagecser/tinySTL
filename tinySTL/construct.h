#ifndef _SZ_CONSTRUCT_H_
#define _SZ_CONSTRUCT_H_
#include "type_traits.h"
#include <new>

namespace sz {
    template<class T1, class T2>
    inline void construct(T1* p, const T2& value) {
        new (p) T1(value);
    }

    template<class T>
    inline void destroy(T *ptr) {
        ptr->~T();
    }

    template<class FwdIt>
    inline void _destroy(FwdIt first, FwdIt last, _true_type){}

    template<class FwdIt>
    inline void _destroy(FwdIt first, FwdIt last, _false_type) {
        for(; first < last; ++first)
            destroy(&*first);
    }

    template<class FwdIt>
    inline void destroy(FwdIt first, FwdIt last) {
        typedef class _type_traits<FwdIt>::is_POD_type is_POD_type;
        _destroy(first, last, is_POD_type());
    }
}

#endif // !_CONSTRUCT_H_
