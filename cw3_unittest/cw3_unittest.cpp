#include "pch.h"
#include "CppUnitTest.h"
#include "../cw3/cw3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cw3unittest
{
	TEST_CLASS(cw3unittest)
	{
	private:
		string toString(Stack* stack) {
			stringstream str;
			while (MathUnit* u = stack->pop()) {
				str << *u;
			}
			return str.str();
		}

	public:
		
		TEST_METHOD(TestProcessExpression)
		{
			Stack* stack1 = process_expression("(5 - 6/3) * (8/2 - 1)")->reverse();
			Stack* stack2 = process_expression("-sin(5) + cos(3) - log2(5) + ln(5)")->reverse();
			Stack* stack3 = process_expression("(2*3 + (1+5)*3^2 + 4*2 - 6^2 - 5^2)/2")->reverse();
			Assert::AreEqual("( 5 - 6 / 3 ) * ( 8 / 2 - 1 ) ", toString(stack1).c_str());
			Assert::AreEqual("-sin ( 5 ) + cos ( 3 ) - log2 ( 5 ) + ln ( 5 ) ", toString(stack2).c_str());
			Assert::AreEqual("( 2 * 3 + ( 1 + 5 ) * 3 ^ 2 + 4 * 2 - 6 ^ 2 - 5 ^ 2 ) / 2 ", toString(stack3).c_str());
		}

		TEST_METHOD(InvalidSymbolsException)
		{
			try {
				process_expression("death(666)");
			}
			catch (exception error) {
				Assert::AreEqual("Invalid symbols in the expression", error.what());
			}
		}

		TEST_METHOD(TestPrefixNotation)
		{
			Stack* stack1 = prefix_notation(process_expression("(5 - 6/3) * (8/2 - 1)"));
			Stack* stack2 = prefix_notation(process_expression("-sin(5) + cos(3) - log2(5) + ln(5)"));
			Stack* stack3 = prefix_notation(process_expression("(2*3 + (1+5)*3^2 + 4*2 - 6^2 - 5^2)/2"));
			Assert::AreEqual("* - 5 / 6 3 - / 8 2 1 ", toString(stack1).c_str());
			Assert::AreEqual("+ - + -sin 5 cos 3 log2 5 ln 5 ", toString(stack2).c_str());
			Assert::AreEqual("/ - - + + * 2 3 * + 1 5 ^ 3 2 * 4 2 ^ 6 2 ^ 5 2 2 ", toString(stack3).c_str());
		}

		TEST_METHOD(InvalidBracketsException)
		{
			try {
				prefix_notation(process_expression("5 + (3 + 2"));
			}
			catch (exception error) {
				Assert::AreEqual("Invalid brackets in the expression", error.what());
			}
			try {
				prefix_notation(process_expression("5 + (3 + 2))"));
			}
			catch (exception error) {
				Assert::AreEqual("Invalid brackets in the expression", error.what());
			}
			try {
				prefix_notation(process_expression("5) + 3 + (2"));
			}
			catch (exception error) {
				Assert::AreEqual("Invalid brackets in the expression", error.what());
			}
			try {
				prefix_notation(process_expression("(5 + 3) + 2) + (6"));
			}
			catch (exception error) {
				Assert::AreEqual("Invalid brackets in the expression", error.what());
			}
		}

		TEST_METHOD(TestPrefixCalculation)
		{
			MathUnit* u1 = prefix_calculation(prefix_notation(process_expression("(5 - 6/3) * (8/2 - 1)"))->reverse());
			MathUnit* u2 = prefix_calculation(prefix_notation(process_expression("-sin(5) + cos(3) - log2(5) + ln(5)"))->reverse());
			MathUnit* u3 = prefix_calculation(prefix_notation(process_expression("(2*3 + (1+5)*3^2 + 4*2 - 6^2 - 5^2)/2"))->reverse());
			Assert::AreEqual(9.0, u1->val());
			Assert::IsTrue(abs(u2->val() - (-0.74355840439)) < 0.00000000001);
			Assert::AreEqual(3.5, u3->val());
		}
	};
}
