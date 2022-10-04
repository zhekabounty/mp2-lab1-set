// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) {
        throw len;
    }
    else {
        BitLen = len;
        MemLen = (BitLen + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8);
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    pMem = nullptr;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw n;
    }
    else {
        return n / (sizeof(TELEM) * 8);
    }
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw n;
    }
    else {
        return 1 << (n % (sizeof(TELEM) * 8));
    }
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw n;
    }
    else {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw n;
    }
    else {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen)) {
        throw n;
    }
    else {
        return pMem[GetMemIndex(n)] & GetMemMask(n);
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf) {
        return *this;
    }
    if (pMem != NULL)
        delete[] pMem;
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
    if (BitLen != bf.BitLen) {
        return 0;
    }
    else {
        for (int i = 0; i < BitLen; i++) {
            if (GetBit(i) != bf.GetBit(i)) {
                return 0;
            }
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int NewBitLen;
    if (BitLen > bf.BitLen)
    {
        NewBitLen = BitLen;
    }
    else {
        NewBitLen = bf.BitLen;
    }
    TBitField newbf(NewBitLen);
    for (int i = 0; i < MemLen; i++) {
        newbf.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        newbf.pMem[i] |= bf.pMem[i];
    }
    return newbf;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int NewBitLen;
    if (BitLen > bf.BitLen)
    {
        NewBitLen = BitLen;
    }
    else {
        NewBitLen = bf.BitLen;
    }
    TBitField newbf(NewBitLen);
    for (int i = 0; i < MemLen; i++) {
        newbf.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        newbf.pMem[i] &= bf.pMem[i];
    }
    return newbf;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField newbf(BitLen);
    for (int i = 0; i < MemLen; i++) {
        newbf.pMem[i] = ~pMem[i];
    }
    return newbf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{

    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    return ostr;
}
