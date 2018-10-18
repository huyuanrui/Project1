#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"

course *create_link_cour()
{
    FILE *fp = NULL;
    course *head = NULL, *p = NULL, *newp = NULL, val;
    if ( (fp = fopen("./resource/course.txt", "r")) == NULL)
    {
        printf("打开文件 course.txt 失败!\n");
        exit(1);
    }
    head = (course *)malloc(sizeof(course));
    head->next = NULL;
    p = head;
    while ( fread(&val, sizeof(course), 1, fp) )
    {
        newp = (course *)malloc(sizeof(course));
        newp->next = NULL;
        strcpy(newp->num, val.num);
        strcpy(newp->name, val.name);
        strcpy(newp->type, val.type);
        newp->time = val.time;
        newp->score = val.score;
        newp->sum = val.sum;
        newp->max = val.max;

        p->next = newp;
        p = p->next;
    }
    fclose(fp);
    return head;
}

void course_add(course *head)
{
    course *p = head, *newp = NULL;
    char answer = 'y', log[100] = "课程编号: ";
    while (answer == 'y')
    {
        newp = (course *)malloc(sizeof(course));
        newp->next = NULL;
        printf("请输入课程编号:");
        scanf("%s", newp->num);
        p = head;
        strcpy(head->num, "-1");
        while (p->next != NULL)
        {
            if ( strcmp(p->num, newp->num) == 0 )
            {
                printf("该课程已经存在!\n");
                free(newp);
                return;
            }
            p = p->next;
        }
        if ( strcmp(p->num, newp->num) == 0 )
        {
            printf("该课程已经存在!\n");
            free(newp);
            return;
        }
        printf("请输入课程名称:");
        scanf("%s", newp->name);
        printf("请输入课程性质:");
        scanf("%s", newp->type);
        printf("请输入授课学时:");
        scanf("%d", &newp->time);
        printf("请输入课程学分:");
        scanf("%d", &newp->score);
        printf("请输入课程人数上限:");
        scanf("%d", &newp->max);
        newp->sum = 0;

        p->next = newp;
        p = p->next;

        printf("\n\t课程信息录入成功!\n\n");

		strcat(log, p->num);
		strcat(log, " 操作类型: add 时间: ");
		write_log(log);

        printf("您需要再次添加学生信息吗？<y/n>");
        scanf(" %c", &answer);
    }
    course_update(head);
}

void course_delete(course *head_cour, student *head_stu)
{
    course *p = head_cour->next, *q = head_cour;
    char answer = 'y', input[20], log[100] = "课程编号: ";
    while (answer == 'y')
    {
        printf("请输入需要删除课程的编号或名字: ");
        scanf("%s", input);
        if (input[0] >= '0' && input[0] <= '9')
            p = cour_find_num(head_cour, input);
        else
            p = cour_find_name(head_cour, input);
        if (p == NULL)
            printf("\n\t未找到该课程!\n\n");
        else
        {
			strcat(log, p->num);
            stu_coursedele(head_stu, p->name, p->score);
            q = head_cour;
            while (q->next != p)
                q = q->next;
            q->next = p->next;
            free(p);
            printf("\n\t删除课程成功!\n\n");

			strcat(log, " 操作类型: delete 时间: ");
			write_log(log);
        }
        printf("您要继续删除课程吗？<y/n>");
        scanf(" %c", &answer);
    }
    course_update(head_cour);
    student_update(head_stu);
}

void course_look(course *head_cour, student *head_stu)
{
    char input[20], answer = 'y', log[100] = "课程编号: ";
    course *p = NULL;
    while (answer == 'y')
    {
        printf("请输入需要查找课程的编号或名字:");
        scanf("%s", input);
        if (input[0] >= '0' && input[0] <= '9')
        {
            p = cour_find_num(head_cour, input);
        }
        else
        {
            p = cour_find_name(head_cour, input);
        }
        if (p == NULL)
            printf("\n\t未找到该课程!\n\n");
        else
		{
            course_showone(p, head_stu);

			strcat(log, p->num);
			strcat(log, " 操作类型: look 时间: ");
			write_log(log);
		}
        printf("您要继续查找吗？<y/n>");
        scanf(" %c", &answer);
    }
}

void course_modify(course *head_cour, student *head_stu)
{
    char input[20], answer = 'y', oldname[20], log[100] = "课程编号(原编号:";
    int oldscore, flag, ret;
    course *p = head_cour->next, *temp = NULL;
    while (answer == 'y')
    {
        p = head_cour->next;
        printf("请输入需要修改课程的编号或名字:");
        scanf("%s", input);
        if (input[0] >= '0' && input[0] <= '9')
            p = cour_find_num(head_cour, input);
        else
            p = cour_find_name(head_cour, input);
        if (p == NULL)
        {
            printf("\n\t未找到该课程!\n\n");
            return;
        }
		strcat(log, p->num);
        strcpy(oldname, p->name);
        oldscore = p->score;
        printf("原课程编号: %s\t请输入修改后的编号:", p->num);
        scanf("%s", p->num);
        temp = cour_find_num(head_cour, p->num);
        if (temp != p)
        {
            printf("\n该课程编号已存在!请重新输入!\n\n");
            continue;
        }
        temp = cour_find_num(p, p->num);
        if (temp != NULL)
        {
            printf("\n该课程编号已存在!\n\n");
            return;
        }
        printf("原课程名称: %s\t请输入修改后的名称:", p->name);
        scanf("%s", p->name);
		stu_cournamechange(head_stu, oldname, p->name);
        printf("原课程性质: %s\t请输入修改后的性质:", p->type);
        scanf("%s", p->type);
        printf("原授课学时: %d\t请输入修改后的学时:", p->time);
        scanf("%d", &p->time);
        printf("原课程学分: %d\t请输入修改后的学分:", p->score);
        scanf("%d", &p->score);
		stu_courscorechange(head_stu, p->name, oldscore, p->score);
        printf("原课程已选人数: %d\t请输入修改后的已选人数:", p->sum);
        scanf("%d", &p->sum);
        printf("原课程人数上限: %d\t请输入修改后的人数上限:", p->max);
        scanf("%d", &p->max);
		while (1)
		{
			printf("所选学生列表：\n");
			course_showstu(head_stu, p->name);
			printf("[0]退出\t[1]增加学生\t[2]删除学生\n");
			scanf("%d", &flag);
			if (flag == 0)
				break;
			else if (flag == 1)
			{
				ret = course_addstu(head_stu, p->name, p->score);	
				if (ret == 1)
					p->sum++;
			}
			else if(flag == 2)
			{
				ret = course_delstu(head_stu, p->name, p->score);
				if (ret == 1)
					p->sum--;
			}
		}
        printf("\n\t修改课程成功!\n");
		strcat(log, "): ");
		strcat(log, p->num);
		strcat(log, " 操作类型: modify 时间: ");
		write_log(log);

        printf("您要继续修改吗？<y/n>");
        scanf(" %c", &answer);
    }
    course_update(head_cour);
    student_update(head_stu);
}

void course_update(course *head)
{
    FILE *fp = NULL;
    course *p = head->next;
    if ( (fp = fopen("./resource/course.txt", "w")) == NULL)
    {
        printf("打开文件 course.txt 失败!\n");
        exit(1);
    }
    while (p != NULL)
    {
        fwrite(p, sizeof(course), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void course_showall(course *head)
{
    course *p = head->next;
	printf("\n\t---------------------------全部课程信息---------------------------\n");
	printf("\t编号\t名称\t性质\t学时\t学分\t已选人数\t人数上限\n");
	while (p != NULL)
	{
		printf("\t%s\t%s\t%s\t%d\t%d\t%d\t\t%d\n", p->num, p->name, p->type, p->time, p->score, p->sum, p->max);
		p = p->next;
	}
	printf("\t------------------------------------------------------------------\n");
	printf("按下回车键继续!");
    getchar();
    getchar();
}

void course_showone(course *p, student *head_stu)
{
	student *p_stu = head_stu->next;
	int i, count = 0;
	if (p == NULL)
		return;
	printf("\n\t\t----------------------------\n");
	printf("\t\t课程编号: %s\n", p->num);
	printf("\t\t课程名称: %s\n", p->name);
	printf("\t\t课程性质: %s\n", p->type);
	printf("\t\t授课学时: %d\n", p->time);
	printf("\t\t学分: %d\n", p->score);
	printf("\t\t课程已选人数: %d\n", p->sum);
	printf("\t\t课程人数上限: %d\n", p->max);
	if (p->sum > 0)
		printf("\t\t所选学生列表:\n");
	while (count < p->sum && p_stu != NULL)
	{
		for (i = 0; i < p_stu->course_sum; i++)
		{
			if ( strcmp(p_stu->course[i], p->name) == 0 )
			{
				count++;
				printf("\t\t\t学号:%s\t姓名:%s\n", p_stu->id, p_stu->name);
				break;
			}
		}
		p_stu = p_stu->next;
	}
	printf("\t\t----------------------------\n");
}

void coursesum_change(course *head, char *coursename, int val)
{
    course *p = NULL;
    p = cour_find_name(head, coursename);
    if (p == NULL)
    {
        printf("\n\t更改课程已选人数出错!\n");
        return;
    }
    p->sum += val;
    course_update(head);
}

course *cour_find_num(course *head, char num[])
{
    course *p = NULL;
    if (head == NULL)
        return head;
    p = head->next;
    while (p != NULL)
    {
        if (strcmp(num, p->num) == 0)
            return p;
        p = p->next;
    }
    return p;
}

course *cour_find_name(course *head, char name[])
{
    course *p = head->next;
    while (p != NULL)
    {
        if (strcmp(name, p->name) == 0)
            return p;
        p = p->next;
    }
    return p;
}

void stu_coursedele(student *head_stu, char name[], int val)
{
    int i;
    student *p = head_stu->next;
    while (p != NULL)
    {
        for (i = 0; i < p->course_sum; i++)
        {
            if (strcmp(p->course[i], name) == 0)
            {
                p->score -= val; 
                for (; i < p->course_sum - 1; i++)
                    strcpy(p->course[i], p->course[i+1]);
                p->course_sum--;
                break;
            }
        }
        p = p->next;
    }
    if (p == NULL)
        printf("删除课程同时修改学生信息是出错!\n");
}

void stu_cournamechange(student *head_stu, char oldname[], char newname[])
{
    int i;
    student *p = head_stu->next;
    while (p != NULL)
    {
        for (i = 0; i < p->course_sum; i++)
        {
            if ( strcmp(p->course[i], oldname) == 0 )
                strcpy(p->course[i], newname);
            break;
        }
        p = p->next;
    }
}

void stu_courscorechange(student *head_stu, char courname[], int oldscore, int newscore)
{
    int i;
    student *p = head_stu->next;
    while (p != NULL)
    {
        for (i = 0; i < p->course_sum; i++)
        {
            if (strcmp(p->course[i], courname) == 0)
            {
                p->score = p->score - oldscore + newscore;
                break;
            }
        }
        p = p->next;
    }
}

void course_showstu(student *head_stu, char coursename[])
{
	int i;
	student *p = head_stu->next;
	while (p != NULL)
	{
		for (i = 0; i < p->course_sum; i++)
		{
			if ( strcmp(p->course[i], coursename) == 0 )
			{
				student_showone(p);
				break;
			}
		}
		p = p->next;
	}
}

int course_addstu(student *head_stu, char coursename[], int score)
{
	int i;
	char id[20];
	student *p_stu = NULL;
	printf("请输入需要添加学生的学号:\n");
	scanf("%s", id);
	p_stu = stu_find_id(head_stu, id);
	if (p_stu == NULL)
	{
		printf("未找到该学号!按回车键继续");
		getchar();
		getchar();
		return 0;
	}
	for (i = 0; i < p_stu->course_sum; i++)
	{
		if (strcmp(p_stu->course[i], coursename) == 0)
		{
			printf("该学生已选该课程!按回车键继续");
			getchar();
			getchar();
			return 0;
		}
	}
	strcpy(p_stu->course[p_stu->course_sum], coursename);
	p_stu->course_sum++;
	p_stu->score += score;
	printf("添加学生成功!按回车键继续!");
	getchar();
	getchar();
	return 1;
}

int course_delstu(student *head_stu, char coursename[], int score)
{
	int i;
	student *p_stu = NULL;
	char id[20];
	printf("请输入需要添加学生的学号:\n");
	scanf("%s", id);
	p_stu = stu_find_id(head_stu, id);
	if (p_stu == NULL)
	{
		printf("未找到该学号!按回车键继续");
		getchar();
		getchar();
		return 0;
	}
	for (i = 0; i < p_stu->course_sum; i++)
	{
		if ( strcmp(p_stu->course[i], coursename) == 0 )
		{
			for (; i < p_stu->course_sum - 1; i++)
				strcpy(p_stu->course[i], p_stu->course[i+1]);
			p_stu->course_sum--;
			p_stu->score -= score;
			printf("删除学生成功!按回车键继续");
			getchar();
			getchar();
			return 1;
		}
	}
	printf("该学生没有选择该课程!按回车键继续");
	getchar();
	getchar();
	return 0;
}
