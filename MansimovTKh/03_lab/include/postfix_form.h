#ifndef POSTFIX_FORM
#define POSTFIX_FORM

#include <iostream>
#include <string.h>	
#include <vector>
#include <algorithm>
#include <sstream>
#include "stack.h"

using namespace std;

class PostfixForm {
private:
	string expression;
	string postfixExpression;

 public:
	 PostfixForm(const string& expression);

	 string getPostfix() const { return this->postfixExpression; }

	 void setOperands(vector<pair<char, double>>& operands);
	 double calculate(const vector<pair<char, double>>& operands);

};


#endif