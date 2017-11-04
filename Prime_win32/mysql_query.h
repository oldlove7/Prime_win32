
#include "mysql.h"
#pragma comment(lib, "libmySQL.lib") 
//#pragma comment(lib, "ws2_32.lib") 


#define DB_HOST "180.224.148.44"
#define DB_USER "root"
#define DB_PASS "old7302"
#define DB_NAME "oldlove7"

class MYSQL_QUERY
{
public:
int table_create();
int db_conn();
int db_close();
int Mysql_Ver();
int insert_query(int *array,int _even,int _odd,int _sum);
int insert_query_prime(unsigned __int64 prime, unsigned __int64 first_prime);
int insert_query_olddata(int *array, int _order, int  _even,int _odd,int _sum);
int insert_query_test(int *array,int _even,int _odd,int _sum);
int select_max_prime();
};
