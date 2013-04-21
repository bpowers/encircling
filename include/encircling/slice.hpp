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

	~Slice() {}

	T& operator[](size_t i) {
		i += _off;
		if (unlikely(i >= _len))
			throw RuntimePanic("Slice::operator[] out-of-bounds");
		return _data.get()[i];
	}
	T const& operator[](size_t i) const {
		i += _off;
		if (unlikely(i >= _len))
			throw RuntimePanic("Slice::operator[] out-of-bounds");
		return _data.get()[i];
	}

	Slice<T> operator()(size_t i, size_t j) {
		if (unlikely(i >= _len || j > _len || i > j))
			throw RuntimePanic("Slice::operator(,) out-of-bounds");
		return Slice(i, j - i, _cap-i, _data);
	}
	Slice<T> operator()(size_t i) {
		return (*this)(i, _len-_off);
	}


	iterator begin() { return iterator(*this, _off); }
	iterator end() { return iterator(*this, _len); }
	const_iterator begin() const { return iterator(*this, _off); }
	const_iterator end() const { return iterator(*this, _len); }

	size_t len() const { return _len; }
	size_t cap() const { return _cap; }
private:
	explicit Slice(const size_t len, const size_t cap)
		: _off(0), _len(len), _cap(cap), _data(new T[__enc_max(_cap,1)], _ArrayFree<T>()) {
		// zero our data, like go does.
		memset((void*)_data.get(), 0, len*sizeof(T));
	}
	explicit Slice(const size_t off, const size_t len, const size_t cap, std::shared_ptr<T> data)
		: _off(off), _len(len), _cap(cap), _data(data) {
	}

	friend class Iter<Slice, T>;

	size_t const _off;
	size_t const _len;
	size_t const _cap;
	std::shared_ptr<T> const _data;
};

} // namespace encircling

#endif // _ENCIRCLING_SLICE_HPP_
