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
	int year, i;
	Sem srr[3];

	do {
		system("CLS");
		student* stuUsing = 0;
		staff* staUsing = 0;
		cout << "Creator: Nguyen Khai Phu, Nguyen Duy Thinh, Nguyen Duy Nien, Nguyen Hoang Quoc Huy\n"
			<< "COURSE REGISTRATION SYSTEM\n"
			<< "--------------------------";
		login(stuAcc, staAcc, stuUsing, staUsing, exit);

		int opt;
		bool logout = false;
		if (staUsing) {
			do {
				displayBasicInfo(stuUsing, staUsing);
				cout << "--------------------------";
				cout << "Press 0 to log out\n"
					<< setw(6) << " " << "1 to add a school year\n"
					<< setw(6) << " " << "2 to add a semester\n"
					<< setw(6) << " " << "3 to go to Course\n"
					<< setw(6) << " " << "4 to go to View\n"
					<< setw(6) << " " << "5 to export list of student from a course\n";					
				cin >> opt;
				switch (opt) {
				case 0:
					logout = true;
					break;
				case 1:
					create_school_year;
					break;
				case 2:
					student* list = 0;
					create_class(list);
					break;
				case 3:
					TCmenu(srr, i, year);
					break;
				case 4://to be khong tinh yeu
					break;
				case 5: 
				{
					student* head = nullptr;
					string classs = choose_class();// Chon lop de export file

					load_stu_course_class(head, &classs);
					export_student_in_courses(head, &classs);
					import_stu_mark();
					break; 
				}
				default:
					cout << "Invalid option. Please enter again\n";
					break;
				}
			} while (!logout);
		}
		else {
			do {
				displayBasicInfo(stuUsing, staUsing);
				cout << "--------------------------";
				cout << "Press 0 to log out\n"
					<< setw(6) << " " << "1 to enroll a course\n"
					<< setw(6) << " " << "2 to view list of courses you have enrolled\n"
					<< setw(6) << " " << "3 to remove a course you have enrolled\n"
					<< setw(6) << " " << "4 to view your score\n";
				cin >> opt;
				switch (opt) {
				case 0:
					logout = true;
					break;
				case 1: 
					if (checkRealTime(srr,i) == 1){
						//mai lam, phan cua Nien
					}
					break;
				case 2:
					//mai lam, phan cua Nien
					break;
				case 3:
					//mai lam, phan cua Nien
					break;
				case 4:
					//mai lam
					break;
				default:
					cout << "Invalid option. Please enter again\n";
					break;
				}
			} while (!logout);
		}
	} while (!exit);
	return 0;
}
