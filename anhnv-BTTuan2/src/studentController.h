#ifndef _SUTDENTCONTROLLER_H_
#define _SUTDENTCONTROLLER_H_

#include "student.h"

bool checkID(string, int, Student);
void addFK(int);
void addFF(int);
void add(int);
void show();
void update();
void searchID();
void searchName();
void searchMath();
void searchPhysics();
void searchChemistry();
void searchTotal();
void search();
void swap();
void sortID(int, Student[]);
void sortName(int, Student[]);
void sortTotal(int, Student[]);
void sort(int, Student[]);
void del();
void stat();

#endif
