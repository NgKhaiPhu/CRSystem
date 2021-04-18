#include <iostream>
#include <fstream>
#include <string>
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

void ViewClass() {
	ifstream myfile;
	string temp;
	myfile.open("classes.txt");
	if (myfile.eof() || !myfile.is_open()) {
		cout << "List not available\n";
		return;
	}

	getline(myfile, temp);//skip dong dau
	while (!myfile.eof()) {
		getline(myfile, temp);
		cout << temp << endl;
	}
	myfile.close();
}

void ViewStudentofClass(student* head) {
	string temp, check;
	cout << "View student list of: ";
	cin >> temp;

	ifstream myfile;	
	myfile.open("classes.txt");
	if (!myfile.is_open()) {
		cout << "Cannot access list of classes\n";
		return;
	}

	getline(myfile, check);//skip dong dau
	while (!myfile.eof() && check != temp)
		getline(myfile, check);

	string display;
	if (myfile.eof()) {
		cout << "Class does not exist\n";
		return;
	}

	ifstream classfile;
	classfile.open("classes.txt");
	if (!classfile.is_open()) {
		cout << "Class does not exist\n";
		return;
	}

	while (!classfile.eof()) {
		classfile >> display;
		cout << display << " "; //no
		classfile >> display;
		cout << display << endl; //id
		classfile >> display;
		cout << display << " "; //first name
		classfile >> display;
		cout << display << endl << endl; //last name
		classfile >> display; //skip 3 dong sau
		classfile >> display;
		classfile >> display;
	}	
}