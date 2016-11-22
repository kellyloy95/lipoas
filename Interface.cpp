#include <conio.h> //консольный ввод/вывод
#include <fstream>
#include <sstream>
#include <vector>// для динамического массива
#include "inout.h"
#include "enterValues.h"
#include "substrings.h"
#include "test.h"
const int FIRST_DIGIT_CODE = 48;//код первой цифры(наименьший)
const int FIRST_MENU_ITEM = 1;//номер первого пункта меню
const int SECOND_MENU_ITEM = 2;
const int LAST_MENU_ITEM = 4;
const int READ_FAIL = -1;//код ошибки чтения файла
const string EMPTY_STRING = "";//пустая строка
using namespace std;
bool File();
//enum menuItem { inputFromKeyboard = 1, inputFromFile, useTestValues,exitProgram, Shifr= 1, Rashifr, BACK };
enum mainMenuItems { inputFromKeyboard = 1, inputFromFile, useTestValues, exitProgram, Shifr = 1, Rashifr, BACK };

void ShowInformation() {
	cout << "\nЛабораторная работа №3.\nВыполнена Полониной Кариной.\nПрограмма предназначена для нахождения в тексте повторяющихся подстрок длиннее \nзаданного числа\n";
}
bool ShowMainMenu() {
	entrenceData newEntrenceData; //экземпляр структуры, который содержит в себе новые данные для расчетов.
	cout << "1. Ввод текста с клавиатуры\n";
	cout << "2. Загрузка текста из файла\n";
	cout << "3. Тестирование\n";
	cout << "4. Выход\n";
	mainMenuItems programmMode;
	char currentSymbol = 0;//объявление переменной (последний введенный символ)
	while (currentSymbol - FIRST_DIGIT_CODE < FIRST_MENU_ITEM || currentSymbol - FIRST_DIGIT_CODE > LAST_MENU_ITEM) {
		currentSymbol = _getch();
	}
	programmMode = (mainMenuItems) (currentSymbol - FIRST_DIGIT_CODE);//режим работы программы
	switch (programmMode) {
	case inputFromKeyboard:
		newEntrenceData = UseKeyboardInput();//для ручного ввода
		break;
	case inputFromFile:
		File();
		//newEntrenceData = UseFileFromData();//для загрузки данных из файла
		break;
	case useTestValues:
		newEntrenceData = UseTestInput();//тестовый пример
		break;
	case exitProgram://выход из программы
		return true;
	}
	entrenceData readyData = Compute(newEntrenceData);
	cout << Decode(readyData).text << "Исходный текст" << endl;

	return false;
}
entrenceData Compute(entrenceData newEntrenceData){
	entrenceData newText; //текст, полученный после обработки программой.
	if (newEntrenceData.subStringLenth != READ_FAIL) {
		newText = GetNewText(newEntrenceData); //GetNewText - функция для генерации нового текста из исходного, согласно условиям задачи
		cout << endl << "Результат работы программы:";
		cout << endl << newText.text;
		cout << endl << "\nВведите имя файла для сохранения сгенерированного текста.\n";
		bool mistake = SaveResults(newText);//mistake- показатель ошибки записи в файл результатов выполнения программы.
	}
	else {
		cout << "\n Ошибка чтения, файл прочитан не был!\n";
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
	cout << "Введите текст\n";
	cout << "Ввод двух пустых строк - прекратить ввод.\n";
	string currentString = "a";//текущая строка, как часть текста
	string previosString = ""; //предыдущая строка, как часть текста
	do {
		previosString = currentString;
		getline(cin, currentString);
		allLines.push_back(currentString);// добавление нового элемента в конец вектора push_back
	} while (currentString != EMPTY_STRING || previosString != EMPTY_STRING);
	allLines.pop_back();// pop_back() — удалить последний элемент
	allLines.pop_back();
	newEntrenceData.text = "";
	for (int j = 0; j < (int)allLines.size(); j++)// количество элементов определяется методом size()
	{
		newEntrenceData.text += allLines[j];
	}
	cout << newEntrenceData.text;
	newEntrenceData.subStringLenth = GetSubstringLenth(newEntrenceData.text.size());
	return newEntrenceData;

}
int GetSubstringLenth(int textSize)//запрос у пользователя длины подстроки
{
	int subStringLenth;
	cout << endl << "Введите количество символов подстроки\n";
	subStringLenth = InputInt32PositiveType();//функция проверяет число на положительность
	while (subStringLenth > textSize / 2) {
		cout << "Длина подстроки не может быть больше длины строки. \nК тому же длина подстроки должна быть как минимум в 2 раза короче самой строки.\nВведите длину подстроки снова.\n";
		subStringLenth = InputInt32Type();
	}
	return subStringLenth;
}
void DisplayFailMenu() {
	cout << "Загрузка текста из файла" << endl;
	cout << "Выберите один из пунктов" << endl;
	cout << "1. Зашифровать текст" << endl;
	cout << "2. Расшифровать текст" << endl;
	cout << "3. Назад" << endl;
	cout << "Ваш выбор: ";
}

/*void File(){
	int choice = 0;
	do {
		cout << endl;
		DisplayFailMenu ();
		switch (choice) {
		case Shifr:
			cout << "Выбор сложности" << endl;
			system("PAUSE");
			break;
		case Rashifr:
			cout << "Выбор звука" << endl;
			system("PAUSE");
			break;
		case BACK:
			break;
		default:
			cout << "Нет такого пункта." << endl;
			system("PAUSE");
			break;
		}
	} while (choice != BACK);
}*/
bool Fail() {
	entrenceData newEntrenceData; //экземпляр структуры, который содержит в себе новые данные для расчетов.
	/*cout << "Загрузка текста из файла" << endl;
	cout << "Выберите один из пунктов" << endl;
	cout << "1. Зашифровать текст" << endl;
	cout << "2. Расшифровать текст" << endl;
	cout << "3. Назад" << endl;
	mainMenuItems programmMode;
	char currentSymbol = 0;//объявление переменной (последний введенный символ)
	while (currentSymbol - FIRST_DIGIT_CODE < FIRST_MENU_ITEM || currentSymbol - FIRST_DIGIT_CODE > LAST_MENU_ITEM) {
		currentSymbol = _getch();
	}
	programmMode = (mainMenuItems) (currentSymbol - FIRST_DIGIT_CODE);//режим работы программы
	switch (programmMode) {
	case Shifr:
		newEntrenceData = UseFileFromData();
		//entrenceData readyData = Compute(newEntrenceData);
		break;
	case Rashifr:
		
		newEntrenceData = UseFileFromData();//для загрузки данных из файла
		break;

	case exitProgram://выход из программы
		return true;
	}
	entrenceData readyData = Compute(newEntrenceData);
	cout << Decode(readyData).text << "Исходный текст" << endl;*/

	return false;
}

