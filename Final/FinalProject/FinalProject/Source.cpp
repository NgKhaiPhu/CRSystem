#include "Final.h"

//mai hoan thanh, them clearscr
int main() {
	//inputAcc
	fstream acc;
	acc.open("testLogin.csv", fstream::in);
	if (!acc.is_open()) {
		cout << "Cannot open account file\n";
		return 0;
	}
	student* stuAcc = 0;
	staff* staAcc = 0;
	inputAcc(acc, stuAcc, staAcc);//0,StudentID,password,fullname,Gender,DOB
								  //1,username,password,fullname,Gender
	acc.close();

	//login
	bool exit = false;
	int year = 0, i = 1;
	Sem* srr = new Sem[3];

	do {
		system("CLS");
		student* stuUsing = 0;
		staff* staUsing = 0;
		cout << "Creator: Nguyen Khai Phu, Nguyen Duy Thinh, Nguyen Duy Nien, Nguyen Hoang Quoc Huy\n"
			<< "COURSE REGISTRATION SYSTEM\n"
			<< "--------------------------";
		login(stuAcc, staAcc, stuUsing, staUsing, exit);
		if (exit)
			continue;

		int opt;
		bool logout = false;
		if (staUsing) {
			do {
				system("CLS");
				displayBasicInfo(stuUsing, staUsing);
				cout << "--------------------------\n";
				cout << "Press 0 to log out\n"
					<< setw(6) << " " << "1 to add a school year\n"
					<< setw(6) << " " << "2 to create a new class\n"
					<< setw(6) << " " << "3 to go to Course\n"
					<< setw(6) << " " << "4 to go to View\n"
					<< setw(6) << " " << "5 to export list of student from a course\n"
					<< setw(6) << " " << "6 to go to Score\n";
				cin >> opt;
				switch (opt) {
				case 0:
					logout = true;
					break;
				case 1:
					system("CLS");
					create_school_year();
					break;
				case 2: {
					system("CLS");
					student* list = 0;
					create_class(list);
					break;
				}
				case 3:
					TCmenu(srr, i, year);
					break;
				case 4:
					menuView(srr, i, year);
					break;
				case 5: 
				{
					student* head = nullptr;
					string classs = choose_class();// Chon lop de export file
					system("CLS");
					load_stu_course_class(head, &classs);
					export_student_in_courses(head, &classs);
					import_stu_mark();
					break; 
				}
				case 6:
					//menuScore();
					break;
				default:
					cout << "Invalid option. Please enter again\n";
					system("pause");
					break;
				}
			} while (!logout);
		}
		else {
			string filename = to_string(stuUsing->id) + "_Courses.txt";
			ofstream f;
			f.open(filename, fstream::app);
			f.close();
			do {
				system("CLS");
				displayBasicInfo(stuUsing, staUsing);
				cout << "--------------------------\n";
				cout << "Press 0 to log out\n"
					<< setw(6) << " " << "1 to go to Course\n"
					<< setw(6) << " " << "2 to view your score\n";
				cin >> opt;
				switch (opt) {
				case 0:
					logout = true;
					break;
				case 1: {
					delete[]srr;
					Sem* srr = new Sem[3];

					OperateTask(srr, stuUsing, i);
					break; }
				case 2:
					//mai lam, phan cua Thinh
					break;
				default:
					cout << "Invalid option. Please enter again\n";
					system("pause");
					break;
				}
			} while (!logout);
		}
	} while (!exit);

	//delete
	student* stucur = stuAcc;
	while (stuAcc->next) {
		stuAcc = stuAcc->next;
		delete stucur;
		stucur = stuAcc;
	}

	staff* stacur = staAcc;
	while (staAcc->next) {
		staAcc = staAcc->next;
		delete stacur;
		stacur = staAcc;
	}


	return 0;
}