#include "postfix_form.h"

int getPriority(char oper) {
	switch (oper) {
	case '*': return 3;
	case '/': return 3;
	case '+': return 2;
	case '-': return 2;
	case '(': return 1;
	default: return 0;
	}
}

PostfixForm::PostfixForm(const string& exp) : expression(exp) {
	size_t size = exp.size();
	Stack<char> stack1(size);
	Stack<char> stack2(size);

	for (char c : exp) {
		if (c == ' ') continue;
		else if (c >= 'A' && c <= 'Z') stack1.push(c);
		else if (c == '(') stack2.push(c);
		else if (c == ')') {
			while (1) {
				if (stack2.isEmpty()) throw invalid_argument("Incorrect expression");

				if (stack2.Top() == '(') { stack2.pop(); break; }

				stack1.push(stack2.Top());
				stack2.pop();
			}
		}
		else if (c == '*' || c == '/' || c=='+' || c=='-') {
			while ( !stack2.isEmpty()
				&& getPriority(c) <= getPriority(stack2.Top()) 
				&& stack2.Top() != '(' ) {

				stack1.push(stack2.Top());
				stack2.pop();
			}
			stack2.push(c);
		}
		else {
			throw invalid_argument("Invalid character");
		}
	}
	while (!stack2.isEmpty()) {
		if (stack2.Top() == '(') throw invalid_argument("Invalid expression");
		stack1.push(stack2.Top());
		stack2.pop();
	}

	string reversed_postfix_exp;
	while (!stack1.isEmpty()) {
		reversed_postfix_exp += stack1.Top();
		stack1.pop();
	}
	reverse(reversed_postfix_exp.begin(), reversed_postfix_exp.end());
	this->postfixExpression = reversed_postfix_exp;
}

void PostfixForm::setOperands(vector<pair<char, double>>& operands) {
	for (char c : this->postfixExpression) {
		if (c >= 'A' && c <= 'Z') {
			double double_value;
			string input;
			bool dublicate = false;

			for (const pair<char, double>& operand : operands) {
				if (operand.first == c) {
					dublicate = true;
					break;
				}
			}

			if (dublicate) continue;

			while (true) {
				cout << "Set a value for operand " << c << ": ";
				getline(cin, input);

				istringstream iss(input);
				char extra;

				if ((iss >> double_value) && !(iss >> extra)) break;

				cout << "Ivalid input";
			}

			operands.push_back({ c, double_value });
		}
	}
}

double PostfixForm::calculate(const vector<pair<char, double>>& operands) {
	size_t size = (this->postfixExpression).size();
	if (size == 0) throw invalid_argument("the expression is empty");

	Stack<double> stack(size);

	for (char c : this->postfixExpression) {
		if (c >= 'A' && c <= 'Z') {
			bool found = false;
			for (const pair<char, double>& operand : operands) {
				if (c == operand.first) {
					stack.push(operand.second);
					found = true;
					break;
				}
			}
			if (!found) throw invalid_argument("Operand value not found");
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/'){
			if (stack.length() < 2) throw invalid_argument("Incorrect postfix expression");

			double op1 = stack.Top(); stack.pop();
			double op2 = stack.Top(); stack.pop();

			switch (c) {
			case '+': 
				stack.push(op2 + op1);
				break;
			case '-':
				stack.push(op2 - op1);
				break;
			case '*':
				stack.push(op2 * op1);
				break;
			case '/':
				if (op1 == 0.0) throw invalid_argument("Division by zero");
				stack.push(op2 / op1);
				break;
			}
		}
	}
	if (stack.length() != 1) throw invalid_argument("Incorrect postfix expression");

	return stack.Top();
}