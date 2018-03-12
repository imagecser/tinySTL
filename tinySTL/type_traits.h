#ifndef _SZ_TYPE_TRAITS_H_
#define _SZ_TYPE_TRAITS_H_

namespace sz {
    struct _true_type {};
    struct _false_type {};

    /*_type_traits*/

#define _make_true_traits(temp, type) \
template<temp> \
struct _type_traits<type> { \
    typedef _true_type has_trival_default_constructor; \
    typedef _true_type has_trival_copy_constructor; \
    typedef _true_type has_trival_assignment_constructor; \
    typedef _true_type has_trival_destructor; \
    typedef _true_type is_POD_type; \
};

    template<typename _T>
    struct _type_traits {
        typedef _false_type this_dummy_member_must_be_first;
        typedef _false_type has_trival_default_constructor;
        typedef _false_type has_trival_copy_constructor;
        typedef _false_type has_trival_assignment_constructor;
        typedef _false_type has_trival_destructor;
        typedef _false_type is_POD_type;
    };

    _make_true_traits(, bool);
    _make_true_traits(, char);
    _make_true_traits(, unsigned char);
    _make_true_traits(, signed char);
    _make_true_traits(, wchar_t);
    _make_true_traits(, short);
    _make_true_traits(, unsigned short);
    _make_true_traits(, int);
    _make_true_traits(, unsigned int);
    _make_true_traits(, long);
    _make_true_traits(, unsigned long);
    _make_true_traits(, long long);
    _make_true_traits(, unsigned long long);
    _make_true_traits(, float);
    _make_true_traits(, double);
    _make_true_traits(, long double);
    _make_true_traits(typename T, T*);
    _make_true_traits(typename T, const T*);
    _make_true_traits(, char*);
    _make_true_traits(, unsigned char*);
    _make_true_traits(, signed char*);
    _make_true_traits(, const char*);
    _make_true_traits(, const unsigned char*);
    _make_true_traits(, const signed char*);

    /*remove_reference*/

#define _make_remove_reference(arg) template<class T> \
    struct arg \
    {typedef T type;}

    _make_remove_reference(remove_reference);
    _make_remove_reference(remove_reference<T&>);
    _make_remove_reference(remove_reference<T&&>);

    template<class T>
    using remove_reference_t = typename remove_reference<T>::type;
}

#endif // !_SZ_TYPE_TRAITS_H_
