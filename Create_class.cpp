#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

struct date
{
	int year;
	int month;
	int day;
};

struct student
{
	int no;
	int id;
	string firstname;
	string lastname;
	string gender;
	date dob;
	string password;
	const int type = 1;
	int social_id;
	student* next;
	string classes;
};

struct staff
{
	string username;
	string password;
	string gender;
	string fullname;
	const int type = 0;
};

void import_file(string* classes, student*& head);
void delete_linked_list(student*& head);
void create_class(student*& head);
void add_class_to_list(string* severalclass);

int main()
{
	student* head = nullptr;
	create_class(head);
	display(head);
	delete_linked_list(head);
	return 0;
}

void import_file(string* classes, student*& head)
{
	char temp;
	string file;
	fstream myfile;
	cout << "Enter the address of the file that you want input:"; cin >> file;
	myfile.open(file, fstream::in);
	if (myfile.is_open() == false) { cout << "Can't open the file." << endl; return; }
	student* current = nullptr;
	while (!myfile.eof())
	{
		student* add = new student;
		myfile >> add->no;
		if (add->no < 0) break;// check it reached empty line
		myfile >> temp;
		myfile >> add->id;
		myfile >> temp;
		getline(myfile, add->firstname, ',');
		getline(myfile, add->lastname, ',');
		getline(myfile, add->gender, ',');
		myfile >> add->dob.day;
		myfile >> temp;
		myfile >> add->dob.month;
		myfile >> temp;
		myfile >> add->dob.year;
		myfile >> temp;
		myfile >> add->social_id;
		add->classes = *classes;
		myfile.ignore();


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
	myfile.close();
}


void delete_linked_list(student*& head)
{
	student* current = head;
	while (head != nullptr)
	{
		head = head->next;
		delete current;
		current = head;
	}
}

void create_class(student*& head)
{
	string severalclass;
	cout << "Enter the class:"; cin >> severalclass;
	fstream myfile, myfile1;
	string file = severalclass + ".txt";
	//Check the class created or not
	myfile.open(file, fstream::in);
	if (myfile.is_open()) { cout << "This class already exist."; myfile.close(); return; }
	else { myfile.close(); }

	add_class_to_list(&severalclass);

	myfile.open(file, fstream::out);
	myfile1.open("student.txt", fstream::app);
	import_file(&severalclass, head);
	//input to list of student file and student_account_file
	student* current = head;
	while (current != nullptr)
	{
		myfile1 << current->id << endl;
		myfile1 << current->dob.day << current->dob.month << current->dob.year << endl;
		myfile1 << current->firstname << endl << current->lastname << endl;
		myfile1 << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl;
		myfile1 << current->classes << endl;
		myfile1 << current->type << endl;

		myfile << current->no << " " << current->id << endl;
		myfile << current->firstname << endl << current->lastname << endl << current->gender << endl;
		myfile << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl;
		myfile << current->social_id << endl;
		current = current->next;
	}
	myfile.close();
	myfile1.close();
}

void add_class_to_list(string* severalclass)
{
	int temp;
	fstream myfile;
	myfile.open("class.txt", fstream::in);
	myfile >> temp;
	myfile.ignore();
	string* classes = new string[temp];
	for (int i = 0; i < temp; i++)
	{
		getline(myfile, classes[i]);
		myfile.ignore();
	}
	myfile.close();


	myfile.open("class.txt", fstream::out);
	myfile << (temp + 1) << endl;
	for (int i = 0; i < temp; i++) { myfile << classes[i] << endl; }
	myfile << *severalclass;
	myfile.close();
}