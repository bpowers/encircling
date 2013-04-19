// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "array.hpp"
#include "slice.hpp"
#include "string.hpp"

#include <gtest/gtest.h>

#include <cstdio>

using namespace encircling;

TEST(ArrayTest, basic_use)
{
	const size_t n = 20;
	EXPECT_TRUE(true);
	auto r1 = Array<double>::make(n);
	if (r1.error()) {
		FAIL();
		return;
	}
	Array<double> arr(*r1);

	for (size_t i=0; i < n; ++i) {
		// proving to myself the T& is the correct return type
		// for operator[]
		double val = arr[i];
		EXPECT_EQ(0, arr[i]);
		EXPECT_EQ(0, val);
		EXPECT_EQ(arr[i], val);
	}

	for (size_t i=0; i < n; ++i) {
		// proving to myself the T& is the correct return type
		// for operator[]
		arr[i] = i;
		EXPECT_EQ(i, arr[i]);
	}

	EXPECT_THROW(arr[n], RuntimePanic);
	EXPECT_THROW(arr[n+1], RuntimePanic);

	{
		double n = 0;
		for (double val : arr) {
			EXPECT_EQ(n, val);
			n += 1;
		}
	}

	// make sure this doesn't throw for some reason
	auto r2 = Array<double>::make(0);
	if (r2.error()) {
		FAIL();
		return;
	}
	const Array<double> zero_length(*r2);
	EXPECT_THROW(zero_length[0], encircling::RuntimePanic);
	EXPECT_EQ(zero_length.begin(), zero_length.end());
	for (const int _ : zero_length) {
		(void)_;
		FAIL();
	}
}
