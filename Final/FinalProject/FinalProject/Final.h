#ifndef _FINAL_H_
#define _FINAL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

struct date
{
	int day;
	int month;
	int year;
};

struct student
{
	int no;
	long int id;
	string firstname;
	string lastname;
	string password;
	string sclass;
	string gender;
	const int type = 0;
	int socialid;
	student* next;
	date dob;
};

struct staff
{
	string fullname;
	string gender;
	string password;
	string username;
	const int type = 1;
	staff* next;
};

struct Course {
	int no;
	string CoId, CoName, teacherName;
	int credit, maxSt = 50;
	string day[2], s[2];
	Course* next;
};

struct Sem {
	int year;
	string SemStart;
	string SemEnd;
	string regisStart;
	string regisEnd;
	Course* head = nullptr;
	Course* cur = nullptr;
	Course s;
};

void inputAcc(fstream& acc, student*& stuAcc, staff*& staAcc);
void login(student* stuAcc, staff* staAcc, string& usn, student*& stuCur, staff*& staCur);
void displayBasicInfo(student* stuCur, staff* staCur);
void changepass(student* stuAcc, staff* staAcc, student* stuCur, staff* staCur);

//1
bool check_file_exist(string* file);
void create_class(student*& head);
void import_list(student*& head, string* severalclass);
void add_class_list(string* severalclass);
void create_school_year();

//2 
void TCmenu(Sem srr[], int i, int year);
void create_courselist(Sem srr[], int& i, int& year);
void displayCourseList(Sem srr[], int i, int year);
void deleteCourse(Sem srr[]);
void write_data_CourseList(Sem srr[], int i, int year);
void updateCourse(Sem srr[]);
bool checkRealTime(Sem srr[], int i);
bool isInSem(string SemStart, string SemEnd, tm* t, int* day, int* mon, int* year);
bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int* year, int* hour, int* min);
void write_data_course(Sem srr[], int i, int year);

//3

//4 
void ViewMyCourseAfterRegistrationOver(Sem S, int y);

//5
void ViewClass(ifstream myfile);
void ViewStudentofClass(student* head);

//6

#endif