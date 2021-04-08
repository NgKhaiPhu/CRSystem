#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
struct Course {
	int CoID;
	int stt;
	string CoName;
	string TeacherName;
	int Credit;
	int NumofStu = 50;
	string* Dayofweek;
	string* Session;
	Course* nxt;
};

struct Sem {
	int sem;
	string SemStart;
	string SemEnd;
	string regisStart;
	string regisEnd;
	Course* C;
	//Course* head = nullptr;
	//Course* cur = nullptr;
};

void InputCourse(fstream& f, Sem& S, int& y)
{
	y = 1;
	int t;
	Course* pcur = nullptr;
	f >> y;
	f >> S.sem;
	f >> S.regisStart;
	f >> S.regisEnd;
	f >> S.SemStart;
	f >> S.SemEnd;
	f >> t;
	while (t != 0)
	{
		if (S.C == nullptr)
		{
			S.C = new Course;
			pcur = S.C;
		}
		else
		{
			pcur->nxt = new Course;
			pcur = pcur->nxt;
		}
		pcur->Dayofweek = new string[2];
		pcur->Session = new string[2];
		pcur->stt = t;
		f >> pcur->CoID;
		f >> pcur->CoName;
		f >> pcur->TeacherName;
		f >> pcur->Credit;
		f >> pcur->NumofStu;
		f >> pcur->Dayofweek[0];
		f >> pcur->Session[0];
		f >> pcur->Dayofweek[1];
		f >> pcur->Session[1];
		pcur->nxt = nullptr;
		f >> t;
	}
}
void EnrollCourse(Sem S, Course*& MyCourse) // S la hoc ki voi cac course dc staff nhap vao
{
	int ID;
	bool check;
	if (S.C == nullptr)	return;
	cout << endl << "Please input the Course ID you want to enroll." << endl;
	cout << "ID: ";
	cin >> ID;
	Course* pC = S.C;
	while (pC != nullptr && pC->CoID != ID) pC = pC->nxt;
	if (MyCourse != nullptr)
	{
		Course* pCheck = MyCourse;
		while (pCheck != nullptr)
		{
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					if (pC->Dayofweek[i] == pCheck->Dayofweek[j])
						if (pC->Session[i] == pCheck->Session[j])
						{
							check = false;
							cout << " Enrollment fails. Session is conficted!" << endl;
							return;
						}
		}
	}
	if (pC == nullptr)
	{
		cout << "Wrong ID  !!!";
		return;
	}
	Course* pcur = MyCourse;
	if (MyCourse == nullptr)
	{
		MyCourse = pC;
	}
	else
	{
		while (pcur->nxt != nullptr) pcur = pcur->nxt;
		pcur->nxt = pC;
	}
	if (pC == S.C)
	{
		S.C = S.C->nxt;
	}
	else
	{
		Course* pLink = S.C;
		while (pLink->nxt != pC) pLink = pLink->nxt;
		pLink->nxt = pC->nxt;
	}
	pC->nxt = nullptr;
}
void ViewAvailableCourse(Sem S, int y)
{
	cout << setfill(' ');
	cout << "Course List of Sem " << S.sem + 1 << " in the year of " << y << " ,which from ";
	cout << S.SemStart << " to " << S.SemEnd << endl;
	cout << "==========================================================================================" << endl;
	cout << "Registion time is from " << S.regisStart << " to " << S.regisEnd << endl;
	cout << "==========================================================================================" << endl;
	cout << setw(5) << "ID";
	cout << setw(15) << "Name";
	cout << setw(15) << "Teacher";
	cout << setw(5) << "Credit";
	cout << setw(5) << "Maximum";
	cout << setw(15) << "Day";
	cout << setw(15) << "Sesson";
	Course* pC = S.C;
	while (pC != nullptr)
	{
		cout << endl;
		cout << setw(5) << pC->CoID;
		cout << setw(15) << pC->CoName;
		cout << setw(15) << pC->TeacherName;
		cout << setw(5) << pC->Credit;
		cout << setw(5) << pC->NumofStu;
		cout << setw(15) << pC->Dayofweek[0];
		cout << setw(15) << pC->Session[0];
		cout << endl << setw(89) << pC->Dayofweek[1];
		cout << endl << setw(15) << pC->Session[1];
		pC = pC->nxt;
	}
}

void ViewMyCourse(Sem S, int y, Course* MyCo)
{
	cout << setfill(' ');
	cout << "Course List of Sem " << S.sem + 1 << " in the year of " << y << " ,which from ";
	cout << S.SemStart << " to " << S.SemEnd << endl;
	cout << "==========================================================================================" << endl;
	cout << "Registion time is from " << S.regisStart << " to " << S.regisEnd << endl;
	cout << "==========================================================================================" << endl;
	cout << setw(5) << "ID";
	cout << setw(15) << "Name";
	cout << setw(15) << "Teacher";
	cout << setw(5) << "Credit";
	cout << setw(5) << "Maximum";
	cout << setw(15) << "Day";
	cout << setw(15) << "Sesson";
	if (MyCo == nullptr) return;
	Course* pC = MyCo;
	while (pC != nullptr)
	{
		cout << endl;
		cout << setw(5) << pC->CoID;
		cout << setw(15) << pC->CoName;
		cout << setw(15) << pC->TeacherName;
		cout << setw(5) << pC->Credit;
		cout << setw(5) << pC->NumofStu;
		cout << setw(15) << pC->Dayofweek[0];
		cout << setw(15) << pC->Session[0];
		cout << endl << setw(89) << pC->Dayofweek[1];
		cout << endl << setw(15) << pC->Session[1];
		pC = pC->nxt;
	}
}

void DeleteCourse(Sem& S, Course*& MyCo)
{
	if (MyCo == nullptr)
	{
		cout << "There are no courses available to delete!!! \n";
		return;
	}
	Course* pC = S.C;
	if (S.C != nullptr) while (pC->nxt != nullptr) pC = pC->nxt;
	int ID;
	cout << "Input the Course ID that you want to delete. \n";
	cout << "ID: ";
	cin >> ID;
	Course* pCur = MyCo;
	while (pCur != nullptr && pCur->CoID != ID) pCur = pCur->nxt;
	if (S.C == nullptr)
	{
		S.C = pCur;
	}
	else
	{
		Course* pC = S.C;
		while (pC->nxt != nullptr) pC = pC->nxt;
		pC->nxt = pCur;
	}

	if (pCur == MyCo)
	{
		MyCo = MyCo->nxt;
	}
	else
	{
		Course* pLink = MyCo;
		while (pLink->nxt != pCur) pLink = pLink->nxt;
		pLink->nxt = pC->nxt;
	}
	pCur->nxt = nullptr;
}

void OperateTask(Sem& S, Course*& MyCourse, int& y)
{
	int option = 1;
	while (option != 4)
	{
		cout << "\n\n";
		cout << "Course: " << endl;
		cout << "\t1. Enroll course.\n";
		cout << "\t2. Delete course.\n";
		cout << "\t3. View list of enrolled courses.\n";
		cout << "\t4. Do nothing. Stop.\n";
		cout << "What do you want to do (1-4 only): ";
		cin >> option;
		if (option != 1 && option != 2 && option != 3 && option != 4) continue;
		switch (option)
		{
		case 1:
		{
			ViewAvailableCourse(S, y);
			EnrollCourse(S, MyCourse);
			break;
		}
		case 2:
		{
			DeleteCourse(S, MyCourse);
			break;
		}
		case 3:
		{
			ViewMyCourse(S, y, MyCourse);
			break;
		}
		case 4: return;
		}
	}

}

int main()
{
	Sem Avail;
	Course* myCo;
	fstream fin;
	fin.open("Course.txt", fstream::in);
	int y;
	if (fin.fail())
	{
		cout << "Can't open the file!!!";
	}
	else
	{
		OperateTask(Avail, myCo, y);
		fin.close();
	}
	return 0;
}