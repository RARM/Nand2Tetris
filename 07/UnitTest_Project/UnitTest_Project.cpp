#include "pch.h"
#include "CppUnitTest.h"
#include "../VM Translator/Parser.h"
#include "../VM Translator/Parser.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
	TEST_CLASS(ParserClass)
	{
	public:
		
		TEST_METHOD(FindNextCommand)
		{
			std::string filename("Test.vm");
			Parser my_parser(filename);

			my_parser.find_next_command();
			std::string expected("push constant 7");
			Assert::AreEqual(expected, my_parser.get_current_command());
		}
	};
}
