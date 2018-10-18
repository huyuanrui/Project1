#include <stdio.h>
#include <string.h>
#include "choose_course.h"


student *student_login(student *head)
{
	char id[20], passwd[10];
	student *p = NULL;
	while (p == NULL)
	{
		printf("\n请输入你的学号:");
		scanf("%s", id);
		p = stu_find_id(head, id);
		if (p == NULL)
			printf("学号错误!\n");
	}
	while (1)
	{
		printf("请输入密码:");
		scanf("%s", passwd);
		if (strcmp(passwd, p->passwd) == 0)
		{
			printf("\n学生用户登录成功!\n欢迎!\n");
			return p;
		}
		printf("密码错误!\n");
	}
}

int student_menu(void)
{
	int ret;
	printf("\t\t\t--------------菜单--------------\n");
	printf("\t\t\t[0]返回上一级\n\n");
	printf("\t\t\t[1]显示个人信息\n");
	printf("\t\t\t[2]选课\n");
	printf("\t\t\t--------------------------------\n");
	scanf("%d", &ret);
	return ret;
}

void choose_course(student *p_stu, course *head_cour)
{
	int i;
	char input[20];
	course *p_cour = NULL;
	printf("已有课程:\n");
	course_showall(head_cour);
	printf("请输入课程编号或名字:");
	scanf("%s", input);
	if (input[0] >= '0' && input[0] <= '9')
	{
		p_cour = cour_find_num(head_cour, input);
	}
	else
	{
		p_cour = cour_find_name(head_cour, input);
	}
	if (p_cour == NULL)
	{
		printf("没有该课程!请检查输入是否错误!\n");
		return;
	}
	else if (p_cour->sum == p_cour->max)
	{
		printf("该课程人数已达上限!\n");
		return;
	}
	for (i = 0; i < p_stu->course_sum; i++)
	{
		if ( strcmp(p_cour->name, p_stu->course[i]) == 0 )
		{
			printf("你已选择该课程，不可再次选择!\n");
			return;
		}
	}
	strcpy(p_stu->course[p_stu->course_sum], p_cour->name);
	p_stu->course_sum++;
	p_stu->score += p_cour->score;
	p_cour->sum++;
	course_update(head_cour);
	printf("选课成功!\n");
}

