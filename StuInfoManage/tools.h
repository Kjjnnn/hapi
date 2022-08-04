#ifndef TOOLS_H
#define TOOLS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>

#define CACHE_CLEAR stdin->_IO_read_ptr = stdin->_IO_read_end	//清除输入缓存
#define INIT_PWD "111111"	//初始密码
//教师
typedef struct Teacher
{
	char name[20];
	char sex[4];
	char id[8];
	char pwd[12];
	char is_work;
	int is_lock;	
}Teacher;
//学生
typedef struct Student
{
	char name[20];
	char sex[4];
	char id[8];
	char pwd[12];
	char is_sch;
	int  is_lock;
}Student;
//成绩
typedef struct Score
{
	char name[20];
	char id[8];
	double chn;
	double math;
	double eng;
	double total;
}Score;

void login(void);	//总登录
void init_data(void);	//初始化
void fCreate(void);		//读取文件
void save_data(void);	//保存
void login_m(void *p,int num,int n);	//教师、学生登录
void rand_id(int year,char* id);		//产生id
void anykey_continue(void);	
void hide_pwd(char *a);		//隐藏
void mod_pwd(char* old_pwd);	//修改密码
void encrypt(char* p,int f);	//加密解密
char* fgets_m(char* s,int size);	//fgets去除末尾回车

extern char Hm_pwd[12];
extern int Rank;
extern char User[11];
extern int Tea_num;
extern int Stu_num;
extern int Sco_num;
extern int Sub;
extern Teacher *tea;
extern Student *stu;
extern Score *sco;
extern int Imp_suc;	//导入成功数
extern int Imp_fail;	//导入失败数

#endif//TOOLS_H
