#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
	string username;
	string password;
	bool stt;//0-gv, 1-sv
	Node* nxt;
};

void inputAcc(fstream& acc, Node*& a);
void login(Node* a, string& usn);
void deleteList(Node*& a);
void display(ifstream& ifs, string u);
void changepass(fstream& fs, string u, Node* a);

int main() {
	Node* acc1 = 0;
	fstream fs;
	fs.open("testLogin.csv", ios::in | ios::out | ios::app);

	if (!fs.is_open()) {
		cout << "Cannot open file. " << endl;
		return 0;
	}

	inputAcc(fs, acc1);

	string usn;
	login(acc1,usn);

	fs.close();

	ifstream ifs;
	ifs.open("profileInfo.csv");

	if (!ifs.is_open()) {
		cout << "Cannot open file. \n";
		return 0;
	}

	display(ifs, usn);	
	changepass(fs, usn, acc1);

	ifs.close();
	deleteList(acc1);
	return 0;
} 

void display(ifstream& ifs, string u) {
	string t;
	getline(ifs, t, ',');
	
	while (t != u && t != "") {
		getline(ifs, t);
		getline(ifs, t, ',');
	}

	cout << "Student ID: " << t << endl;
	getline(ifs, t);
	stringstream ss(t);
	getline(ss, t, ',');
	cout << "Full name: " << t << endl;
	getline(ss, t);
	cout << "D.O.B: " << t << endl;
}

void changepass(fstream& fs, string u, Node* a) {
	Node* pC = a;
	while (pC->username != u)
		pC = pC->nxt;
	cout << "Type your new password: ";
	cin >> pC->password;

	fs.open("testLogin.csv", ios::out);

	while (a) {
		fs << a->username << ',' << a->password << ',' << int(a->stt) << endl;
		a = a->nxt;
	}

	fs.close();
}

void inputLL(Node*& a, Node*& pC, string t) {
	stringstream ss(t);
	if (a == nullptr) {
		a = new Node;
		pC = a;
	}
	else {
		pC->nxt = new Node;
		pC = pC->nxt;
	}

	getline(ss, pC->username, ',');
	getline(ss, pC->password, ',');
	ss >> pC->stt;
	pC->nxt = nullptr;
}

void inputAcc(fstream& ifs, Node*& a) {
	Node* pC = nullptr;
	while (!ifs.eof())
	{
		string t;
		getline(ifs, t);
		inputLL(a, pC, t);
	}
}

void login(Node* a, string& usn) {
	string u, p;
	Node* a0 = a;

	do {
		a = a0;
		cout << "Username: ";
		cin >> u;
		cout << "Password: ";
		cin >> p;

		while (a != 0 && a->username != u) 
			a = a->nxt;
		
		if (a == 0)
			cout << "Account does not exist\n";
		else if (a->password != p)
			cout << "Wrong password.\n";
	} while (a == 0 || a->password != p);
		
	usn = a->username;
	system("CLS");
}

void deleteList(Node*& a) {
	Node* pC = a;
	while (pC->nxt != nullptr) {
		a = a->nxt;
		delete pC;
		pC = a;
	}
}