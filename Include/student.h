#ifndef _STUDENT_H
#define _STUDENT_H

#include "common.h"

student *student_login(student *head);
int student_menu(void);
student *create_link_stu();
void student_add(student *head);
void student_delete(student *head_stu, course *head_cour);
void student_modify(student *head);
void student_look(student *head);
void student_showall(student *head);

#endif

