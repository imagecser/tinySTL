#ifndef _STRING_H_
#define _STRING_H_
#include <cstring>
#include <iostream>
#include <type_traits>
#include "allocator.h"
namespace sz {
    class string {
        private:
			char * _begin;
			char * _end; 
			char * _storage_end;

			typedef sz::allocator<char> dataAlloc;
			/*
			void allocateCopy(Iterator first, Iterator last);
			void checkCapacity(unsigned & count);
			*/
			template<class InputIterator>
			void allocateCopy(InputIterator first, InputIterator last) {
				_begin = new value_type[last - first];
				strncpy(_begin, first, last - first);
				_begin[last - first] = 0;
				_storage_end = _end = _begin + (last - first);
			}
			void checkCapacity(unsigned & count) {
				if (_end + count > _storage_end) {
					_storage_end = 2 * capacity() > (capacity() + count) ? (2 * capacity() + _begin) : (_storage_end + count);
					iterator temp = new value_type[capacity()];
					strcpy(temp, _begin);
					delete[] _begin;
					_begin = temp;
				}
			}
			template<class InputIterator>
			void string_aux(InputIterator first, InputIterator last, std::false_type) {
				allocateCopy(first, last);
			}

        public:
			static const size_t npos = -1;
			typedef char value_type;
			typedef char* iterator;
			typedef const char* const_iterator;
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
				_begin = str._begin;
				_end = str._end;
				_storage_end = str._storage_end;
				str._begin = str._end = str._storage_end = NULL;
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
				_begin = new char[n];
				_storage_end = _end = _begin + n;
				for (size_t i = 0; i < n; ++i)
					_begin[i] = ch;
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
