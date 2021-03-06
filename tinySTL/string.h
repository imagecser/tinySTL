﻿#ifndef _SZ_STRING_H_
#define _SZ_STRING_H_
#include <cstring>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include "allocator.h"

namespace sz {
    class string {
    public:
        typedef char                                value_type;
        typedef char*                               iterator;
        typedef const char*                         const_iterator;
        typedef reverse_iterator_<char*>            reverse_iterator;
        typedef reverse_iterator_<const char*>      const_reverse_iterator;
        typedef size_t                              size_type;
        typedef char&                               reference;
        typedef const char&                         const_reference;
        typedef ptrdiff_t                           difference_type;
        
        static const size_t npos = -1;

    private:
        iterator _begin;
        iterator _end;
        iterator _storage_end;

        allocator<value_type> dataAlloc;

        template<class InIt>
        void allocateCopy(InIt first, InIt last) {
            //_begin = new value_type[last - first];
            size_type pcapacity = last - first;
            _begin = dataAlloc.allocate(pcapacity + 1);
            //strncpy(_begin, (char *)first, last - first);
            uninitialized_copy(first, last, _begin);
            //for (size_t i = 0; i < pcapacity; ++i)
            //    *(_begin + i) = *(first + i);
            _storage_end = _end = _begin + pcapacity;
            *_end = 0;
        }
        void allocateFill(size_type n, value_type ch) {
            _begin = dataAlloc.allocate(n + 1);
            _storage_end = _end = _begin + n;
            uninitialized_fill_n(_begin, n, ch);
            *_end = 0;
            //for (size_t i = 0; i < n; ++i)
            //    _begin[i] = ch;
        }
        /*iterator unintializedFill(iterator ptr, size_t n, value_type ch) {
            for (size_t i = 0; i < n; ++i)
                ptr[i] = ch;
            return ptr + n;
        }
        template<class InIt>
        iterator unintializedCopy(InIt start, InIt end, iterator ptr) {
            for (size_t i = 0; i < (size_t)(end - start); ++i)
                *(ptr + i) = *(start + i);
            return ptr + (end - start);
        }*/

        template<class FwdIt>
        void fillNull(FwdIt first, FwdIt last) {
            for (; first < last; ++first)
                *first = 0;
        }
        size_type getNewCapacity(size_type n) const {
            size_type _old = _storage_end - _begin;
            return _old + (_old > n ? _old : n);
        }
        template<class InIt>
        void string_aux(InIt first, InIt last, std::false_type) {
            allocateCopy(first, last);
        }
        void moveData(string& str) {
            _begin = str._begin;
            _end = str._end;
            _storage_end = str._storage_end;
            str._begin = str._end = str._storage_end = 0;
        }    

        size_t find_aux(const_iterator cite, size_t pos, size_t n) const {
            size_t i, j;
            for (i = pos; i != _end - _begin; ++i) {
                for (j = 0; j < n; ++j)
                    if (*(_begin + i + j) != *(cite + j))
                        break;
                if (j == n)
                    return i;
            }
            return npos;
        }
        size_t rfind_aux(const_iterator cite, size_t pos, size_t n) const {
            pos = changeWhenNpos(pos, _end - _begin, n);
            size_t j;
            for (int i = pos; i >= 0; --i) {
                for (j = 0; j < n; ++j)
                    if (*(_begin + i + j) != *(cite + j))
                        break;
                if (j == n)
                    return i;
            }
            return npos;
        }
        int compare_aux(size_t pos, size_t len, const_iterator cfirst, const_iterator clast) const {
            size_t i;
            for (i = pos; i != pos + len && cfirst != clast; ++i, ++cfirst) {
                if (*(_begin + i) < *cfirst)
                    return -1;
                else if (*(_begin + i) > *cfirst)
                    return 1;
            }
            if (i == pos + len && cfirst == clast)
                return 0;
            else if (i == pos + len)
                return -1;
            else
                return 1;
        }
        bool isContained(char c, const_iterator first, const_iterator last) const {
            for (; first != last; ++first)
                if (*first == c)
                    return true;
            return false;
        }
        size_t changeWhenNpos(size_t pos, size_t maxVal, size_t el) const {
            return pos == npos ? maxVal - el : pos;
        }


    public:

        string() : _begin(NULL), _end(_begin), _storage_end(_end) {
        }
        string(const char *s, size_t n) {
            allocateCopy(s, s + n);
        }
        string(const char *s) {
            allocateCopy(s, s + strlen(s));
        }
        string(string&& str) {
            moveData(str);
        }
        string(const string& str) {
            allocateCopy(str._begin, str._end);
        }
        string(const string& str, size_t pos, size_t len = npos) {
            //len = len == npos ? str._end - str._begin - pos : len;
            len = changeWhenNpos(len, str.size(), pos);
            allocateCopy(str._begin + pos, str._begin + pos + len);
        }
        template<class InIt>
        string(InIt first, InIt last) {
            string_aux(first, last, typename std::is_integral<InIt>::type());
        }
        string(size_t n, char c) {
            allocateFill(n, c);
        }
        string(std::initializer_list<char> ilist) {
            allocateCopy(ilist.begin(), ilist.end());
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
        string& operator= (const char* s) {
            if (_begin != _storage_end)
                dataAlloc.deallocate(_begin);
            allocateCopy(s, s + strlen(s));
            return *this;
        }
        string& operator= (char c) {
            if (_begin != _storage_end)
                dataAlloc.deallocate(_begin);
            allocateFill(1, c);
            return *this;
        }
        const char* c_str() {
            return _begin;
        }
        void clear() {
            //dataAlloc.destroy(_begin, _end);
            fillNull(_begin, _end);
            _end = _begin;
        }
        bool empty() {
            return _begin == _end;
        }
        void resize(size_t n, const char c = '\000') {
            if (n < size()) {
                //dataAlloc.destroy(_begin + n, _storage_end);
                fillNull(_begin + n, _storage_end);
                _end = _begin + n;
            }
            else if (n > size() && n <= capacity()) {
                //_end = unintializedFill(_end, n - size(), ch);
                _end = uninitialized_fill_n(_end, n - size(), c);
                *_end = 0;
            }
            else if (n > capacity()) {
                size_type pcapacity = getNewCapacity(n - size());
                iterator pbegin = dataAlloc.allocate(pcapacity + 1);
                _storage_end = pbegin + pcapacity;
                //iterator pend = unintializedCopy(_begin, _end, pbegin);
                //pend = unintializedFill(pend, n - size(), ch);
                iterator pend = uninitialized_copy(_begin, _end, pbegin);
                pend = uninitialized_fill_n(pend, n - size(), c);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _end = pend;
                *_end = 0;
            }
        }
        void reserve(size_t n) {
            if (n <= capacity())
                return;
            iterator pbegin = dataAlloc.allocate(n + 1);
            //iterator pend = unintializedCopy(_begin, _end, pbegin);
            iterator pend = uninitialized_copy(_begin, _end, pbegin);
            dataAlloc.deallocate(_begin);
            _begin = pbegin;
            _end = pend;
            *_end = 0;
            _storage_end = _begin + n;
        }
        void shrink_to_fit() {
            //dataAlloc.destroy(_end + 1, _storage_end);
            //_storage_end = _end;
            if (_storage_end != _end) {
                iterator pbegin = dataAlloc.allocate(size() + 1);
                _storage_end = _end = uninitialized_copy(_begin, _end, pbegin);
                *_end = 0;
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
            }
        }
        void swap(string& str) {
            sz::swap(_begin, str._begin);
            sz::swap(_end, str._end);
            sz::swap(_storage_end, str._storage_end);
        }
        size_t copy(char *s, size_t len, size_t pos = 0) const {
            //unintializedCopy(_begin + pos, _begin + pos + len, str);
            uninitialized_copy(_begin + pos, _begin + pos + len, s);
            return len;
        }
        string substr(size_t pos = 0, size_t len = npos) const {
            len = changeWhenNpos(len, _end - _begin, pos);
            return string(_begin + pos, _begin + pos + len);
        }

        iterator begin() {
            return _begin;
        }
        iterator end() {
            return _end;
        }
        const_iterator begin() const {
            return _begin;
        }
        const_iterator end() const {
            return _end;
        }
        const_iterator cbegin() const {
            return _begin;
        }
        const_iterator cend() const {
            return _end;
        }
        reverse_iterator rbegin() {
            return reverse_iterator(_end);
        }
        reverse_iterator rend() {
            return reverse_iterator(_begin);
        }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_end);
        }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(_begin);
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(_end);
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(_begin);
        }
        size_t size() const {
            return _end - _begin;
        }
        size_t length() const {
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
        const char& front() const {
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
            sublen = changeWhenNpos(sublen, str.size(), subpos);
            insert(_begin + pos, str.begin() + subpos, str.begin() + subpos + sublen);
            //insert(_begin + pos, str.begin() + subpos, sublen == npos ? str.end() : str.begin() + subpos + sublen);
            return *this;
        }
        string& insert(size_t pos, const char* s) {
            insert(_begin + pos, s, s + strlen(s));
            return *this;
        }
        string& insert(size_t pos, const char* s, size_t n) {
            insert(_begin + pos, s, s + n);
            return *this;
        }
        string& insert(size_t pos, size_t n, char c) {
            insert(_begin + pos, n, c);
            return *this;
        }
        iterator insert(iterator ptr, size_t n, char c) {
            if (n < (size_type)(_storage_end - _end)) {
                for (iterator ite = _end - 1; ite >= ptr; --ite)
                    *(ite + n) = *ite;
                _end += n;
                *_end = 0;
                //return unintializedFill(ptr, n, ch);
                return uninitialized_fill_n(ptr, n, c);
            }
            else {
                size_type pcapacity = getNewCapacity(n);
                iterator pbegin = dataAlloc.allocate(pcapacity + 1);
                //iterator pend = unintializedCopy(_begin, ptr, pbegin);
                //iterator res = pend = unintializedFill(pend, n, ch);
                //pend = unintializedCopy(ptr, _end, pend);
                iterator pend = uninitialized_copy(_begin, ptr, pbegin);
                iterator res = pend = uninitialized_fill_n(pend, n, c);
                pend = uninitialized_copy(ptr, _end, pend);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _end = pend;
                *_end = 0;
                _storage_end = _begin + pcapacity;
                return res;
            }
        }
        iterator insert(iterator ptr, char c) {
            return insert(ptr, 1, c);
        }
        template<class InIt>
        iterator insert(iterator ptr, InIt first, InIt last) {
            size_type offset = last - first;
            if (offset < (size_type)(_storage_end - _end)) {
                string pstr(first, last);
                for (iterator ite = _end - 1; ite >= ptr; --ite)
                    *(ite + offset) = *ite;
                _end += offset;
                *_end = 0;
                //return unintializedCopy(pstr.begin(), pstr.end(), ptr);
                return uninitialized_copy(pstr.begin(), pstr.end(), ptr);
            }
            else {
                size_type pcapacity = getNewCapacity(offset);
                iterator pbegin = dataAlloc.allocate(pcapacity + 1);
                //iterator pend = unintializedCopy(_begin, ptr, pbegin);
                //iterator res = pend = unintializedCopy(first, last, pend);
                //pend = unintializedCopy(ptr, _end, pend);
                iterator pend = uninitialized_copy(_begin, ptr, pbegin);
                iterator res = pend = uninitialized_copy(first, last, pend);
                pend = uninitialized_copy(ptr, _end, pend);
                dataAlloc.deallocate(_begin);
                _begin = pbegin;
                _end = pend;
                *_end = 0;
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
        string& append(const char* s) {
            return insert(size(), s);
        }
        string& append(const char* s, size_t n) {
            return insert(size(), s, n);
        }
        string& append(size_t n, char c) {
            return insert(size(), n, c);
        }
        template <class InIt>
        string& append(InIt first, InIt last) {
            insert(_end, first, last);
            return *this;
        }

        string& operator+= (const string& str) {
            return append(str);
        }
        string& operator+= (const char* s) {
            return append(s);
        }
        string& operator+= (char c) {
            return append(1, c);
        }

        void pop_back() {
            erase(_end - 1);
        }
        string& erase(size_t pos = 0, size_t len = npos) {
            len = changeWhenNpos(len, _end - _begin, pos);
            erase(_begin + pos, _begin + pos + len);
            //erase(_begin + pos, len == npos ? _end : _begin + pos + len);
            return *this;
        }
        iterator erase(iterator p) {
            return erase(p, p + 1);
        }
        iterator erase(iterator first, iterator last) {
            size_type lenMove = _end - last;
            for (size_t i = 0; i < lenMove; ++i)
                *(first + i) = *(last + i);
            //dataAlloc.destroy(first + lenMove, _end);
            fillNull(first + lenMove, _end);
            _end = first + lenMove;
            *_end = 0;
            return first;
        }

        string& replace(size_t pos, size_t len, const string& str) {
            return replace(_begin + pos, _begin + pos + len, str.begin(), str.end());
        }
        string& replace(iterator first, iterator last, const string& str) {
            return replace(first, last, str.begin(), str.end());
        }
        string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos) {
            sublen = changeWhenNpos(sublen, str.size(), subpos);
            return replace(_begin + pos, _begin + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
            //return replace(_begin + pos, _begin + pos + len, str.begin() + subpos, sublen == npos ? str.end() : (str.begin() + subpos + sublen));
        }
        string& replace(size_t pos, size_t len, const char* s) {
            return replace(_begin + pos, _begin + pos + len, s, s + strlen(s));
        }
        string& replace(iterator first, iterator last, const char* s) {
            return replace(first, last, s, s + strlen(s));
        }
        string& replace(size_t pos, size_t len, const char* s, size_t n) {
            return replace(_begin + pos, _begin + pos + len, s, s + n);
        }
        string& replace(iterator first, iterator last, const char* s, size_t n) {
            return replace(first, last, s, s + n);
        }
        string& replace(size_t pos, size_t len, size_t n, char c) {
            return replace(_begin + pos, _begin + pos + len, n, c);
        }
        string& replace(iterator first, iterator last, size_t n, char c) {
            erase(first, last);
            insert(first, n, c);
            return *this;
        }
        template <class InIt>
        string& replace(iterator first, iterator last, InIt inputfirst, InIt inputlast) {
            erase(first, last);
            insert(first, inputfirst, inputlast);
            return *this;
        }

        size_t find(const string& str, size_t pos = 0) const {
            return find_aux(str.cbegin(), pos, str.size());
        }
        size_t find(const char* s, size_t pos = 0) const {
            return find_aux(s, pos, strlen(s));
        }
        size_t find(const char* s, size_t pos, size_t n) const {
            return find_aux(s, pos, n);
        }
        size_t find(char c, size_t pos = 0) const {
            for (size_t i = pos; i < size(); ++i)
                if (*(_begin + i) == c)
                    return i;
            return npos;
        }

        size_t rfind(const string& str, size_t pos = npos) const {
            return rfind_aux(str.cbegin(), pos, str.size());
        }
        size_t rfind(const char* s, size_t pos = npos) const {
            return rfind_aux(s, pos, strlen(s));
        }
        size_t rfind(const char* s, size_t pos, size_t n) const {
            return rfind_aux(s, pos, n);
        }
        size_t rfind(char c, size_t pos = npos) const {
            pos = changeWhenNpos(pos, _end - _begin, 1);
            for (size_t i = pos; i >= 0; --i)
                if (*(_begin + i) == c)
                    return i;
            return npos;
        }

        size_t find_first_of(const string& str, size_t pos = 0) const {
            return find_first_of(str.cbegin(), pos, str.size());
        }
        size_t find_first_of(const char* s, size_t pos = 0) const {
            return find_first_of(s, pos, strlen(s));
        }
        size_t find_first_of(const char* s, size_t pos, size_t n) const {
            for (size_t i = pos; i != _end - _begin; ++i)
                if (isContained(*(_begin + i), s, s + n))
                    return i;
            return npos;
        }
        size_t find_first_of(char c, size_t pos = 0) const {
            return find(c, pos);
        }

        size_t find_last_of(const string& str, size_t pos = npos) const {
            return find_last_of(str.cbegin(), pos, str.size());
        }
        size_t find_last_of(const char* s, size_t pos = npos) const {
            return find_last_of(s, pos, strlen(s));
        }
        size_t find_last_of(const char* s, size_t pos, size_t n) const {
            pos = changeWhenNpos(pos, _end - _begin, 1);
            for (size_t i = pos; i != -1; --i)
                if (isContained(*(_begin + i), s, s + n))
                    return i;
            return npos;
        }
        size_t find_last_of(char c, size_t pos = npos) const {
            pos = changeWhenNpos(pos, _end - _begin, 1);
            for (size_t i = pos; i != -1; --i)
                if (*(_begin + i) == c)
                    return i;
            return npos;
        }
        size_t find_first_not_of(const string& str, size_t pos = 0) const {
            return find_first_not_of(str.begin(), pos, str.size());
        }
        size_t find_first_not_of(const char* s, size_t pos = 0) const {
            return find_first_not_of(s, pos, strlen(s));
        }
        size_t find_first_not_of(const char* s, size_t pos, size_t n) const {
            for (size_t i = pos; i != _end - _begin; ++i)
                if (!isContained(*(_begin + i), s, s + n))
                    return i;
            return npos;
        }
        size_t find_first_not_of(char c, size_t pos = 0) const {
            for (size_t i = pos; i != _end - _begin; ++i)
                if (*(_begin + i) != c)
                    return i;
            return npos;
        }
        size_t find_last_not_of(const string& str, size_t pos = npos) const {
            return find_last_not_of(str.begin(), pos, str.size());
        }
        size_t find_last_not_of(const char* s, size_t pos = npos) const {
            return find_last_not_of(s, pos, strlen(s));
        }
        size_t find_last_not_of(const char* s, size_t pos, size_t n) const {
            pos = changeWhenNpos(pos, _end - _begin, 1);
            for (size_t i = pos; i != -1; --i)
                if (!isContained(*(_begin + i), s, s + n))
                    return i;
            return npos;
        }
        size_t find_last_not_of(char c, size_t pos = npos) const {
            pos = changeWhenNpos(pos, _end - _begin, 1);
            for (size_t i = pos; i != -1; --i)
                if (*(_begin + i) != c)
                    return i;
            return npos;
        }

        int compare(const string& str) const {
            return compare_aux(0, size(), str.cbegin(), str.cend());
        }
        int compare(size_t pos, size_t len, const string& str) const {
            return compare_aux(pos, len, str.cbegin(), str.cend());
        }
        int compare(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos) const {
            sublen = changeWhenNpos(sublen, str.size(), subpos);
            return compare_aux(pos, len, str.cbegin() + subpos, str.cbegin() + subpos + sublen);
        }
        int compare(const char* s) const {
            return compare_aux(0, size(), s, s + strlen(s));
        }
        int compare(size_t pos, size_t len, const char* s) const {
            return compare_aux(pos, len, s, s + strlen(s));
        }
        int compare(size_t pos, size_t len, const char* s, size_t n) const {
            return compare_aux(pos, len, s, s + n);
        }

        friend std::ostream& operator<< (std::ostream& os, const string& str) {
            for (size_t i = 0; i != str.size(); ++i)
                os << str[i];
            return os;
        }
        friend std::istream& operator>> (std::istream& is, string& str) {
            str.clear();
            char ch;
            for (; is.get(ch);)
                if (!(isblank(ch) || ch == '\n'))
                    break;
            is.putback(ch);
            for (; is.get(ch);)
                if (ch != -1 && !isblank(ch) && ch != '\n')
                    str.push_back(ch);
                else
                    break;
            return is;
        }
        friend std::istream& getline(std::istream& is, string& str, char delim = '\n') {
            char ch;
            str.clear();
            for (; is.get(ch);)
                if (ch == delim)
                    break;
                else
                    str.push_back(ch);
            return is;
        }

        friend string operator+ (const string& lhs, const string& rhs) {
            string res(lhs);
            return res += rhs;
        }
        friend string operator+ (const string& lhs, const char* rhs) {
            string res(lhs);
            return res += rhs;
        }
        friend string operator+ (const char* lhs, const string& rhs) {
            string res(lhs);
            return res += rhs;
        }
        friend string operator+ (const string& lhs, char rhs) {
            string res(lhs);
            return res += rhs;
        }
        friend string operator+ (char lhs, const string& rhs) {
            string res(1, lhs);
            return res += rhs;
        }

        friend bool operator== (const string& lhs, const string& rhs) {
            return lhs.compare(rhs) == 0;
        }
        friend bool operator== (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs) == 0;
        }
        friend bool operator== (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs) == 0;
        }
        friend bool operator!= (const string& lhs, const string& rhs) {
            return lhs.compare(rhs);
        }
        friend bool operator!= (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs);
        }
        friend bool operator!= (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs);
        }
        friend bool operator<  (const string& lhs, const string& rhs) {
            return lhs.compare(rhs) == -1;
        }
        friend bool operator<  (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs) == 1;
        }
        friend bool operator<  (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs) == -1;
        }
        friend bool operator<= (const string& lhs, const string& rhs) {
            return lhs.compare(rhs) != 1;
        }
        friend bool operator<= (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs) != -1;
        }
        friend bool operator<= (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs) != 1;
        }
        friend bool operator>  (const string& lhs, const string& rhs) {
            return lhs.compare(rhs) == 1;
        }
        friend bool operator>  (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs) == -1;
        }
        friend bool operator>  (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs) == 1;
        }
        friend bool operator>= (const string& lhs, const string& rhs) {
            return lhs.compare(rhs) != -1;
        }
        friend bool operator>= (const char*   lhs, const string& rhs) {
            return rhs.compare(lhs) != 1;
        }
        friend bool operator>= (const string& lhs, const char*   rhs) {
            return lhs.compare(rhs) != -1;
        }
        friend void swap(string& lhs, string& rhs) {
            lhs.swap(rhs);
        }
    }; 
}
#endif !_SZ_STRING_H_
