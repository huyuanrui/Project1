#ifndef _COMMON_H
#define _COMMON_H

typedef struct COURSE
{
    char num[20];       /* 课程编号 */
    char name[20];      /* 课程名称 */
    char type[20];      /* 课程性质 */
    int time;           /* 授课学时 */
    int score;          /* 学分 */
    int sum;            /* 课程已选人数 */
    int max;            /* 课程人数上限 */
    struct COURSE *next;
}course;

typedef struct STUDENT
{
    char id[20];        /* 学生学号 */
    char name[20];      /* 学生姓名 */
    char course[20][20];    /* 已选课程列表 */
    int course_sum;         /* 已选课程数量 */
    int score;          /* 已选课程总学分 */
    char passwd[20];    /* 学生密码 */
    struct STUDENT *next;
}student;

void coursesum_change(course *head, char *coursename, int val);
course *cour_find_num(course *head, char num[]);
course *cour_find_name(course *head, char name[]);
void course_update(course *head);
void student_update(student *head);
student *stu_find_id(student *head, char id[]);
student *stu_find_name(student *head, char name[]);
void student_showone(student *p);
void write_log(char *str);

#endif
