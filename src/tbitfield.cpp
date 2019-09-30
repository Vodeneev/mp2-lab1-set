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
	MemLen = BitLen / (sizeof(TELEM)*8) + 1;
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
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 <<( n % (sizeof(TELEM) * 8)); // побитовый сдвиг на нужное нам число,в нужный блок
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	
pMem[n% (sizeof(TELEM) * 8)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[n % (sizeof(TELEM) * 8)] &=  ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[n % (sizeof(TELEM) * 8)] & GetMemMask(n) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	
	if (BitLen != bf.BitLen)
		return 0;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]);
				return 0;
			
		}
		return 1;
	}
	}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
return 1;
else {
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 1;

	}
	return 0;
}
	}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		~pMem[i];
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string a;
	cin >> a;
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
		cout << bf.GetBit(i);
	}

	return ostr;
}
