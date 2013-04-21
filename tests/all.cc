// Copyright 2013 Bobby Powers. All rights reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include <encircling/array.hpp>
#include <encircling/slice.hpp>
#include <encircling/string.hpp>

#include <gtest/gtest.h>

#include <cstdio>

using namespace encircling;

TEST(All, array)
{
	size_t n = 20;

	auto result = Array<double>::make(n);
	if (result.error()) {
		printf("Array::make(%zu) failed: %s\n", n, result.error_msg());
		return;
	}
	// arr is now of type Array<double>
	auto arr = *result;

	for (size_t i=0; i < n; ++i) {
		// proving to myself the T& is the correct return type
		// for operator[]
		double val = arr[i];
		EXPECT_EQ(0, arr[i]);
		EXPECT_EQ(0, val);
		EXPECT_EQ(arr[i], val);
	}

	{
		double n = 0;
		for (double& val : arr) {
			val = n;
			n += 1;
		}
	}

	for (size_t i=0; i < n; ++i) {
		EXPECT_EQ(i, arr[i]);
		// proving to myself the T& is the correct return type
		// for operator[]
		arr[i] = i*2;
		EXPECT_EQ(i*2, arr[i]);
	}

	EXPECT_THROW(arr[n], RuntimePanic);
	EXPECT_THROW(arr[n+1], RuntimePanic);

	{
		double n = 0;
		for (double val : arr) {
			EXPECT_EQ(n, val);
			n += 2;
		}
	}

	// make sure this doesn't throw for some reason
	auto zero_len_res = Array<int>::make(0);
	if (zero_len_res.error()) {
		FAIL();
		return;
	}
	const Array<int> zero_length(*zero_len_res);
	EXPECT_THROW(zero_length[0], encircling::RuntimePanic);
	EXPECT_EQ(zero_length.begin(), zero_length.end());
	// looping through a zero_length array should never invoke the
	// loop body.
	for (const int _ : zero_length) {
		(void)_;
		FAIL();
	}

	n = 128;
	Array<void*> third = *Array<void*>::make(n);
	EXPECT_EQ(n, third.len());
}

TEST(All, slice)
{
	size_t n = 20;

	auto result = Slice<double>::make(n);
	if (result.error()) {
		printf("Slice::make(%zu) failed: %s\n", n, result.error_msg());
		return;
	}
	// arr is now of type Slice<double>
	auto arr = *result;

	for (size_t i=0; i < n; ++i) {
		// proving to myself the T& is the correct return type
		// for operator[]
		double val = arr[i];
		EXPECT_EQ(0, arr[i]);
		EXPECT_EQ(0, val);
		EXPECT_EQ(arr[i], val);
	}

	{
		double n = 0;
		for (double& val : arr) {
			val = n;
			n += 1;
		}
	}

	for (size_t i=0; i < n; ++i) {
		EXPECT_EQ(i, arr[i]);
		// proving to myself the T& is the correct return type
		// for operator[]
		arr[i] = i*2;
		EXPECT_EQ(i*2, arr[i]);
	}

	EXPECT_THROW(arr[n], RuntimePanic);
	EXPECT_THROW(arr[n+1], RuntimePanic);

	{
		double n = 0;
		for (double val : arr) {
			EXPECT_EQ(n, val);
			n += 2;
		}
	}

	// make sure this doesn't throw for some reason
	auto zero_len_res = Slice<int>::make(0);
	if (zero_len_res.error()) {
		FAIL();
		return;
	}
	const Slice<int> zero_length(*zero_len_res);
	EXPECT_THROW(zero_length[0], encircling::RuntimePanic);
	EXPECT_EQ(zero_length.begin(), zero_length.end());
	// looping through a zero_length array should never invoke the
	// loop body.
	for (const int _ : zero_length) {
		(void)_;
		FAIL();
	}

	n = 128;
	Slice<void*> third = *Slice<void*>::make(n);
	EXPECT_EQ(n, third.len());

	n = 32;
	auto parent = *Slice<byte>::make(n);
	EXPECT_EQ(32UL, parent.len());

	Slice<byte> sub1 = parent(1);
	EXPECT_EQ(31UL, sub1.len());
	EXPECT_EQ(31UL, sub1.cap());

	Slice<byte> sub2 = parent(3,5);
	EXPECT_EQ(2UL, sub2.len());
	EXPECT_EQ(29UL, sub2.cap());

	// should end up with parent[20:24]
	Slice<byte> subsub1 = parent(16,32)(4,8);
	EXPECT_EQ(4UL, subsub1.len());
	EXPECT_EQ(12UL, subsub1.cap());
}
