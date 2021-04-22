#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

string cutSpaces(string infix)
{
	string output = "";
	for (int i = 0; i != infix.size(); i++)
	{
		if (infix[i] != ' ')
		{
			output += infix[i];
		}
	}
	return output;
}

bool checkBrack(string infix) {
	stack<char> brack;
	for (int i = 0; i != infix.size(); i++) {
		if (infix[i] == '(') {
			if (i + 1 >= infix.size() || infix[i + 1] == ')') {
				return false;
			}
			brack.push('(');
		}
		if (infix[i] == ')') {
			if (brack.empty()) {
				return false;
			}
			brack.pop();
		}
	}
	return brack.empty();
}

int precedence(char val) {
	switch (val)
	{
	case '!':
		return 3;
	case '&':
		return 2;
	case '^':
		return 1;
	default:
		return 4;
	}
}

bool precCheck(char current, char top) {
	current = precedence(current);
	top = precedence(top);
	if (current > top) {
		return true;
	}
	else {
		return false;
	}
}

bool postEval(string postfix , bool& good) {
	stack<bool> eval;
	for (int i = 0; i != postfix.size(); i++) {
		char curr = postfix[i];
		if (isalpha(curr)) {
			if (curr == 'T') {
				eval.push(true);
			}
			else if(curr == 'F') {
				eval.push(false);
			}
		}
		else {
			if (postfix[i] == '!') {
				bool operand = eval.top();
				eval.pop();
				eval.push(!operand);
			}
			else if (postfix[i] == '^') {
				bool operand2 = eval.top();
				eval.pop();
				if (eval.empty()) {
					good = false;
					return false;
				}
				bool operand1 = eval.top();
				eval.pop();
				if (operand1)
				{
					if (!operand2)
						eval.push(true);
					else
						eval.push(false);
				}
				else
				{
					if (operand2)
						eval.push(true);
					else
						eval.push(false);
				}
			}
			else {
				bool operand2 = eval.top();
				eval.pop();
				if (eval.empty()) {
					good = false;
					return false;
				}
				bool operand1 = eval.top();
				eval.pop();
				eval.push(operand1 && operand2);
			}
		}
	}

	if (!eval.empty()){
		bool result = eval.top();
		return result;
	}

	good = false;
	return false;
}

int evaluate(string infix, string& postfix, bool& result)
{
	postfix = "";
	stack<char> oStack;
	infix = cutSpaces(infix);
	if (!checkBrack(infix)) {
		return 1;
	}
	
	for (int i = 0; i != infix.size(); i++) {
		char curr = infix[i];
		if (isalpha(curr)) {
			if (i != 0) {
				if (!(infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '(')) {
					return 1;
				}
			} 
			if (i != infix.size() - 1) {
				if (!(infix[i + 1] == '!' || infix[i + 1] == '&' || infix[i + 1] == '^' || infix[i + 1] == ')')) {
					return 1;
				}
			}
			postfix += curr;
		}
		else if (curr == '(') {
			oStack.push(curr);
		} 
		else if (curr == ')') {
			char top = oStack.top();
			while (!oStack.empty() && top != '(') {
				oStack.pop();
				postfix += top;
				top = oStack.top();
			}
			oStack.pop();
		}
		else {
			if (oStack.empty()) {
				oStack.push(curr);
			}
			else if (oStack.top() == '(') {
				oStack.push(curr);
			}
			else {
				if (precCheck(curr, oStack.top())) {
					oStack.push(curr);
				}
				else {
					while (!oStack.empty() && !precCheck(curr, oStack.top())) {
						char lid = oStack.top();
						oStack.pop();
						postfix += lid;
					}
					oStack.push(curr);
				}
			}
		}
	}
	while (!oStack.empty()) {
		postfix += oStack.top();
		oStack.pop();
	}

	bool good = true;
	bool temp = postEval(postfix, good);
	if (good) {
		result = temp;
		return 0;
	}
	return 1;
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}