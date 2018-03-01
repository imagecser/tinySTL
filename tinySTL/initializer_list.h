#ifndef _SZ_INITIALIZER_LIST_H_
#define _SZ_INITIALIZER_LIST_H_

namespace sz {
	template<class T>
	class initializer_list {
	public:
		typedef T			value_type;
		typedef const T&	reference;
		typedef reference	const_reference;
		typedef const T*	iterator;
		typedef const T*	const_iterator;
		typedef size_t		size_type;

	private:
		const T* _first;
		const T* _last;

	public:
		constexpr initializer_list() noexcept :
			_first(0), _last(0) {}

		constexpr initializer_list(const_reference  _first_arg, const_reference _last_arg) noexcept :
			_first(_first_arg), _last(_last_arg) {}

		constexpr const_iterator begin() const noexcept {
			return _first;
		}
		constexpr const_iterator end() const noexcept {
			return _last;
		}

		constexpr size_t size() const noexcept {
			return (size_t)(_last - _first);
		}
	};

	template<class T>
	constexpr const T* begin(initializer_list<T> _il) noexcept {
		return _il.begin();
	}
	template<class T>
	constexpr const T* end(initializer_list<T> _il) noexcept {
		return _il.end();
	}
}

#endif // !_SZ_INITIALLIZER_LIST_H