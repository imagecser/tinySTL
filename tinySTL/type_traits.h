#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

namespace sz {
	struct _true_type {};
	struct _false_type {};

#define make_true_traits(temp, type) \
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

	make_true_traits(, bool)
	make_true_traits(, char)
	make_true_traits(, unsigned char)
	make_true_traits(, signed char)
	make_true_traits(, wchar_t)
	make_true_traits(, short)
	make_true_traits(, unsigned short)
	make_true_traits(, int)
	make_true_traits(, unsigned int)
	make_true_traits(, long)
	make_true_traits(, unsigned long)
	make_true_traits(, long long)
	make_true_traits(, unsigned long long)
	make_true_traits(, float)
	make_true_traits(, double)
	make_true_traits(, long double)
	make_true_traits(typename T, T*)
	make_true_traits(typename T, const T*)
	make_true_traits(, char*)
	make_true_traits(, unsigned char*)
	make_true_traits(, signed char*)
	make_true_traits(, const char*)
	make_true_traits(, const unsigned char*)
	make_true_traits(, const signed char*)
}

#endif // !_TYPE_TRAITS_H_
