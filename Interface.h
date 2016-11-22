#pragma once
#include <iostream>
#include <string>
using namespace std;
bool ShowMainMenu();
void ShowInformation();



struct entrenceData {
	string text;
	int subStringLenth;
};
entrenceData UseKeyboardInput();
int GetSubstringLenth(int textSize);
entrenceData Compute(entrenceData entData);
entrenceData Decode(entrenceData entData);
bool Fail();