#include "tools.h"
#include "teacher.h"


//教师菜单
void menu_tch(void)
{
	while(1)
	{
		system("clear");
		puts("-------学生管理系统(教师端)-------");
		puts("       1-添加学生");
		puts("       2-删除学生");
		puts("       3-查找学生");
		puts("       4-修改学生信息");
		puts("       5-录入学生成绩");
		puts("       6-重置学生密码");
		puts("       7-显示在校生信息");
		puts("       8-显示退校生信息");
		puts("       9-修改密码");
		puts("       0-退出系统");
		puts("--------------------------------");

		int option=0;
		printf("请选择：");
		scanf("%d",&option);
		switch(option)
		{
			case 1:add_stu();	break;	//添加学生
			case 2:del_stu();	break;	//删除学生
			case 3:find_stu();	break;	//查找学生
			case 4:mod_stu();	break;	//修改学生
			case 5:input_score();	break;	//录入成绩
			case 6:unlock_stu();	break;	//解锁学生
			case 7:show_stu_info('T');	break;	//显示在校学生
			case 8:show_stu_info('F');	break;	//显示退学学生
			case 9:mod_pwd(tea[Sub].pwd);	break;	//修改密码
			case 0:return;	//退出
		}
	}
}
//添加学生
void add_stu(void)
{
	system("clear");
	puts("\n***********添加学生***********\n");
	int option=0;
	printf("1-单个添加	2-批量导入	3-取消\n");
	printf("请选择：");
	scanf("%d",&option);	//记录选项
	switch(option)
	{
		case 1:single_import();break;
		case 2:bulk_import();break;
		default:return;
	}
	anykey_continue();
}
//单个导入学生
void single_import(void)
{
	char name[20];		//输入姓名
	char sex[4];		//输入性别
	int year=0;			//入学年份
	printf("请输入要添加的学生姓名:");
	fgets_m(name,18);	
	printf("%s",name);
	printf("请输入性别:");
	fgets_m(sex,4);
	if(strcmp(sex,"男") && strcmp(sex,"女"))	//性别不是男或女
	{
		printf("性别输入有误\n");
		anykey_continue();
		return;
	}
	do{
		printf("请输入该学生入学年份(1980~3000):");
		scanf("%d",&year);
	}while(year<1980 || year>3000);	//限定年份范围		
	strcpy(stu[Stu_num].name,name);
	strcpy(stu[Stu_num].sex,sex);
	import(year);		//导入剩余数据
	printf("添加完成\n");	
}
//批量导入学生
void bulk_import(void)
{
	printf("请输入文件位置：");
	char path[50]={};
	fgets_m(path,50);
	int year[1000]={};		//年份
	FILE* frp=fopen(path,"r");	//打开文件
	if(frp==NULL)
	{
		printf("导入失败\n");
		return;
	}
	int i=0;
	while(fscanf(frp,"%s %s %d",stu[Stu_num].name,stu[Stu_num].sex,&year[i])!=EOF)
	{
		import(year[i]);
		i++;
	}
	fclose(frp);
	frp=NULL;
	printf("导入完成\n");
}

//导入剩余信息
void import(int year)
{
	char id[8]={};
	rand_id(year,id);
	strcpy(stu[Stu_num].id,id);
	strcpy(stu[Stu_num].pwd,INIT_PWD);
	stu[Stu_num].is_sch='T';
	stu[Stu_num].is_lock=0;
	Stu_num++;	//学生人数自增
}

//删除学生
void del_stu(void)
{
	system("clear");
	puts("\n***********删除学生***********\n");
	char key[8]={};
	printf("请输入要删除的学生学号:");
	fgets_m(key,8);
	int i=0;
	for(i=0;i<Stu_num;i++)
	{
		if(!strcmp(stu[i].id,key))
		{
			if(stu[i].is_sch=='F')		//判断学生是否已被删除
			{
				printf("该学生已被删除\n");
				anykey_continue();
				return;
			}
			else
				break;
		}
		if(i==Stu_num-1)		//未找到
		{
			printf("学号输入错误\n");
			anykey_continue();
			return;
		}		
	}
	printf("请再次输入学号:");
	fgets_m(key,8);
	if(!strcmp(stu[i].id,key))
	{
		stu[i].is_sch='F';		//改标记
		printf("删除成功\n");
		anykey_continue();
		return;
	}
	printf("取消删除\n");
	anykey_continue();
}

//查找学生
void find_stu(void)
{
	system("clear");
	puts("\n***********查找学生***********\n");
	int option=0;
	printf("1-按姓名查找	2-按学号查找 3-取消\n");
	printf("请选择：");
	scanf("%d",&option);	
	if(option!=1 && option!=2)
	{
		return;
	}
	char key[20]={};
	printf("请输入信息：");
	fgets_m(key,20);
	printf("学号\t姓名\t性别\t语文\t数学\t英语\t总分\n");
	for(int i=0;i<Stu_num;i++)
	{
		if(option==1 && strstr(stu[i].name,key))
			match(stu[i].id,i);
		if(option==2 && strstr(stu[i].id,key))
			match(stu[i].id,i);
	}
	anykey_continue();
}
//匹配输出学生信息
void match(char* id,int n)	//id:学号	n:查出的学生下标
{
	//打印学号姓名性别
	printf("%s\t%s\t%s\t",stu[n].id,stu[n].name,stu[n].sex);	
	//打印成绩
	for(int i=0;i<Sco_num;i++)
	{
		if(!strcmp(sco[i].id,id))
		{
			printf("%.1lf\t%.1lf\t%.1lf\t%.1lf\n",sco[i].chn,sco[i].math,sco[i].eng,sco[i].total);		
			return;
		}
	}
	printf("\n");
	return;
}

//修改学生信息
void mod_stu(void)
{
	system("clear");
	puts("\n*********学生信息修改*********\n");
	printf("1-修改基础信息		2-修改成绩 	3-取消\n");
	int option=0;
	printf("请选择:");
	scanf("%d",&option);
	char id[8]={};	
	printf("请输入要修改的学生学号：");
	fgets_m(id,8);
	int stu_sub=0;		//记录学生下标
	int sco_sub=-1;		//记录成绩下标
	for(int i=0;i<Stu_num;i++)
	{
		if(!strcmp(stu[i].id,id))
		{
			stu_sub=i;
			break;
		}
		if(i==Stu_num-1)
		{
			printf("学号输入错误");
			anykey_continue();
			return;
		}		
	}
	//绑定学号与成绩下标，若没有 sco_sub还为-1
	for(int i=0;i<Sco_num;i++)
	{
		if(!strcmp(sco[i].id,id))
		{
			sco_sub=i;
			break;
		}	
	}
	switch(option)
	{
		case 1:mod_stu_info(stu_sub,sco_sub);break;
		case 2:mod_stu_score(stu_sub,sco_sub);break;
		default:return;
	}

	anykey_continue();
}

//基础信息修改
void mod_stu_info(int stu_sub,int sco_sub)
{
	char sex[4]={};
	printf("请输入要修改的信息：\n");
	printf("姓名:");
	fgets_m(stu[stu_sub].name,19);
	//若成绩表中有此学生成绩，更改表中名字
	if(sco_sub!=-1)
	{
		strcpy(sco[sco_sub].name,stu[stu_sub].name);
	}
	printf("性别:");
	fgets_m(sex,4);
	if(strcmp(sex,"男") && strcmp(sex,"女"))
	{
		printf("性别输入有误,修改失败\n");
		return;
	}
	strcpy(stu[stu_sub].sex,sex);
}

//学生成绩修改
void mod_stu_score(int stu_sub,int sco_sub)
{
	//判断此学生成绩是否录入
	if(sco_sub==-1)
	{
		char sel=0;
		printf("该学生成绩未录入，是否添加(y/n):");
		scanf("%c",&sel);
		if(sel=='y'||sel=='Y')
		{
			sco_sub=Sco_num;
			strcpy(sco[sco_sub].id,stu[stu_sub].id);
			Sco_num++;
		}
		else{
			return;
		}
	}
	strcpy(sco[sco_sub].name,stu[stu_sub].name);
	score(sco_sub);		//输入成绩
}

//录入成绩
void input_score(void)
{
	system("clear");
	puts("\n*********学生成绩录入*********\n");
	int option=0;
	char id[8]={};
	printf("1-单个录入	2-批量导入	3-取消\n");
	printf("请选择：");
	scanf("%d",&option);	
	if(option==1)
	{
		printf("请输入学号：");		
		fgets_m(id,8);
		score_jge(id,-1,-1,-1);
	}
	else if(option==2)
	{
		import_score();
	}
	else
	{
		return;
	}
	anykey_continue();
}
//批量导入成绩
void import_score(void)
{
	int n=0;
	Score* im_sco=calloc(sizeof(Score),100);
	printf("请输入文件位置：");
	char path[80]={};
	fgets_m(path,80);
	//打开文件
	FILE* frp=fopen(path,"r");
	if(frp==NULL)
	{
		printf("文件不存在,导入失败\n");
		return;
	}
	while(fscanf(frp,"%s %lf %lf %lf",im_sco[n].id,&im_sco[n].chn,&im_sco[n].math,&im_sco[n].eng)!=EOF)
	{
		n++;
	}
	Imp_suc=0;	//重置计数
	Imp_fail=0;	//重置计数
	for(int i=0;i<n;i++)
	{
		score_jge(im_sco[i].id,im_sco[i].chn,im_sco[i].math,im_sco[i].eng);
	}
	printf("共%d条数据，%d条成功导入，%d条导入失败\n",n,Imp_suc,Imp_fail);
	//释放
	fclose(frp);
	frp=NULL;
	free(im_sco);	
	im_sco=NULL;
}

void score_jge(char* id,double chn,double math,double eng)
{
	//判断成绩是否已存在
	for(int i=0;i<Sco_num;i++)
	{
		if(!strcmp(sco[i].id,id))	//存在则覆盖
		{
			if(chn>-1)
			{
				sco[i].chn=chn;
				sco[i].math=math;
				sco[i].eng=eng;
				sco[i].total=chn+math+eng;
			}
			else
			{
				score(i);
			}
			Imp_suc++;
			printf("%s %s 成绩已更新\n",sco[i].id,sco[i].name);
			return;
		}
	}
	for(int i=0;i<Stu_num;i++)
	{
		if(!strcmp(stu[i].id,id))
		{
			//判断是否已退学
			if(stu[i].is_sch=='F')
			{
				printf("%s %s 已退学，录入失败",stu[i].id,stu[i].name);
				Imp_fail++;
				return;
			}
			strcpy(sco[Sco_num].id,id);
			strcpy(sco[Sco_num].name,stu[i].name);
			break;
		}
		else if(i==Stu_num-1)
		{
			Imp_fail++;
			printf("%s 不存在,录入失败\n",id);
			return;
		}
	}
	if(chn>-1)
	{
		sco[Sco_num].chn=chn;
		sco[Sco_num].math=math;
		sco[Sco_num].eng=eng;
		sco[Sco_num].total=chn+math+eng;
	}
	else
	{
		score(Sco_num);
	}
	Imp_suc++;
	Sco_num++;
}

//输入成绩
void score(int n)
{
	printf("语文：");	
	sco[n].chn=enter_jge();
	printf("数学：");
	sco[n].math=enter_jge();
	printf("英语：");	
	sco[n].eng=enter_jge();
	sco[n].total=sco[n].chn+sco[n].math+sco[n].eng;
}

//判断成绩输入是否合法
double enter_jge(void)
{
	double a=0;
	while(scanf("%lf",&a)!=1)
	{
		printf("成绩有误，请重新输入\n");
		CACHE_CLEAR;
	}
	return a;
}
//解锁学生
void unlock_stu(void)
{
	system("clear");
	puts("**********学生帐号解锁**********\n");
	printf("1-解锁帐号	2-重置密码	3-取消\n");
	int option=0;
	printf("请选择:");
	scanf("%d",&option);
	if(option!=1 && option!=2)
	{
		return;
	}
	char id[8]={};
	printf("请输入要操作的学生学号：");
	fgets_m(id,8);
	for(int i=0;i<Stu_num;i++)
	{
		if(!strcmp(stu[i].id,id))
		{
			stu[i].is_lock=0;		//解锁
			if(option==1)
			{
				printf("解锁成功!\n");
				anykey_continue();
				return;
			}
			strcpy(stu[i].pwd,INIT_PWD);	//重置密码
			printf("重置成功!\n");
			anykey_continue();
			return;
		}		
	}
	printf("查无此人，重置失败");
	anykey_continue();
}
//显示学生信息
void show_stu_info(char at)
{
	system("clear");
	printf("\n*********%s学生信息*********\n\n",at=='T'?"在校":"退学");
	printf("学号\t姓名\t性别\n");
	for(int i=0;i<Stu_num;i++)
	{
		if(stu[i].is_sch==at)
		{
			printf("%s\t%s\t%s\n",stu[i].id,stu[i].name,stu[i].sex);
		}
	}
	anykey_continue();
}









