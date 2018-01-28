#ifndef _STRING_H_
#define _STRING_H_
#include <cstring>
#include <iostream>
namespace sz {
    class string {
        private:
			char * _begin;
			char * _end; 
			char * _storage_end;
			/*
			void checkCapacity(unsigned & count);
			*/
			void checkCapacity(unsigned & count) {
				if (_end + count > _storage_end) {
					_storage_end = 2 * capacity() > (capacity() + count) ? (2 * capacity() + _begin) : (_storage_end + count);
					char * temp = new char[capacity()];
					strcpy(temp, _begin);
					delete[] _begin;
					_begin = temp;
				}
			}

        public:
			typedef char* iterator;
			typedef const char* const_iterator;
			/*
				friend std::ostream & operator << (std::ostream & out, const String & str);
				String();
				String(const char *str);
			*/
			friend std::ostream & operator << (std::ostream & out, const string & str) {
				out << str.begin();
				return out;
			}
			string() : _begin(new char[1]), _end(_begin), _storage_end(_end) {
				_begin[0] = '\0';
			}
			string(const char *str) : _begin(new char[strlen(str) + 1]), _end(_begin + strlen(str)), _storage_end(_end) {
				strcpy(_begin, str);
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
    }; 
}
#endif
