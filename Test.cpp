#include <string>
#include "interface.h"
entrenceData UseTestInput()
{
	entrenceData testData;
	testData.text = "Тестовая строка. Данный текст из строк является тестовым.";
	testData.subStringLenth = GetSubstringLenth(testData.text.size());
	return testData;
}