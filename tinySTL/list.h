#ifndef _SZ_LIST_H_
#define _SZ_LIST_H_
#include "allocator.h"
#include <type_traits>
namespace sz {
	template<class T>
	struct _list_node {
		typedef _list_node<T>* pointer;
		pointer prev;
		pointer next;
		T data;
	};
	template<class T>
	struct _list_iterator {
		typedef _list_iterator<T>			iterator;
		typedef _list_node<T>*				link_type;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		link_type _node;

		_list_iterator(const link_type node) : _node(node) {}
		_list_iterator() {}
		_list_iterator(const iterator& ite) : _node(ite._node) {}

		reference operator*() {
			return _node->data;
		}
		pointer operator->() {
			return &(operator*());
		}

		bool operator==(const iterator& src) const {
			return _node == src._node;
		}
		bool operator!=(const iterator& src) const {
			return _node != src._node;
		}

		_list_iterator& operator++(int) {
			_list_iterator _temp = *this;
			++*this;
			return _temp;
		}
		_list_iterator& operator--(int) {
			_list_iterator _temp = *this;
			--*this;
			return _temp;
		}
		_list_iterator& operator++() {
			_node = _node->next;
			return *this;
		}
		_list_iterator& operator--() {
			_node = _node->prev;
			return *this;
		}
	};

	template<class T, class Alloc = allocator<_list_node<T>>>
	class list {
		typedef T									value_type;
		typedef T&									reference;
		typedef const T&							const_reference;
		typedef _list_node<T>						list_node;
		typedef list_node*							link_type;
		typedef _list_iterator<T>					iterator;
		typedef _list_iterator<const T>				const_iterator;
		typedef reverse_iterator_<iterator>			reverse_iterator;
		typedef reverse_iterator_<const iterator>	const_reverse_iterator;
		typedef size_t								size_type;
		typedef ptrdiff_t							difference_type;
	private:
		link_type _end;
		allocator<_list_node<T>> dataAlloc;

		link_type _get_node() {
			return dataAlloc.allocate();
		}
		void _put_node(link_type node) {
			dataAlloc.deallocate(node);
		}

		link_type _create_node(const_reference val, link_type prev = nullptr, link_type next = nullptr) {
			link_type res = _get_node();
			res->data = val;
			res->prev = prev;
			res->next = next;
			return res;
		}
		void _destroy_node(link_type node) {
			destroy(node);
			_put_node(node);
		}

		link_type _insert_node(link_type _node, const_reference val) {
			link_type pnode = _create_node(val, _node->prev, _node);
			_node->prev->next = pnode;
			_node->prev = pnode;
			return pnode;
		}
		link_type _insert_aux(link_type _pos, size_type n, const_reference val, std::true_type) {
			for (size_type i = 0; i < n; ++i)
				_insert_node(_pos, val);
			return _pos;
		}
		template<class InputIterator>
		link_type _insert_aux(link_type _pos, InputIterator first, InputIterator last, std::false_type) {
			for (; first != last; ++first)
				_insert_node(_pos, *first);
			return _pos;
		}

		link_type _erase_node(link_type _node) {
			link_type next = _node->next;
			link_type prev = _node->prev;
			next->prev = prev;
			prev->next = next;
			_destroy_node(_node);
			return next;
		}
		link_type _erase_aux(link_type first, link_type last) {
			for (; first != last;)
				first = _erase_node(first);
			return last;
		}

		void _empty_initial() {
			_end = _get_node();
			_end->next = _end;
			_end->prev = _end;
		}
		void list_aux(size_type n, const_reference val, std::true_type) {
			for (size_type i = 0; i < n; ++i)
				_insert_node(_end, val);
		}
		template<class InputIterator>
		void list_aux(InputIterator first, InputIterator last, std::false_type) {
			for (; first != last; ++first)
				_insert_node(_end, *first);
		}
	public:
		list() {
			_empty_initial();
		}
		explicit list(size_type n, const_reference val = value_type()) {
			_empty_initial();
			list_aux(n, val, std::true_type());
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last) {
			_empty_initial();
			list_aux(first, last, std::is_integral<InputIterator>::type());
		}
		list(const list& src) {
			//list(src.begin(), src.end());
			_empty_initial();
			for (link_type _tmp = src._end->next; _tmp != src._end; _tmp = _tmp->next)
				_insert_node(_end, _tmp->data);
		}
		list& operator=(const list& src) {
			if (this != &src) {
				_erase_aux(_end->next, _end);
				for (link_type _tmp = src._end->next; _tmp != src._end; _tmp = _tmp->next)
					_insert_node(_end, _tmp->data);
			}
			return *this;
		}
		~list() {
			_erase_aux(_end->next, _end);
		}

		void push_front(const_reference val) {
			_insert_node(_end->next, val);
		}
		void pop_front() {
			_erase_node(_end->next);
		}
		void push_back(const_reference val) {
			_insert_node(_end, val);
		}
		void pop_back() {
			_erase_node(_end->prev);
		}

		iterator begin() {
			return iterator(_end->next);
		}
		const_iterator begin() const {
			return const_iterator(_end->next);
		}
		iterator end() {
			return iterator(_end);
		}
		const_iterator end() const {
			return const_iterator(_end);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(_end);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_end);
		}
		reverse_iterator rend() {
			return reverse_iterator(_end->next);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_end->next);
		}
		
		reference front() {
			return _end->next->data;
		}
		reference back() {
			return _end->prev->data;
		}
		bool empty() const {
			return _end->next == _end;
		}
		size_type size() const {
			size_type res = 0;
			for (link_type _tmp = _end->next; _tmp != _end; _tmp = _tmp->next)
				res++;
			return res;
		}
		void swap(list& src) {
			sz::swap(_end, src._end);
		}
		void clear() {
			_erase_aux(_end->next, _end);
		}

		iterator insert(iterator _pos, const_reference val) {
			return _insert_node(_pos._node, val);
		}
		iterator insert(iterator _pos, size_type n, const_reference val) {
			return _insert_aux(_pos._node, n, val, std::true_type());
		}
		template<class InputIterator>
		iterator insert(iterator _pos, InputIterator first, InputIterator last) {
			return _insert_aux(_pos._node, first, last, std::is_integral<InputIterator>::type());
		}

		iterator erase(iterator _pos) {
			return _erase_node(_pos._node);
		}
		iterator erase(iterator first, iterator last) {
			return _erase_aux(first, last);
		}

	};
}
#endif // !_SZ_LIST_H_
