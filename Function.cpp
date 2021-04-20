#include <iostream>
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
	int id;
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
};

struct Course {
	int CoId;
	string CoName;
	string teacherName;
	int credit;
	int maxSt = 50;
	string day[2];
	string s[2];
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
};

void inputAcc(fstream& acc, student*& a);
void login(student* a, string& usn);
void deleteList(student*& a);
void display(ifstream& ifs, string u);
void changepass(fstream& fs, string u, student* a);

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