/*
*                       "BigInteger Class"
*
*
* Arbitrary Precision Integer를 목표로 만들었습니다.
* 그러나 Perfect Arbitrary에는 미치지 못했습니다.
* 최대 10^4,294,967,301까지 생성, 출력 가능합니다.
* 이것보다 더 높은 숫자는 만들 수 없습니다.
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
* 위와 같이 기본 정수형과 사용법이 똑같습니다.
*
* int형이 지원하는 모든 연산자를 지원합니다.(비트연산, 쉬프트연산, 사칙연산...)
* 추가적으로 BigIntger형은 문자열로부터 초기화가 가능합니다.
* 2~36진법의 문자열로부터 초기화 할 수 있습니다.
* 다음과 같이 사용합니다.
*
* BigInteger a("123", 16);
*
* 16진법 123으로 초기화 되며 이는 10진법으로 291이 됩니다.
*
*
*
* 이 클래스는 후에, Arbitrary Precision Decimal를 만들기 위한 토대가 될 것입니다.
* 클래스를 처음으로 배포한 날짜는 2011년 7월 14일이며
* 이 클래스에 대한 추가설명 및 배포는 제 개인 블로그
* http://transparenttape.tistory.com/
* 에서 계속 할 것입니다.
* BigInteger를 만들기 위해 이 자료를 보시는 거라면
* 제 블로그에 부연설명 글을 올렸으니 참고하시기 바랍니다.
*
* 혹시 제가 만든 라이브러리를 사용하면서
* 오류, 버그를 발견하셨다면 지체없이 위의 블로그에 글을 남겨주시거나
* ghwjd111@naver.com 혹은 ghwjd111@gmail.com으로 메일을 보내주신다면 감사하겠습니다. ^^
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
	* 배열을 사용하여 숫자를 저장
	* little endian, 2진법을 사용
	*
	* 하나의 BigInteger형은
	* 숫자를 저장하는 동적 배열,
	* 배열의 길이를 저장하는 unsigned long형 변수,
	* 부호
	* 로 이루어져있습니다.
	*/

public:
	/*
	* 타입 및 변수
	*
	* --타입--
	*
	* length : 길이 관련 타입, 코드의 가독성을 높이고자 썼으며
	* 별다른 이유는 없습니다. 함수의 인수로 넘어가거나 함수 내
	* 지역변수 사용시에 쉽게 이해할 수 있습니다.
	*
	* index : 배열의 번호 관련 타입, 위와 이유는 같습니다.
	*
	* blocktype : 배열의 타입, 위와 이유는 같습니다.
	*
	* _sign : 부호 타입, 양수와 음수 그리고 0으로 구성되어있습니다.
	*
	*
	* --변수--
	*
	* blk : 실질적으로 숫자가 저장되는 동적 배열입니다.
	*
	* len : 배열의 길이를 저장하는 변수입니다.
	*
	* sign : 숫자의 부호를 나타낸다.
	*/
	typedef unsigned long length; // 길이 관련 타입

	typedef unsigned long index; // blk의 배열 번호 관련 타입

	typedef unsigned long blocktype; // blk의 배열 타입

	typedef enum {
		Positive = 1,
		Zero = 0,
		Negative = -1
	} _sign; // 부호, 양수, 음수, 영으로 구성

private:
	blocktype *blk; // 실질적인 숫자 저장 공간
	length len; // 배열 길이
	_sign sign;




private:
	// 길이 c만큼 blk를 할당하는 함수입니다.
	void Allocate(length c);
	// 길이 c만큼 재할당하는 함수입니다.
	// 무조건 길이 c만큼으로 재할당하며
	// blk를 해제 후, Allocate 함수를 호출합니다.
	void Reallocate(length c);
	// blk배열의 모든 요소를 0으로 만듭니다.
	inline void Blkinit();
	// blk배열을 복사합니다.
	inline void Blkcopy(const BigInteger &x);
	// 0으로 초기화하기 위해 사용합니다.
	inline void SetZero();
	// blk를 해제 후, 0으로 초기화 합니다.
	inline void Reset();

	/*
	* 연산 과정에서 blk가 할당 한 만큼 차지 않을 수 있습니다.
	* 그런 경우 zapLeadingZeros 함수를 호출하여
	* len의 길이를 줄입니다.
	*/
	inline void ZapLeadingZeros();
public:
	/*
	* 기본 생성자는 0을 만드는 것으로 정의
	* 0은 다음과 같이 정의
	*	 len = 0
	*	 blk = NULL
	*	 sign = Zero
	*/
	BigInteger();
	~BigInteger();
	BigInteger(const BigInteger &x);
	// 생성 가능한 모든 타입으로부터 대입이 가능합니다.
	BigInteger & operator =(const BigInteger &x);


private:
	// ConversionAssist1은 unsigned으로부터 생성시 사용
	template <typename PRI>
	void ConversionAssist1(PRI x);
	template <>
	void ConversionAssist1<unsigned long long>(unsigned long long x);

	// ConversionAssist2는 signed으로부터 생성시 사용
	template <typename PRI>
	void ConversionAssist2(PRI x);
	template <>
	void ConversionAssist2<long long>(long long x);
public:
	// bool형 및 정수형으로부터 생성이 가능합니다.
	// float, double형에서의 생성은 지원하지 않습니다.
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
	// ConversionAssist3은 unsigned으로 변환시 사용
	template<typename PRI>
	const PRI ConversionAssist3() const;
	template <>
	const unsigned long long
		ConversionAssist3<unsigned long long>() const;

	// ConversionAssist4은 signed으로 변환시 사용
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
	// char 형 배열, string으로 부터 생성 가능합니다.
	explicit BigInteger(const char *str, int radix = 10);
	explicit BigInteger(const std::string &str, int radix = 10);
	// string을 BigInteger형으로 바꾸는 함수입니다.
	const BigInteger & stob(const std::string &str, int radix = 10);
	// BigInteger형을 string으로 바꿉니다.
	const std::string btos(int radix = 10) const;
	// 표준 입 출력 함수를 오버로딩 하여
	// 일반 정수형처럼 입 출력 할 수 있습니다.
	// 단, 10진법만으로 입력, 출력합니다.
	friend std::ostream & operator <<(std::ostream &os, const BigInteger &x);
	// 임의 진법으로 출력합니다.
	void print(int radix = 10) const;
	friend std::istream & operator >>(std::istream &is, BigInteger &x);
#pragma endregion
#pragma endregion

	/*
	*			연산의 순서도(this, x)
	*
	*		1. 주소가 같은가 다른가 ?
	*			ㄱ. 같을 경우 - (처리)
	*			ㄴ. 다를 경우 - (다음으로)
	*		2. 부호가 같은가 다른가 ?
	*			ㄱ. Zero 존재
	*				a. 둘 다 0 - (처리)
	*				b. this만 0 - (처리)
	*				c. x만 0 - (처리)
	*			ㄴ. 두 개의 부호가 다를 경우 - (처리)
	*			ㄷ. 부호가 서로 같을 경우 - (다음으로)
	*		3. 길이가 같은가 다른가 ?
	*			ㄱ. 다를 경우 - (처리)
	*			ㄴ. 같은 경우 - (다음으로)
	*		4. 그 외 경우 처리
	*
	*		연산에 따라서
	*		일부는 생략 가능 혹은 바뀔 수 있음
	*/

#pragma region 비교연산
public:
	const _sign getsign() const; // 부호 리턴

	// 크기를 비교합니다.
	const int compare(const BigInteger &x) const;

	// 비교 연산자 오버로딩 입니다.
	// BigInteger형과 BigInteger형의 비교
	// BigInteger형과 정수형의 비교.. 등
	// 일반 정수형처럼 사용 가능합니다.
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

#pragma region 비트연산
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
	*		'&' 연산과 '^' 연산은 Z가 나올 가능성이 있습니다.
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

#pragma region 쉬프트연산
private:
	// 블록 단위로 쉬프트 하는 보조함수입니다.
	const blocktype Get_LShiftedBlock(index x, length n) const;
public:
	const BigInteger   operator << (int leftmove)  const;
	const BigInteger & operator <<=(int leftmove);
	const BigInteger   operator >> (int rightmove) const;
	const BigInteger & operator >>=(int rightmove);
#pragma endregion

#pragma region 사칙/나머지/증감
private:
	void add(const BigInteger &Left, const BigInteger &Right);
	void subtract (const BigInteger &Left, const BigInteger &Right);
	void multiply(const BigInteger &Left, const BigInteger &Right);
	void divideWithRemainder(const BigInteger &Divisor, BigInteger &Quotient);
public:
	// +, -, *, /, %
	// +=, -=, *=, /=, %=
	// -(단항연산자), abs함수
	// ++, --
	// 등을 제공합니다.
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

#pragma region 기타연산
	// 거듭제곱
	friend BigInteger pow(const BigInteger &x, const BigInteger &y);
	template <typename X> BigInteger pow(const BigInteger &x, const X &y);
	template <typename X> BigInteger pow(const X &x, const BigInteger &y);
	// 팩토리얼
	friend BigInteger factorial(const BigInteger &x);
	// 최대공약수
	friend BigInteger gcd(BigInteger x, BigInteger y);
	template <typename X> BigInteger gcd(BigInteger x, X y);
	template <typename X> BigInteger gcd(X x, BigInteger y);
	// 최소공배수
	friend BigInteger lcm(BigInteger x,BigInteger y);
	template <typename X> BigInteger lcm(BigInteger x, X y);
	template <typename X> BigInteger lcm(X x, BigInteger y);
#pragma endregion
};

#pragma region 템플릿정의
#pragma  region 생성/변환-정의
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
	// 0 처리
	if (x == 0)
	{
		SetZero();
		return;
	}

	if ( (x >> 32) == 0 ) // 상위 32비트가 비어있다면
	{
		Allocate(1);
	}
	else // 상위 32비트에 숫자가 있다면
	{
		Allocate(2);
		blk[1] = blocktype(x >> 32); // x의 상위 32비트 대입
	}
	blk[0] = blocktype(x); // x의 하위 32비트 대입
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
	// 0 처리
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
	if ( (x >> 32) == 0 ) // 상위 32비트가 비어있다면
	{
		Allocate(1);
	}
	else // 상위 32비트에 숫자가 있다면
	{
		Allocate(2);
		blk[1] = blocktype(x >> 32); // x의 상위 32비트 대입
	}
	blk[0] = blocktype(x); // x의 하위 32비트 대입
	sign = (isminus == true) ? Negative : Positive;
}
template <typename PRI>
const PRI BigInteger::ConversionAssist3() const
{
	if (sign == Negative)
	{
#if defined(_DEBUG)
		throw "음수를 Unsigned로 바꿀 수 없습니다.";
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
	throw "값이 너무 커서 변환 할 수 없습니다.";
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
		throw "음수를 Unsigned로 바꿀 수 없습니다.";
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
	throw "값이 너무 커서 변환 할 수 없습니다.";
#else
	return x;
#endif
}
template <typename PRI>
const PRI BigInteger::ConversionAssist4() const
{
	/*
	* blk[0]의 최고 비트가 1인 경우,
	* 변환값에서 숫자를 음수로 인식하는 오류가 생긴다.
	* 따라서, 애초에 이런 변환은 금지한다.
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
	throw "값이 너무 커서 변환 할 수 없습니다.";
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
		throw "값이 너무 커서 변환 할 수 없습니다.";
	}
#endif
	return (sign == Positive) ? x : -x;
}
#pragma  endregion

#pragma region 비교연산-정의
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

#pragma region 비트연산-정의
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

#pragma region 사칙/나머지/증감연산-정의
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
// y == BigInteger(x)로 하면 무한 재귀호출 발생!!!
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

#pragma region //기타연산-정의
template <typename X> BigInteger pow(const BigInteger &x, const X &y){return pow(x, BigInteger(y));}
template <typename X> BigInteger pow(const X &x, const BigInteger &y){return pow(BigInteger(x), y);}
template <typename X> BigInteger gcd(BigInteger x, X y) {return gcd(x, BigInteger(y));}
template <typename X> BigInteger gcd(X x, BigInteger y) {return gcd(BigInteger(x), y);}
template <typename X> BigInteger lcm(BigInteger x, X y) {return lcm(x, BigInteger(y));}
template <typename X> BigInteger lcm(X x, BigInteger y) {return lcm(BigInteger(x), y);}
#pragma endregion

#pragma endregion

#endif /* _BIGINTEGER_H_ */
