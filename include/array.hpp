// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#pragma once
#ifndef _ENCIRCLING_ARRAY_HPP_
#define _ENCIRCLING_ARRAY_HPP_

#include "_common.hpp"

#include <iterator>
#include <memory>
#include <cstring>

namespace encircling {

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

template<typename T>
class Array;

template<typename T>
class ArrayIter : public std::iterator<std::forward_iterator_tag, T>
{
public:
	ArrayIter(const Array<T>& a, const size_t i) : _i(i), _arr(a) {}
	ArrayIter& operator++() {_i++; return *this;}
	bool operator==(const ArrayIter& rhs) const {
		return _arr._data.get() == rhs._arr._data.get() && _i == rhs._i;
	}
	bool operator!=(const ArrayIter& rhs) const {
		return _arr._data.get() != rhs._arr._data.get() || _i != rhs._i;
	}
	T& operator*() { return _arr._data.get()[_i]; }
private:
	size_t _i;
	const Array<T>& _arr;
};

template<typename T>
class Array {
public:
	typedef T value_type;
	typedef ArrayIter<T> iterator;
	typedef ArrayIter<T> const const_iterator;

	explicit Array(const size_t n) : _n(n), _data(new T[__enc_max(n,1)], _ArrayFree<T>()) {
		memset(_data.get(), 0, n*sizeof(T));
	}
	virtual ~Array() {}

	T& operator[](size_t i) {
		if (unlikely(i >= _n))
			throw RuntimePanic("Array::operator[] out-of-bounds");
		return _data.get()[i];
	}
	T const& operator[](size_t i) const {
		if (unlikely(i >= _n))
			throw RuntimePanic("Array::operator[] out-of-bounds");
		return _data.get()[i];
	}

	iterator begin() { return ArrayIter<T>(*this, 0); }
	iterator end() { return ArrayIter<T>(*this, this->last()); }
	const_iterator begin() const { return ArrayIter<T>(*this, 0); }
	const_iterator end() const { return ArrayIter<T>(*this, this->last()); }

	size_t len() const { return _n; }
private:
	friend class ArrayIter<T>;
	size_t const _n;
	std::shared_ptr<T> const _data;

	size_t last() const { return _n > 0 ? _n - 1 : 0; }
};

} // namespace encircling

#endif // _ENCIRCLING_ARRAY_HPP_
