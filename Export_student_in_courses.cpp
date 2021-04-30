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
void load_stu_course_class(student*& head, string* classs);
void export_student_in_courses(student* head, string* classs);
void delete_linked_list(student*& head);
void import_stu_mark();
int main()
{
	student* head = nullptr;
	string classs = choose_class();// Chon lop de export file

	load_stu_course_class(head, &classs);
	export_student_in_courses(head, &classs);
	import_stu_mark();

	return 0;
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
			output << head->socialid << ",";
			output << ",,," << endl;
			
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

void load_stu_course_class(student*& head,string* classs)
{
	fstream data;
	data.open((*classs + ".csv").c_str(), fstream::in);
	if (!data.is_open()) return;
	
	data.ignore(1000,'\n');
	char temp;
	student* current = nullptr;
	while (!data.eof())
	{
		student* add = new student;
		data >> add->no; if (add->no < 0)break;
		data >> temp;

		data >> add->id; data >> temp;
		getline(data, add->firstname, ',');
		getline(data, add->lastname, ',');
		getline(data, add->gender, ',');
		data >> add->dob.day; data >> temp;
		data >> add->dob.month; data >> temp;
		data >> add->dob.year; data >> temp;
		data >> add->socialid;
		data.ignore();
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
	data.close();
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

void import_stu_mark()
{
	student* head = nullptr,*current=nullptr;
	string classs = choose_class();
	string* temp = &classs;
	cout << "Enter the address of mark file: ";
	while (getchar() != '\n');
	string a; getline(cin, a);
	fstream import;

	char tempp;
	import.open(a, fstream::in);
	import.ignore(100000, '\n');
	while (!import.eof())
	{
		student* add = new student;
		import >> add->no;
		if (add->no < 0)break; import >> tempp; 
		import >> add->id; import >> tempp;
		getline(import, add->firstname, ',');
		getline(import, add->lastname, ',');
		getline(import, add->gender, ',');
		import >> add->dob.day;import >> tempp;
		import >> add->dob.month;import >> tempp;
		import >> add->dob.year;import >> tempp;
		import >> add->socialid; import >> tempp;
		import >> add->midtermmark; import >> tempp;
		import >> add->finalmark; import >> tempp;
		import >> add->orthermark; import >> tempp;
		import >> add->totalmark; 
		import.ignore();

		
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

	import.close();


	current = head;




	fstream storage;
	storage.open((*temp + "_math.csv").c_str(), fstream::out);
	storage << "No" << "," << "Student ID" << ',' << "First Name" << "," << "Last Name" << "," << "Gender" << ", " << "Date of Birth" << ", " << "Social ID" << "," << "Midterm Mark" << "," << "Final Mark" << "," << "Other Mark" << "," << "Total Mark" << endl;
	while (current != nullptr)
	{
		storage << current->no << ",";
		storage << current->id << ",";
		storage << current->firstname << ",";
		storage << current->lastname << ",";
		storage << current->gender << ",";
		storage << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << ",";
		storage << current->socialid << ",";
		storage << current->midtermmark << ",";
		storage << current->finalmark << ",";
		storage << current->orthermark << ",";
		storage << current->totalmark;
		if (current->next!=nullptr) storage << endl;
		current = current->next;
	}
	storage.close();


	delete_linked_list(head);
}

