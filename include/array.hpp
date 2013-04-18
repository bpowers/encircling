// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#pragma once
#ifndef _ENCIRCLING_ARRAY_HPP_
#define _ENCIRCLING_ARRAY_HPP_

#include "_common.hpp"

#include <memory>
#include <cstring>

namespace encircling {

// Without passing an instance of this to std::shared_ptr, Valgrind
// reports a mismatched free error.
template <typename T>
class _ArrayFree
{
public:
    void operator() (T* d) const
    {
        delete[] d;
    }
};

template <typename T>
class Array {
public:
	typedef T value_type;

	explicit Array(const size_t n) : _n(n), _data(new T[n], _ArrayFree<T>())
	{
		memset(_data.get(), 0, n*sizeof(T));
	}
	virtual ~Array() {}

	T& operator[](size_t i)
	{
		if (unlikely(i >= _n))
			throw RuntimePanic("Array::operator[] out-of-bounds");
		return _data.get()[i];
	}
	T const& operator[](size_t i) const
	{
		if (unlikely(i >= _n))
			throw RuntimePanic("Array::operator[] out-of-bounds");
		return _data.get()+i;
	}
	size_t len() { return _n; }
private:
	size_t const _n;
	std::shared_ptr<T> const _data;
};

} // namespace encircling

#endif // _ENCIRCLING_ARRAY_HPP_
