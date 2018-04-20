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

    template<class InIt, class UnFn>
    UnFn for_each(InIt first, InIt last, UnFn f) {
        for (; first != last; ++first)
            f(*first);
        return f;
    }
    template<class InIt, class Size, class UnFn>
    InIt for_each_n(InIt first, Size n, UnFn f) {
        for (Size i = 0; i != n; ++first, (void)++i)
            f(*first);
        return first;
    }

    template<class InIt, class T>
    _SZ _Iter_diff_t<InIt>
        count(InIt first, InIt last, const T& val) {
        return _SZ count_if(first, last,
            [=](_SZ _Iter_value_t<InIt> _cur) {return _cur == val; });
    }
    template<class InIt, class UnPr>
    _SZ _Iter_diff_t<InIt>
        count_if(InIt first, InIt last, UnPr p) {
        _SZ _Iter_diff_t<InIt> ret = 0;
        for (; first != last; ++first)
            if (p(*first))
                ret++;
        return ret;
    }

    //mismatch function

    /*find*/

    template<class InIt, class T>
    InIt find(InIt first, InIt last, const T& val) {
        return _SZ find_if(first, last,
            [=](_SZ _Iter_value_t<InIt> _cur) {return _cur == val; });
    }
    template<class InIt, class UnPr>
    InIt find_if(InIt first, InIt last, UnPr p) {
        for (; first != last; ++first)
            if (p(*first))
                return first;
        return last;
    }
    template<class InIt, class UnPr>
    InIt find_if_not(InIt first, InIt last, UnPr p) {
        for (; first != last; ++first)
            if (!p(*first))
                return first;
        return last;
    }

    template<class FwdIt1, class FwdIt2>
    FwdIt1 find_end(FwdIt1 first, FwdIt1 last,
        FwdIt2 s_first, FwdIt2 s_last) {
        return _SZ find_end(first, last,
            s_first, s_last, _SZ equal_to<>());
    }
    template<class FwdIt1, class FwdIt2, class BiPr>
    FwdIt1 find_end(FwdIt1 first, FwdIt1 last,
        FwdIt2 s_first, FwdIt2 s_last, BiPr p) {
        if (s_first == s_last)
            return last;
        FwdIt1 res = last;
        while (true) {
            FwdIt1 new_res = _SZ search(first, last, s_first, s_last, p);
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

    template<class InIt, class FwdIt>
    InIt find_first_of(InIt first, InIt last, FwdIt s_first, FwdIt s_last) {
        return _SZ find_first_of(first, last,
            s_first, s_last, _SZ equal_to<>());
    }
    template<class InIt, class FwdIt, class BiPr>
    InIt find_first_of(InIt first, InIt last,
        FwdIt s_first, FwdIt s_last, BiPr p) { //potential refactoring based on KMP
        for (; first != last; ++first)
            for (FwdIt it = s_first; it != s_last; ++it)
                if (p(*first, *it))
                    return first;
        return last;
    }

    template<class FwdIt>
    FwdIt adjacent_find(FwdIt first, FwdIt last) {
        return _SZ adjacent_find(first, last, _SZ equal_to<>());
    }
    template<class FwdIt, class BiPr>
    FwdIt adjacent_find(FwdIt first, FwdIt last, BiPr p) {
        if (first == last)
            return last;
        FwdIt next = first;
        next++;
        for (; next != last; ++first, ++next)
            if (p(*first, *next))
                return first;
        return last;
    }

    /*search*/

    template<class FwdIt1, class FwdIt2>
    FwdIt1 search(FwdIt1 first, FwdIt1 last,
        FwdIt2 s_first, FwdIt2 s_last) {
        return _SZ search(first, last, s_first, s_last, equal_to<>());
    }
    template<class FwdIt1, class FwdIt2, class BiPr>
    FwdIt1 search(FwdIt1 first, FwdIt1 last,
        FwdIt2 s_first, FwdIt2 s_last, BiPr p) {
        for (;; ++first) {
            FwdIt1 it = first;
            for (FwdIt2 s_it = s_first; ; ++it, ++s_it) {
                if (s_it == s_last)
                    return first;
                else if (it == last)
                    return last;
                else if (!p(*it, *s_it))
                    break;
            }
        }
    }
    template<class FwdIt, class Searcher>
    FwdIt search(FwdIt first, FwdIt last, const Searcher& searcher) {
        return searcher(first, last).first;
    }

    template<class FwdIt, class Size, class T>
    FwdIt search_n(FwdIt first, FwdIt last, Size n, const T& val) {
        return _SZ search_n(first, last, n, val, _SZ equal_to<>());
    }
    template<class FwdIt, class Size, class T, class BiPr>
    FwdIt search_n(FwdIt first, FwdIt last,
        Size n, const T& val, BiPr p) {
        for (; first != last; ++first) {
            if (!p(*first, val))
                continue;
            FwdIt candicate = first;
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

    template<class InIt, class OutIt>
    OutIt copy(InIt first, InIt last, OutIt d_first) {
        return _SZ copy_if(first, last, d_first, _SZ logical_true_1op<>());
    }
    template<class InIt, class OutIt, class UnPr>
    OutIt copy_if(InIt first, InIt last, OutIt d_first, UnPr pred) {
        for (; first != last; ++first)
            if (pred(*first))
                *d_first++ = *first;
        return d_first;
    }
    template<class InIt, class Size, class OutIt>
    OutIt copy_n(InIt first, Size n, OutIt result) {
        if (n > 0) {
            *result++ = *first;
            for (Size i = 1; i < n; ++i)
                *result++ = *++first;
        }
        return result;
    }
    template<class BidIt1, class BidIt2>
    BidIt2 copy_backward(BidIt1 first, BidIt1 last, BidIt2 d_last) {
        while (first != last)
            *(--d_last) = *(--last);
        return d_last;
    }

    /*move*/

    template<class InIt, class OutIt>
    OutIt move(InIt first, InIt last, OutIt d_first) {
        while (first != last)
            *d_first++ = _SZ move(*first++);
        return d_first;
    }
    template<class BidIt1, class BidIt2>
    BidIt2 move_backward(BidIt1 first, BidIt1 last, BidIt2 d_last) {
        while (first != last)
            *(--d_last) = _SZ move(*(--last));
        return d_last;
    }

    /*fill*/

    template<class FwdIt, class T>
    void fill(FwdIt first, FwdIt last, const T& val) {
        for (; first != last; ++first)
            *first = val;
    }
    template<class OutIt, class Size, class T>
    OutIt fill_n(OutIt first, Size n, const T& val) {
        for (; n > 0; ++first, --n)
            *first = val;
        return first;
    }

    /*transform*/

    template<class InIt, class OutIt, class UnFn>
    OutIt transform(InIt first, InIt last, OutIt d_first, UnFn unary_op) {
        while (first != last)
            *d_first++ = unary_op(*first++);
        return d_first;
    }
    template<class InIt1, class InIt2, class OutIt, class BinaryOperation>
    OutIt transform(InIt1 first1, InIt1 last1, InIt2 first2, OutIt d_first, BinaryOperation binary_op) {
        while (first1 != last1)
            *d_first++ = binary_op(*first1++, *first2++);
        return d_first;
    }

    /*generate*/

    template<class FwdIt, class Fn>
    void generate(FwdIt first, FwdIt last, Fn g) {
        while (first != last)
            *first++ = g();
    }
    template<class OutIt, class Fn, class Size>
    OutIt generate_n(OutIt first, Size n, Fn g) {
        while (n--)
            *first++ = g();
        return first;
    }

    /*remove*/

    template<class FwdIt, class T>
    FwdIt remove(FwdIt first, FwdIt last, const T& val) {
        return _SZ remove_if(first, last,
            [=](_SZ _Iter_value_t<FwdIt> _cur) {return _cur == val; });
    }
    template<class FwdIt, class UnPr>
    FwdIt remove_if(FwdIt first, FwdIt last, UnPr p) {
        first = _SZ find_if(first, last, p);
        if (first != last)
            for (FwdIt it = first; ++it != last;)
                if (!p(*it))
                    *first++ = _SZ move(*it);
        return first;
    }

    /*remove_copy*/

    template<class InIt, class OutIt, class T>
    OutIt remove_copy(InIt first, InIt last, OutIt d_first, const T& val) {
        return _SZ remove_copy_if(first, last, d_first,
            [=](_SZ _Iter_value_t<InIt> _cur) {return _cur == val; });
    }
    template<class InIt, class OutIt, class UnPr>
    OutIt remove_copy_if(InIt first, InIt last, OutIt d_first, UnPr p) {
        for (; first != last; ++first)
            if (!p(*first))
                *d_first++ = *first;
        return d_first;
    }

    /*replace*/

    template<class FwdIt, class T>
    void replace(FwdIt first, FwdIt last,
        const T& old_value, const T& new_value) {
        _SZ replace_if(first, last,
            [=](_SZ _Iter_value_t<FwdIt> _cur)
        {return _cur == old_value; }, new_value);
    }
    template<class FwdIt, class UnPr, class T>
    void replace_if(FwdIt first, FwdIt last, UnPr p, const T& new_value) {
        for (; first != last; ++first)
            if (p(*first))
                *first = new_value;
    }

    /*replace_copy*/

    template<class InIt, class OutIt, class T>
    OutIt replace_copy(InIt first, InIt last, OutIt d_first,
        const T& old_value, const T& new_value) {
        return _SZ replace_copy_if(first, last, d_first,
            [=](_SZ _Iter_value_t<InIt> _cur)
        {return _cur == old_value; }, new_value);
    }
    template<class InIt, class OutIt, class UnPr, class T>
    OutIt replace_copy_if(InIt first, InIt last,
        OutIt d_first, UnPr p, const T& new_value) {
        for (; first != last; ++first)
            *d_first++ = p(*first) ? new_value : *first;
        return d_first;
    }

    /*swap*/

    template<class FwdIt1, class FwdIt2>
    FwdIt2 swap_ranges(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2) {
        while (first1 != last1)
            _SZ iter_swap(first1++, first2++);
        return first2;
    }
    template<class FwdIt1, class FwdIt2>
    void iter_swap(FwdIt1 a, FwdIt2 b) {
        _SZ swap(*a, *b);
    }

    /*reverse*/

    template<class BidIt>
    void reverse(BidIt first, BidIt last) {
        while (first != last && first != --last)
            _SZ iter_swap(first++, last);
    }
    template<class BidIt, class OutIt>
    OutIt reverse_copy(BidIt first, BidIt last, OutIt d_first) {
        while (last != first)
            *d_first++ = *--last;
        return d_first;
    }

    /*rotate*/

    template<class FwdIt>
    FwdIt rotate(FwdIt first, FwdIt n_first, FwdIt last) {
        if (first == n_first) return last;
        if (n_first == last) return first;

        FwdIt next = n_first;
        do {
            _SZ iter_swap(first++, next++);
            if (first == n_first)
                n_first = next;
        } while (next != last);

        FwdIt ret = first;
        for (next = n_first; next != last;) {
            _SZ iter_swap(first++, next++);
            if (first == n_first)
                n_first = next;
            else if (next == last)
                next = n_first;
        }
        return ret;
    }
    template<class InIt, class OutIt>
    OutIt rotate_copy(InIt first, InIt n_first, InIt last, OutIt d_first) {
        d_first = _SZ copy(n_first, last, d_first);
        return _SZ copy(first, n_first, d_first);
    }

    /*shuffle*/

    template<class RanIt>
    void random_shuffle(RanIt first, RanIt last) {
        std::srand((unsigned)time(NULL));
        _SZ _Iter_diff_t<RanIt> i = n - 1, n = last - first;
        for (; i > 0; --i)
            _SZ swap(first[i], first[std::rand() % (i + 1)]);
    }
    template<class RanIt, class RandomFunc>
    void random_shuffle(RanIt first, RanIt last, RandomFunc&& r) {
        _SZ _Iter_diff_t<RanIt> i = n - 1, n = last - first;
        for (; i > 0; --i)
            _SZ swap(first[i], first[r(i + 1)]);
    }

    /*unique*/

    template<class FwdIt>
    FwdIt unique(FwdIt first, FwdIt last) {
        return _SZ unique(first, last, _SZ equal_to<>());
    }
    template<class FwdIt, class BiPr>
    FwdIt unique(FwdIt first, FwdIt last, BiPr p) {
        if (first == last)
            return last;
        FwdIt res = first;
        while (++first != last)
            if (!p(*res, *first) && ++res != first)
                *res = _SZ move(*first);
        return ++res;
    }

    template<class InIt, class OutIt>
    OutIt unique_copy(InIt first, InIt last, OutIt d_first) {
        return _SZ unique_copy(first, last, d_first, equal_to<>());
    }
    template<class InIt, class OutIt, class BiPr>
    OutIt unique_copy(InIt first, InIt last, OutIt d_first, BiPr p) {
        if (first == last)
            return d_first;
        InIt prev = first, cur = first;
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

    template<class InIt, class UnPr>
    bool is_partitioned(InIt first, InIt last, UnPr p) {
        for (; first != last; ++first)
            if (!p(*first))
                break;
        for (; first != last; ++first)
            if (p(*first))
                return false;
        return true;
    }
    template<class FwdIt, class UnPr>
    FwdIt partition(FwdIt first, FwdIt last, UnPr p) {
        first = _SZ find_if_not(first, last, p);
        if (first == last)
            return first;
        for (FwdIt it = _SZ next(first); it != last; ++it)
            if (p(*it)) {
                _SZ iter_swap(it, first);
                ++first;
            }
        return first;
    }
    template<class InIt, class OutIt1, class OutIt2, class UnPr>
    _SZ pair<OutIt1, OutIt2>
        partition_copy(InIt first, InIt last, 
            OutIt1 d_first_true, OutIt2 d_first_false, UnPr p) {
        for (; first != last; ++first) {
            if (p(*first))
                *d_first_true++ = *first;
            else
                *d_first_false++ = *first;
        }
        return std::pair<OutIt1, OutIt2>(d_first_true, d_first_false);
    }
    // stable partition to do 

    template<class FwdIt, class UnPr>
    FwdIt partition_point(FwdIt first, FwdIt last, UnPr p) {
        return _SZ find_if_not(first, last, p);
    }
    
    /*bound*/

    template<class FwdIt, class T>
    FwdIt lower_bound(FwdIt first, FwdIt last, const T& val) {
        return _SZ lower_bound(first, last, val, _SZ less<>());
    }
    template<class FwdIt, class T>
    FwdIt upper_bound(FwdIt first, FwdIt last, const T& val) {
        return _SZ upper_bound(first, last, val, _SZ less<>());
    }

#define _algorithm_make_bound_func(_name, _calc_line) \
    template<class FwdIt, class T, class Compare> \
    FwdIt _name(FwdIt first, FwdIt last, const T& val, Compare comp) { \
        FwdIt it; \
        _SZ _Iter_diff_t<FwdIt> count, step; \
        count = _SZ distance(first, last); \
        while (count > 0) { \
            it = first; \
            step = count >> 1; \
            _SZ advance(it, step); \
            if (_calc_line) { \
                first = ++it; \
                count -= step + 1; \
            } else { \
                count = step; \
            } \
        } \
        return first; \
    }

    _algorithm_make_bound_func(lower_bound, (comp(*it, val)));
    _algorithm_make_bound_func(upper_bound, (!comp(val, *it)));

    template<class FwdIt, class T>
    bool binary_search(FwdIt first, FwdIt last, const T& val) {
        first = _SZ lower_bound(first, last, val);
        return (first != last && !(val < *first));
    }
    template<class FwdIt, class T, class Compare>
    bool binary_search(FwdIt first, FwdIt last, const T& val, Compare comp) {
        first = _SZ lower_bound(first, last, val, comp);
        return (first != last && !(comp(val, *first)));
    }

    template<class FwdIt, class T>
    _SZ pair<FwdIt, FwdIt> 
        equal_range(FwdIt first, FwdIt last, const T& val) {
        return _SZ make_pair(_SZ lower_bound(first, last, val),
            _SZ upper_bound(first, last, val));
    }
    template<class FwdIt, class T, class Compare>
    _SZ pair<FwdIt, FwdIt> 
        equal_range(FwdIt first, FwdIt last, const T& val, Compare comp) {
        return _SZ make_pair(_SZ lower_bound(first, last, val, comp),
            _SZ upper_bound(first, last, val, comp));
    }

    /*Set operations (on sorted ranges)*/

    /*merge*/

    template<class InIt1, class InIt2, class OutIt>
    OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2,
        InIt2 last2, OutIt d_first) {
        return _SZ merge(first1, last1, first2, last2, d_first, _SZ less<>());
    }

    template<class InIt1, class InIt2, class OutIt, class Compare>
    OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2,
        InIt2 last2, OutIt d_first, Compare comp) {
        for (; first1 != last1; ++d_first) {
            if (first2 == last2)
                return _SZ copy(first1, last1, d_first);
            if (comp(*first2, *first1))
                *d_first = *first2++;
            else
                *d_first = *first1++;
        }
        return _SZ copy(first2, last2, d_first);
    }

    template<class BidIt>
    void inplace_merge(BidIt first, BidIt middle, BidIt last) {
        return _SZ inplace_merge(first, middle, last, _SZ less<>());
    }

    template<class BidIt, class Compare>
    void inplace_merge(BidIt first, BidIt middle, BidIt last, Compare comp) {
        if (first != last) {
            typedef _SZ _Iter_value_t<BidIt> T;
            _SZ _Iter_diff_t<BidIt> dist = _SZ distance(first, last);
            if (dist != 1) {
                T* tmp = new T[dist];
                _SZ merge(first, middle, middle, last, tmp);
                _SZ copy_n(tmp, dist, first);
                delete[] tmp;
            }
        }
    }

    /*includes*/

    template<class InIt1, class InIt2>
    bool includes(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2) {
        return _SZ includes(first1, last1, first2, last2, _SZ less<>());
    }

    template<class InIt1, class InIt2, class Compare>
    bool includes(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, Compare comp) {
        for (; first2 != last2; ++first1) {
            if (first1 == last1 || comp(*first2, *first1))
                return false;
            if (!comp(*first1, *first2))
                ++first2;
        }
        return true;
    }

    /*set_difference*/

    template<class InIt1, class InIt2, class OutIt>
    OutIt set_difference(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first) {
        return _SZ set_difference(first1, last1,
            first2, last2, d_first, _SZ less<>());
    }

    template<class InIt1, class InIt2, class OutIt, class Compare>
    OutIt set_difference(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2) 
                return _SZ copy(first1, last1, d_first);
            if (comp(*first1, *first2)) {
                *d_first++ = *first1++;
            } else {
                if (!comp(*first2, *first1))
                    ++first1;
                ++first2;
            }
        }
        return d_first;
    }

    /*set_intersection*/

    template<class InIt1, class InIt2, class OutIt>
    OutIt set_intersection(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first) {
        return _SZ set_intersection(first1, last1,
            first2, last2, d_first, _SZ less<>());
    }

    template<class InIt1, class InIt2, class OutIt, class Compare>
    OutIt set_intersection(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first, Compare comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                ++first1;
            } else {
                if (!comp(*first2, *first1))
                    *d_first++ = *first1++;
                ++first2;
            }
        }
        return d_first;
    }

    /*set_symmetric_difference*/

    template<class InIt1, class InIt2, class OutIt>
    OutIt set_symmetric_difference(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first) {
        return _SZ set_symmetric_difference(first1, last1,
            first2, last2, d_first, _SZ less<>());
    }

    template<class InIt1, class InIt2, class OutIt, class Compare>
    OutIt set_symmetric_difference(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2)
                return _SZ copy(first1, last1, d_first);
            if (comp(*first1,*first2)) {
                *d_first++ = *first1++;
            } else {
                if (comp(*first2, *first1))
                    *d_first++ = *first2;
                else
                    ++first1;
                ++first2;
            }
        }
        return _SZ copy(first1, last1, d_first);
    }

    /*set union*/

    template<class InIt1, class InIt2, class OutIt>
    OutIt set_union(InIt1 first1, InIt1 last1,
        InIt2 first2, InIt2 last2, OutIt d_first) {
        return _SZ set_union(first1, last1,
            first2, last2, d_first, _SZ less<>());
    }

    template<class InIt1, class InIt2, class OutIt, class Compare>
    OutIt set_union(InIt1 first1, InIt1 last1, InIt2 first2,
        InIt2 last2, OutIt d_first, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2)
                return _SZ copy(first1, last1, d_first);
            if (comp(*first1, *first2)) {
                *d_first++ = *first1++;
            } else {
                *d_first++ = *first2;
                if (!comp(*first2, *first1))
                    ++first1;
                ++first2;
            }
        }
        return _SZ copy(first2, last2, d_first);
    }

    /*heap operations*/
    
    /*is_heap_until*/

    template<class RanIt>
    RanIt is_heap_until(RanIt first, RanIt last) {
        return _SZ is_heap_until(first, last, _SZ less<>());
    }

    template<class RanIt, class Compare>
    RanIt is_heap_until(RanIt first, RanIt last, Compare comp) {
        const _SZ _Iter_diff_t<RanIt> size = _SZ distance(first, last);
        for (_Iter_diff_t<RanIt> off = 1; off < size; ++off)
            if (comp(first[(off - 1) / 2], first[off]))
                return first + off;
        return last;
    }

    /*is_heap*/

    template<class RanIt>
    bool is_heap(RanIt first, RanIt last) {
        return (_SZ is_heap_until(first, last) == last);
    }

    template<class RanIt, class Compare>
    bool is_heap(RanIt first, RanIt last, Compare comp) {
        return (_SZ is_heap_until(first, last, comp) == last);
    }
}

#endif // !_SZ_ALGORITHM_H_
