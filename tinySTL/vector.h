#ifndef _SZ_VECTOR_H_
#define _SZ_VECTOR_H_
#include "allocator.h"
#include <type_traits>
#include <initializer_list>
namespace sz {
    template<class T, class Alloc = allocator<T>>
    class vector {
    public:
        typedef T                            value_type;
        typedef T*                            iterator;
        typedef const T*                    const_iterator;
        typedef reverse_iterator_<T*>        reverse_iterator;
        typedef reverse_iterator_<const T*>    const_reverse_iterator;
        typedef size_t                        size_type;
        typedef T&                            reference;
        typedef const T&                    const_reference;
        typedef ptrdiff_t                    difference_type;
        typedef allocator<T>                allocator_type;
    private:
        T* _begin;
        T* _end;
        T* _storage_end;

        Alloc dataAlloc;
        template<class InIt>
        void allocateCopy(InIt first, InIt last) {
            size_type pcapacity = last - first;
            _begin = dataAlloc.allocate(pcapacity);
            _storage_end = _end = uninitialized_copy(first, last, _begin);
        }
        void allocateFilln(size_t n, value_type val) {
            _begin = dataAlloc.allocate(n);
            _storage_end = _end = uninitialized_fill_n(_begin, n, val);
        }
        size_type getNewCapacity(size_type n) const {
            size_type _old = _storage_end - _begin;
            return _old + (_old > n ? _old : n);
        }
        void moveData(vector& vec) {
            _begin = vec._begin;
            _end = vec._end;
            _storage_end = vec._storage_end;
            vec._begin = vec._end = vec._storage_end = 0;
        }
        template<class InIt>
        void vector_aux(InIt first, InIt last, std::false_type) {
            allocateCopy(first, last);
        }
        template<class Integer>
        void vector_aux(Integer n, const_reference val, std::true_type) {
            allocateFilln(n, val);
        }
        template<class InIt>
        iterator insert_aux(iterator pos, InIt first, InIt last, std::false_type) {
            size_type _mov = _end - pos, offset = last - first;
            if (offset < (size_type)(_storage_end - _end)) {
                for (size_type i = _mov; i != -1; --i)
                    *(pos + i + offset) = *(pos + i);
                _end += offset;
                return uninitialized_copy(first, last, pos);
            }
            else {
                size_type pcapacity = getNewCapacity(offset);
                iterator pbegin = dataAlloc.allocate(pcapacity);
                iterator pend = uninitialized_copy(_begin, pos, pbegin);
                iterator res = uninitialized_copy(first, last, pend);
                _end = uninitialized_copy(pos, _end, res);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _storage_end = pbegin + pcapacity;
                return res;
            }
        }
        iterator insert_aux(iterator pos, const size_type& n, const_reference val, std::true_type) {
            if (n < (size_type)(_storage_end - _end)) {
                for (iterator ite = _end - 1; ite >= pos; --ite)
                    *(ite + n) = *ite;
                _end += n;
                return uninitialized_fill_n(pos, n, val);
            }
            else {
                size_type pcapacity = getNewCapacity(n);
                iterator pbegin = dataAlloc.allocate(pcapacity);
                iterator pend = uninitialized_copy(_begin, pos, pbegin);
                iterator res = uninitialized_fill_n(pend, n, val);
                _end = uninitialized_copy(pos, _end, res);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _storage_end = _begin + pcapacity;
                return res;
            }
        }

    public:
        vector() : _begin(0), _end(0), _storage_end(0) {}
        explicit vector(const size_type n) {
            allocateFilln(n, value_type());
        }
        vector(const size_type n, value_type val) {
            allocateFilln(n, val);
        }
        template<class InIt>
        vector(InIt first, InIt last) {
            vector_aux(first, last, typename std::is_integral<InIt>::type());
        }
        vector(const vector& vec) {
            allocateCopy(vec.begin(), vec.end());
        }
        vector(vector&& vec) {
            moveData(vec);    
        }
        vector(std::initializer_list<value_type> ilist) {
            allocateCopy(ilist.begin(), ilist.end());
        }
        ~vector() {
            dataAlloc.deallocate(_begin);
        }
        vector& operator=(const vector& vec) {
            if (this != &vec) {
                dataAlloc.deallocate(_begin);
                allocateCopy(vec.begin(), vec.end());
            }
            return *this;
        }
        vector& operator=(vector&& vec) {
            if (this != &vec) {
                dataAlloc.deallocate(_begin);
                moveData(vec);
            }
            return *this;
        }
        
        iterator begin() {
            return _begin;
        }
        const_iterator begin() const {
            return _begin;
        }
        const_iterator cbegin() const {
            return _begin;
        }
        reverse_iterator rbegin() {
            return reverse_iterator(_end);
        }
        const_reverse_iterator rbegin() const {
            return reverse_iterator(_end);
        }
        const_reverse_iterator crbegin() {
            return const_reverse_iterator(_end);
        }
        iterator end() {
            return _end;
        }
        const_iterator end() const {
            return _end;
        }
        const_iterator cend() const {
            return _end;
        }
        reverse_iterator rend() {
            return reverse_iterator(_begin);
        }
        const_reverse_iterator rend() const {
            return reverse_iterator(_begin);
        }
        const_reverse_iterator crend() {
            return const_reverse_iterator(_begin);
        }

        size_type size() const {
            return _end - _begin;
        }
        size_type capacity() const {
            return _storage_end - _begin;
        }
        bool empty() const {
            return _begin == _end;
        }
        void resize(size_type n, value_type val = value_type()) {
            if (n < size()) {
                uninitialized_fill(_begin + n, _end, val);
                _end = _begin + n;
            }
            else if (n > size() && n <= capacity()) {
                _end = uninitialized_fill_n(_end, n - size(), val);
            }
            else if (n > capacity()) {
                size_type pcapacity = getNewCapacity(n - size());
                iterator pbegin = dataAlloc.allocate(pcapacity);
                _storage_end = pbegin + pcapacity;
                iterator pend = uninitialized_copy(_begin, _end, pbegin);
                pend = uninitialized_fill_n(pend, n - size(), val);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _end = pend;
            }
        }
        void reserve(size_type n) {
            if (n <= capacity())
                return;
            iterator pbegin = dataAlloc.allocate(n);
            iterator pend = uninitialized_copy(_begin, _end, pbegin);
            dataAlloc.deallocate(_begin);
            _begin = pbegin;
            _end = pend;
            _storage_end = _begin + n;
        }
        void shrink_to_fit() {
            if (_storage_end != _end) {
                iterator pbegin = dataAlloc.allocate(size());
                _storage_end = _end = uninitialized_copy(_begin, _end, pbegin);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
            }
        }

        reference operator[](const size_type i) {
            return *(_begin + i);
        }
        const_reference operator[](const size_type i) const {
            return *(_begin + i);
        }
        reference front() {
            return *_begin;
        }
        const_reference front() const {
            return *_begin;
        }
        reference back() {
            return *(_end - 1);
        }
        const_reference back() const {
            return *(_end - 1);
        }
        iterator data() {
            return _begin;
        }

        void clear() {
            uninitialized_fill(_begin, _end, value_type());
            _end = _begin;
        }
        void swap(vector& vec) {
            sz::swap(_begin, vec._begin);
            sz::swap(_end, vec._end);
            sz::swap(_storage_end, vec._storage_end);
        }
        
        template<class InIt>
        iterator insert(iterator pos, InIt first, InIt last) {
            return insert_aux(pos, first, last, typename std::is_integral<InIt>::type());
        }
        iterator insert(iterator pos, const size_type& n, const_reference val) {
            return insert_aux(pos, n, val, std::true_type());
        }
        iterator insert(iterator pos, const_reference val) {
            return insert(pos, 1, val);
        }
        void push_back(const_reference val) {
            insert(_end, val);
        }

        iterator erase(iterator first, iterator last) {
            size_type _mov = _end - last;
            for (size_type i = 0; i < _mov; ++i)
                *(first + i) = *(last + i);
            uninitialized_fill(first + _mov, _end, 0);
            _end = first + _mov;
            return first;
        }
        iterator erase(iterator pos) {
            return erase(pos, pos + 1);
        }
        void pop_back() {
            erase(_end - 1, _end);
        }

        allocator_type get_allocator() {
            return dataAlloc;
        }
    };
}
#endif // !_SZ_VECTOR_H_
