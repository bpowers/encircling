// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#pragma once
#ifndef _ENCIRCLING__COMMON_HPP_
#define _ENCIRCLING__COMMON_HPP_

#include <exception>
#include <stddef.h>

// the '!!' is from Love's LSP book.  it ensures that integer and
// pointer values are converted to boolean values (not (not x)), so
// that the comparisions to 0 and 1 behave as expected.
#define likely(x)   __builtin_expect(!!(x),1)
#define unlikely(x) __builtin_expect(!!(x),0)

namespace encircling {

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

}

#endif // _ENCIRCLING__COMMON_HPP_