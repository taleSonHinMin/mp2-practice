#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}



TEST(TDynamicVector, can_create_vector_from_array) {
	int arr[] = { 1, 2, 3, 4, 5 };
	ASSERT_NO_THROW(TDynamicVector<int> v(arr, 5));
}

TEST(TDynamicVector, throws_when_create_vector_from_array_with_negative_length) {
	int arr[] = { 1, 2, 3, 4, 5 };
	ASSERT_ANY_THROW(TDynamicVector<int> v(arr, -5));
}

TEST(TDynamicVector, throws_when_create_from_array_with_zero_size) {
	int arr[] = {1};
	ASSERT_ANY_THROW(TDynamicVector<int> v(arr, 0));
}

TEST(TDynamicVector, throws_when_create_from_nullptr)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(nullptr, 5));
}



TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) {
		v[i] = i;
	}
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) {
		v[i] = i;
	}
	TDynamicVector<int> v1(v);
	v[0] = 10;
	EXPECT_EQ(v1[0], 0);
}



TEST(TDynamicVector, ctor_moved_data_correctly) {
	int arr[] = { 1, 2, 3 };
	TDynamicVector<int> v(arr, 3);
	TDynamicVector<int> v1(move(v));

	EXPECT_EQ(v1.size(), 3);
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v1[2], 3);
}



TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}



TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 2);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(100) = 2);
}



TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;
	v = v;

	EXPECT_EQ(5, v.size());
	for (size_t i = 0; i < 5; i++)
		EXPECT_EQ(i, v[i]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;
	TDynamicVector<int> v1(5);
	v1 = v;

	for (size_t i = 0; i < 5; i++)
		EXPECT_EQ(v[i], v1[i]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(10);
	v1 = v;

	EXPECT_EQ(5, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10);
	for (size_t i = 0; i < 10; i++) v[i] = i;

	TDynamicVector<int> v1(5);
	v1 = v;

	EXPECT_EQ(10, v1.size());
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(v[i], v1[i]);
	}
}



TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i <5; i++) v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) v1[i] = i;

	EXPECT_TRUE(v1 == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(6);
	TDynamicVector<int> v1(3);

	EXPECT_FALSE(v == v1);
	EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, different_vectors_with_same_size_are_not_equal)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) { v[i] = i; v1[i] = i; }
	v1[4] = 0;

	EXPECT_FALSE(v == v1);
	EXPECT_TRUE(v != v1);
}



TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;
	
	TDynamicVector<int>res = v + 5;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i] + 5);
	}
}

TEST(TDynamicVector, add_zero_returns_same_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int>res = v + 0;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i]);
	}
}



TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int>res = v - 5;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i] - 5);
	}
}

TEST(TDynamicVector, subtract_zero_returns_same_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int>res = v - 0;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i]-0);
	}
}



TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;
	TDynamicVector<int> res = v * 5;

	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i] * 5);
	}
}



TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) v1[i] = i;

	TDynamicVector<int> res = v + v1;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i] + v1[i]);
	}
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(10);

	ASSERT_ANY_THROW(v + v1);
}



TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) v1[i] = i;

	TDynamicVector<int> res = v - v1;
	EXPECT_EQ(5, res.size());
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(res[i], v[i] - v1[i]);
	}
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(10);

	ASSERT_ANY_THROW(v - v1);
}



TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) v[i] = i;

	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) v1[i] = i;

	int res = v * v1;
	int expected = 0;
	for (size_t i = 0; i < 5; i++)
		expected += v[i] * v1[i];

	EXPECT_EQ(expected, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(10);

	ASSERT_ANY_THROW(v * v1);
}



TEST(TDynamicVector, can_swap_vectors) {
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; i++) v1[i] = i;

	TDynamicVector<int> v2(10);

	std::swap(v1, v2);
	EXPECT_EQ(5, v2.size());
	EXPECT_EQ(10, v1.size());

	for (size_t i = 0; i < 5; i++) EXPECT_EQ(i, v2[i]);
	for (size_t i = 0; i < 5; i++) EXPECT_EQ(0, v1[i]);
}



