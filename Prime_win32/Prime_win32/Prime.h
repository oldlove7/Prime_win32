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
    int ch;//Ű���� ó����
	unsigned __int64 FirstInputNumber;
	unsigned __int64 PrimeNumber;
	unsigned __int64 InputNumber;
	//unsigned __int64 X;
    unsigned __int64 first_prime;
    unsigned __int64 term_prime;
	__int64 prime_array[100000];
	unsigned __int64 Prime[9999];//���μ� ������ �� �μ� ���� �迭
public:
	PRIME();
	void prime_generation_db_insert();//�Ǻ��� �Ҽ��� DB�� �Է�
	bool isPrime(unsigned __int64);//�Ҽ��Ǻ� �Լ�
	void show_time();//����ð��� ���
	void prime_generation();
	void getPrime();
	
};