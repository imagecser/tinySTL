#ifndef _STRING_H_
#define _STRING_H_
#include <cstring>
#include <iostream>
#include <type_traits>
#include "allocator.h"

namespace sz {
    class string {
	public:
		static const size_t npos = -1;
		typedef char value_type;
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef size_t size_type;

	private:
		char * _begin;
		char * _end; 
		char * _storage_end;

		sz::allocator<value_type> dataAlloc;
		/*
		void allocateCopy(Iterator first, Iterator last);
		void allocateFill(size_t n, value_type ch);
		iterator unintializedFill(iterator ptr, size_t n, value_type ch);
		template<class InputIterator>
		iterator unintializedCopy(iterator start, iterator end, iterator ptr);
		size_type getNewCapacity(size_type n) const;
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type);
		void moveData(string& str);
		template<class T>
		void swap(T src, T dest);
		*/
		template<class InputIterator>
		void allocateCopy(InputIterator first, InputIterator last) {
			//_begin = new value_type[last - first];
			size_type pcapacity = last - first;
			_begin = dataAlloc.allocate(pcapacity);
			//strncpy(_begin, (char *)first, last - first);
			for (size_t i = 0; i < pcapacity; ++i)
				*(_begin + i) = *(first + i);
			_storage_end = _end = _begin + pcapacity;
		}
		void allocateFill(size_type n, value_type ch) {
			_begin = dataAlloc.allocate(n);
			_storage_end = _end = _begin + n;
			for (size_t i = 0; i < n; ++i)
				_begin[i] = ch;
		}
		iterator unintializedFill(iterator ptr, size_t n, value_type ch) {
			for (size_t i = 0; i < n; ++i)
				ptr[i] = ch;
			return ptr + n;
		}
		template<class InputIterator>
		iterator unintializedCopy(InputIterator start, InputIterator end, iterator ptr) {
			for (size_t i = 0; i < (size_t)(end - start); ++i)
				*(ptr + i) = *(start + i);
			return ptr + (end - start);
		}
		size_type getNewCapacity(size_type n) const{
			size_type _old = _storage_end - _begin;
			return _old + (_old > n ? _old : n);
		}
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type) {
			allocateCopy(first, last);
		}
		void moveData(string& str) {
			_begin = str._begin;
			_end = str._end;
			_storage_end = str._storage_end;
			str._begin = str._end = str._storage_end = 0;
		}

		template<class T>
		void swap(T src, T dest) {
			T temp = src;
			src = dest;
			dest = temp;
		}

	public:
		/*
			friend std::ostream & operator << (std::ostream & out, const string & str);
			string();
			string(string&& str);
			string(const char *str, size_t n)
			String(const char *str);
			string(string&& str);
			string(const string& str);
			string(const string& str, size_t pos, size_t len = npos);
			template<class InputIterator>
			string(InputIterator first, InputIterator last);
			string(size_t n, char ch);
			~string();

			string& operator= (const string& str);
			string& operator= (string&& str);
			string& operator= (const char* str);
			string& operator= (char ch);

			void clear();
			bool empty();
			void resize(size_t n, const char ch = '\000');
			void reserve(size_t n);
			void shrink_to_fit();

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			size_t size() const;
			size_t capacity() const;
			char& operator[](size_t pos);
			const char& operator[](size_t pos);
			char& back();
			const char& back() const;
			char& front();
			const char& front() const;
			
			void push_back(char ch);
			string& insert(size_t pos, const string& str);
			string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);
			string& insert(size_t pos, const char* str);
			string& insert(size_t pos, const char* str, size_t n);
			string& insert(size_t pos, size_t n, char ch);
			iterator insert(const_iterator ptr, size_t n, char ch);
			iterator insert(const_iterator ptr, char ch);
			template <class InputIterator>
			iterator insert(iterator ptr, InputIterator first, InputIterator last);

			string& append(const string& str);
			string& append(const string& str, size_t subpos, size_t sublen = npos);
			string& append(const char* s);
			string& append(const char* s, size_t n);
			string& append(size_t n, char c);
			template <class InputIterator>
			string& append(InputIterator first, InputIterator last);

			string& operator+= (const string& str);
			string& operator+= (const char* str);
			string& operator+= (char ch);

			void pop_back();
			string& erase(size_t pos = 0, size_t len = npos);
			iterator erase(iterator p);
			iterator erase(iterator first, iterator last);

			string& replace(size_t pos, size_t len, const string& str);
			string& replace(iterator first, iterator last, const string& str);
			string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);
			string& replace(size_t pos, size_t len, const char* str);
			string& replace(iterator first, iterator last, const char* str);
			string& replace(size_t pos, size_t len, const char* str, size_t n);
			string& replace(iterator first, iterator last, const char* str, size_t n);
			string& replace(size_t pos, size_t len, size_t n, char ch);
			string& replace(iterator first, iterator last, size_t n, char ch);
			template <class InputIterator>
			string& replace(iterator first, iterator last, InputIterator inputfirst, InputIterator inputlast);
		*/
		friend std::ostream & operator << (std::ostream & out, const string & str) {
			for (auto item : str)
				out << item;
			return out;
		}
		string() : _begin(NULL), _end(_begin), _storage_end(_end) {
		}
		string(const char *str, size_t n){
			allocateCopy(str, str + n);
		}
		string(const char *str) {
			allocateCopy(str, str + strlen(str));
		}
		string(string&& str) {
			moveData(str);
		}
		string(const string& str) {
			allocateCopy(str._begin, str._end);
		}
		string(const string& str, size_t pos, size_t len = npos) {
			len = len == npos ? str._end - str._begin - pos : len;
			allocateCopy(str._begin + pos, str._begin + pos + len);
		}
		template<class InputIterator>
		string(InputIterator first, InputIterator last) {
			string_aux(first, last, typename std::is_integral<InputIterator>::type());
		}
		string(size_t n, char ch) {
			allocateFill(n, ch);
		}
		~string() {
			if (_begin != _storage_end)
				dataAlloc.deallocate(_begin);
		}
		string& operator= (const string& str) {
			if (this != &str) {
				dataAlloc.deallocate(_begin);
				allocateCopy(str.begin(), str.end());
			}
			return *this;
		}
		string& operator= (string&& str) {
			if (this != &str) {
				dataAlloc.deallocate(_begin);
				moveData(str);
			}
			return *this;
		}
		string& operator= (const char* str) {
			if(_begin != _storage_end)
				dataAlloc.deallocate(_begin);
			allocateCopy(str, str + strlen(str));
			return *this;
		}
		string& operator= (char ch) {
			if(_begin != _storage_end)
				dataAlloc.deallocate(_begin);
			allocateFill(1, ch);
			return *this;
		}

		void clear() {
			dataAlloc.destroy(_begin, _end);
			_end = _begin;
		}
		bool empty() {
			return _begin == _end;
		}
		void resize(size_t n, const char ch = '\000') {
			if (n < size()) {
				dataAlloc.destroy(_begin + n, _storage_end);
				_end = _storage_end = _begin + n;
			}
			else if (n > size() && n <= capacity()) {
				_end = unintializedFill(_end, n - size(), ch);
			}
			else if (n > capacity()) {
				iterator pbegin = dataAlloc.allocate(getNewCapacity(n - size()));
				iterator pend = unintializedCopy(_begin, _end, pbegin);
				pend = unintializedFill(pend, n - size(), ch);
				dataAlloc.deallocate(_begin);
				_begin = pbegin;
				_storage_end = _end = pend;
			}
		}
		void reserve(size_t n) {
			if (n <= capacity())
				return;
			iterator pbegin = dataAlloc.allocate(n);
			iterator pend = unintializedCopy(_begin, _end, pbegin);
			dataAlloc.deallocate(_begin);
			_begin = pbegin;
			_end = pend;
			_storage_end = _begin + n;
		}
		void shrink_to_fit() {
			dataAlloc.destroy(_end, _storage_end);
			_storage_end = _end;
		}
		void swap(string& str) {
			swap(_begin, str._begin);
			swap(_end, str._end);
			swap(_storage_end, str._storage_end);
		}
		size_t copy(char *str, size_t len, size_t pos = 0) {
			unintializedCopy(_begin + pos, _begin + pos + len, str);
		}

		iterator begin() {
			return _begin;
		}
		iterator end() {
			return _end;
		}
		const_iterator begin() const{
			return _begin;
		}
		const_iterator end() const {
			return _end;
		}
		size_t size() const {
			return _end - _begin;
		}
		size_t capacity() const {
			return _storage_end - _begin;
		}

		char& operator[](size_t pos) {
			return *(_begin + pos);
		}
		const char& operator[](size_t pos) const {
			return *(_begin + pos);
		}
		char& back() {
			return *(_end - 1);
		}
		const char& back() const {
			return *(_end - 1);
		}
		char& front() {
			return *_begin;
		}
		const char& front() const{
			return *_begin;
		}

		void push_back(char ch) {
			insert(_end, ch);
		}
		string& insert(size_t pos, const string& str) {
			insert(_begin + pos, str.begin(), str.end());
			return *this;
		}
		string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos) {
			insert(_begin + pos, str.begin() + subpos, sublen == npos ? str.end() : str.begin() + subpos + sublen);
			return *this;
		}
		string& insert(size_t pos, const char* str) {
			insert(_begin + pos, str, str + strlen(str));
			return *this;
		}
		string& insert(size_t pos, const char* s, size_t n) {
			insert(_begin + pos, s, s + n);
			return *this;
		}
		string& insert(size_t pos, size_t n, char ch) {
			insert(_begin + pos, n, ch);
			return *this;
		}
		iterator insert(iterator ptr, size_t n, char ch) {
			if (n < (size_type)(_storage_end - _end)) {
				for (iterator ite = _end - 1; ite >= ptr; --ite)
					*(ite + n) = *ite;
				_end += n;
				return unintializedFill(ptr, n, ch);
			}
			else {
				size_type pcapacity = getNewCapacity(n);
				iterator pbegin = dataAlloc.allocate(pcapacity);
				iterator pend = unintializedCopy(_begin, ptr, pbegin);
				iterator res = pend = unintializedFill(pend, n, ch);
				pend = unintializedCopy(ptr, _end, pend);
				dataAlloc.deallocate(_begin);
				_begin = pbegin;
				_end = pend;
				_storage_end = _begin + pcapacity;
				return res;
			}
		}
		iterator insert(iterator ptr, char ch) {
			return insert(ptr, 1, ch);
		}
		template<class InputIterator>
		iterator insert(iterator ptr, InputIterator first, InputIterator last) {
			size_type offset = last - first;
			if (offset < (size_type)(_storage_end - _end)) {
				string pstr(first, last);
				for (iterator ite = _end - 1; ite >= ptr; --ite)
					*(ite + offset) = *ite;
				_end += offset;
				return unintializedCopy(pstr.begin(), pstr.end(), ptr);
			}
			else {
				size_type pcapacity = getNewCapacity(offset);
				iterator pbegin = dataAlloc.allocate(pcapacity);
				iterator pend = unintializedCopy(_begin, ptr, pbegin);
				iterator res = pend = unintializedCopy(first, last, pend);
				pend = unintializedCopy(ptr, _end, pend);
				dataAlloc.deallocate(_begin);
				_begin = pbegin;
				_end = pend;
				_storage_end = pbegin + pcapacity;
				return res;
			}
		}

		string& append(const string& str) {
			return insert(size(), str);
		}
		string& append(const string& str, size_t subpos, size_t sublen = npos) {
			return insert(size(), str, subpos, sublen);
		}
		string& append(const char* str) {
			return insert(size(), str);
		}
		string& append(const char* str, size_t n) {
			return insert(size(), str, n);
		}
		string& append(size_t n, char ch) {
			return insert(size(), n, ch);
		}
		template <class InputIterator>
		string& append(InputIterator first, InputIterator last) {
			insert(_end, first, last);
			return *this;
		}

		string& operator+= (const string& str) {
			return append(str);
		}
		string& operator+= (const char* str) {
			return append(str);
		}
		string& operator+= (char ch) {
			return append(1, ch);
		}

		void pop_back() {
			erase(_end - 1);
		}
		string& erase(size_t pos = 0, size_t len = npos) {
			erase(_begin + pos, len == npos ? _end : _begin + pos + len);
			return *this;
		}
		iterator erase(iterator p) {
			return erase(p, p + 1);
		}
		iterator erase(iterator first, iterator last) {
			size_type lenMove = _end - last;
			for (size_t i = 0; i < lenMove; ++i)
				*(first + i) = *(last + i);
			dataAlloc.destroy(first + lenMove, _end);
			_end = first + lenMove;
			return first;
		}

		string& replace(size_t pos, size_t len, const string& str) {
			return replace(_begin + pos, _begin + pos + len, str.begin(), str.end());
		}
		string& replace(iterator first, iterator last, const string& str) {
			return replace(first, last, str.begin(), str.end());
		}
		string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos) {
			return replace(_begin + pos, _begin + pos + len, str.begin() + subpos, sublen == npos ? str.end() : (str.begin() + subpos + sublen));
		}
		string& replace(size_t pos, size_t len, const char* str) {
			return replace(_begin + pos, _begin + pos + len, str, str + strlen(str));
		}
		string& replace(iterator first, iterator last, const char* str) {
			return replace(first, last, str, str + strlen(str));
		}
		string& replace(size_t pos, size_t len, const char* str, size_t n) {
			return replace(_begin + pos, _begin + pos + len, str, str + n);
		}
		string& replace(iterator first, iterator last, const char* str, size_t n) {
			return replace(first, last, str, str + n);
		}
		string& replace(size_t pos, size_t len, size_t n, char ch) {
			return replace(_begin + pos, _begin + pos + len, n, ch);
		}
		string& replace(iterator first, iterator last, size_t n, char ch) {
			erase(first, last);
			insert(first, n, ch);
			return *this;
		}
		template <class InputIterator>
		string& replace(iterator first, iterator last, InputIterator inputfirst, InputIterator inputlast) {
			erase(first, last);
			insert(first, inputfirst, inputlast);
			return *this;
		}
    }; 
}
#endif
