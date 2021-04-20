#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
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

bool check_file_exist(string* file);
void create_class(student*& head);
void import_list(student*& head, string* severalclass);
void add_class_list(string* severalclass);
void create_school_year();

int main()
{
	student* list=nullptr;
	create_school_year();
	create_class(list);
}


bool check_file_exist(string* file)
{
	fstream myfile;
	myfile.open(*file, fstream::in);
	if (myfile.is_open())  return true;
	else return false;
	myfile.close();
}

void import_list(student*& head, string* severalclass)
{
	string fast_input;
	cout << "Enter the address of your file for fast input: "; cin >> fast_input;
	if (!check_file_exist(&fast_input)) { cout << "This file is not exist." << endl; return; }
	fstream myfile;
	myfile.open(fast_input, fstream::in);

	student* current = nullptr;
	char temp;
	while (!myfile.eof())
	{
		student* temp_ptr = new student;
		myfile >> temp_ptr->no; myfile >> temp;
		if (temp_ptr->no < 0) { break; }
		myfile >> temp_ptr->id; myfile >> temp;
		getline(myfile, temp_ptr->firstname, ',');
		getline(myfile, temp_ptr->lastname, ',');
		getline(myfile, temp_ptr->gender, ',');
		myfile >> temp_ptr->dob.day; myfile >> temp;
		myfile >> temp_ptr->dob.month; myfile >> temp;
		myfile >> temp_ptr->dob.year; myfile >> temp;
		myfile >> temp_ptr->socialid;
		temp_ptr->sclass = *severalclass;
		myfile.ignore();

		if (head == nullptr)
		{
			head = temp_ptr;
			current = head;
		}
		else
		{
			current->next = temp_ptr;
			current = current->next;
		}
		current->next = nullptr;
	}
	myfile.close();
}

void create_class(student*& head)
{
	string severalclass;
	while (getchar() != '\n');
	cout << "Enter the class:"; getline(cin, severalclass);
	string temp = severalclass + ".txt";
	if (check_file_exist(&temp)) { cout << "The class " << severalclass << " is exist." << endl; return; }
	import_list(head, &severalclass);
	add_class_list(&severalclass);
	fstream myfile, myfile1;
	myfile1.open("student.txt", fstream::app);
	myfile.open(temp, fstream::out);
	
	student* current = head;
	while (current != nullptr)
	{
		myfile1 << current->id << endl;
		myfile1 << current->dob.day << current->dob.month << current->dob.year << endl;
		myfile1 << current->firstname << endl << current->lastname << endl;
		myfile1 << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl;
		myfile1 << current->sclass << endl;
		myfile1 << current->type << endl;

		myfile << current->no << " " << current->id << endl;
		myfile << current->firstname << endl << current->lastname << endl << current->gender << endl;
		myfile << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl;
		myfile << current->socialid << endl;
		current = current->next;
	}
	myfile.close();
	myfile1.close();
}


void add_class_list(string* severalclass)
{
	fstream myfile;
	myfile.open("classes.txt", fstream::app);
	myfile << endl;
	myfile << *severalclass;
	myfile.close();
}


void create_school_year()
{
	cout << "Enter the school year (yy-yy): "; int x; int y; cin >> x >> y;
	fstream myfile;
	myfile.open("classes.txt", fstream::out);
	myfile << x << " " << y;
	myfile.close();
}
