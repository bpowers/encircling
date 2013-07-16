// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#pragma once
#ifndef _ENCIRCLING__COMMON_HPP_
#define _ENCIRCLING__COMMON_HPP_

#include <iterator>
#include <exception>
#include <cstddef>
#include <stdint.h>

typedef uint8_t byte;

// the '!!' is from Love's LSP book.  it ensures that integer and
// pointer values are converted to boolean values (not (not x)), so
// that the comparisions to 0 and 1 behave as expected.
#define likely(x)   __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)

namespace encircling {

#define __enc_max(a, b) (((a) < (b)) ? (b) : (a))

template<typename Container, typename T>
class Iter : public std::iterator<std::forward_iterator_tag, T>
{
public:
	Iter(const Container& a, const size_t i) : _i(i), _cont(a) {}
	Iter& operator++() {_i++; return *this;}
	bool operator==(const Iter& rhs) const {
		return _cont._data.get() == rhs._cont._data.get() && _i == rhs._i;
	}
	bool operator!=(const Iter& rhs) const {
		return _cont._data.get() != rhs._cont._data.get() || _i != rhs._i;
	}
	T& operator*() { return _cont._data.get()[_i]; }
private:
	size_t _i;
	const Container& _cont;
};

class RuntimePanic : public std::exception {
public:
	explicit RuntimePanic(char const* msg) : _msg(msg) {}

	virtual char const* what() const throw()
	{
		return _msg;
	}
private:
	char const* _msg;
};

/// passes T by value, but allows us to indicate if there was an error
/// and T is invalid.
template<typename T>
class Result
{
public:
	explicit Result(T r) : _result(r), _err(NULL) {}
	Result(T r, char const* const err) : _result(r), _err(err) {}

	T operator*() { return _result; }

	bool error() const { return _err != NULL; }
	char const* error_msg() const { return _err; }
private:
	T _result;
	char const* _err;
};

// Without passing an instance of this to std::shared_ptr, Valgrind
// reports a mismatched free error.
template<typename T>
class _ArrayFree
{
public:
    void operator() (T* d) const
    {
        delete[] d;
    }
};

}

#endif // _ENCIRCLING__COMMON_HPP_
