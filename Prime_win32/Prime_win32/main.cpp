/*2015.07.26
copy write oldlove7
source ver 1.0
*/

#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "menu.h"
#include "BigInteger.h"
#include "mysql.h"
#include "mysql_query.h"
#include "Prime.h"


using namespace std;

int db_stat=0;//데이터 베이스 상태

int main()
{
	PRIME prime;
	PRINT_MENU menu;
	MYSQL_QUERY query;
	clock_t  finish;
	double duration=0;
	db_stat=query.db_conn();//데이터 베이스 접속

	//데이터베이스에 접속이 안되면 실행중지
	if(db_stat==0)
	{
		cout<<"데이터베이스에 접속할 수 없습니다."<<endl;
		//Sleep(3000);
	}

    int choice; 
    while(1){	
        menu.menu();
		cin>>choice;
        switch(choice){
            case 1: 
				db_stat=query.db_conn();//데이터 베이스 접속
				break;
            case 2:
				prime.prime_generation_db_insert();
				break;
            case 3:
				query.db_conn();
				break;
            case 4:
				prime.getPrime();
				break;
            case 5:
				break;
            case 6:
				break;
			case 7:
				break;
			case 8:
				query.select_max_prime();
				break;
            case 9:
				printf("bye bye \n");
				finish = clock();
			    //duration = (double)(finish - start) / CLOCKS_PER_SEC;
				printf("%duration time=\n",duration);
				Sleep(5000);
				return 0;
        }
    }
}
