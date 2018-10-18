#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"

int manger_login(void)
{
	char passwd[20];
	int count = 0;
	while (1)
	{
		if (count >= 5)
		{
			printf("\n密码已输错5次，将退出系统!\n");
			return 0;
		}
		printf("\n请输入密码:");
		scanf("%s", passwd);
		if (strcmp(passwd, "123456") == 0)
		{
			printf("\n管理员登录成功!\n");
			break;
		}
		printf("密码错误!(密码输错5次将会自动退出系统)\n");
		count++;
	}
}

int manger_menu(void)
{
	int ret;
	printf("\n\n");
	printf("\t\t\t--------------菜单--------------\n");
	printf("\t\t\t[0]返回上一级\n\n");
	printf("\t\t\t[1]新增课程\n");	
	printf("\t\t\t[2]删除课程\n");
	printf("\t\t\t[3]查看课程信息\n");
	printf("\t\t\t[4]修改课程信息\n\n");

	printf("\t\t\t[5]新增学生\n");
	printf("\t\t\t[6]删除学生\n");
	printf("\t\t\t[7]查看学生信息\n");
	printf("\t\t\t[8]修改学生信息\n\n");

	printf("\t\t\t[9]查看所有学生信息\n");
	printf("\t\t\t[10]查看所有学生信息\n");
	printf("\t\t\t--------------------------------\n\n");

	scanf("%d", &ret);
	return ret;
}

student *create_link_stu(void)
{
    FILE *fp = NULL;
    student *head = NULL, *p = NULL, *newp = NULL, val;
    if ( (fp = fopen("./resource/student.txt", "r")) == NULL )
    {
        printf("打开文件 student.txt 失败!\n");
        exit(1);
    }
    head = (student *)malloc(sizeof(student));
    head->next = NULL;
    p = head;
    while ( fread(&val, sizeof(student), 1, fp) )
    {
        newp = (student *)malloc(sizeof(student));

        strcpy(newp->id, val.id);
        strcpy(newp->name, val.name);
        memcpy(newp->course , val.course, sizeof(val.course));
        newp->course_sum = val.course_sum;
        newp->score = val.score;
        strcpy(newp->passwd, val.passwd);
        newp->next = NULL;

        p->next = newp;
        p = p->next;
    }
    fclose(fp);
    return head;
}

void student_add(student *head)
{
    student *p = head, *newp = NULL;
    char answer = 'y', log[100] = "学生学号: ";
    while (answer == 'y')
    {
        newp = (student *)malloc(sizeof(student));
        newp->next = NULL;
        printf("请输入学生学号：");
        scanf("%s", newp->id);
        p = head;
        strcpy(head->id, "-1");
        while (p->next != NULL)
        {
            if ( strcmp(p->id, newp->id) == 0 )
            {
                printf("该学号已经存在!\n");
                free(newp);
                return;
            }
            p = p->next;
        }
        if ( strcmp(p->id, newp->id) == 0 )
        {
            printf("该学号已经存在!\n");
            free(newp);
            return;
        }
        printf("请输入学生姓名：");
        scanf("%s", newp->name);
        newp->score = 0;
        newp->course_sum = 0;
        strcpy(newp->passwd, "123456");

        p->next = newp;
        p = p->next;
        printf("\n\t学生信息录入成功!\n\n");

		strcat(log, p->id);
		strcat(log, " 操作类型: add 时间: ");
		write_log(log);

        printf("您要再次录入学生信息吗？<y/n>");
        scanf(" %c", &answer);
    }
    student_update(head);
}

void student_delete(student *head_stu, course *head_cour)
{
    int i;
    char id[20];
    char answer = 'y', log[100] = "学生学号: ";
    student *p = head_stu->next, *q = head_stu;
    while (answer == 'y')
    {
        p = head_stu->next;
        q = head_stu;
        printf("请输入需要删除的学生的学号：");
        scanf("%s", id);
        while (p != NULL)
        {
            if ( strcmp(id, p->id) == 0 )
            {
				strcat(log, p->id);
                for (i = 0; i < p->course_sum; i++)     /* 减少对应课程数量 */
                {
                    coursesum_change(head_cour, p->course[i], -1);
                }
                q->next = p->next;
                free(p);
                printf("\n\t删除学生信息成功!\n\n");

				strcat(log, " 操作类型: delete 时间: ");
				write_log(log);
                break;
            }
            q = p;
            p = p->next;
        }
        if (p == NULL)
            printf("\n\t未找到该学生!\n\n");
        printf("您要继续删除学生信息吗? <y/n>");
        scanf(" %c", &answer);
    }
    student_update(head_stu);
}


void student_modify(student *head)
{
    student *p = head->next;
    char answer = 'y', id[20], log[100] = "学生学号(原学号:";
    while (answer == 'y')
    {
        p = head->next;
        printf("请输入需要修改学生的学号:");
        scanf("%s", id);
        while (p != NULL)
        {
            if (strcmp(id, p->id) == 0)
            {
                printf("原学号: %s\t请输入修改后的学号:", p->id);
                scanf("%s", p->id);
                printf("原姓名: %s\t请输入修改后的姓名:", p->name);
                scanf("%s", p->name);
                printf("原总学分: %d\t请输入修改后的总学分:", p->score);
                scanf("%d", &p->score);
                printf("\n\t修改学生信息成功!\n\n");

				strcat(log, id);
				strcat(log, "): ");
				strcat(log, p->id);
				strcat(log, " 操作类型: modify 时间: ");
				write_log(log);
                break;
            }
            p = p->next;
        }
        if (p == NULL)
            printf("\n\t未找到该学生!\n\n");
        printf("您要继续修改吗？<y/n>");
        scanf(" %c", &answer);
    }
    student_update(head);
}

void student_look(student *head)
{
    student *p = NULL;
    char answer = 'y';
    char input[20], log[100];
    while (answer == 'y')
    {
        printf("请输入需要查找学生的学号或姓名:");
        scanf("%s", input);
        if ( input[0] >= '0' && input[0] <= '9' )
        {
            p = stu_find_id(head, input);
        }
        else
        {
            p = stu_find_name(head, input);
        }
        if (p == NULL)
            printf("\n\t未找到该学生!\n\n");
        else
		{
            student_showone(p);
			log[0] = '\0';
			strcat(log, "学生学号: ");
			strcat(log, p->id);
			strcat(log, " 操作类型: look 时间: ");
			write_log(log);
		}
        printf("您需要继续查找吗？<y/n>");
        scanf(" %c", &answer);
    }
}

void student_showone(student *p)
{
    int i;
    if (p == NULL)
        return;
    printf("\n\t\t------------------------------\n");
    printf("\t\t学生学号：%s\n", p->id);
    printf("\t\t学生姓名：%s\n", p->name);
    if (p->course_sum == 0)
        printf("\n\t\t该学生暂未选课!\n\n");
    else
        printf("\t\t已选课程:\n");
    for (i = 0; i < p->course_sum; i++)
        printf("\t\t\t%s\n", p->course[i]);
    printf("\t\t已选课程学分：%d\n",p->score);
    printf("\t\t密码: %s\n", p->passwd);
    printf("\t\t------------------------------\n");
}

void student_showall(student *head)
{
    student *p = head->next;
	printf("\n\t\t------------------全部学生信息------------------\n");
	printf("\t\t学号\t姓名\t选课数量\t已选课程学分\n");
	while (p != NULL)
	{
		printf("\t\t%s\t%s\t%d\t\t%d\n", p->id, p->name, p->course_sum, p->score);
		p = p->next;
	}
	printf("\t\t------------------------------------------------\n");
	printf("按下回车键返回主菜单!");
    getchar();
    getchar();
}

void student_update(student *head)
{
    FILE *fp = NULL;
    student *p = head->next;
    if ( (fp = fopen("./resource/student.txt", "w")) == NULL )
    {
        printf("打开文件 student.txt 失败!\n");
        exit(1);
    }
    while (p != NULL)
    {
        fwrite(p, sizeof(student), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

student *stu_find_id(student *head, char id[])
{
    student *p = head->next;
    while (p != NULL)
    {
        if (strcmp(id, p->id) == 0)
        {
            break;
        }
        p = p->next;
    }
    return p;
}

student *stu_find_name(student *head, char name[])
{
    student *p = head->next;
    while (p != NULL)
    {
        if ( strcmp(name, p->name) == 0 )
        {
            break;
        }
        p = p->next;
    }
    return p;
}

void write_log(char *str)
{
	time_t t;
	struct tm *tp;
	FILE *fp = NULL;
	if ( (fp = fopen("log.log", "a")) == NULL )
	{
		printf("打开日志文件失败!\n");
		return;
	}
	time(&t);
	tp = localtime(&t);
	fprintf(fp, "%s", str);
	fprintf(fp, "%d年%d月%d日%d时%d分%d秒\n", tp->tm_year+1900, tp->tm_mon+1,tp->tm_mday ,tp->tm_hour,tp->tm_min,tp->tm_sec);   
	fclose(fp);
}

