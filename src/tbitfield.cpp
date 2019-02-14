// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "Len isn't correct";
	bitLen = len;
	int size = sizeof(uInt) * 8;
	memLen = bitLen / size + 1;
	pMem = new uInt[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new uInt[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(uInt) * 8);
}

uInt TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(uInt) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitLen;
}





void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= bitLen)
		throw 1;
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > bitLen)
		throw "index isn't correct";
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > bitLen)
		throw "index isn't correct";
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n % (sizeof(uInt) * 8));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	pMem = NULL;
	delete[] pMem;
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new uInt[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bitLen != bf.bitLen)
		return 0;
	for (int i = 0; i < memLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bitLen != bf.bitLen)
		return 1;
	for (int i = 0; i < memLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	if (bitLen < bf.bitLen)
		len = bf.bitLen;
	else
		len = bitLen;
	TBitField result(len);
	for (int i = 0; i < result.memLen; i++)
		result.pMem[i] = pMem[i] | bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	if (bitLen < bf.bitLen)
		len = bf.bitLen;
	else
		len = bitLen;
	TBitField result(len);
	for (int i = 0; i < result.memLen; i++)
		result.pMem[i] = pMem[i] & bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(bitLen);
	for (int i = 0; i < bitLen; i++)
		if (GetBit(i) == 0)
			result.SetBit(i);
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string str;
	istr >> str;
	if (str.size() != bf.GetLength())
		throw "exception";
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (str[i] == '0')
			bf.ClrBit(i);
		else if (str[i] == '1')
			bf.SetBit(i);
		else
			throw "exception";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << "[";
	for (int i = bf.GetLength(); i > 0; i--)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else
			ostr << 0;
	}
	ostr << "]";
	return ostr;
}
