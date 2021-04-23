#include<iostream>
#include<fstream>
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
	float totalmark;
	float finalmark;
	float midtermmark;
	float orthermark;
	const int type = 0;
	int socialid;
	student* next;
	date dob;
};

// Thieu Ham Lay Du Lieu Tu File Course Class vo Linked List
void export_student_in_courses(student* head, string course_class)
{
	
	if (head == nullptr) {// Ham lay danh sach lop vao linked list };


	fstream export;
	export.open(course_class + ".csv", fstream::out);
	export << "No" << "," << "Student ID" << "First Name" << "," << "Last Name" << "," << "Gender"<<", "<<"Date of Birth"<<", "<<"Social ID"<<","<<"Midterm Mark"<<","<<"Final Mark"<<","<<"Other Mark"<<","<<"Total Mark"<<endl;
	while (head !=nullptr)
	{
		export << head->no << ",";
		export << head->id << ",";
		export << head->firstname << ",";
		export << head->lastname << ",";
		export << head->gender << ",";
		export << head->dob.day << "/" << head->dob.month << "/" << head->dob.year << ",";
		export << head->sclass << ",";
		export << head->socialid << ",";
		export << ",,,";
		if (head->next != nullptr)  cout<<endl;
	
		head = head->next;
}
	export.close();
}
