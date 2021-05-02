#ifndef _FINAL_H_
#define _FINAL_H_
#define _CRT_SECURE_NO_WARNINGS

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
	float totalmark;
	float finalmark;
	float midtermmark;
	float othermark;
	const int type = 0;
	string socialid;
	student* next = 0;
	date dob;
};

struct staff
{
	string fullname;
	string gender;
	string password;
	string username;
	const int type = 1;
	staff* next = 0;
};

struct StuofCourse
{
	int StuEnroll = 0;//num of Students enrolling to course right now;
	student* Stu = 0;
};

struct Course {
	int no;
	string CoId, CoName, teacherName;
	int credit, maxSt = 50;
	string day[2], s[2];
	Course* next = 0;
	StuofCourse* SofC = 0;
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

struct course_class
{
	string data;
	course_class* next = 0;
};

//log in
void inputAcc(fstream& acc, student*& stuAcc, staff*& staAcc);
void login(student* stuAcc, staff* staAcc, student*& stuCur, staff*& staCur, bool& exit);
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
void displayCourseList(Sem srr[], int i, int year);//4
void deleteCourse(Sem srr[]);
void write_data_CourseList(Sem srr[], int i, int year);
void updateCourse(Sem srr[]);
int checkRealTime(Sem srr[], int i);
bool isInSem(string SemStart, string SemEnd, tm* t, int* day, int* mon, int* year);
bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int* year, int* hour, int* min);
void write_data_course(Sem srr[], int i, int year);

//3
void InputMyCourse(Course*& MyCo, int& n, student* Student);
void InputAvailCourse(Sem srr[], Course* MyCo, int& i);
void EnrollCourse(Sem S, Course*& MyCourse, int& count, student* Student, fstream& fSoC); // S la hoc ki voi cac course dc staff nhap vao
void AddStutoCourse(Course*& MyCo, student* Student);
void ViewAvailableCourse(Sem S, int i);
void RemoveAlreadyCourses(Course*& pHead, int k);
void ViewMyCourse(Sem S, int i, Course* MyCo);
void DeleteCourse(Sem& S, Course*& MyCo, int& count, student *Student, fstream& fSoC);
void RemoveStuofCo(Course*& MyCo, student* Student);
void OperateTask(Sem srr[], student* Student, int i);
void DeleteList(Course*& MyCo, Sem& S);
void StoreCoursesofStu(Course* MyCourse, int count, student* Student);
void StoreStusofCourse(Course* MyCourse, fstream& f);

//4 
void ViewMyCourseAfterRegistrationOver(Course* MyCo, int i);

//5
void menuView(Sem srr[], int i, int year);
void ViewClass();
void ViewStudentofClass();
void ViewStudentsofCourse(Sem S);

//6
string choose_class();
void load_stu_course_class(student*& head, string* classs);
void export_student_in_courses(student* head, string* classs);
void delete_linked_list(student*& head);
void import_stu_mark();
void view_course_score();
void view_class_score();
void view_owner_score();
void menuScore();

#endif