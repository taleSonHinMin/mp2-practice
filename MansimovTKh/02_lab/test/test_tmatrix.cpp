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
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m.size(), m1.size());
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(m[i][j], m1[i][j]);
		}
	}
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(m);
	m1[0][2] = 20;
	EXPECT_NE(m[0][2], 20);
}



TEST(TDynamicMatrix, ctor_moved_matrix_correctly) {
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(move(m));

	EXPECT_EQ(m1.size(), 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(m1[i][j], i + j);
		}
	}
}



TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	EXPECT_EQ(m.size(), 5);
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
	ASSERT_ANY_THROW(m.at(-1, 0) = 100);
	ASSERT_ANY_THROW(m.at(0, -1) = 100);
	ASSERT_ANY_THROW(m.at(-2, -1) = 100);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(100,100) = 1);
	ASSERT_ANY_THROW(m.at(100, 0) = 1);
	ASSERT_ANY_THROW(m.at(0, 100) = 1);
}



TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	m = m;
	EXPECT_EQ(3, m.size());
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			EXPECT_EQ(i + j, m[i][j]);
		}
	}
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(3);
	m1 = m;
	EXPECT_EQ(m.size(), m1.size());
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			EXPECT_EQ(m[i][j], m1[i][j]);
		}
	}
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(5);
	m1 = m;
	EXPECT_EQ(m.size(), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(5);
	m1 = m;
	EXPECT_EQ(m.size(), m1.size());
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			EXPECT_EQ(m[i][j], m1[i][j]);
		}
	}
}



TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}

	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}

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
	TDynamicMatrix<int> v(2);
	TDynamicMatrix<int> v1(2);
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 2; j++) {
			v[i][j] = i + j;
			v1[i][j] = i + j;
		}
	}
	v1[1][1] = 100;

	EXPECT_FALSE(v == v1);
	EXPECT_TRUE(v != v1);
}



TEST(TDynamicMatrix, can_multiply_matrix_to_scalar)
{
	TDynamicMatrix<int> m(3);

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> res = m * 2;

	EXPECT_EQ(3, res.size());
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			EXPECT_EQ((i + j) * 2, res[i][j]);
		}
	}
}



TEST(TDynamicMatrix, can_multiply_matrix_to_vector_with_same_size)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}

	TDynamicVector<int> v(3);
	for (size_t i = 0; i < 3; i++) {
		v[i] = i;
	}

	TDynamicVector<int> res = m * v;

	EXPECT_EQ(3, res.size());
	int sum;
	for (size_t i = 0; i < 3; i++) {
		sum = 0;
		for (size_t j = 0; j < 3; j++) {
			sum += (i + j) * j;
		}
		EXPECT_EQ(sum, res[i]);
	}
}

TEST(TDynamicMatrix, cannot_multiply_matrix_to_vector_with_different_size)
{
	TDynamicMatrix<int> m(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			m[i][j] = i + j;
		}
	}

	TDynamicVector<int> v(5);
	for (size_t i = 0; i < 5; i++) {
		v[i] = i;
	}

	ASSERT_ANY_THROW(TDynamicVector<int> res = m * v);

}



TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  ADD_FAILURE();
}

