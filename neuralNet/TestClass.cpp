#include "stdafx.h"
//#include <CppUnitTest.h>  
//#include "..\MyProjectUnderTest\MyCodeUnderTest.h"  
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
TEST_CLASS(TestClassName)
{
public:
	TEST_METHOD(TestMethodName)
	{
		// Run a function under test here.  
		Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());
	}
}