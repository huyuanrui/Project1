#ifndef _CHOOSE_COURSE_H
#define _CHOOSE_COURSE_H

#include "common.h"

student *student_login(student *head);
int student_menu(void);
void choose_course(student *p_stu, course *head_cour);

#endif
