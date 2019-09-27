// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / 32 + 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = sizeof(bf);
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.GetMemIndex(i);
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << n % 32); // побитовый сдвиг на нужное нам число,в нужный блок
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	
pMem[n%32] = pMem[n % 32] || this->GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[n % 32] = pMem[n % 32] || ~(this->GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[n % 32] & this->GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.GetLength();
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.GetMemIndex(i);
	}
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int n;
	n = bf.GetLength();
	if (n != MemLen) 
		return 0;
	else {
		for (int i = 0; i < n; i++) {
			if (pMem[i] != bf.GetMemIndex(i))
				return 0;
			
		}
		return 1;
	}
	}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
int n;
n = bf.GetLength();
if (n != MemLen)
return 1;
else {
	for (int i = 0; i < n; i++) {
		if (pMem[i] != bf.GetMemIndex(i))
			return 1;

	}
	return 0;
}
	}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
