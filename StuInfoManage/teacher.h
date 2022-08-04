#ifndef TEACHER_H
#define TEACHER_H

void menu_tch(void);	//教师菜单
void mod_stu(void);		//修改学生
void mod_stu_info(int stu_sub,int sco_sub);	//修改基础信息
void mod_stu_score(int stu_sub,int sco_sub);	//修改学生成绩
void add_stu(void);		//添加学生
void del_stu(void);		//删除学生
void find_stu(void);	//查找学生
void input_score(void);	//录入成绩
void unlock_stu(void);	//解锁学生
void show_stu_info(char at);	//显示学生	at='T'在校	at='F'离校
void single_import(void);		//单个导入学生
void bulk_import(void);	//批量导入学生
void import(int year);		//导入剩余信息
double enter_jge(void);		//判断成绩合法
void score(int n);		//输入成绩
void import_score(void);	//批量导入成绩
void score_jge(char* id,double chn,double math,double eng);//录入成绩判断
void match(char* id,int n);	//匹配输出学生信息



#endif//TEACHER_H
