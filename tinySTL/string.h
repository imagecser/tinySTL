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

	private:
		char * _begin;
		char * _end; 
		char * _storage_end;

		sz::allocator<value_type> dataAlloc;
		/*
		void allocateCopy(Iterator first, Iterator last);
		void allocateFill(size_t n, value_type ch);
		void checkCapacity(unsigned & count);
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type);
		void moveData(string& str);
		*/
		template<class InputIterator>
		void allocateCopy(InputIterator first, InputIterator last) {
			//_begin = new value_type[last - first];
			_begin = dataAlloc.allocate(last - first);
			strncpy(_begin, first, last - first);
			_storage_end = _end = _begin + (last - first);
		}
		void allocateFill(size_t n, value_type ch) {
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
		iterator unintializedCopy(iterator ptr, iterator start, iterator end) {
			for (size_t i = 0; i < (size_t)(end - start); ++i)
				ptr[i] = *(start + i);
			return ptr + (end - start);
		}
		void checkCapacity(size_t & count) {
			if (_end + count > _storage_end) {
				_storage_end = 2 * capacity() > (capacity() + count) ? (2 * capacity() + _begin) : (_storage_end + count);
				//iterator temp = new value_type[capacity()];
				iterator temp = dataAlloc.allocate(capacity());
				strcpy(temp, _begin);
				dataAlloc.deallocate(_begin);
				_begin = temp;
			}
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

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			size_t size() const;
			size_t capacity() const;
			value_type operator[](size_t n);
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
			dataAlloc.deallocate(_begin);
			_end = _storage_end = _begin;
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
				iterator pstart = dataAlloc.allocate(n);
				iterator pend = unintializedCopy(pstart, _begin, _end);
				pend = unintializedFill(pend, n - size(), ch);
				dataAlloc.deallocate(_begin);
				_begin = pstart;
				_storage_end = _end = pend;
			}
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
		value_type operator[](size_t n) {
			return _begin[n];
		}
    }; 
}
#endif
