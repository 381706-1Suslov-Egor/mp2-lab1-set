// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"



TSet::TSet(int mp) : bitField(mp), maxPower(mp)
{

}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField), maxPower(s.maxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf), maxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return bitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	//   if(this == &s)
	// 	return *this;
	maxPower = s.maxPower;
	bitField = s.bitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (maxPower != s.maxPower)
		return 0;
	if (bitField != s.bitField)
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (maxPower != s.maxPower)
		return 1;
	if (bitField != s.bitField)
		return 1;
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	if (this == &s)
		return *this;
	if (maxPower >= s.maxPower)
	{
		TSet result(maxPower);
		result.bitField = bitField | s.bitField;
		return result;
	}
	else
	{
		TSet result(s.maxPower);
		result.bitField = bitField | s.bitField;
		return result;
	}
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem < maxPower) || (Elem > -1))
	{
		TSet result(bitField);
		result.bitField.SetBit(Elem);
		return result;
	}
	else
		return 1;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < maxPower) || (Elem > -1))
	{
		TSet result(bitField);
		result.bitField.ClrBit(Elem);
		return result;
	}
	else
		return 1;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (this == &s)
		return *this;
	if (maxPower >= s.maxPower)
	{
		TSet result(maxPower);
		result.bitField = bitField & s.bitField;
		return result;
	}
	else
	{
		TSet result(s.maxPower);
		result.bitField = bitField & s.bitField;
		return result;
	}
}

TSet TSet::operator~(void) // дополнение
{
	TSet A(maxPower);
	A.bitField = ~bitField;
	return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	cin >> i;
	for (; ((i > -1) && (i < s.maxPower)); cin >> i)
		s.bitField.SetBit(i);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.bitField << ' ';
	return ostr;
}