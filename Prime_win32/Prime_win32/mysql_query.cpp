#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdlib.h>
#include "mysql_query.h"
#include "Prime.h"


#define SQL_INSERT_RECORD "INSERT INTO `mysql_api_test` ( `id` , `num` , `string` ) \
    VALUES (\ NULL , '%d', '%d'\);" 

#define SQL_CREATE_TABLE "CREATE TABLE `mysql_api_test` (\
    `id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,\
    `num` INT NULL ,\
    `string` VARCHAR( 20 ) NULL \
    ) TYPE = MYISAM ;" //"

MYSQL *connection=NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat; 
char query[255];

int MYSQL_QUERY::table_create()
{
    // 테이블 생성
    query_stat=mysql_query(connection,SQL_CREATE_TABLE);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }
	return 0;
}

int MYSQL_QUERY::db_conn()
{
	mysql_init(&conn);
    // DB 연결
    connection = mysql_real_connect(&conn, DB_HOST,
        DB_USER, DB_PASS,DB_NAME, 3306,(char *)NULL, 0);
    if(connection==NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 0;
    }
	else if(connection != NULL)
	{
		//prime.ListView(str);
		//printf("DB 접속성공\n");
	}
	return 1;
}
int MYSQL_QUERY::db_close()
{
	  mysql_close(connection);
	  printf("DB 연결끊김\n");
	  return 0;
}

int MYSQL_QUERY::Mysql_Ver()
{
	long Ver;
	Ver= mysql_get_client_version();
	return Ver;
}

int MYSQL_QUERY::insert_query(int *array,int _even,int _odd,int _sum)
{
	    sprintf(query,"insert into t_lotto values('NULL','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
			                    array[0],array[1],array[2],array[3],array[4],array[5],_even,_odd,_sum);
        query_stat = mysql_query(connection, query);
        if (query_stat == 1)
        {
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
            return 1;
        }
		return 0;
}
int MYSQL_QUERY::insert_query_prime(unsigned __int64 prime,unsigned __int64 term_prime)
{
	    sprintf(query,"insert into prime values('%lld','%lld')",
			                                 prime,term_prime);
        query_stat = mysql_query(connection, query);
        if (query_stat == 1)
        {
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
            return 1;
        }
		return 0;
}
int MYSQL_QUERY::insert_query_olddata(int *array, int _order, int  _even,int _odd,int _sum)
{
	    sprintf(query,"insert into t_lotto_statistics values('NULL','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
			                  _order,array[0],array[1],array[2],array[3],array[4],array[5],_even,_odd,_sum);
        query_stat = mysql_query(connection, query);
        if (query_stat == 1)
        {
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
			//getchar();
            return 1;
        }
		return 0;
}

int MYSQL_QUERY::insert_query_test(int *array,int _even,int _odd,int _sum)
{
	    sprintf(query,"insert into test values('NULL','%d','%d','%d')",
			                              array[0],array[1],array[2]);
        query_stat = mysql_query(connection, query);
        if (query_stat == 1)
        {
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
			//getchar();
            return 1;
        }
		return 0;
}

// selct Max 결과 출력
int MYSQL_QUERY::select_max_prime()
{
	int max=0;
	sprintf(query,"SELECT MAX(prime) from prime");
	//sprintf(query,"SELECT * from prime");
  query_stat=mysql_query(connection,query);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }
    // 결과 출력
	sql_result=mysql_store_result(connection);
    while((sql_row=mysql_fetch_row(sql_result))!=NULL)
    {
        printf("입력된 가장큰소수=%s\n",sql_row[0]);
		max=atoi(sql_row[0]);
    }
	
     mysql_free_result(sql_result);

	 getchar();
	 return max;
}
