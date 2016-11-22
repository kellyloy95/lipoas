#include <conio.h>
#include <math.h>
#include "enterValues.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
// ������ ��� ����� ����� ���� double
double InputDoubleType() {
	//������� ��� �������
	int currentKeyCode;
	//��� ������� Enter
	const int ENTER_CODE = 13;
	//��� ������ �����
	const int FIRST_DIGIT_CODE = 48;
	//��� ��������� �����
	const int LAST_DIGIT_CODE = 57;
	//��� ������� "�����"
	const int POINT_CODE = 46;
	//��� ������� "�����"
	const int MINUS_CODE = 45;
	//����� ������� �������
	const int FIRST_SYMBOL_NUMBER = 1;
	//����� �������� �������
	int currentSymbolNumber = 1;
	//������� �������� �����
	double value = 0;
	//������� �������� ����������� ��� ��������� ��������� ����� ������� �����
	double pointModeDenominator = 10;
	//����������, ������������ �� � ����� "�����"
	bool pointMode = false;
	//����������, ��������� �� ����� ��� ����� �����
	bool mistakeMode = false;
	//����������, ����� �� ������� � ����� ���������� �������, �� �������� ����������
	//��������, ���� ������� "�����" ��� ����� "�����"
	bool returnMode = false;
	//����������, ������������ �� � ����� ���� "�����"
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
			cout << "\n�������� ���������� ����� ����� ��� �����.";
			mistakeMode = true;
		}
		if (mistakeMode)
		{
			cout << "\n��������� ������ ��� �����, ��������� �������.\n";
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
	//������� ��� �������
	int currentKeyCode;
	//��� ������� Enter
	const int ENTER_CODE = 13;
	//��� ������ �����
	const int FIRST_DIGIT_CODE = 48;
	//��� ��������� �����
	const int LAST_DIGIT_CODE = 57;
	//��� ������� "�����"
	const int MINUS_CODE = 45;
	//����� ������� �������
	const int FIRST_SYMBOL_NUMBER = 1;
	//����� �������� �������
	int currentSymbolNumber = 1;
	//������� �������� �����
	int value = 0;

	//����������, ��������� �� ����� ��� ����� �����
	bool mistakeMode = false;
	//����������, ����� �� ������� � ����� ���������� ������� �� �������� ����������
	//�������� ���� ������� "�����" ��� ����� "�����"
	bool returnMode = false;
	//����������, ������������ �� � ����� ���� "�����"
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
			cout << "\n�������� ���������� ����� ����� ��� �����.";
			mistakeMode = true;
		}
		if (mistakeMode)
		{
			cout << "\n��������� ������ ��� �����, ��������� �������.\n";
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
			cout << "�������� ������ ���� �������������.\n";
	}
	return value;
}