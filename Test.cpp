#include <string>
#include "interface.h"
entrenceData UseTestInput()
{
	entrenceData testData;
	testData.text = "�������� ������. ������ ����� �� ����� �������� ��������.";
	testData.subStringLenth = GetSubstringLenth(testData.text.size());
	return testData;
}