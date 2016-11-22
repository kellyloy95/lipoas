#include <conio.h> //���������� ����/�����
#include <fstream>
#include <sstream>
#include <vector>// ��� ������������� �������
#include "inout.h"
#include "enterValues.h"
#include "substrings.h"
#include "test.h"
const int FIRST_DIGIT_CODE = 48;//��� ������ �����(����������)
const int FIRST_MENU_ITEM = 1;//����� ������� ������ ����
const int SECOND_MENU_ITEM = 2;
const int LAST_MENU_ITEM = 4;
const int READ_FAIL = -1;//��� ������ ������ �����
const string EMPTY_STRING = "";//������ ������
using namespace std;
bool File();
//enum menuItem { inputFromKeyboard = 1, inputFromFile, useTestValues,exitProgram, Shifr= 1, Rashifr, BACK };
enum mainMenuItems { inputFromKeyboard = 1, inputFromFile, useTestValues, exitProgram, Shifr = 1, Rashifr, BACK };

void ShowInformation() {
	cout << "\n������������ ������ �3.\n��������� ��������� �������.\n��������� ������������� ��� ���������� � ������ ������������� �������� ������� \n��������� �����\n";
}
bool ShowMainMenu() {
	entrenceData newEntrenceData; //��������� ���������, ������� �������� � ���� ����� ������ ��� ��������.
	cout << "1. ���� ������ � ����������\n";
	cout << "2. �������� ������ �� �����\n";
	cout << "3. ������������\n";
	cout << "4. �����\n";
	mainMenuItems programmMode;
	char currentSymbol = 0;//���������� ���������� (��������� ��������� ������)
	while (currentSymbol - FIRST_DIGIT_CODE < FIRST_MENU_ITEM || currentSymbol - FIRST_DIGIT_CODE > LAST_MENU_ITEM) {
		currentSymbol = _getch();
	}
	programmMode = (mainMenuItems) (currentSymbol - FIRST_DIGIT_CODE);//����� ������ ���������
	switch (programmMode) {
	case inputFromKeyboard:
		newEntrenceData = UseKeyboardInput();//��� ������� �����
		break;
	case inputFromFile:
		File();
		//newEntrenceData = UseFileFromData();//��� �������� ������ �� �����
		break;
	case useTestValues:
		newEntrenceData = UseTestInput();//�������� ������
		break;
	case exitProgram://����� �� ���������
		return true;
	}
	entrenceData readyData = Compute(newEntrenceData);
	cout << Decode(readyData).text << "�������� �����" << endl;

	return false;
}
entrenceData Compute(entrenceData newEntrenceData){
	entrenceData newText; //�����, ���������� ����� ��������� ����������.
	if (newEntrenceData.subStringLenth != READ_FAIL) {
		newText = GetNewText(newEntrenceData); //GetNewText - ������� ��� ��������� ������ ������ �� ���������, �������� �������� ������
		cout << endl << "��������� ������ ���������:";
		cout << endl << newText.text;
		cout << endl << "\n������� ��� ����� ��� ���������� ���������������� ������.\n";
		bool mistake = SaveResults(newText);//mistake- ���������� ������ ������ � ���� ����������� ���������� ���������.
	}
	else {
		cout << "\n ������ ������, ���� �������� �� ���!\n";
	}
	return newText;
}
entrenceData Decode(entrenceData entData) {
	for (int i = 0; i < entData.text.size(); i++) {
		int startPos = 0;
		int finishPos = 0;
		int pos = 0;
		int lenght = 0;
		string signature;
		string data;
		if (entData.text[i] == '{') {
			startPos = i;
			while (entData.text[i] != '}') {
				i++;
			}
			finishPos = i;
			signature = entData.text.substr(startPos + 1, finishPos - startPos - 1);
			for (int j = 0; j < signature.size(); j++){
				if (signature[j] == ',') {
					istringstream posStream(signature.substr(0, j - 1), istringstream::in);
					posStream >> pos;
					istringstream lenghtStream(signature.substr(j + 1, signature.size()), istringstream::in);
					lenghtStream >> lenght;
				}
			}
			string firstPath = entData.text.substr(0, startPos);
			string finishPath = entData.text.substr(finishPos + 1, entData.text.size());
			data = entData.text.substr(pos, lenght);
			entData.text = firstPath + data + finishPath;
		}
	}
	return entData;
}
entrenceData UseKeyboardInput() {
	vector <string> allLines;
	entrenceData newEntrenceData;
	cout << "������� �����\n";
	cout << "���� ���� ������ ����� - ���������� ����.\n";
	string currentString = "a";//������� ������, ��� ����� ������
	string previosString = ""; //���������� ������, ��� ����� ������
	do {
		previosString = currentString;
		getline(cin, currentString);
		allLines.push_back(currentString);// ���������� ������ �������� � ����� ������� push_back
	} while (currentString != EMPTY_STRING || previosString != EMPTY_STRING);
	allLines.pop_back();// pop_back() � ������� ��������� �������
	allLines.pop_back();
	newEntrenceData.text = "";
	for (int j = 0; j < (int)allLines.size(); j++)// ���������� ��������� ������������ ������� size()
	{
		newEntrenceData.text += allLines[j];
	}
	cout << newEntrenceData.text;
	newEntrenceData.subStringLenth = GetSubstringLenth(newEntrenceData.text.size());
	return newEntrenceData;

}
int GetSubstringLenth(int textSize)//������ � ������������ ����� ���������
{
	int subStringLenth;
	cout << endl << "������� ���������� �������� ���������\n";
	subStringLenth = InputInt32PositiveType();//������� ��������� ����� �� ���������������
	while (subStringLenth > textSize / 2) {
		cout << "����� ��������� �� ����� ���� ������ ����� ������. \n� ���� �� ����� ��������� ������ ���� ��� ������� � 2 ���� ������ ����� ������.\n������� ����� ��������� �����.\n";
		subStringLenth = InputInt32Type();
	}
	return subStringLenth;
}
void DisplayFailMenu() {
	cout << "�������� ������ �� �����" << endl;
	cout << "�������� ���� �� �������" << endl;
	cout << "1. ����������� �����" << endl;
	cout << "2. ������������ �����" << endl;
	cout << "3. �����" << endl;
	cout << "��� �����: ";
}

/*void File(){
	int choice = 0;
	do {
		cout << endl;
		DisplayFailMenu ();
		switch (choice) {
		case Shifr:
			cout << "����� ���������" << endl;
			system("PAUSE");
			break;
		case Rashifr:
			cout << "����� �����" << endl;
			system("PAUSE");
			break;
		case BACK:
			break;
		default:
			cout << "��� ������ ������." << endl;
			system("PAUSE");
			break;
		}
	} while (choice != BACK);
}*/
bool Fail() {
	entrenceData newEntrenceData; //��������� ���������, ������� �������� � ���� ����� ������ ��� ��������.
	/*cout << "�������� ������ �� �����" << endl;
	cout << "�������� ���� �� �������" << endl;
	cout << "1. ����������� �����" << endl;
	cout << "2. ������������ �����" << endl;
	cout << "3. �����" << endl;
	mainMenuItems programmMode;
	char currentSymbol = 0;//���������� ���������� (��������� ��������� ������)
	while (currentSymbol - FIRST_DIGIT_CODE < FIRST_MENU_ITEM || currentSymbol - FIRST_DIGIT_CODE > LAST_MENU_ITEM) {
		currentSymbol = _getch();
	}
	programmMode = (mainMenuItems) (currentSymbol - FIRST_DIGIT_CODE);//����� ������ ���������
	switch (programmMode) {
	case Shifr:
		newEntrenceData = UseFileFromData();
		//entrenceData readyData = Compute(newEntrenceData);
		break;
	case Rashifr:
		
		newEntrenceData = UseFileFromData();//��� �������� ������ �� �����
		break;

	case exitProgram://����� �� ���������
		return true;
	}
	entrenceData readyData = Compute(newEntrenceData);
	cout << Decode(readyData).text << "�������� �����" << endl;*/

	return false;
}

