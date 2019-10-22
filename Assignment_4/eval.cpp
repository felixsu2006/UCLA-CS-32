#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
	int letters = 0;
	int paran = 0;
	int pCheck = 0;
	int signCheck = 0;
	int letterCheck = 0;
	int openCheck = 0;
	for (size_t k = 0; k < infix.size(); k++)	//check for validity
	{
		if (isalpha(infix[k]) && islower(infix[k]))
		{
			if (letters != 0)
				return 1;
			letters++;
			signCheck = 0;
			letterCheck = 1;
			pCheck = 0;
			openCheck = 1;
		}
		else if (infix[k] == '(')
		{
			if (openCheck != 0)
				return 1;
			paran++;
			pCheck = 1;
			signCheck = 0;
			openCheck = 0;
		}
		else if (infix[k] == ')')
		{
			if (pCheck == 1)
				return 1;
			if (signCheck == 1)
				return 1;
			pCheck = 0;
			if (paran == 0)
				return 1;
			paran--;
			signCheck = 0;
		}
		else if (infix[k] == '&' || infix[k] == '|')
		{
			if (signCheck == 1)
				return 1;
			if (k == infix.size() - 1 || k == 0)
				return 1;
			signCheck = 1;
			letters = 0;
			letterCheck = 0;
			pCheck = 1;
			openCheck = 0;
		}
		else if (infix[k] == '!')
		{
			if (k == infix.size() - 1)
				return 1;
			pCheck = 1;
			openCheck = 0;
		}
		else if (infix[k] == ' ')
		{}
		else
			return 1;
	}
	if (letterCheck != 1)
		return 1;
	if (paran != 0)
		return 1;

	int setCheck = 0;
	int validCheck = 0;
	int zeroCheck = 0;
	int doubleCheck = 0;
	ItemType x;
	for (size_t k = 0; k < infix.size(); k++)
	{
		if (!isalpha(infix[k]))
			continue;
		for (int j = 0; j < trueValues.size(); j++)
		{
			trueValues.get(j, x);
			if (infix[k] == x)
			{
				setCheck++;
				break;
			}
		}
		for (int j = 0; j < falseValues.size(); j++)
		{
			falseValues.get(j, x);
			if (infix[k] == x)
			{
				setCheck++;
				break;
			}
		}
		if (setCheck == 0)
		{
			zeroCheck++;
			validCheck = -1;
		}
		else if (setCheck == 2)
		{
			doubleCheck++;
			validCheck = -1;
			setCheck = 0;
		}
		else if(setCheck == 1)
		{
			setCheck = 0;
		}
	}
	
	if (validCheck == -1)
	{
		if (zeroCheck != 0)
			return 2;
		else if (doubleCheck != 0)
			return 3;
		else
			return 2;
	}
	else if (validCheck == 0)
	{
		postfix = "";
		stack<ItemType> charStack;
		for (size_t k = 0; k < infix.size(); k++)
		{
			switch (infix[k])
			{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				postfix += infix[k];
				break;
			case '(':
				charStack.push(infix[k]);
				break;
			case ')':
				while (charStack.top() != '(')
				{
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.pop();
				break;
			case '!':
				while (!charStack.empty() && (charStack.top() != '(') && (charStack.top() == '!'))
				{
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.push(infix[k]);
				break;
			case '&':
				while (!charStack.empty() && (charStack.top() != '(') && (charStack.top() == '&' || charStack.top() == '!'))
				{
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.push(infix[k]);
				break;
			case '|':
				while (!charStack.empty() && (charStack.top() != '(') && (charStack.top() == '|' || charStack.top() == '&' || charStack.top() == '!'))
				{
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.push(infix[k]);
				break;
			}
		}

		while (!charStack.empty())
		{
			postfix += charStack.top();
			charStack.pop();
		}
	}

	stack<ItemType> operandStack;
	for (size_t k = 0; k < postfix.size(); k++)
	{
		if (isalpha(postfix[k]))
		{
			operandStack.push(postfix[k]);
		}
		else
		{
			if (operandStack.size() >= 2)
			{
				ItemType operand2 = operandStack.top();
				operandStack.pop();
				ItemType operand1 = operandStack.top();
				operandStack.pop();
				if (postfix[k] == '&')
				{
					if (trueValues.contains(operand1) && trueValues.contains(operand2))
					{
						operandStack.push(operand1);
					}
					else if (trueValues.contains(operand1))
					{
						operandStack.push(operand2);
					}
					else
						operandStack.push(operand1);
				}
				else if (postfix[k] == '|')
				{
					if (falseValues.contains(operand1) && falseValues.contains(operand2))
					{
						operandStack.push(operand1);
					}
					else if (trueValues.contains(operand1))
					{
						operandStack.push(operand1);
					}
					else
						operandStack.push(operand2);
				}
				else
				{
					operandStack.push(operand1);
					if (trueValues.contains(operand2))
					{
						falseValues.get(0, x);
						operandStack.push(x);
					}
					else
					{
						trueValues.get(0, x);
						operandStack.push(x);
					}

				}
			}
			else
			{
				if (postfix[k] == '&' || postfix[k] == '|')
					return 1;
				else
				{
					ItemType operand1 = operandStack.top();
					operandStack.pop();
					if (trueValues.contains(operand1))
					{
						falseValues.get(0, x);
						operandStack.push(x);
					}
					else
					{
						trueValues.get(0, x);
						operandStack.push(x);
					}

				}
			}
			
			//consider adding a check to see if stack only has one thing
		}
	}
	result = trueValues.contains(operandStack.top());
	return 0;

}

int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (size_t k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (size_t k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x"  &&  answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	assert(evaluate("t&!f", trues, falses, pf, answer) == 0 && answer && pf == "tf!&");
	assert(evaluate("t!&(", trues, falses, pf, answer) == 1);
	assert(evaluate("!(!(s", trues, falses, pf, answer) == 1);
	evaluate("!(t&f)", trues, falses, pf, answer);
	cout << pf << endl;

	cout << "Passed all tests" << endl;
}
