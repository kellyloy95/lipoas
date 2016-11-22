#include <conio.h>
#include <math.h>
#include "enterValues.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
// Фунция для ввода числа типа double
double InputDoubleType() {
	//текущий код клавиши
	int currentKeyCode;
	//код клавиши Enter
	const int ENTER_CODE = 13;
	//код первой цифры
	const int FIRST_DIGIT_CODE = 48;
	//код последней цифры
	const int LAST_DIGIT_CODE = 57;
	//код символа "точка"
	const int POINT_CODE = 46;
	//код символа "минус"
	const int MINUS_CODE = 45;
	//номер первого символа
	const int FIRST_SYMBOL_NUMBER = 1;
	//номер текущего символа
	int currentSymbolNumber = 1;
	//текущее значение числа
	double value = 0;
	//текущее значение знаменателя для получения следующей цифры дробной части
	double pointModeDenominator = 10;
	//показывает, используется ли в числе "точка"
	bool pointMode = false;
	//показывает, произошла ли ошбка при вводе числа
	bool mistakeMode = false;
	//показывает, стоит ли перейти к вводу следующего символа, не выполняя вычислений
	//например, если введена "точка" или введён "минус"
	bool returnMode = false;
	//показывает, используется ли в числе знак "минус"
	bool minusMode = false;
	currentKeyCode = _getche();
	while (currentKeyCode != ENTER_CODE)
	{
		if (currentKeyCode <= LAST_DIGIT_CODE && currentKeyCode >= FIRST_DIGIT_CODE
			|| currentKeyCode >= MINUS_CODE && currentKeyCode <= POINT_CODE)
		{
			if (currentKeyCode == POINT_CODE && pointMode)
			{
				mistakeMode = true;
			}
			if (currentKeyCode == POINT_CODE && !pointMode)
			{
				currentSymbolNumber++;
				pointMode = true;
				returnMode = true;
			}
			if (currentKeyCode == MINUS_CODE && currentSymbolNumber > FIRST_SYMBOL_NUMBER)
			{
				mistakeMode = true;
			}
			if (currentKeyCode == MINUS_CODE && currentSymbolNumber == FIRST_SYMBOL_NUMBER)
			{
				currentSymbolNumber++;
				minusMode = true;
				returnMode = true;
			}
			if (!returnMode)
			{
				if (currentKeyCode <= LAST_DIGIT_CODE &&
					currentKeyCode >= FIRST_DIGIT_CODE)
				{
					value *= 10;
					currentSymbolNumber++;
				}
				if (!minusMode)
				{
					if (!pointMode)
					{
						currentKeyCode -= FIRST_DIGIT_CODE;
						value += double(currentKeyCode);
					}
					else
					{
						value /= 10;
						currentKeyCode -= FIRST_DIGIT_CODE;
						value += double(currentKeyCode) / pointModeDenominator;
						pointModeDenominator *= 10;
					}
				}
				else
				{
					if (!pointMode)
					{
						currentKeyCode -= FIRST_DIGIT_CODE;
						value -= double(currentKeyCode);
					}
					else
					{
						value /= 10;
						currentKeyCode -= FIRST_DIGIT_CODE;
						value -= double(currentKeyCode) / pointModeDenominator;
						pointModeDenominator *= 10;
					}
				}
			}
		}
		else
		{
			mistakeMode = true;
		}
		if (value > LONG_MAX || value < LONG_MIN)
		{
			cout << "\nПревышен допустимый лимит ввода для числа.";
			mistakeMode = true;
		}
		if (mistakeMode)
		{
			cout << "\nПроизошла ошибка при вводе, повторите попытку.\n";
			currentSymbolNumber = FIRST_SYMBOL_NUMBER;
			value = 0;
			pointMode = false;
			pointModeDenominator = 10;
			minusMode = false;
			mistakeMode = false;
		}
		returnMode = false;
		currentKeyCode = _getche();
	}
	cout << endl;
	return value;
}
int InputInt32Type()
{
	//текущий код клавиши
	int currentKeyCode;
	//код клавиши Enter
	const int ENTER_CODE = 13;
	//код первой цифры
	const int FIRST_DIGIT_CODE = 48;
	//код последней цифры
	const int LAST_DIGIT_CODE = 57;
	//код символа "минус"
	const int MINUS_CODE = 45;
	//номер первого символа
	const int FIRST_SYMBOL_NUMBER = 1;
	//номер текущего символа
	int currentSymbolNumber = 1;
	//текущее значение числа
	int value = 0;

	//показывает, произошла ли ошбка при вводе числа
	bool mistakeMode = false;
	//показывает, стоит ли перейти к вводу следующего символа не выполняя вычеслений
	//например если введена "точка" или введён "минус"
	bool returnMode = false;
	//показывает, используется ли в числе знак "минус"
	bool minusMode = false;
	currentKeyCode = _getche();
	while (currentKeyCode != ENTER_CODE)
	{
		if (currentKeyCode <= LAST_DIGIT_CODE && currentKeyCode >= FIRST_DIGIT_CODE
			|| currentKeyCode == MINUS_CODE)
		{

			if (currentKeyCode == MINUS_CODE && currentSymbolNumber > FIRST_SYMBOL_NUMBER)
			{
				mistakeMode = true;
			}
			if (currentKeyCode == MINUS_CODE && currentSymbolNumber == FIRST_SYMBOL_NUMBER)
			{
				currentSymbolNumber++;
				minusMode = true;
				returnMode = true;
			}
			if (!returnMode)
			{
				if (currentKeyCode <= LAST_DIGIT_CODE &&
					currentKeyCode >= FIRST_DIGIT_CODE)
				{
					value *= 10;
					currentSymbolNumber++;
				}
				if (!minusMode)
				{
					currentKeyCode -= FIRST_DIGIT_CODE;
					value += currentKeyCode;
				}
				else
				{
					currentKeyCode -= FIRST_DIGIT_CODE;
					value -= currentKeyCode;
				}
			}
		}
		else
		{
			mistakeMode = true;
		}
		if (value > LONG_MAX || value < LONG_MIN)
		{
			cout << "\nПревышен допустимый лимит ввода для числа.";
			mistakeMode = true;
		}
		if (mistakeMode)
		{
			cout << "\nПроизошла ошибка при вводе, повторите попытку.\n";
			currentSymbolNumber = FIRST_SYMBOL_NUMBER;
			value = 0;
			minusMode = false;
			mistakeMode = false;
		}
		returnMode = false;
		currentKeyCode = _getche();
	}
	cout << endl;
	return value;
}
int InputInt32PositiveType()
{
	int value = 0;
	while (value < 1)
	{
		value = InputInt32Type();
		if (value < 1)
			cout << "Значение должно быть положительным.\n";
	}
	return value;
}