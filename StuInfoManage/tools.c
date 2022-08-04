#include "tools.h"
#include "teacher.h"
#include "student.h"
#include "headmaster.h"
#define TEA 50		//教师上限		
#define STU 200		//学生上限
#define SCO 200		//成绩上限
#define TEA_LOC "./info/tch_info.txt"	//教师文件位置
#define STU_LOC "./info/stu_info.txt"	//学生文件位置
#define SCO_LOC "./info/stu_score.txt"	//成绩文件位置
#define HM_LOC "./info/hm.txt"	//成绩文件位置


int Rank;		//标记身份
int Sub;		//登录者下标
char User[11];	//用户ID
int Tea_num=0;	//教师人数
int Stu_num=0;	//学生人数
int Sco_num=0;	//成绩数
int Imp_suc=0;	//导入成功数
int Imp_fail=0;	//导入失败数
char Hm_pwd[12];	//校长密码

Teacher *tea=NULL;	//教师
Student *stu=NULL;	//学生
Score *sco=NULL;	//成绩

//分配内存，初始化
void init_data(void)
{
	tea=calloc(sizeof(Teacher),TEA);	//老师
	stu=calloc(sizeof(Student),STU);	//学生
	sco=calloc(sizeof(Score),SCO);		//成绩
	fCreate();
}

//提取文件数据
void fCreate(void)
{	
	//教师
	FILE *t_frp=fopen(TEA_LOC,"r");
	if(t_frp==NULL)
	{
		printf("教师数据加载失败\n");
	}
	while(fscanf(t_frp,"%s %s %s %s %c %d",tea[Tea_num].name,tea[Tea_num].sex,tea[Tea_num].id,tea[Tea_num].pwd,&tea[Tea_num].is_work,&tea[Tea_num].is_lock)!=EOF)
	{
		encrypt(tea[Tea_num].pwd,2);	//解密
		Tea_num++;
	}
	fclose(t_frp);
	t_frp=NULL;
	//学生
	FILE *si_frp=fopen(STU_LOC,"r");
	if(si_frp==NULL)
	{
		printf("学生数据加载失败\n");
	}
	while(fscanf(si_frp,"%s %s %s %s %c %d",stu[Stu_num].name,stu[Stu_num].sex,stu[Stu_num].id,stu[Stu_num].pwd,&stu[Stu_num].is_sch,&stu[Stu_num].is_lock)!=EOF)
	{
		encrypt(stu[Stu_num].pwd,2);	//解密
		Stu_num++;
	}	
	fclose(si_frp);
	si_frp=NULL;
	//成绩
	FILE *ss_frp=fopen(SCO_LOC,"r");
	if(ss_frp==NULL)
	{
		printf("学生成绩加载失败\n");
	}
	while(fscanf(ss_frp,"%s %s %lf %lf %lf %lf",sco[Sco_num].name,sco[Sco_num].id,&sco[Sco_num].chn,&sco[Sco_num].math,&sco[Sco_num].eng,&sco[Sco_num].total)!=EOF)
	{
		Sco_num++;
	}
	fclose(ss_frp);	
	ss_frp=NULL;
	
	//校长
	FILE *hm_frp=fopen(HM_LOC,"r");
	if(hm_frp==NULL)
	{
		printf("校长加载失败\n");
	}
	fscanf(hm_frp,"%s",Hm_pwd);
	encrypt(Hm_pwd,2);
	fclose(hm_frp);	
	hm_frp=NULL;
}

//登录
void login(void)
{
	system("clear");
	printf("\n-------------------------------------\n");
	printf("请选择您的身份(0-校长;1-教师;2-学生;3-退出)：");
	
	if(scanf("%d",&Rank)!=1)
	{
		CACHE_CLEAR;
		return;
	}
	
	switch(Rank)
	{
		case 0:login_hm();	break;
		case 1:login_m(tea,Tea_num,sizeof(Teacher));	break;
		case 2:login_m(stu,Stu_num,sizeof(Student));	break;
		default:save_data();	//保存数据
			//释放内存
			free(tea);	tea=NULL;
			free(stu);	stu=NULL;
			free(sco);	sco=NULL;
			exit(0);	//退出
	}
}

//保存数据
void save_data(void)
{
	//写入教师数据
	FILE *t_fwp=fopen(TEA_LOC,"w");
	if(t_fwp==NULL)
	{
		perror("fopen");
	}
	for(int i=0;i<Tea_num;i++)
	{
		encrypt(tea[i].pwd,1);	//加密
		fprintf(t_fwp,"%s %s %s %s %c %d\n",tea[i].name,tea[i].sex,tea[i].id,tea[i].pwd,tea[i].is_work,tea[i].is_lock);
	}
	fclose(t_fwp);
	t_fwp=NULL;
	//写入学生数据
	FILE *si_fwp=fopen(STU_LOC,"w");
	if(si_fwp==NULL)
	{
		perror("fopen");
	}
	for(int i=0;i<Stu_num;i++)
	{
		encrypt(stu[i].pwd,1);	//加密
		fprintf(si_fwp,"%s %s %s %s %c %d\n",stu[i].name,stu[i].sex,stu[i].id,stu[i].pwd,stu[i].is_sch,stu[i].is_lock);
	}
	fclose(si_fwp);
	si_fwp=NULL;
	//写入成绩
	FILE *ss_fwp=fopen(SCO_LOC,"w");
	if(ss_fwp==NULL)
	{
		perror("fopen");
	}
	for(int i=0;i<Sco_num;i++)
	{
		fprintf(ss_fwp,"%s %s %.1lf %.1lf %.1lf %.1lf\n",sco[i].name,sco[i].id,sco[i].chn,sco[i].math,sco[i].eng,sco[i].total);
	}
	fclose(ss_fwp);	
	ss_fwp=NULL;
	
	//写入校长密码
	FILE *hm_fwp=fopen(HM_LOC,"w");
	if(hm_fwp==NULL)
	{
		printf("校长加载失败\n");
	}
	encrypt(Hm_pwd,1);	//加密
	fprintf(hm_fwp,"%s",Hm_pwd);
	fclose(hm_fwp);	
	hm_fwp=NULL;
}

//产生随机id
void rand_id(int year,char* id)
{
	int n=year*1000;
	n+=Stu_num;
	sprintf(id,"%d",n);
}

//学生、老师登录
void login_m(void *p,int num,int n)	//p:结构首地址 num:人数 n:结构大小
{
	char (*mem)[n]=p;
	char pwd[30]={};
	
	printf("请输入%s:",Rank==1?"工号":"学号");
	scanf("%s",User);	
	int i=0;
	for(i=0;i<num;i++)
	{
		if(!strcmp(&mem[i][24],User))
		{
			break;
		}
	}
	//判断用户是否存在
	if(strcmp(&mem[i][24],User))
	{
		printf("该用户不存在\n");
		anykey_continue();
		return;
	}
	//判断用户有无登录权限
	if(mem[i][44]=='F')
	{
		printf("该用户无登录权限\n");
		anykey_continue();
		return;
	}
	//判断帐号是否被锁定
	if(mem[i][48]==3)
	{
		printf("此帐号已被锁定，请找上级解锁\n");
		anykey_continue();
		return;
	}
	printf("请输入密码:");
	CACHE_CLEAR;
	hide_pwd(pwd);
	CACHE_CLEAR;
	if(strcmp(&mem[i][32],pwd))
	{
		printf("\n密码错误\n");
		mem[i][48]++;	//密码错误次数自增
		anykey_continue();
		return;
	}
	else
	{
		mem[i][48]=0;	//将密码错误次数置0
		Sub=i;		//确认下标
		//若密码为初始密码，则进入修改密码
		if(!strcmp(&mem[i][32],INIT_PWD))	
		{	
			mod_pwd(&mem[i][32]);
		}	
		if(Rank==1)		//若为1则进入教师菜单
		{
			menu_tch();
		}
		if(Rank==2)		//若为2则进入学生菜单
		{
			menu_stu();
		}
		return;
	}
}
//按任意键继续
void anykey_continue(void)
{	
	 puts("按任意键继续...");
	 CACHE_CLEAR;
	 getch();
}

//隐藏显示密码
void hide_pwd(char *pwd)
{
	int i=0;
	for(i=0;i<30;i++)
	{
		pwd[i]=getch();	//不显示输入
		if(pwd[i]==127)
		{
			if(i>0)
			{
				pwd[--i]='\0';
				i--;
				printf("\33[1D");	//输入退格，光标左移
			}
			else
				i=-1;
		}
		else
			printf("\33[1C");		//输入其他键，光标右移
		if(pwd[i]=='\n'){			
			break;
		}
	}
	pwd[i]='\0';
}

//修改密码
void mod_pwd(char* old_pwd)
{
	system("clear");
	puts("\n**********密码修改**********\n");
	char pwd[30]={};
	char pwd1[30]={};
	if(strcmp(old_pwd,INIT_PWD))
	{
		printf("请输入原密码：");
		CACHE_CLEAR;
		hide_pwd(pwd);
		if(strcmp(old_pwd,pwd))
		{
			printf("密码输入错误\n");
			anykey_continue();
			return;
		}
	}
	while(1)
	{
		while(1)
		{
			printf("\n请输入新密码：");
			CACHE_CLEAR;
			hide_pwd(pwd);
			if(!strcmp(pwd,INIT_PWD) || strlen(pwd)<6)
			{
				printf("\n密码过于简单,请重新输入\n");
				continue;
			}
			if(strlen(pwd)>11)
			{
				printf("\n超过密码11位长度限制,请重新输入\n");
				continue;
			}
			break;
		}
		printf("\n请二次确认密码：");
		CACHE_CLEAR;
		hide_pwd(pwd1);
		if(!strcmp(pwd,pwd1))
		{
			strcpy(old_pwd,pwd);
			printf("\n重置成功\n");
			break;
		}
		else
		{
			printf("\n密码不一致,重置失败\n");
			if(strcmp(old_pwd,INIT_PWD))
			{
				break;
			}
		}
	}	
	anykey_continue();
}
//加密解密
void encrypt(char* p,int f)	//f=1加密	f=2解密
{
	for(int i=0;p[i];i++)
	{
		if(f==1)
			p[i]+=2*(i-3);
		if(f==2)
			p[i]-=2*(i-3);
	}
}
//fgets去除末尾回车
char* fgets_m(char* s,int size)
{
	CACHE_CLEAR;
	fgets(s,size,stdin);
	CACHE_CLEAR;
	if(strlen(s)<size-1)
	{
		s[strlen(s)-1]='\0';
	}
	return s;
}










