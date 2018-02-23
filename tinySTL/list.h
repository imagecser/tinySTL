#ifndef _SZ_LIST_H_
#define _SZ_LIST_H_
#include "allocator.h"
namespace sz {
	template<class T>
	struct _list_node {
		typedef _list_node<T>* pointer;
		pointer prev;
		pointer next;
		T data;
	};
	template<class T, class Ref = T & , class Ptr = T * >
	struct _list_iterator {
		typedef _list_iterator<T, T&, T*>	iterator;
		typedef _list_iterator<T, Ref, Ptr>	self;

		typedef _list_node<T>*				link_type;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Ptr							pointer;
		typedef Ref							reference;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		link_type _node;

		_list_iterator(link_type node) : _node(node) {}
		_list_iterator() {}
		_list_iterator(const iterator& ite) : _node(ite._node) {}

		reference operator*() {
			return _node->data;
		}
		pointer operator->() {
			return &(operator*());
		}

		bool operator==(const self& src) const {
			return _node == src._node;
		}
		bool operator!=(const self& src) const {
			return _node != src._node;
		}

		self& operator++() {
			_node = _node->next;
			return *this;
		}
		self& operator++(int) {
			self _temp = *this;
			++*this;
			return _temp;
		}
		self& operator--() {
			_node = _node->prev;
			return *this;
		}
		self& operator--(int) {
			self _temp = *this;
			--*this;
			return _temp;
		}
	};

	template<class T>
	class list {
		typedef T								value_type;
		typedef T&								reference;
		typedef _list_node<T>					list_node;
		typedef list_node*						link_type;
		typedef _list_iterator<T>				iterator;
		typedef _list_iterator<const T>			const_iterator;
		typedef reverse_iterator_<iterator>		reverse_iterator;
		typedef size_t							size_type;
		typedef ptrdiff_t						difference_type;
	protected:
		link_type _node;
	};
}
#endif // !_SZ_LIST_H_
