#include<iostream>
#include<string>
#include<iomanip>
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

struct course_class
{
	string data;
	course_class* next;
};

string choose_class();
void load_stu_course_class(student*& head, string classs);
void export_student_in_courses(student* head,string* classs);

int main()
{
	student* head = nullptr;
	string classs = choose_class();// Chon lop de export file

	
	export_student_in_courses(head, &classs);

}


void export_student_in_courses(student* head, string* classs)
{
	
		
		ofstream output;
		output.open((*classs+"_math.csv").c_str());
		
		output << "No" << "," << "Student ID" <<','<< "First Name" << "," << "Last Name" << "," << "Gender" << ", " << "Date of Birth" << ", " << "Social ID" << "," << "Midterm Mark" << "," << "Final Mark" << "," << "Other Mark" << "," << "Total Mark" << endl;
		while (head != nullptr)
		{
			output << head->no << ",";
			output << head->id << ",";
			output << head->firstname << ",";
			output << head->lastname << ",";
			output << head->gender << ",";
			output << head->dob.day << "/" << head->dob.month << "/" << head->dob.year << ",";
			output << head->sclass << ",";
			output << head->socialid << ",";
			output << ",,,";
			if (head->next != nullptr)  cout << endl;

			head = head->next;
		}


		student* current = head;
		while (head != nullptr)
		{
			head = head->next;
			delete current;
			current = head;
		}



		output.close();
		
}



string choose_class()
{
	course_class* head =nullptr;
	course_class* current = nullptr;
	fstream input;
	input.open("Course_classes_list.csv", fstream::in);

	while (!input.eof())
	{
		course_class* add = new course_class;
		getline(input, add->data, ',');
		if (add->data.size() == 1) break;
		if (head == nullptr)
		{
			head = add;
			current = head;
		}
		else
		{
			current->next = add;
			current = current->next;
		}
		
		current->next = nullptr;
	}

	current = head;
	cout << "Course class list:" << endl;
	for (int i = 1; current != nullptr; i++)
	{
		cout << i << ". " << current->data << endl;
		current = current->next;
	}


	current = head;
	
	int key = 0; cout << "Enter your option:"; cin >> key;
	for (int i = 1; i < key; i++) current = current->next;
	string a(current->data.begin(), current->data.end());
	
	return a;
	input.close();
	
}

void load_stu_course_class(student*& head,string classs)
{

}

