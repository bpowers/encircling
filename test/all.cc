// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "array.hpp"
#include "slice.hpp"
#include "string.hpp"

#include <gtest/gtest.h>

#include <cstdio>

TEST(ArrayTest, construction)
{
	const size_t n = 20;
	EXPECT_TRUE(true);
	encircling::Array<double> arr(n);

	for (size_t i=0; i < n; ++i)
	{
		// proving to myself the T& is the correct return type
		// for operator[]
		double d = arr[i];
		EXPECT_EQ(0, arr[i]);
		EXPECT_EQ(0, d);
		EXPECT_EQ(arr[i], d);
	}

	for (size_t i=0; i < n; ++i)
	{
		// proving to myself the T& is the correct return type
		// for operator[]
		arr[i] = i;
		EXPECT_EQ(i, arr[i]);
	}

	EXPECT_THROW(arr[n], encircling::RuntimePanic);
	EXPECT_THROW(arr[n+1], encircling::RuntimePanic);
}
