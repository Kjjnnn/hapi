#include "tools.h"
#include "headmaster.h"

//添加教师
void add_tch(void)
{

	char id[8]={};		//存储输入的工号
	char name[20]={};		//存储输入的姓名
	char sex[4]={};			//存储输入的性别
	printf("请输入教师的信息:\n");
	printf("工号:");
	fgets_m(id,8);
	int i=0;
	while(i<=Tea_num)			//对内存中的结构体成员进行遍历
	{
		if(strcmp(tea[i].id,id) == 0) 	//进行一个判断，输入工号是否已存在于内存中
		{
			printf("工号已重复，添加失败\n");
			anykey_continue();			
			return;
		}
		else
		{
			i++;
		}
	}
	printf("姓名:");
	fgets_m(name,19);
	printf("性别:");
	fgets_m(sex,4);
	if(strcmp(sex,"男") && strcmp(sex,"女"))	//性别不是男或女
	{
		printf("性别输入有误\n");
		anykey_continue();
		return;
	}
	printf("将添加 工号：%s 姓名：%s 性别：%s 的教师\n确认添加(y/n):",id,name,sex);
	char sel;
	scanf("%c",&sel);
	if(sel!='y' && sel!='Y')
	{
		printf("取消添加\n");
		anykey_continue();
		return;
	}	
	strcpy(tea[Tea_num].name,name);		//将信息存入内存中的结构体中，将密码，在职状态和帐号状态初始化
	strcpy(tea[Tea_num].sex,sex);
	strcpy(tea[Tea_num].id,id);
	strcpy(tea[Tea_num].pwd,INIT_PWD);
	tea[Tea_num].is_work='T';
	tea[Tea_num].is_lock=0;
	Tea_num++;						//教师人数+1
	printf("添加成功\n");
	anykey_continue();	
}

//解聘教师
void del_tch(void)
{	
	int cnt = 0,pan=0;		//cnt是下标，pan是检查是否有符合条件数据的一个标志
	char strj[12]={};		//存储输入的教师工号
	printf("请输入需要解聘的教师工号：\n");
	fgets_m(strj,12);
	while(cnt<=Tea_num)
	{
		if(strcmp(tea[cnt].id,strj) ==0 )	//进行判断
		{
			pan=-1;							//找到了符合条件的数据，将pan赋值为-1
			tea[cnt].is_work='F';			//将在职标识改为离职
			tea[cnt].is_lock=3;				//将账户状态改为锁定
			printf("解聘成功,且该教师帐号已锁定！\n");
			anykey_continue();
		}
		cnt++;
	}
	if(pan == 0)		//判断是否找到过符合条件的数据
	{
	printf("信息有误，请检查\n");
	anykey_continue();
	}	
}


//显示教师
void show_tch_info(void)
{
	printf("显示在职教师请按’T‘，离职教师请按’F‘，所有教师请按’A‘\n");
	char sign;
	int cnt =0;
	scanf(" %c",&sign);			//存储打印的标志
	if(sign == 'A')
	{
		while(cnt<=Tea_num)		//直接打印
		{
			printf("%s %s %s\n",tea[cnt].name,tea[cnt].sex,tea[cnt].id);
			cnt++;
		}
		
	}
	else if(sign == 'T')
	{
		while(cnt<=Tea_num)
		{
				if(tea[cnt].is_work == 'T')		//对标志进行遍历比较
				{
					printf("%s %s %s\n",tea[cnt].name,tea[cnt].sex,tea[cnt].id);
				}
			cnt++;
			
		}
	}
	else if(sign =='F')
	{
		while(cnt<=Tea_num)
		{
				if(tea[cnt].is_work == 'F')
				{
					printf("%s %s %s\n",tea[cnt].name,tea[cnt].sex,tea[cnt].id);
				}
			cnt++;
		}
	}
	anykey_continue();
}

//解锁教师帐号
void unlock_tch(void)
{
	printf("请输入需要解锁的教师工号：\n");
	char strj[8]={};		//存储输入的工号
	fgets_m(strj,8);
	for(int i=0;i<Tea_num;i++)
	{
		if(!strcmp(strj,tea[i].id))
		{
			tea[i].is_lock='T';
			printf("解锁成功\n");
			anykey_continue();
			break;
		}
		if(i==Tea_num-1)
		{
			printf("该教师不存在,请检查\n");
			anykey_continue();
		}
	}

}

//重置教师密码
void reset_tch_pwd(void)
{
	printf("请输入需要重置的教师工号：\n");
	char id[8]={};
	fgets_m(id,8);
	for(int i=0;i<Tea_num;i++)
	{
		if(!strcmp(tea[i].id,id))
		{
			strcpy(tea[i].pwd,INIT_PWD);
			tea[i].is_lock='T';
			anykey_continue();
			return;
		}
		if(i==Tea_num-1)
		{
			printf("该教师不存在,请检查\n");
			anykey_continue();
		}
	}		
}

//重置自己密码
void reset_hea_pwd(void)
{	
	char whe;
	printf("确定重置admin密码 T/F？\n");		//进行流程的询问
	scanf(" %c",&whe);
	if(whe=='T')
	{
		strcpy(Hm_pwd,INIT_PWD);
		printf("重置完成\n");
		return;
	}
	else
	{
		return;
	}
}
//校长登录
void login_hm(void)
{
	char pwd1[30]={};
	printf("欢迎您校长\n请输入密码:");
	CACHE_CLEAR;
	hide_pwd(pwd1);
	CACHE_CLEAR;
	if(!strcmp(pwd1,Hm_pwd))
	{
		if(!strcmp(Hm_pwd,INIT_PWD))
		{
			mod_pwd(Hm_pwd);
		}
		menu_hm();
	}
	else
	{
		printf("密码错误\n");
		anykey_continue();
	}
}


void menu_hm(void)
{
	while(1)
	{
		system("clear");
		puts("--------学生管理系统(校长端)--------");
		puts("       1-添加教师");
		puts("       2-解聘教师");
		puts("       3-显示教师");
		puts("       4-解锁教师帐号");
		puts("       5-重置教师密码");
		puts("       6-重置自己密码");
		puts("       7-退出系统");
		puts("--------------------------------");
		
		int option=0;
		printf("请选择:");
		scanf("%d",&option);
		switch(option)
		{
			case 1:add_tch();	break;
			case 2:del_tch();	break;
			case 3:show_tch_info();	break;
			case 4:unlock_tch();	break;
			case 5:reset_tch_pwd();	break;
			case 6:reset_hea_pwd();	break;	
			case 7:return;
		}
	}
}

