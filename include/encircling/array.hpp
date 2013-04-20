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

template<typename T>
class Array {
public:
	typedef T value_type;
	typedef Iter<Array, T> iterator;
	typedef Iter<Array, T> const const_iterator;

	static Result<Array<T> > make(size_t n) {
		return Result<Array<T> >(Array<T>(n));
	}

	~Array() {}

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

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, _n); }
	const_iterator begin() const { return iterator(*this, 0); }
	const_iterator end() const { return iterator(*this, _n); }

	size_t len() const { return _n; }
private:
	explicit Array(const size_t n) : _n(n), _data(new T[__enc_max(n,1)], _ArrayFree<T>()) {
		memset((void*)_data.get(), 0, n*sizeof(T));
	}
	friend class Iter<Array, T>;
	size_t const _n;
	std::shared_ptr<T> const _data;
};

} // namespace encircling

#endif // _ENCIRCLING_ARRAY_HPP_
