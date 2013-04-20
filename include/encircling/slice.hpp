// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#pragma once
#ifndef _ENCIRCLING_SLICE_HPP_
#define _ENCIRCLING_SLICE_HPP_

#include "_common.hpp"
#include "array.hpp"

#include <memory>
#include <cstring>

namespace encircling {

template<typename T>
class Slice {
public:
	typedef T value_type;
	typedef Iter<Slice, T> iterator;
	typedef Iter<Slice, T> const const_iterator;

	static Result<Slice<T> > make(const size_t n) {
		return Result<Slice<T> >(Slice<T>(n, n));
	}
	static Result<Slice<T> > make(const size_t n, const size_t cap) {
		return Result<Slice<T> >(Slice<T>(n, cap));
	}

	virtual ~Slice() {}

	T& operator[](size_t i) {
		if (unlikely(i >= _n))
			throw RuntimePanic("Slice::operator[] out-of-bounds");
		return _data.get()[i];
	}
	T const& operator[](size_t i) const {
		if (unlikely(i >= _n))
			throw RuntimePanic("Slice::operator[] out-of-bounds");
		return _data.get()[i];
	}

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, _n); }
	const_iterator begin() const { return iterator(*this, 0); }
	const_iterator end() const { return iterator(*this, _n); }

	size_t len() const { return _n; }
	size_t cap() const { return _cap; }
private:
	explicit Slice(const size_t n, const size_t cap)
			: _n(n), _cap(cap), _data(new T[__enc_max(_cap,1)], _ArrayFree<T>()) {
		memset((void*)_data.get(), 0, n*sizeof(T));
	}
	friend class Iter<Slice, T>;
	size_t const _n;
	size_t const _cap;
	std::shared_ptr<T> const _data;
};

} // namespace encircling

#endif // _ENCIRCLING_SLICE_HPP_
