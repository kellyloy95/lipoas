#include <iostream>
#include <string>
#include <cstdio>//добавляет связанные имена в пространство имен std
#include <fstream>
#include <conio.h>
#include <windows.h> 
#include "interface.h"

using namespace std;
bool SaveResults(entrenceData DataToSave)
{
	char filename[MAX_PATH]; // путь к файлу
	cin >> filename;
	ofstream out(filename);
	if (!out)
	{
		cout << " Не удалось открыть файл \n";
		return false;
	}
	out << DataToSave.text;
	return true;
}
entrenceData UseFileFromData()
{
	entrenceData newData;
	ifstream in;
	char filename[MAX_PATH];//путь к файлу
	cout << " Введите путь и имя файла: ";
	cin >> filename;
	in.open(filename);
	if (!in.is_open())
	{
		cout << " Не удается открыть файл!";
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