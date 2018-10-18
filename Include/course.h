#ifndef _COURSE_H
#define _COURSE_H

#include "common.h"

course *create_link_cour();
void course_add(course *head);
void course_delete(course *head_cour, student *head_stu);
void course_look(course *head_cour, student *head_stu);
void course_modify(course *head_cour, student *head_stu);
int course_addstu(student *head_stu, char coursename[], int score);
int course_delstu(student *head_stu, char coursename[], int score);
void course_showone(course *p, student *head_stu);
void course_showall(course *head);
void stu_coursedele(student *head_stu, char name[], int val);
void stu_cournamechange(student *head_stu, char oldname[], char newname[]);
void stu_courscorechange(student *head_stu, char courname[], int oldscore, int newscore);
void course_showstu(student *head_stu, char coursename[]);

#endif

