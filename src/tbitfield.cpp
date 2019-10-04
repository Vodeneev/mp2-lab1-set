// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string.h>

TBitField::TBitField(int len)
{
	if (len < 0)
		throw 1;
	BitLen = len;
	MemLen = (BitLen-1) / (sizeof(TELEM)*8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}



TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if(pMem != 0)
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw 1;
	return TELEM(1) <<( n % (sizeof(TELEM) * 8)); // побитовый сдвиг на нужное нам число,в нужный блок
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= BitLen) || (n < 0))
		throw 1;
	
	pMem[n/(sizeof(TELEM) * 8)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || n >= BitLen)
		throw 1;
	pMem[n / (sizeof(TELEM) * 8)] &=  ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || (n < 0))
		throw 1;
  return (pMem[n/ (sizeof(TELEM) * 8)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		if (pMem != NULL) delete[] pMem;
		pMem = new TELEM[MemLen];

	}
	if(pMem!=NULL)
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else {
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) {
				res = 0;
				break;
			}
	}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}


TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{

	if (bf.BitLen < BitLen) {
		TBitField res(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
		{
			res.pMem[i] = pMem[i] | bf.pMem[i];
		}
		return res;
	}
	else {
		TBitField res(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			res.pMem[i] = pMem[i] | bf.pMem[i];
		}
		return res;
	}

	}



TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (bf.BitLen < BitLen) {
		TBitField res(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
		{
			res.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return res;
	}
	else {
		TBitField res(bf.BitLen);
		res.MemLen = MemLen;
		for (int i = 0; i < MemLen; i++)
		{
			res.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return res;
	}

}


TBitField TBitField::operator~(void) // отрицание
{

	TBitField res(*this);

	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}

	if (res.BitLen % (sizeof(TELEM) * 8)  != 0)
	{
		TELEM x = 1;

		for (int i = 0; i < res.BitLen % (sizeof(TELEM) * 8) - 1; i++)
		{
			x = x << 1;
			x += 1;
		}

		res.pMem[MemLen - 1] = res.pMem[MemLen - 1] & x;
	}

	return res;
	}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string a;
	istr >> a;
	TBitField res(a.size());
	for (int i = 0; i < res.GetLength();i++) {
		if (a[i] == '1') {
			bf.SetBit(i);
		}
		else {
			bf.ClrBit(i);
		}
	}
	res = bf;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.GetBit(i);
	}

	return ostr;
}
