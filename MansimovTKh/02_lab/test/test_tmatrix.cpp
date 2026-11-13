#include "tmatrix.h"

#include <gtest.h>


TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}



TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	TDynamicMatrix<int> m1(m);
	EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	TDynamicMatrix<int> m1(m);
	m1[0][2] = 20;
	EXPECT_NE(m[0][2], 20);
}



TEST(TDynamicMatrix, ctor_moved_matrix_correctly) {
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	TDynamicMatrix<int> m1(move(m));

	EXPECT_EQ(3, m1.size());
	EXPECT_EQ(1, m1[0][0]); EXPECT_EQ(2, m1[0][1]); EXPECT_EQ(3, m1[0][2]);
	EXPECT_EQ(4, m1[1][0]); EXPECT_EQ(5, m1[1][1]);
	EXPECT_EQ(6, m1[2][0]);
}



TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	EXPECT_EQ(5, m.size());
}



TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[0][1] = 10;
	EXPECT_EQ(10, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-2][-1] = 100);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[100][100] = 1);
}



TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	m1 = m;
	EXPECT_EQ(3, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	ASSERT_NO_THROW(m1 = m);
}



TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(2);

	EXPECT_FALSE(m == m1);
	EXPECT_TRUE(m != m1);
}

TEST(TDynamicMatrix, different_matrices_with_same_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3;
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 100;

	EXPECT_FALSE(m == m1);
	EXPECT_TRUE(m != m1);
}



TEST(TDynamicMatrix, can_multiply_matrix_to_scalar)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	TDynamicMatrix<int> res = m * 2;

	EXPECT_EQ(2, res[0][0]); EXPECT_EQ(4, res[0][1]); EXPECT_EQ(6, res[0][2]);
	EXPECT_EQ(8, res[1][0]); EXPECT_EQ(10, res[1][1]);
	EXPECT_EQ(12, res[2][0]);
}



TEST(TDynamicMatrix, can_multiply_matrix_to_vector_with_same_size)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	TDynamicVector<int> v(3);
	v[0] = 2; v[1] = 4; v[2] = 8;

	TDynamicVector<int> res = m * v;

	EXPECT_EQ(34, res[0]); EXPECT_EQ(56, res[1]); EXPECT_EQ(48, res[2]);

}

TEST(TDynamicMatrix, cannot_multiply_matrix_to_vector_with_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(2);

	ASSERT_ANY_THROW(m * v);

}



TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3;

	TDynamicMatrix<int> res = m1+m2;
	EXPECT_EQ(2, res[0][0]); EXPECT_EQ(4, res[0][1]);
	EXPECT_EQ(6, res[1][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	
	ASSERT_ANY_THROW(m1+m2);
}



TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3;

	TDynamicMatrix<int> res = m1 - m2;
	EXPECT_EQ(0, res[0][0]); EXPECT_EQ(0, res[0][1]);
	EXPECT_EQ(0, res[1][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}



TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size) {
	TDynamicMatrix<int> m(3), m1(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5;
	m[2][0] = 6;

	m1[0][0] = 2; m1[0][1] = 1; m1[0][2] = 2;
	m1[1][0] = 4; m1[1][1] = 3;
	m1[2][0] = 5;
	TDynamicMatrix<int> res = m * m1;

	EXPECT_EQ(2, res[0][0]); EXPECT_EQ(9, res[0][1]); EXPECT_EQ(23, res[0][2]);
	EXPECT_EQ(16, res[1][0]); EXPECT_EQ(37, res[1][1]);
	EXPECT_EQ(30, res[2][0]);

}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size) {
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 * m2);
}





