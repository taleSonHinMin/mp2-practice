#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_a_stack) {
	ASSERT_NO_THROW(Stack<int> st(10));
}
TEST(Stack, cant_create_a_stack_with_too_large_size) {
	ASSERT_ANY_THROW(Stack<int> st(MAX_SIZE+1));
}
TEST(Stack, cant_create_a_stack_with_non_size) {
	ASSERT_ANY_THROW(Stack<int> st(0));
}


TEST(Stack, can_create_a_copied_stack) {
	Stack<char> st(5);
	st.push('A'); st.push('B'); st.push('+');
	Stack<char> st1(st);

	EXPECT_EQ(5, st1.size());
	EXPECT_EQ(3, st1.length());
	EXPECT_EQ('+', st1.Top()); st1.pop();
	EXPECT_EQ('B', st1.Top()); st1.pop();
	EXPECT_EQ('A', st1.Top());
}
TEST(Stack, copied_stack_has_its_own_memory) {
	Stack<char> st(5);
	st.push('A'); st.push('B'); st.push('+');
	Stack<char> st1(st);

	st1.push('C');
	EXPECT_EQ(3, st.length());
	EXPECT_EQ('+', st.Top());
}


TEST(Stack, ctor_moved_data_correctly) {
	Stack<char> st(5);
	st.push('A'); st.push('B'); st.push('+');
	Stack<char> st1(move(st));

	EXPECT_EQ(5, st1.size());
	EXPECT_EQ(3, st1.length());
	EXPECT_EQ('+', st1.Top()); st1.pop();
	EXPECT_EQ('B', st1.Top()); st1.pop();
	EXPECT_EQ('A', st1.Top());
}


TEST(Stack, can_get_size) {
	Stack<char> st(5);
	EXPECT_EQ(5, st.size());
}
TEST(Stack, can_get_length) {
	Stack<int> st(5);
	st.push(1);
	EXPECT_EQ(1, st.length());
}


TEST(Stack, can_define_empty_stack) {
	Stack<char> st(3);
	EXPECT_TRUE(st.isEmpty());
}
TEST(Stack, can_define_full_stack) {
	Stack<char> st(3);
	st.push('1'); st.push('1'); st.push('1');
	EXPECT_TRUE(st.isFull());
}


TEST(Stack, can_get_a_top_element) {
	Stack<char> st(3);
	st.push('1'); st.push('1'); st.push('2');
	EXPECT_EQ('2', st.Top());
}
TEST(Stack, cant_get_a_top_element_from_empty_stack) {
	Stack<char> st(3);
	ASSERT_ANY_THROW(st.Top());
}

TEST(Stack, can_pop_an_element) {
	Stack<char> st(3);
	st.push('3'); st.push('1'); st.push('2');
	
	st.pop();
	EXPECT_EQ(2, st.length());
	EXPECT_EQ('1', st.Top());

	st.pop(); st.pop();
	EXPECT_EQ(0, st.length());
}
TEST(Stack, cant_pop_an_element_in_empty_stack) {
	Stack<char> st(3);

	ASSERT_ANY_THROW(st.pop());
}


TEST(Stack, can_push_an_element) {
	Stack<char> st(5);
	st.push('3');
	EXPECT_EQ('3', st.Top());

	st.push('+');
	EXPECT_EQ('+', st.Top());

	EXPECT_EQ(2, st.length());

}
TEST(Stack, cant_push_an_element_in_full_stack) {
	Stack<char> st(3);
	st.push('3'); st.push('1'); st.push('2');

	ASSERT_ANY_THROW(st.push('='));
}

