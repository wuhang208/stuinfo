#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	char cno[16] = "\0";
	char cname[32] = "\0";
  char sdept[32] = "\0";
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

	status = cgiFormString("cno",  cno, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("cname",  cname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}
  status = cgiFormString("sdept",  sdept, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sdept error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
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



	strcpy(sql, "create table course (cno char(16) primary key, cname char(32) not null, sdept char(32) not null, fl char(8), foreign key(sdept)references school(sdept))character set = utf8;");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}

	sprintf(sql, "insert into course values('%s', '%s', '%s', '1')", cno, cname, sdept);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add course ok!\n");
	mysql_close(db);
	return 0;
}
