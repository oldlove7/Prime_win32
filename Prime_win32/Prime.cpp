#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Prime.h"
#include "mysql.h"
#include "mysql_query.h"

#define ESC 27

using namespace std;



//생성자 초기화
PRIME::PRIME()
{
	m_u6Count = 0;
	PrimeNumber=0;
	first_prime=0;
	term_prime=0;
	
}
//소수판별 함수
bool PRIME::isPrime(unsigned __int64 n)
{
    //printf("isPrime start \n");
    unsigned __int64 i=2;
	unsigned __int64 k=0;
    int Prime=0,check=0;
	k=n/2;
	if(n % 2 != 0)//홀수일 경우만 진행
	{
			for(i; i<=k; i++){
				if(n%i==0){
                 check++;//check 가 1이상이면 짝수기 때문
				// printf("prime check = %d \n",check);
                // printf("                      check=%d\n",check);			 
				}
            //printf("Random_p_q = %d i=%d \n",n,i);
			}
			//check 가 0이여야만 소수임
			if(check==0){
				//printf("prime ok=%d \n",n);
				return true;
			}
			else if(check>=1){
            //printf("prime false \n");
            check=0,i=2;
			}
	}
	return false;
}
/**
설명:입력범위의 소수를 구하는 함수
@class    PRIME
@date    2017/10/29
@author    유승일
@warning
인수: 없음
리턴값: void
수정내용: 
*/

/******************************************************************************
설      명: 통신 Thread
리  턴  값: 0
매개변수값: 핸들 값
매개변수명: 다이얼로그 핸들
Remark    : BitSvrcom 함수를 호출하여 스레드 실행
History
2016. 04/03 수정자: oldlove7
1. 수정 사유: 최초작성
******************************************************************************/
void PRIME::prime_generation()
{
	//cout << a * a * a * a * a * a * a << endl;
	//int i=0,j=0,k=0,p_start=0, p_end=0;
	unsigned __int64 i=0,j=0,k=0;
	
	cout << "p_start?";
	cin >> m_PrimeStart;
	cout << "p_end";
	cin >> m_PrmepEnd;
	for(i= m_PrimeStart; i<m_PrmepEnd; i++){
		if(true==isPrime(i)){
			//cout<< i << endl;
			//printf("prime = %d \n",i);
			prime_array[j]=i;
			j++;
		}
	}
	
	for(k=0; k<=j; k++){
		cout<< prime_array[k] << endl;
		//printf("prime %d \n",prime_array[k]);
	}

	cout << j << endl;
}

//입력된 수를 소인수 분해하는 함수
void PRIME::getPrime()
{
	unsigned __int64 X;
	unsigned __int64 i;

	cout<<"분해할 소인수 입력 =";
	cin>>FirstInputNumber;
	InputNumber=FirstInputNumber;

	
	    
		for(i=2;i<=InputNumber;i++)
		{
			cout<<"i="<<i<<endl;
			if(InputNumber%i==0)
			{
				Prime[PrimeNumber]=i;
				PrimeNumber++;
				InputNumber=InputNumber/i;
				i=1;
				m_u6Count++;
				cout<<"count="<< m_u6Count <<endl;
				cout<<"PrimeNumber="<<Prime[PrimeNumber-1]<<endl;
			}
		}
		X=1;
		i=0;
		cout<<"prime print"<<endl;
		while(FirstInputNumber!=X)
		{
			//printf("%d ",Prime[i]);
			//Sleep(2000);
			cout<<"X="<<X<<endl;
			cout<<"i="<<i<<endl;
			cout<<"소수의 인수="<<Prime[i]<<endl;
			X=X*Prime[i];
			
			cout<<X<<"*"<<Prime[i]<<endl;
			i++;
			if(X==0)
			{
				cout<<"문제발생"<<endl;
				cout<<"x="<<X<<endl;
				cout<<"prime="<<Prime[0]<<endl;
				cout<<"prime="<<Prime[1]<<endl;
				cout<<"prime="<<Prime[2]<<endl;
				cout<<"prime="<<Prime[3]<<endl;
				cout<<"prime="<<Prime[4]<<endl;
				cout<<"prime="<<Prime[5]<<endl;
				cout<<"prime="<<Prime[6]<<endl;
				cout<<"prime="<<Prime[7]<<endl;
				return;
			}
		}
		m_u6Count = 0;//재실행을 위한 카운트 초기화	
}
//현재시간을 출력
void PRIME::show_time()
{
	char date[64], time[64]; 
     _strdate(date); 
     _strtime(time); 
     printf("%s %s\n", date, time); 
} 
/******************************************************************************
설      명: 소수를 순차적으로 카운트하여 데이터 베이스에 저장하는 함수
리  턴  값: 0
매개변수값: 
매개변수명: 
Remark    : 
History
2017. 11/04 수정자: oldlove7
1. 수정사유: 계산 누적 시간 보완
******************************************************************************/
void PRIME::prime_generation_db_insert()
{
	unsigned __int64 i;
	double aTime, bTime = 0;

	MYSQL_QUERY query;
    //숫자 범위 입력
	while(1)
	{
		//가장큰값 조회하여 1 더하기
		m_PrimeStart = query.select_max_prime()+1;
		
	    //cin >> p_start;
	    cout << "저장할 소수 범위 입력 = ";
	    cin >> m_PrmepEnd;
		if(m_PrmepEnd <= m_PrimeStart)
		{
			cout<<"저장된 수보다 작습니다"<<endl;
		}
		else{
			break;
		}
	}
	first_prime=query.select_max_prime();//가장큰수를 첫번째 변수에 저장
	for(i= m_PrimeStart; i<m_PrmepEnd; i++){
		//int 최대크기면 종료 2147483647
		if (m_PrmepEnd >= 2147483647) {
			cout << "int 범위를 초과했습니다" << endl;
			return;
		}

		//ESC가 입력되면 루프종료
		if(_kbhit())
		{
			ch=_getch();
			if(ch==ESC)
			{
				return;
			}
		}
		////////////////////////////////
		m_start_time = clock();//계산시작 시간
		
		
		//소수를 판별하여 데이터베이스에 저장
		if(true==isPrime(i)){
			prime=i;
            term_prime = prime - first_prime;
			//판별된 소수를 DB에 저장
			query.insert_query_prime(prime,term_prime);
			cout << "insert success primeNumber = " << prime << endl;
			m_u6Count++;
			cout << "count = " << m_u6Count << endl;

			m_finish_time = clock();//계산종료 시간
			aTime = (double)(m_finish_time - m_start_time) / CLOCKS_PER_SEC;
			bTime = bTime + aTime;
			cout << "calculation  time = " << bTime << endl;//계산시간 출력
			bTime = 0;//누적시간을 초기화
			first_prime = prime;
			show_time();//현재시간 출력
		}
		m_finish_time = clock();//계산종료 시간
		aTime = (double)(m_finish_time - m_start_time) / CLOCKS_PER_SEC;//시작시간과 종료시간 차이 계산
		bTime = bTime + aTime;//계산시간 누적
	}
}
