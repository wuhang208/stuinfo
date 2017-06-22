#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  char stuId[16] = "\0";
	char cno[16] = "\0";
	char flag[8] = "\0";
	int status = 0;

	FILE * fd;
  char ch;
 fd=fopen("head.html", "r");
 if(fd==NULL){
     fprintf(cgiOut, "Cannot open file,head.html \n");
     return -1;
   }
   ch = fgetc(fd);

   while(ch != EOF){
     fprintf(cgiOut, "%c", ch);
     ch = fgetc(fd);
   }
 fclose(fd);

  status = cgiFormString("stuId",  stuId, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}
	status = cgiFormString("cno",  cno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}
	status = cgiFormString("flag",  flag, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get flag error!\n");
		return 1;
	}

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	if (flag[0]=='1'){
	sprintf(sql, "delete from score where stuId = '%s' cno = %s", stuId, cno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
}
else{
	sprintf(sql, "update score set fl ='0' where stuId = '%s' cno = %s", stuId, cno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

}

	fprintf(cgiOut, "delete score ok!\n");
	mysql_close(db);

	return 0;
}
