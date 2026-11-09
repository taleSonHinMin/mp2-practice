#include "postfix_form.h" 
#include <gtest.h>

TEST(Postfix_Form, can_create_postfix_expresion) {
	string exp = "A+B"; 
	string exp1 = "A+(B-C)*D";
	string exp2 = "((A+B)*(C-D))";
	string exp3 = "((A))";

	PostfixForm pf(exp);
	PostfixForm pf1(exp1);
	PostfixForm pf2(exp2);
	PostfixForm pf3(exp3);

	EXPECT_EQ("AB+", pf.getPostfix());
	EXPECT_EQ("ABC-D*+", pf1.getPostfix());
	EXPECT_EQ("AB+CD-*", pf2.getPostfix());
	EXPECT_EQ("A", pf3.getPostfix());
}
TEST(Postfix_Form, can_create_postfix_expression_with_extra_spaces) {
	string exp = "    A  +  B    ";
	PostfixForm pf(exp);

	EXPECT_EQ("AB+", pf.getPostfix());
}
TEST(Postfix_Form, throws_when_create_postfix_expression_from_empty_stroke) {
	string exp = "";
	ASSERT_ANY_THROW(PostfixForm pf(exp));
}
TEST(Postfix_Form, creates_empty_postfix_expression_from_stroke_full_of_spaces) {
	string exp = "     ";
	PostfixForm pf(exp);

	EXPECT_EQ("", pf.getPostfix());
}
TEST(Postfix_Form, copied_expressiom_has_same_postfix_form) {
	string exp = "((A+B)*(C-D))";
	PostfixForm pf(exp);
	PostfixForm pf1(pf);

	EXPECT_EQ(pf.getPostfix(), pf1.getPostfix());
	EXPECT_EQ("AB+CD-*", pf1.getPostfix());
}



TEST(Postfix_Form, throws_when_create_postfix_expression_with_invalid_count_of_parenthesis) {
	string exp = "A+B)";
	string exp1 = "A+(B*C";
	string exp2 = ")(A+B";
	string exp3 = "A+)(B";
	string exp4 = "A+B))";

	ASSERT_ANY_THROW(PostfixForm pf(exp));
	ASSERT_ANY_THROW(PostfixForm pf1(exp1));
	ASSERT_ANY_THROW(PostfixForm pf2(exp2));
	ASSERT_ANY_THROW(PostfixForm pf3(exp3));
	ASSERT_ANY_THROW(PostfixForm pf4(exp4));
}
TEST(Postfix_Form, throws_when_create_postfix_expression_from_lower_case_stroke) {
	string exp = "a+B";
	string exp1 = "A+b*C";
	string exp2 = "a+b";

	ASSERT_ANY_THROW(PostfixForm pf(exp));
	ASSERT_ANY_THROW(PostfixForm pf1(exp1));
	ASSERT_ANY_THROW(PostfixForm pf2(exp2));
}
TEST(Postfix_Form, throws_when_create_postfix_expression_with_special_charecter) {
	string exp = "a__ &";
	string exp1 = "%+b*C";
	string exp2 = "@b";

	ASSERT_ANY_THROW(PostfixForm pf(exp));
	ASSERT_ANY_THROW(PostfixForm pf1(exp1));
	ASSERT_ANY_THROW(PostfixForm pf2(exp2));
}



TEST(Postfix_Form, can_calculate_simple_arithmetic_expressions) {
	PostfixForm pf("A+B");
	PostfixForm pf1("A-B");
	PostfixForm pf2("A*B");
	PostfixForm pf3("A/B");

	vector<pair<char, double>> operands= {
		{'A', 8.0},
		{'B', 2.0}
	};

	EXPECT_DOUBLE_EQ(10.0, pf.calculate(operands));
	EXPECT_DOUBLE_EQ(6.0, pf1.calculate(operands));
	EXPECT_DOUBLE_EQ(16.0, pf2.calculate(operands));
	EXPECT_DOUBLE_EQ(4.0, pf3.calculate(operands));
}
TEST(Postfix_Form, can_calculate_complex_arithmetic_expressions) {
	PostfixForm pf("A/(B-C)+D*(E+F)-G");
	PostfixForm pf1("((A+B+C)*(D-E-F))/(G-H/I)");

	vector<pair<char, double>> operands1 = {
		{'A', 12.0},
		{'B', 5.0},
		{'C', 3.0},
		{'D', 8.0},
		{'E', 2.0},
		{'F', 7.0},
		{'G', 4.0}
	};
	vector<pair<char, double>> operands2 = {
		{'A', 12.0},
		{'B', 5.0},
		{'C', 3.0},
		{'D', 8.0},
		{'E', 2.0},
		{'F', 7.0},
		{'G', 4.0},
		{'H', 6.0},
		{'I', 9.0},
	};

	EXPECT_DOUBLE_EQ(74.0, pf.calculate(operands1));
	EXPECT_DOUBLE_EQ(-6.0, pf1.calculate(operands2));
}
TEST(Postfix_Form, throws_when_division_by_zero) {
	PostfixForm pf("(A+C)\B");
	vector<pair<char, double>> operands = {
		{'A', 1.0},
		{'B', 0.0},
		{'C', 4.0}
	};
	ASSERT_ANY_THROW(pf.calculate(operands));
}
TEST(Postfix_Form, throws_when_calculate_expression_with_missing_operand) {
	PostfixForm pf("(A+C)\B+D");
	vector<pair<char, double>> operands = {
		{'A', 1.0},
		{'B', 2.0},
	};
	ASSERT_ANY_THROW(pf.calculate(operands));
}
TEST(Postfix_Form, throws_when_calculate_expression_with_not_enough_operand) {
	PostfixForm pf("A+C+");
	vector<pair<char, double>> operands = {
		{'A', 1.0},
		{'C', 2.0},
	};
	ASSERT_ANY_THROW(pf.calculate(operands));
}
TEST(Postfix_Form, throws_when_calculate_expression_with_not_enough_operation) {
	PostfixForm pf("ABC+D");
	vector<pair<char, double>> operands = {
		{'A', 1.0},
		{'B', 1.0},
		{'C', 2.0},
		{'D', 1.0},
	};
	ASSERT_ANY_THROW(pf.calculate(operands));
}

