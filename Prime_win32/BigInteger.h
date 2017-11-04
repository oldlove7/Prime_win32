/*
*                       "BigInteger Class"
*
*
* Arbitrary Precision Integer�� ��ǥ�� ��������ϴ�.
* �׷��� Perfect Arbitrary���� ��ġ�� ���߽��ϴ�.
* �ִ� 10^4,294,967,301���� ����, ��� �����մϴ�.
* �̰ͺ��� �� ���� ���ڴ� ���� �� �����ϴ�.
*
*
* #include <iostream>
* #include "BigInteger.h"
* using namespace std;
*
* int main()
* {
*       BigInteger a(123);
*       cout << a * a * a * a * a * a * a << endl;
*       // 425927596977747
* }
*
*
* ���� ���� �⺻ �������� ������ �Ȱ����ϴ�.
*
* int���� �����ϴ� ��� �����ڸ� �����մϴ�.(��Ʈ����, ����Ʈ����, ��Ģ����...)
* �߰������� BigIntger���� ���ڿ��κ��� �ʱ�ȭ�� �����մϴ�.
* 2~36������ ���ڿ��κ��� �ʱ�ȭ �� �� �ֽ��ϴ�.
* ������ ���� ����մϴ�.
*
* BigInteger a("123", 16);
*
* 16���� 123���� �ʱ�ȭ �Ǹ� �̴� 10�������� 291�� �˴ϴ�.
*
*
*
* �� Ŭ������ �Ŀ�, Arbitrary Precision Decimal�� ����� ���� ��밡 �� ���Դϴ�.
* Ŭ������ ó������ ������ ��¥�� 2011�� 7�� 14���̸�
* �� Ŭ������ ���� �߰����� �� ������ �� ���� ��α�
* http://transparenttape.tistory.com/
* ���� ��� �� ���Դϴ�.
* BigInteger�� ����� ���� �� �ڷḦ ���ô� �Ŷ��
* �� ��α׿� �ο����� ���� �÷����� �����Ͻñ� �ٶ��ϴ�.
*
* Ȥ�� ���� ���� ���̺귯���� ����ϸ鼭
* ����, ���׸� �߰��ϼ̴ٸ� ��ü���� ���� ��α׿� ���� �����ֽðų�
* ghwjd111@naver.com Ȥ�� ghwjd111@gmail.com���� ������ �����ֽŴٸ� �����ϰڽ��ϴ�. ^^
*
*
*
*/

#pragma once

#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

#include <string>
#include <string.h>
#include <iostream>

class BigInteger;
typedef BigInteger bigint;

class BigInteger
{
	/*
	* �迭�� ����Ͽ� ���ڸ� ����
	* little endian, 2������ ���
	*
	* �ϳ��� BigInteger����
	* ���ڸ� �����ϴ� ���� �迭,
	* �迭�� ���̸� �����ϴ� unsigned long�� ����,
	* ��ȣ
	* �� �̷�����ֽ��ϴ�.
	*/

public:
	/*
	* Ÿ�� �� ����
	*
	* --Ÿ��--
	*
	* length : ���� ���� Ÿ��, �ڵ��� �������� ���̰��� ������
	* ���ٸ� ������ �����ϴ�. �Լ��� �μ��� �Ѿ�ų� �Լ� ��
	* �������� ���ÿ� ���� ������ �� �ֽ��ϴ�.
	*
	* index : �迭�� ��ȣ ���� Ÿ��, ���� ������ �����ϴ�.
	*
	* blocktype : �迭�� Ÿ��, ���� ������ �����ϴ�.
	*
	* _sign : ��ȣ Ÿ��, ����� ���� �׸��� 0���� �����Ǿ��ֽ��ϴ�.
	*
	*
	* --����--
	*
	* blk : ���������� ���ڰ� ����Ǵ� ���� �迭�Դϴ�.
	*
	* len : �迭�� ���̸� �����ϴ� �����Դϴ�.
	*
	* sign : ������ ��ȣ�� ��Ÿ����.
	*/
	typedef unsigned long length; // ���� ���� Ÿ��

	typedef unsigned long index; // blk�� �迭 ��ȣ ���� Ÿ��

	typedef unsigned long blocktype; // blk�� �迭 Ÿ��

	typedef enum {
		Positive = 1,
		Zero = 0,
		Negative = -1
	} _sign; // ��ȣ, ���, ����, ������ ����

private:
	blocktype *blk; // �������� ���� ���� ����
	length len; // �迭 ����
	_sign sign;




private:
	// ���� c��ŭ blk�� �Ҵ��ϴ� �Լ��Դϴ�.
	void Allocate(length c);
	// ���� c��ŭ ���Ҵ��ϴ� �Լ��Դϴ�.
	// ������ ���� c��ŭ���� ���Ҵ��ϸ�
	// blk�� ���� ��, Allocate �Լ��� ȣ���մϴ�.
	void Reallocate(length c);
	// blk�迭�� ��� ��Ҹ� 0���� ����ϴ�.
	inline void Blkinit();
	// blk�迭�� �����մϴ�.
	inline void Blkcopy(const BigInteger &x);
	// 0���� �ʱ�ȭ�ϱ� ���� ����մϴ�.
	inline void SetZero();
	// blk�� ���� ��, 0���� �ʱ�ȭ �մϴ�.
	inline void Reset();

	/*
	* ���� �������� blk�� �Ҵ� �� ��ŭ ���� ���� �� �ֽ��ϴ�.
	* �׷� ��� zapLeadingZeros �Լ��� ȣ���Ͽ�
	* len�� ���̸� ���Դϴ�.
	*/
	inline void ZapLeadingZeros();
public:
	/*
	* �⺻ �����ڴ� 0�� ����� ������ ����
	* 0�� ������ ���� ����
	*	 len = 0
	*	 blk = NULL
	*	 sign = Zero
	*/
	BigInteger();
	~BigInteger();
	BigInteger(const BigInteger &x);
	// ���� ������ ��� Ÿ�����κ��� ������ �����մϴ�.
	BigInteger & operator =(const BigInteger &x);


private:
	// ConversionAssist1�� unsigned���κ��� ������ ���
	template <typename PRI>
	void ConversionAssist1(PRI x);
	template <>
	void ConversionAssist1<unsigned long long>(unsigned long long x);

	// ConversionAssist2�� signed���κ��� ������ ���
	template <typename PRI>
	void ConversionAssist2(PRI x);
	template <>
	void ConversionAssist2<long long>(long long x);
public:
	// bool�� �� ���������κ��� ������ �����մϴ�.
	// float, double�������� ������ �������� �ʽ��ϴ�.
	BigInteger(          bool    x);
	BigInteger(unsigned  char    x);
	BigInteger(          char    x);
	BigInteger(unsigned  short   x);
	BigInteger(          short   x);
	BigInteger(unsigned  long    x);
	BigInteger(          long    x);
	BigInteger(unsigned  int     x);
	BigInteger(          int     x);
	BigInteger(unsigned  __int64 x);
	BigInteger(          __int64 x);

private:
	// ConversionAssist3�� unsigned���� ��ȯ�� ���
	template<typename PRI>
	const PRI ConversionAssist3() const;
	template <>
	const unsigned long long
		ConversionAssist3<unsigned long long>() const;

	// ConversionAssist4�� signed���� ��ȯ�� ���
	template<typename PRI>
	const PRI ConversionAssist4() const;
	template <>
	const long long
		ConversionAssist4<long long>() const;
public:
	operator          bool   () const;
	operator unsigned char   () const;
	operator          char   () const;
	operator unsigned short  () const;
	operator          short  () const;
	operator unsigned long   () const;
	operator          long   () const;
	operator unsigned int    () const;
	operator          int    () const;
	operator unsigned __int64() const;
	operator          __int64() const;

private:
	void DoubleDabble(BigInteger &dest, int radix) const;
	void DD_Odd(BigInteger &dest, int radix) const;
public:
	// char �� �迭, string���� ���� ���� �����մϴ�.
	explicit BigInteger(const char *str, int radix = 10);
	explicit BigInteger(const std::string &str, int radix = 10);
	// string�� BigInteger������ �ٲٴ� �Լ��Դϴ�.
	const BigInteger & stob(const std::string &str, int radix = 10);
	// BigInteger���� string���� �ٲߴϴ�.
	const std::string btos(int radix = 10) const;
	// ǥ�� �� ��� �Լ��� �����ε� �Ͽ�
	// �Ϲ� ������ó�� �� ��� �� �� �ֽ��ϴ�.
	// ��, 10���������� �Է�, ����մϴ�.
	friend std::ostream & operator <<(std::ostream &os, const BigInteger &x);
	// ���� �������� ����մϴ�.
	void print(int radix = 10) const;
	friend std::istream & operator >>(std::istream &is, BigInteger &x);
#pragma endregion
#pragma endregion

	/*
	*			������ ������(this, x)
	*
	*		1. �ּҰ� ������ �ٸ��� ?
	*			��. ���� ��� - (ó��)
	*			��. �ٸ� ��� - (��������)
	*		2. ��ȣ�� ������ �ٸ��� ?
	*			��. Zero ����
	*				a. �� �� 0 - (ó��)
	*				b. this�� 0 - (ó��)
	*				c. x�� 0 - (ó��)
	*			��. �� ���� ��ȣ�� �ٸ� ��� - (ó��)
	*			��. ��ȣ�� ���� ���� ��� - (��������)
	*		3. ���̰� ������ �ٸ��� ?
	*			��. �ٸ� ��� - (ó��)
	*			��. ���� ��� - (��������)
	*		4. �� �� ��� ó��
	*
	*		���꿡 ����
	*		�Ϻδ� ���� ���� Ȥ�� �ٲ� �� ����
	*/

#pragma region �񱳿���
public:
	const _sign getsign() const; // ��ȣ ����

	// ũ�⸦ ���մϴ�.
	const int compare(const BigInteger &x) const;

	// �� ������ �����ε� �Դϴ�.
	// BigInteger���� BigInteger���� ��
	// BigInteger���� �������� ��.. ��
	// �Ϲ� ������ó�� ��� �����մϴ�.
	bool operator ==(const BigInteger &x) const;
	bool operator !=(const BigInteger &x) const;
	bool operator > (const BigInteger &x) const;
	bool operator >=(const BigInteger &x) const;
	bool operator < (const BigInteger &x) const;
	bool operator <=(const BigInteger &x) const;

	template <typename X> bool operator ==(const X &x) const;
	template <typename X> bool operator !=(const X &x) const;
	template <typename X> bool operator > (const X &x) const;
	template <typename X> bool operator >=(const X &x) const;
	template <typename X> bool operator < (const X &x) const;
	template <typename X> bool operator <=(const X &x) const;

	template <typename X> friend bool operator ==(const X &x, const BigInteger &y);
	template <typename X> friend bool operator !=(const X &x, const BigInteger &y);
	template <typename X> friend bool operator > (const X &x, const BigInteger &y);
	template <typename X> friend bool operator >=(const X &x, const BigInteger &y);
	template <typename X> friend bool operator < (const X &x, const BigInteger &y);
	template <typename X> friend bool operator <=(const X &x, const BigInteger &y);

#pragma endregion

#pragma region ��Ʈ����
public:
	unsigned __int64 bitlength() const;
	length blklength() const;
	/*
	*		P : Positive
	*		N : Negative
	*		Z : Zero
	*
	*
	*        a     b   ||   &    |    ^
	*       ------------------------------
	*        P     P   ||   P    P    P
	*        P     N   ||   P    N    N
	*        N     P   ||   P    N    N
	*        N     N   ||   N    N    P
	*
	*		'&' ����� '^' ������ Z�� ���� ���ɼ��� �ֽ��ϴ�.
	*/

	const BigInteger   operator & (const BigInteger &x) const;
	const BigInteger & operator &=(const BigInteger &x);
	const BigInteger   operator | (const BigInteger &x) const;
	const BigInteger & operator |=(const BigInteger &x);
	const BigInteger   operator ^ (const BigInteger &x) const;
	const BigInteger & operator ^=(const BigInteger &x);
	const BigInteger   operator ~ () const;
	template <typename X> const BigInteger operator & (const X &x) const;
	template <typename X> const BigInteger operator | (const X &x) const;
	template <typename X> const BigInteger operator ^ (const X &x) const;
	template <typename X> const BigInteger operator &=(const X &x);
	template <typename X> const BigInteger operator |=(const X &x);
	template <typename X> const BigInteger operator ^=(const X &x);
	template <typename X> friend const BigInteger operator & (const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator | (const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator ^ (const X &x, const BigInteger &y);
	template <typename X> friend const X & operator &=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator |=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator ^=(X &x, const BigInteger &y);
#pragma endregion

#pragma region ����Ʈ����
private:
	// ��� ������ ����Ʈ �ϴ� �����Լ��Դϴ�.
	const blocktype Get_LShiftedBlock(index x, length n) const;
public:
	const BigInteger   operator << (int leftmove)  const;
	const BigInteger & operator <<=(int leftmove);
	const BigInteger   operator >> (int rightmove) const;
	const BigInteger & operator >>=(int rightmove);
#pragma endregion

#pragma region ��Ģ/������/����
private:
	void add(const BigInteger &Left, const BigInteger &Right);
	void subtract (const BigInteger &Left, const BigInteger &Right);
	void multiply(const BigInteger &Left, const BigInteger &Right);
	void divideWithRemainder(const BigInteger &Divisor, BigInteger &Quotient);
public:
	// +, -, *, /, %
	// +=, -=, *=, /=, %=
	// -(���׿�����), abs�Լ�
	// ++, --
	// ���� �����մϴ�.
	const BigInteger   operator - () const;
	friend const BigInteger abs(const BigInteger &x);
	const BigInteger add(const BigInteger &x) const;
	const BigInteger   operator + (const BigInteger &x) const;
	const BigInteger & operator +=(const BigInteger &x);
	const BigInteger subtract(const BigInteger &x) const;
	const BigInteger   operator - (const BigInteger &x) const;
	const BigInteger & operator -=(const BigInteger &x);
	const BigInteger multiply(const BigInteger &x) const;
	const BigInteger   operator * (const BigInteger &x) const;
	const BigInteger & operator *=(const BigInteger &x);
	const BigInteger divide(const BigInteger &x) const;
	const BigInteger mod(const BigInteger &x) const;
	const BigInteger   operator / (const BigInteger &x) const;
	const BigInteger   operator % (const BigInteger &x) const;
	const BigInteger & operator /=(const BigInteger &x);
	const BigInteger & operator %=(const BigInteger &x);

	template <typename X> const BigInteger operator +(const X &x) const;
	template <typename X> const BigInteger operator -(const X &x) const;
	template <typename X> const BigInteger operator *(const X &x) const;
	template <typename X> const BigInteger operator /(const X &x) const;
	template <typename X> const BigInteger operator %(const X &x) const;

	template <typename X> friend const BigInteger operator +(const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator -(const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator *(const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator /(const X &x, const BigInteger &y);
	template <typename X> friend const BigInteger operator %(const X &x, const BigInteger &y);

	template <typename X> const BigInteger & operator +=(const X &x);
	template <typename X> const BigInteger & operator -=(const X &x);
	template <typename X> const BigInteger & operator *=(const X &x);
	template <typename X> const BigInteger & operator /=(const X &x);
	template <typename X> const BigInteger & operator %=(const X &x);

	template <typename X> friend const X & operator +=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator -=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator *=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator /=(X &x, const BigInteger &y);
	template <typename X> friend const X & operator %=(X &x, const BigInteger &y);

private:
	void PlusOne();
	void MinusOne();
public:
	BigInteger & operator ++();
	const BigInteger operator ++(int dummy);
	BigInteger & operator --();
	const BigInteger operator --(int dummy);
#pragma endregion

#pragma region ��Ÿ����
	// �ŵ�����
	friend BigInteger pow(const BigInteger &x, const BigInteger &y);
	template <typename X> BigInteger pow(const BigInteger &x, const X &y);
	template <typename X> BigInteger pow(const X &x, const BigInteger &y);
	// ���丮��
	friend BigInteger factorial(const BigInteger &x);
	// �ִ�����
	friend BigInteger gcd(BigInteger x, BigInteger y);
	template <typename X> BigInteger gcd(BigInteger x, X y);
	template <typename X> BigInteger gcd(X x, BigInteger y);
	// �ּҰ����
	friend BigInteger lcm(BigInteger x,BigInteger y);
	template <typename X> BigInteger lcm(BigInteger x, X y);
	template <typename X> BigInteger lcm(X x, BigInteger y);
#pragma endregion
};

#pragma region ���ø�����
#pragma  region ����/��ȯ-����
template <typename PRI>
void BigInteger::ConversionAssist1(PRI x)
{
	if (x != 0)
	{
		Allocate(1);
		blk[0] = blocktype(x);
		sign = Positive;
	}
	else
	{
		SetZero();
	}
}
template <>
void BigInteger::ConversionAssist1<unsigned long long>(unsigned long long x)
{
	// 0 ó��
	if (x == 0)
	{
		SetZero();
		return;
	}

	if ( (x >> 32) == 0 ) // ���� 32��Ʈ�� ����ִٸ�
	{
		Allocate(1);
	}
	else // ���� 32��Ʈ�� ���ڰ� �ִٸ�
	{
		Allocate(2);
		blk[1] = blocktype(x >> 32); // x�� ���� 32��Ʈ ����
	}
	blk[0] = blocktype(x); // x�� ���� 32��Ʈ ����
	sign = Positive;
}
template <typename PRI>
void BigInteger::ConversionAssist2(PRI x)
{
	if (x != 0)
	{
		Allocate(1);
		if (x > 0)
		{
			blk[0] = blocktype(x);
			sign = Positive;
		}
		else if (x < 0)
		{
			blk[0] = blocktype(-x);
			sign = Negative;
		}
	}
	else
	{
		SetZero();
	}

}
template <>
void BigInteger::ConversionAssist2<long long>(long long x)
{
	// 0 ó��
	if (x == 0)
	{
		SetZero();
		return;
	}

	bool isminus = false;
	if (x < 0)
	{
		isminus = true;
		x = -x;
	}
	if ( (x >> 32) == 0 ) // ���� 32��Ʈ�� ����ִٸ�
	{
		Allocate(1);
	}
	else // ���� 32��Ʈ�� ���ڰ� �ִٸ�
	{
		Allocate(2);
		blk[1] = blocktype(x >> 32); // x�� ���� 32��Ʈ ����
	}
	blk[0] = blocktype(x); // x�� ���� 32��Ʈ ����
	sign = (isminus == true) ? Negative : Positive;
}
template <typename PRI>
const PRI BigInteger::ConversionAssist3() const
{
	if (sign == Negative)
	{
#if defined(_DEBUG)
		throw "������ Unsigned�� �ٲ� �� �����ϴ�.";
#else
		return PRI(0);
#endif
	}

	if (len == 0)
		return PRI(0);
#ifdef _DEBUG
	if (len == 1)
#endif
	{
		PRI x = PRI(blk[0]);
		if (blocktype(x) == blk[0])
			return x;
	}

#ifdef _DEBUG
	throw "���� �ʹ� Ŀ�� ��ȯ �� �� �����ϴ�.";
#else
	return PRI(0);
#endif
}
template <>
const unsigned long long BigInteger::ConversionAssist3<unsigned long long>() const
{
	unsigned long long x = 0;
	if (sign == Zero)
		return x;
	else if (sign == Negative)
	{
#if defined(_DEBUG)
		throw "������ Unsigned�� �ٲ� �� �����ϴ�.";
#else
		return x;
#endif
	}
	else if (len <= 2)
	{
		x = blk[0];
		if (len == 1) return x;
		x += unsigned long long(blk[1]) << 32;
		return x;
	}
#if defined(_DEBUG)
	throw "���� �ʹ� Ŀ�� ��ȯ �� �� �����ϴ�.";
#else
	return x;
#endif
}
template <typename PRI>
const PRI BigInteger::ConversionAssist4() const
{
	/*
	* blk[0]�� �ְ� ��Ʈ�� 1�� ���,
	* ��ȯ������ ���ڸ� ������ �ν��ϴ� ������ �����.
	* ����, ���ʿ� �̷� ��ȯ�� �����Ѵ�.
	*/
	if (len == 0)
		return PRI(0);

#ifdef _DEBUG
	if (len == 1 && !(blk[0] >> 31) )
	{
#endif
		PRI x = PRI(blk[0]);
		if (blocktype(x) == blk[0])
			return (sign == Positive) ? x : -x;
#ifdef _DEBUG
	}
#endif

#ifdef _DEBUG
	throw "���� �ʹ� Ŀ�� ��ȯ �� �� �����ϴ�.";
#else
	return PRI(0);
#endif
}
template <>
const long long BigInteger::ConversionAssist4<long long>() const
{
	long long x = 0;
	if (sign == Zero)
		return x;
	else if (len <= 2)
	{
		x = blk[0];
		if (len == 2 && !(blk[1] >> 31) )
			x += long long(blk[1]) << 32;
	}

#if defined(_DEBUG)
	else
	{
		throw "���� �ʹ� Ŀ�� ��ȯ �� �� �����ϴ�.";
	}
#endif
	return (sign == Positive) ? x : -x;
}
#pragma  endregion

#pragma region �񱳿���-����
template <typename X> bool BigInteger::operator ==(const X &x) const {return *this == (BigInteger(x));}
template <typename X> bool BigInteger::operator !=(const X &x) const {return *this != (BigInteger(x));}
template <typename X> bool BigInteger::operator > (const X &x) const {return *this >  (BigInteger(x));}
template <typename X> bool BigInteger::operator >=(const X &x) const {return *this >= (BigInteger(x));}
template <typename X> bool BigInteger::operator < (const X &x) const {return *this <  (BigInteger(x));}
template <typename X> bool BigInteger::operator <=(const X &x) const {return *this <= (BigInteger(x));}

template <typename X>bool operator ==(const X &x, const BigInteger &y) { return BigInteger(x) == y; }
template <typename X>bool operator !=(const X &x, const BigInteger &y) { return BigInteger(x) != y; }
template <typename X>bool operator > (const X &x, const BigInteger &y) { return BigInteger(x) >  y; }
template <typename X>bool operator >=(const X &x, const BigInteger &y) { return BigInteger(x) >= y; }
template <typename X>bool operator < (const X &x, const BigInteger &y) { return BigInteger(x) <  y; }
template <typename X>bool operator <=(const X &x, const BigInteger &y) { return BigInteger(x) <= y; }
#pragma endregion

#pragma region ��Ʈ����-����
template <typename X>
const BigInteger BigInteger::operator & (const X &x) const {return *this & BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator | (const X &x) const {return *this | BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator ^ (const X &x) const {return *this ^ BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator &=(const X &x) {return *this = *this & BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator |=(const X &x) {return *this = *this | BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator ^=(const X &x) {return *this = *this ^ BigInteger(x); }
template <typename X>
const BigInteger operator & (const X &x, const BigInteger &y) { return BigInteger(x) & y; }
template <typename X>
const BigInteger operator | (const X &x, const BigInteger &y) { return BigInteger(x) | y; }
template <typename X>
const BigInteger operator ^ (const X &x, const BigInteger &y) { return BigInteger(x) ^ y; }
template <typename X>
const X & operator &=(X &x, const BigInteger &y) {return x = x & y;}
template <typename X>
const X & operator |=(X &x, const BigInteger &y) {return x = x | y;}
template <typename X>
const X & operator ^=(X &x, const BigInteger &y) {return x = x ^ y;}
#pragma endregion

#pragma region ��Ģ/������/��������-����
template <typename X>
const BigInteger BigInteger::operator +(const X &x) const { return *this + BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator -(const X &x) const { return *this - BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator *(const X &x) const { return *this * BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator /(const X &x) const { return *this / BigInteger(x); }
template <typename X>
const BigInteger BigInteger::operator %(const X &x) const { return *this % BigInteger(x); }
// y == BigInteger(x)�� �ϸ� ���� ���ȣ�� �߻�!!!
template <typename X>
const BigInteger operator +(const X &x, const BigInteger &y) { return BigInteger(x) + y; }
template <typename X>
const BigInteger operator -(const X &x, const BigInteger &y) { return BigInteger(x) - y; }
template <typename X>
const BigInteger operator *(const X &x, const BigInteger &y) { return BigInteger(x) * y; }
template <typename X>
const BigInteger operator /(const X &x, const BigInteger &y) { return BigInteger(x) / y; }
template <typename X>
const BigInteger operator %(const X &x, const BigInteger &y) { return BigInteger(x) % y; }
template <typename X> const BigInteger & BigInteger::operator +=(const X &x) { return *this = *this + BigInteger(x); }
template <typename X> const BigInteger & BigInteger::operator -=(const X &x) { return *this = *this - BigInteger(x); }
template <typename X> const BigInteger & BigInteger::operator *=(const X &x) { return *this = *this * BigInteger(x); }
template <typename X> const BigInteger & BigInteger::operator /=(const X &x) { return *this = *this / BigInteger(x); }
template <typename X> const BigInteger & BigInteger::operator %=(const X &x) { return *this = *this % BigInteger(x); }
template <typename X> const X & operator +=(X &x, const BigInteger &y) {return x = x + y;}
template <typename X> const X & operator -=(X &x, const BigInteger &y) {return x = x - y;}
template <typename X> const X & operator *=(X &x, const BigInteger &y) {return x = x * y;}
template <typename X> const X & operator /=(X &x, const BigInteger &y) {return x = x / y;}
template <typename X> const X & operator %=(X &x, const BigInteger &y) {return x = x % y;}
#pragma endregion

#pragma region //��Ÿ����-����
template <typename X> BigInteger pow(const BigInteger &x, const X &y){return pow(x, BigInteger(y));}
template <typename X> BigInteger pow(const X &x, const BigInteger &y){return pow(BigInteger(x), y);}
template <typename X> BigInteger gcd(BigInteger x, X y) {return gcd(x, BigInteger(y));}
template <typename X> BigInteger gcd(X x, BigInteger y) {return gcd(BigInteger(x), y);}
template <typename X> BigInteger lcm(BigInteger x, X y) {return lcm(x, BigInteger(y));}
template <typename X> BigInteger lcm(X x, BigInteger y) {return lcm(BigInteger(x), y);}
#pragma endregion

#pragma endregion

#endif /* _BIGINTEGER_H_ */
