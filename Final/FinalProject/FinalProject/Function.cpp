#include "Final.h"

void inputAcc(fstream& acc, student*& stuAcc, staff*& staAcc) {
	while (!acc.eof())
	{
		int temp;//0 1
		char mark;
		string t;
		getline(acc, t);
		stringstream ss(t);
		ss >> temp;
		ss >> mark;
		if (temp == 1) {
			staff* cur = 0;
			if (staAcc == 0) {
				staAcc = new staff;
				cur = staAcc;
			}
			else {
				cur->next = new staff;
				cur = cur->next;
			}
			getline(ss, cur->username, ',');
			getline(ss, cur->password, ',');
            getline(ss, cur->fullname, ',');
            getline(ss, cur->gender, ',');
			cur->next = 0;
        }
		else {
			student* cur = 0;
			if (stuAcc == 0) {
				stuAcc = new student;
				cur = stuAcc;
			}
			else {
				cur->next = new student;
				cur = cur->next;
			}
			ss >> cur->id;
			ss >> mark;
			getline(ss, cur->password, ',');
            getline(ss, cur->firstname, ',');
            getline(ss, cur->gender, ',');
            ss >> cur->dob.day;
            ss >> mark;
            ss >> cur->dob.month;
            ss >> mark;
            ss >> cur->dob.year;
			cur->next = 0;
		}
	}
}

void login(student* stuAcc, staff* staAcc, string& usn, student*& stuCur, staff*& staCur) {
	string u, p;
	if (stuAcc == 0 && staAcc == 0) {
		cout << "Error" << endl;
		return;
	}

	int stt;
	do {
		stuCur = stuAcc;
		staCur = staAcc;
		cout << "Username: ";
		cin >> u;
		cout << "Password: ";
		cin >> p;
		while (stuCur != 0 && stuCur->id != stoi(u))
			stuCur = stuCur->next;
		if (stuCur == 0 || (stuCur->id == stoi(u) && stuCur->password != p)) {
			while (staCur != 0 && staCur->username != u)
				staCur = staCur->next;
			if (stuCur == 0 && staCur == 0)
				cout << "Account does not exist\n";
			else if (staCur->password != p)
				cout << "Wrong password.\n";
			else
				stuCur = 0;
		}
		else
			staCur = 0;

	} while ((stuCur == 0 && staCur == 0) || stuCur->password != p || staCur->password != p);

	system("CLS");
}

void displayBasicInfo(student* stuCur, staff* staCur) {
    if (stuCur)
        cout << "Student ID: " << stuCur->id << endl
        << "Student: " << stuCur->firstname << endl
        << "Gender: " << stuCur->gender << endl
        << "Day of birth: " << stuCur->dob.day << '/' << stuCur->dob.month << '/' << stuCur->dob.year << endl;
    else if (staCur)
        cout << "Staff: " << staCur->fullname << endl
        << "Gender: " << staCur->gender << endl;
}

void changepass(student* stuAcc, staff* staAcc, student* stuCur, staff* staCur) {
	cout << "Enter new password: ";
	if (stuCur)
		cin >> stuCur->password;
	else
		cin >> staCur->password;

	ofstream changePass;
	changePass.open("testLogin.csv", ios::out);

	if (!changePass.is_open()) {
		cout << "Cannot open file\n";
		return;
	}

	while (stuAcc) {
		changePass << "0," << stuAcc->id << ',' << stuAcc->password << ',' 
            << stuAcc->firstname << ',' << stuAcc->gender << ',' 
            << stuAcc->dob.day << '/' << stuAcc->dob.month << '/' << stuAcc->dob.year << ',' << endl;
		stuAcc = stuAcc->next;
	}
	while (staAcc) {
        changePass << "1," << staAcc->username << ',' << staAcc->password << ','
            << staAcc->fullname << ',' << staAcc->gender << ',';
		if (staAcc->next)
			cout << endl;
		staAcc = staAcc->next;
	}

	changePass.close();
}

//1
bool check_file_exist(string* file)
{
    fstream myfile;
    myfile.open(*file, fstream::in);
    if (myfile.is_open())
        return true;
    else
        return false;
    myfile.close();
}

void import_list(student*& head, string* severalclass)
{
    string fast_input;
    cout << "Enter the address of your file for fast input: ";
    cin >> fast_input;
    if (!check_file_exist(&fast_input)) {
        cout << "This file does not exist" << endl;
        return;
    }
    fstream myfile;
    myfile.open(fast_input, fstream::in);
    student* current = nullptr;
    char temp;
    while (!myfile.eof())
    {
        student* temp_ptr = new student;
        myfile >> temp_ptr->no >> temp;
        if (temp_ptr->no < 0) 
            break; 
        myfile >> temp_ptr->id >> temp;
        getline(myfile, temp_ptr->firstname, ',');
        getline(myfile, temp_ptr->lastname, ',');
        getline(myfile, temp_ptr->gender, ',');
        myfile >> temp_ptr->dob.day >> temp 
            >> temp_ptr->dob.month >> temp
            >> temp_ptr->dob.year >> temp
            >> temp_ptr->socialid;
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
    cout << "Enter the class: "; 
    getline(cin, severalclass);
    string temp = severalclass + ".txt";
    if (check_file_exist(&temp)) {
        cout << "Class " << severalclass << "has already existed" << endl;
        return;
    }
    import_list(head, &severalclass);
    add_class_list(&severalclass);
    fstream myfile, myfile1;
    myfile1.open("student.txt", fstream::app);
    myfile.open(temp, fstream::out);

    student* current = head;
    while (current != nullptr)
    {
        myfile1 << current->id << endl
            << current->dob.day << current->dob.month << current->dob.year << endl
            << current->firstname << endl << current->lastname << endl
            << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl
            << current->sclass << endl
            << current->type << endl;

        myfile << current->no << " " << current->id << endl
            << current->firstname << endl << current->lastname << endl << current->gender << endl
            << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << endl
            << current->socialid << endl;
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
    cout << "Enter school year (yy-yy): "; int x; int y; cin >> x >> y;
    fstream myfile;
    myfile.open("classes.txt", fstream::out);
    myfile << x << " " << y;
    myfile.close();
}

//2 
void TCmenu(Sem se, Sem srr[], int i, int year) {
    bool menuOn = true;
    int option;
    do {
        cout << endl
            << "\t\t\t============================================" << endl
            << "\t\t\t=          Press 0 to Endtask              =" << endl
            << "\t\t\t=                1 to Create Courses       =" << endl
            << "\t\t\t=                2 to Delete Courses       =" << endl
            << "\t\t\t=                3 to Update Course        =" << endl
            << "\t\t\t=                4 to Display List         =" << endl
            << "\t\t\t============================================" << endl
            << "\t\t\tOption => "; 
        cin >> option;
        switch (option) {
        case 0:
            menuOn = false;
            break;
        case 1: 
            create_courselist(se, srr, i, year);
            break;
        case 2: 
            deleteCourse(se, srr);
            break;
        case 3:
            updateCourse(se, srr);
            break;
        case 4:
            displayCourseList(se, srr, i, year);
            break;
        default:
            cout << "Invalid option. Please enter again\n";
            break;
        }
    } while (menuOn);
    write_data_CourseList(se, srr, i, year);
    write_data_course(se, srr, i, year);
}

void create_courselist(Sem& se, Sem srr[], int& i, int& year) {
    ofstream ofs;
    cout << "\t\t\t============================================" << endl;
    cout << "\t\t\t=   Create a List of Course for this semester   =" << endl;
    cout << "\t\t\t============================================" << endl;
    cout << "\t\t\tYear of Current semester: ";
    cin >> year;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhich season?" << endl;
    cout << "\t\t\t-> Press 1 for Fall" << endl;
    cout << "\t\t\t-> Press 2 for Summner" << endl;
    cout << "\t\t\t-> Press 3 for Autumn" << endl;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\t=> ";
    cin >> i; i = i - 1;
    cout << "\t\t\t---------------------------" << endl;
    cin.ignore(32727, '\n');
    cout << "\t\t\tWhen does this semester start and end?" << endl;
    cout << "\t\t\t(Ex format: dd/mm/yyyy)" << endl;
    cout << "\t\t\tStarts on: ";
    getline(cin, srr[i].SemStart);
    cout << "\t\t\tEnds on: ";
    getline(cin, srr[i].SemEnd);
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhen does the registion start and end?" << endl;
    cout << "\t\t\t(Ex format: dd/mm/yyyy hh:mm)" << endl;
    cout << "\t\t\tStarts on: ";
    getline(cin, srr[i].regisStart);
    cout << "\t\t\tEnds on: ";
    getline(cin, srr[i].regisEnd);
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\t(Enter 0 in No to stop inserting!)" << endl;
    int No;
    cout << "\t\t\tNo: ";
    cin >> No;
    srr[i].cur = nullptr;
    while (No != 0) {
        if (srr[i].head == nullptr) {
            srr[i].head = new Course;
            srr[i].cur = srr[i].head;
        }
        else {
            srr[i].cur->next = new Course;
            srr[i].cur = srr[i].cur->next;
        } cin.ignore(32767, '\n');
        cout << "\t\t\tCourse ID: ";
        srr[i].cur->no = No;
        getline(cin, srr[i].cur->CoId);
        cout << "\t\t\tCourse name: ";
        getline(cin, srr[i].cur->CoName);
        string a = srr[i].cur->CoName + ".csv";
        ofs.open(a, ios::out);
        ofs.close();
        cout << "\t\t\tLecturer in class: ";
        getline(cin, srr[i].cur->teacherName);
        cout << "\t\t\tNumber of credits: ";
        cin >> srr[i].cur->credit;
        cin.ignore(32767, '\n');
        for (int j = 0; j < 2; j++) {
            cout << "\t\t\tDay " << j + 1 << ": ";
            getline(cin, srr[i].cur->day[j]);
        }
        for (int j = 0; j < 2; j++) {
            cout << "\t\t\tS" << j + 1 << ": ";
            getline(cin, srr[i].cur->s[j]);
        }
        srr[i].cur->next = nullptr;
        cout << "\t\t\tNo: ";
        cin >> No;
    }
}

void displayCourseList(Sem se, Sem srr[], int i, int year) {
    srr[i].cur = srr[i].head;
    cout << endl << endl;
    cout << setfill(' ');
    cout << "Course list of semester " << i + 1 << " in " << year << " , beginning from ";
    cout << srr[i].SemStart << " to " << srr[i].SemEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << "Registration time starts from " << srr[i].regisStart << " to " << srr[i].regisEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << setw(13) << left << "ID";
    cout << setw(15) << left << "Course";
    cout << setw(17) << left << "Lecturer";
    cout << setw(10) << left << "Credit";
    cout << setw(10) << left << "Maximum";
    cout << setw(12) << left << "Day";
    cout << "Session";
    cout << endl;
    while (srr[i].cur != nullptr) {
        cout << setfill(' ');
        cout << setw(13) << left << srr[i].cur->CoId;
        cout << setw(15) << left << srr[i].cur->CoName;
        cout << setw(17) << left << srr[i].cur->teacherName;
        cout << setw(10) << left << srr[i].cur->credit;
        cout << setw(10) << left << srr[i].cur->maxSt;
        for (int j = 0; j < 2; j++) {
            cout << setw(4) << left << srr[i].cur->day[j] << " ";
        } cout << "  ";
        for (int j = 0; j < 2; j++) {
            cout << "S" << j + 1 << ": ";
            cout << setw(7) << srr[i].cur->s[j] << "  ";
        }
        cout << endl;
        srr[i].cur = srr[i].cur->next;
    }
}

void deleteCourse(Sem& se, Sem srr[]) {
    string ids;
    int m;
    cout << endl;
    cout << "\t\t\tSemester: ";
    cin >> m;
    cin.ignore(32767, '\n');
    cout << "\t\t\tEnter the ID of the course you want to delete: ";
    getline(cin, ids);
    if (!srr[m].head) {
        cout << "List not available!" << endl;
        return;
    }
    srr[m].cur = srr[m].head;
    if (srr[m].head->CoId == ids) {
        srr[m].head = srr[m].head->next;
        delete srr[m].cur;
        srr[m].cur = nullptr;
    }
    else {
        while (srr[m].cur->next->CoId != ids) {
            srr[m].cur = srr[m].cur->next;
        } Course* link = srr[m].cur->next;
        srr[m].cur->next = srr[m].cur->next->next;
        delete link;
    }
}

void updateCourse(Sem& se, Sem srr[]) {
    int n;
    cout << "\t\t\tSemester: "; cin >> n; n = n - 1;
    cout << "\t\t\tEnter the ID of the course you want to adjust: ";
    string idfake; cin >> idfake;
    srr[n].cur = srr[n].head;
    if (!srr[n].head) cout << "\t\t\tList not available !"; return;
    if (srr[n].head->CoId != idfake) {
        while (srr[n].cur != nullptr && srr[n].cur->CoId != idfake) {
            srr[n].cur = srr[n].cur->next;
        }
    } if (!srr[n].cur) cout << "\t\t\tData not found!"; return;
    
    int op;
    bool menuOn = true;
    do {
        cout << endl;
        cout << "\t\t\t=====================================" << endl;
        cout << "\t\t\t=  Which one of these do you want to adjust?  =" << endl;
        cout << "\t\t\t=    Press  1  for  ID              =" << endl;
        cout << "\t\t\t=           2  for  NameCourse      =" << endl;
        cout << "\t\t\t=           3  for  Lecture         =" << endl;
        cout << "\t\t\t=           4  for  Credit          =" << endl;
        cout << "\t\t\t=           5  for  MaxStudent      =" << endl;
        cout << "\t\t\t=           6  for  Day of week     =" << endl;
        cout << "\t\t\t=           7  for  Session of day  =" << endl;
        cout << "\t\t\t=           8  for  ALL             =" << endl;
        cout << "\t\t\t=           0  to   Endtask         =" << endl;
        cout << "\t\t\t=====================================" << endl;
        cin >> op;
        switch (op) {
        case 0:
            menuOn = false;
            break;
        case 1: 
            cout << "\t\t\tnew ID: "; cin >> srr[n].cur->CoId;
            break;
        case 2: 
            cout << "\t\t\tnew NameCourse: "; 
            cin.ignore(32767, '\n');
            getline(cin, srr[n].cur->CoName);
            break;
        case 3: 
            cout << "\t\t\tnew Lecture: "; 
            cin.ignore(32767, '\n');
            getline(cin, srr[n].cur->CoName);
            break;
        case 4: 
            cout << "\t\t\tnew Credit: ";
            cin >> srr[n].cur->credit;
            break;
        case 5: 
            cout << "\t\t\tnew MaxStudent: "; 
            cin >> srr[n].cur->maxSt;
            break;
        case 6: 
            cout << "\t\t\tnew Day of week";
            for (int i = 0; i < 2; i++) {
                cout << "Day " << i + 1 << ": ";
                cin >> srr[n].cur->day[i];
            }
            break;
        case 7:
            cout << "\t\t\tnew Session of day";
            for (int i = 0; i < 2; i++) {
                cout << "Session " << i + 1 << ": ";
                cin >> srr[n].cur->s[i];
            }
            break;
        case 8:
            cout << "\t\t\tnew Id: ";
            getline(cin, srr[n].cur->CoId);
            cout << "\t\t\tnew Name: ";
            getline(cin, srr[n].cur->CoName);
            cout << "\t\t\tnew Lecturer: ";
            getline(cin, srr[n].cur->teacherName);
            cout << "\t\t\tnew Credits: ";
            cin >> srr[n].cur->credit;
            cin.ignore(32767, '\n');
            for (int j = 0; j < 2; j++) {
                cout << "\t\t\tnew Day " << j + 1 << ": ";
                getline(cin, srr[n].cur->day[j]);
            }
            for (int j = 0; j < 2; j++) {
                cout << "\t\t\tnew Session" << j + 1 << ": ";
                getline(cin, srr[n].cur->s[j]);
            }
            break;
        default:
            cout << "Invalid option. Please enter again\n";
            break;
        }
    } while (menuOn);
}

void write_data_CourseList(Sem se, Sem srr[], int i, int year) {
    srr[i].cur = srr[i].head;
    ofstream ofs;
    ofs.open("CourseList.csv", ios::out);
    ofs << "Year," << year << endl;
    int ifake = i + 1;
    ofs << "Semester," << ifake << endl;
    ofs << "Semester Start:," << srr[i].SemStart << endl;
    ofs << "Semester End:," << srr[i].SemEnd << endl;
    ofs << "Registration Start:," << srr[i].regisStart << endl;
    ofs << "Registration End:," << srr[i].regisEnd << endl;
    ofs << "ID,NameCourse,Teacher,Credits,MaxSt,Day 1,Session 1,Day 2,Session 2" << endl;
    while (srr[i].cur != nullptr) {
        ofs << srr[i].cur->CoId << ",";
        ofs << srr[i].cur->CoName << ",";
        ofs << srr[i].cur->teacherName << ",";
        ofs << srr[i].cur->credit << ",";
        ofs << srr[i].cur->maxSt << ",";
        for (int j = 0; j < 2; j++) {
            ofs << srr[i].cur->day[j] << ",";
            ofs << srr[i].cur->s[j] << ",";
        } ofs << endl;
        srr[i].cur = srr[i].cur->next;
    } ofs.close();
}

void write_data_course(Sem se, Sem srr[], int i, int year) {
    srr[i].cur = srr[i].head;
    ofstream ofs;
    ofs.open("CourseList.txt", ios::out);
    int ifake = i + 1;
    ofs << ifake << endl;
    ofs << srr[i].SemStart << endl;
    ofs << srr[i].SemEnd << endl;
    ofs << srr[i].regisStart << endl;
    ofs << srr[i].regisEnd << endl;
    while (srr[i].cur != nullptr) {
        ofs << srr[i].cur->no << endl;
        ofs << srr[i].cur->CoId << endl;
        ofs << srr[i].cur->CoName << endl;
        ofs << srr[i].cur->teacherName << endl;
        ofs << srr[i].cur->credit << endl;
        ofs << srr[i].cur->maxSt << endl;
        for (int j = 0; j < 2; j++) {
            ofs << srr[i].cur->day[j] << endl;
        }
        for (int j = 0; j < 2; j++) {
            ofs << srr[i].cur->s[j] << endl;
        }
        srr[i].cur = srr[i].cur->next;
    } ofs << "0";
    ofs.close();
}

bool checkRealTime(Sem srr[], int i) {
    if (!i) {
        cout << "Course unavailable" << endl;
        return false;
    }
    string SeStart = srr[i].SemStart;
    string SeEnd = srr[i].SemEnd;
    string ReStart = srr[i].regisStart;
    string ReEnd = srr[i].regisEnd;
    time_t now = time(NULL);
    tm* t = localtime(&now);
    int* day = new int[2];
    int* mon = new int[2];
    int* year = new int[2];
    int* hour = new int[2];
    int* min = new int[2];

    if (isInSem(SeStart, SeEnd, t, day, mon, year) == true) {
        if (isInRe(ReStart, ReEnd, t, day, mon, year, hour, min) == true) {
            return true;
        } cout << "Enroll session has ended!" << endl;
        return false;
    } cout << "\t\t\tSemester has ended!" << endl;
    return false;

    delete[]day;
    delete[]mon;
    delete[]year;
    delete[]hour;
    delete[]min;
}

bool isInSem(string SeStart, string SeEnd, tm* t, int* day, int* mon, int* year) {
    for (int i = 0; i < 2; i++) { day[i] = 0; mon[i] = 0; year[i] = 0; }
    int n = SeStart.length();
    for (int i = 0; i < n; i++) {
        char c = SeStart[i];
        switch (i) {
        case 0: {
            day[0] += (c - '0') * 10;
            break;
        }
        case 1: {
            day[0] += c - '0';
            break;
        }
        case 3: {
            mon[0] += (c - '0') * 10;
            break;
        }
        case 4: {
            mon[0] += c - '0';
            break;
        }
        case 6: {
            year[0] += (c - '0') * 1000;
            break;
        }
        case 7: {
            year[0] += (c - '0') * 100;
            break;
        }
        case 8: {
            year[0] += (c - '0') * 10;
            break;
        }
        case 9: {
            year[0] += c - '0';
            break;
        }

        default: continue;
        };
    }
    for (int i = 0; i < n; i++) {
        char c = SeEnd[i];
        switch (i) {
        case 0: {
            day[1] += (c - '0') * 10;
            break;
        }
        case 1: {
            day[1] += c - '0';
            break;
        }
        case 3: {
            mon[1] += (c - '0') * 10;
            break;
        }
        case 4: {
            mon[1] += c - '0';
            break;
        }
        case 6: {
            year[1] += (c - '0') * 1000;
            break;
        }
        case 7: {
            year[1] += (c - '0') * 100;
            break;
        }
        case 8: {
            year[1] += (c - '0') * 10;
            break;
        }
        case 9: {
            year[1] += c - '0';
            break;
        }

        default: continue;
        };
    }

    if (1900 + t->tm_year<year[0] || 1900 + t->tm_year>year[1]) return false;
    else if (1 + t->tm_mon<mon[0] || 1 + t->tm_mon>mon[1]) return false;
    else if (t->tm_mday<day[0] || t->tm_mday>day[1]) return false;
    else return true;
}

bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int* year, int* hour, int* min) {
    for (int i = 0; i < 2; i++) { day[i] = 0; mon[i] = 0; year[i] = 0; hour[i] = 0; min[i] = 0; }
    int n = ReStart.length();
    for (int i = 0; i < n; i++) {
        char c = ReStart[i];
        switch (i) {
        case 0: {
            day[0] += (c - '0') * 10;
            break;
        }
        case 1: {
            day[0] += c - '0';
            break;
        }
        case 3: {
            mon[0] += (c - '0') * 10;
            break;
        }
        case 4: {
            mon[0] += c - '0';
            break;
        }
        case 6: {
            year[0] += (c - '0') * 1000;
            break;
        }
        case 7: {
            year[0] += (c - '0') * 100;
            break;
        }
        case 8: {
            year[0] += (c - '0') * 10;
            break;
        }
        case 9: {
            year[0] += c - '0';
            break;
        }
        case 11: {
            hour[0] += (c - '0') * 10;
            break;
        }
        case 12: {
            hour[0] += c - '0';
            break;
        }
        case 14: {
            min[0] += (c - '0') * 10;
            break;
        }
        case 15: {
            min[0] += c - '0';
            break;
        }
        default: continue;
        };
    }
    for (int i = 0; i < n; i++) {
        char c = ReEnd[i];
        switch (i) {
        case 0: {
            day[1] += (c - '0') * 10;
            break;
        }
        case 1: {
            day[1] += c - '0';
            break;
        }
        case 3: {
            mon[1] += (c - '0') * 10;
            break;
        }
        case 4: {
            mon[1] += c - '0';
            break;
        }
        case 6: {
            year[1] += (c - '0') * 1000;
            break;
        }
        case 7: {
            year[1] += (c - '0') * 100;
            break;
        }
        case 8: {
            year[1] += (c - '0') * 10;
            break;
        }
        case 9: {
            year[1] += c - '0';
            break;
        }
        case 11: {
            hour[1] += (c - '0') * 10;
            break;
        }
        case 12: {
            hour[1] += c - '0';
            break;
        }
        case 14: {
            min[1] += (c - '0') * 10;
            break;
        }
        case 15: {
            min[1] += c - '0';
            break;
        }
        default: continue;
        };
    }

    if (1900 + t->tm_year<year[0] || 1900 + t->tm_year>year[1])
        return false;
    else if (1 + t->tm_mon<mon[0] || 1 + t->tm_mon>mon[1]) 
        return false;
    else if (t->tm_mday<day[0] || t->tm_mday>day[1])
        return false;
    else if (t->tm_hour<hour[0] || t->tm_hour>hour[1])
        return false;
    else if (t->tm_min<min[0] || t->tm_min>min[1])
        return false;
    else 
        return true;
}

//3
void InputCourse(fstream& f, Sem& S, int& y);
void EnrollCourse(Sem S, Course*& MyCourse);
void ViewAvailableCourse(Sem S, int y);
void ViewMyCourse(Sem S, int y, Course* MyCo);
void DeleteCourse(Sem& S, Course*& MyCo);
void OperateTask(Sem& S, Course*& MyCourse, int& y);

//5
void viewClass() {};
void ViewStudentofClass(student* head);
void viewCourseStu() {};

//6
void exportClassList() {};
void importScore() {};//(CSV) 1,20127062,Nguyen Khai Phu,8,10,7,5
void viewCourseScore() {};
void upScore() {};
void viewClassScore() {};//Final scores, Sem GPA, overall GPA
void viewStuScore() {};