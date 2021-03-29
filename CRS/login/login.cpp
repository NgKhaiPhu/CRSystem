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

void inputAcc(ifstream &acc, Node*& a); 
void login(Node* a);
void deleteList(Node*& a);

int main() {
	Node* acc1 = 0;
	ifstream ifs;
	ifs.open("testLogin.csv");

	if (!ifs.is_open()) {
		cout << "Cannot open file. " << endl;
		return 0;
	}

	inputAcc(ifs, acc1);
	login(acc1);

	deleteList(acc1);
	return 0;
}

void inputLL(Node*& a, Node *&pC, string t) {	
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
	cout << pC->username << " ";
	stringstream c(pC->username);
	int check;
	c >> check;
	if (check != 0) pC->stt = 1;
	
	getline(ss, pC->password);
	cout << pC->password << endl;
	pC->nxt = nullptr;	
}

void inputAcc(ifstream& ifs, Node*& a){
	Node* pC = nullptr;
	while (!ifs.eof())
	{
		string t;
		getline(ifs, t);
		inputLL(a, pC, t);
	}
}

void login(Node* a) {
	string u, p;
	cout << "Username: ";
	cin >> u;
	cout << "Password: ";
	cin >> p;
	
	while (a != 0 && a->username != u)
		a = a->nxt;
	if (a != 0 && a->password == p) 
		cout << "Logged in\n";
	else if (a != 0)
		cout << "Sai mat khau\n";
	else
		cout << "Sai tai khoan\n";		
}

void deleteList(Node*& a) {
	Node* pC = a;
	while (pC->nxt != nullptr) {
		a = a->nxt;
		delete pC;
		pC = a;
	}
}