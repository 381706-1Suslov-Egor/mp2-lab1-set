// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw len;
	bitlength = len;
	length = (bitlength + 1) / (sizeof(TELEM) * 8) + 1;
	m = new TELEM[length];
	for (int i = 0; i < length; i++)
		m[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	bitlength = bf.bitlength;
	length = bf.length;
	m = new TELEM[length];
	for (int i = 0; i < length; i++)
		m[i] = bf.m[i];
}

TBitField::~TBitField()
{
	delete m;
	m = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitlength;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw n;
	if (n >= bitlength) throw n;
	m[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw n;
	if (n >= bitlength) throw n;
	m[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw n;
	if (n >= bitlength) throw n;
	if ((m[GetMemIndex(n)] & GetMemMask(n)) != 0) return 1;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete m;
	length = bf.length;
	bitlength = bf.bitlength;
	m = new TELEM[length];
	for (int i = 0; i < length; i++)
		m[i] = bf.m[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (bitlength != bf.bitlength)
		return 0;
	for (int i = 0; i < length; i++)
		if (m[i] != bf.m[i])
			return 0;

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (operator ==(bf) == 1) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max = bitlength;
	if (bitlength < bf.bitlength) max = bf.bitlength;
	TBitField tmp(max);
	for (int i = 0; i < tmp.length; i++)
		tmp.m[i] = m[i] | bf.m[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max = bitlength;
	int min_ml = length;
	if (bitlength < bf.bitlength) max = bf.bitlength;
	if (length > bf.length) min_ml = bf.length;
	TBitField tmp(max);
	for (int i = 0; i < min_ml; i++)
		tmp.m[i] = m[i] & bf.m[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < length; i++)
		tmp.m[i] = ~m[i];
	TELEM mask = 0;
	for (unsigned int i = 0; i < bitlength % (sizeof(TELEM) * 8); i++)
	{
		mask = mask << 1;
		mask += 1;
	}
	tmp.m[length - 1] &= mask;
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char vvod;
	int i = 0;
	istr >> vvod;
	while ((vvod == '1') || (vvod == '0'))
	{
		switch (vvod)
		{
		case '1': bf.SetBit(i);
			break;
		case '0': bf.ClrBit(i);
			break;
		default:
		{
			cout << "Wrong";
		}
		break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitlength; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
