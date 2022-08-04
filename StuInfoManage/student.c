#include "tools.h"
#include "student.h"


//学生界面显示
void menu_stu(void)
{
	while(1)
	{
		system("clear");
		puts("-------学生管理系统(学生端)-------");
		puts("       1-个人信息查询");
		puts("       2-学生成绩查询");
		puts("       3-学生密码修改");
		puts("       4-退出系统");
		puts("--------------------------------");
		printf("请选择：");
		int cmd=0;
		scanf("%d",&cmd);
		switch(cmd)
		{
			case 1:m_info();break;	//查询个人信息
			case 2:sch_score();break;	//查询成绩
			case 3:mod_pwd(stu[Sub].pwd);break;	//修改密码
			case 4:return;	//退出
		}
	}
}

//成绩查询
void sch_score(void)
{
	double total[Sco_num];
	double chn[Sco_num];
	double math[Sco_num];
	double eng[Sco_num];
	double sum_chn=0,sum_math=0,sum_eng=0,sum_total=0;	//各项成绩总和
	//传入成绩
	for(int i=0;i<Sco_num;i++)
	{
		chn[i]=sco[i].chn;
		sum_chn+=chn[i];
		math[i]=sco[i].math;
		sum_math+=math[i];
		eng[i]=sco[i].eng;
		sum_eng+=eng[i];
		total[i]=sco[i].total;
		sum_total+=total[i];
	}	
	//排序
	rank(total);
	rank(chn);
	rank(math);
	rank(eng);
	//打印成绩
	printf("语文\t数学\t英语\t总分\n");
	for(int i=0;i<Sco_num;i++)
	{
		printf("%.1lf\t%.1lf\t%.1lf\t%.1lf\n",chn[i],math[i],eng[i],total[i]);
	}
	printf("平均分：\n");
	printf("%.1lf\t%.1lf\t%.1lf\t%.1lf\n",sum_chn/Sco_num,sum_math/Sco_num,sum_eng/Sco_num,sum_total/Sco_num);
	for(int i=0;i<Sco_num;i++)
	{
		if(!strcmp(sco[i].id,stu[Sub].id))
		{
			printf("你的成绩：\n");
			printf("%.1lf\t%.1lf\t%.1lf\t%.1lf\n",sco[i].chn,sco[i].math,sco[i].eng,sco[i].total);
			break;
		}
		else if(i==Sco_num-1)
		{
			printf("你的成绩未录入\n");
		}
	}
	anykey_continue();
}
//冒泡排序
void rank(double* p)
{
	for(int i=0;i<Sco_num-1;i++)
	{
		for(int j=0;j<Sco_num-1-i;j++)
		{
			if(p[j]<p[j+1])
			{
				int temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
}
//显示信息
void m_info(void)
{
	 printf("学号：%s\n",stu[Sub].id);
	 printf("姓名：%s\n",stu[Sub].name);
	 printf("性别：%s\n",stu[Sub].sex);
	 anykey_continue();	 
}


