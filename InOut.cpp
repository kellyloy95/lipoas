#include <iostream>
#include <string>
#include <cstdio>//��������� ��������� ����� � ������������ ���� std
#include <fstream>
#include <conio.h>
#include <windows.h> 
#include "interface.h"

using namespace std;
bool SaveResults(entrenceData DataToSave)
{
	char filename[MAX_PATH]; // ���� � �����
	cin >> filename;
	ofstream out(filename);
	if (!out)
	{
		cout << " �� ������� ������� ���� \n";
		return false;
	}
	out << DataToSave.text;
	return true;
}
entrenceData UseFileFromData()
{
	entrenceData newData;
	ifstream in;
	char filename[MAX_PATH];//���� � �����
	cout << " ������� ���� � ��� �����: ";
	cin >> filename;
	in.open(filename);
	if (!in.is_open())
	{
		cout << " �� ������� ������� ����!";
		in.clear();
		newData.subStringLenth = -1;
		return newData;
	}
	string partOfTheText;
	while (!in.eof())
	{
		in >> partOfTheText;
		newData.text += (partOfTheText + " ");

	}
	newData.subStringLenth = GetSubstringLenth(newData.text.size());
	return newData;
}