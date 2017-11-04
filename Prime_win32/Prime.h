#include <time.h>
#include <windows.h>

class PRIME
{
private:
	clock_t m_start_time,m_finish_time;
	unsigned __int64 m_PrimeStart;
	unsigned __int64 m_PrmepEnd;
	unsigned __int64 prime;
	unsigned __int64 m_u6Count;
    int ch;//키보드 처리값
	unsigned __int64 FirstInputNumber;
	unsigned __int64 PrimeNumber;
	unsigned __int64 InputNumber;
	//unsigned __int64 X;
    unsigned __int64 first_prime;
    unsigned __int64 term_prime;
	__int64 prime_array[100000];
	unsigned __int64 Prime[9999];//소인수 분해할 때 인수 저장 배열
public:
	PRIME();
	void prime_generation_db_insert();//판별된 소수를 DB에 입력
	bool isPrime(unsigned __int64);//소수판별 함수
	void show_time();//현재시간을 출력
	void prime_generation();
	void getPrime();
	
};