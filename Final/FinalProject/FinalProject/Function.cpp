#include "Final.h"

void inputAcc(fstream& acc, student*& stu, staff*& sta) {
	while (!acc.eof())
	{
		int temp;//0 1
		string t;
		getline(acc, t);
		stringstream ss(t);
		ss >> temp;
		if (temp == 1) {
			staff* pC = 0;
			if (sta == 0) {
				sta = new staff;
				pC = sta;
			}
			else {
				pC->next = new staff;
				pC = pC->next;
			}
			getline(ss, pC->username, ',');
			getline(ss, pC->password, ',');
			pC->next = 0;
		}
		else {
			student* pC = 0;
			if (stu == 0) {
				stu = new student;
				pC = stu;
			}
			else {
				pC->next = new student;
				pC = pC->next;
			}
			getline(ss, pC->username, ',');
			getline(ss, pC->password, ',');
			pC->next = 0;
		}
	}
}

void login(student* stu, string& usn);
void deleteList(student*& stu);
void display(ifstream& ifs, string u);
void changepass(fstream& fs, string u, student* stu);

//realtime
void takeRealTime(string SemStart, string SemEnd, string ReStart, string ReEnd);
bool isInSem(string SemStart, string SemEnd, tm* t, int* day, int* mon, int* year);
bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int* year, int* hour, int* min);

//1
bool check_file_exist(string* file);
void create_class(student*& head);
void import_list(student*& head, string* severalclass);
void add_class_list(string* severalclass);
void create_school_year();

//2 
void TCmenu(Sem se, Sem srr[], int i, int year, int season);
void create_courselist(Sem& se, Sem srr[], int& i, int& year, int& season);
void displayCourseList(Sem se, Sem srr[], int i, int year, int season);
void deleteCourse(Sem& se, Sem srr[], int i);

//3
void InputCourse(fstream& f, Sem& S, int& y);
void EnrollCourse(Sem S, Course*& MyCourse);
void ViewAvailableCourse(Sem S, int y);
void ViewMyCourse(Sem S, int y, Course* MyCo);
void DeleteCourse(Sem& S, Course*& MyCo);
void OperateTask(Sem& S, Course*& MyCourse, int& y);

//5
void viewClass() {};
void ViewStudentofClass(student* head);
void viewCourseStu() {};

//6
void exportClassList() {};
void importScore() {};//(CSV) 1,20127062,Nguyen Khai Phu,8,10,7,5
void viewCourseScore() {};
void upScore() {};
void viewClassScore() {};//Final scores, Sem GPA, overall GPA
void viewStuScore() {};