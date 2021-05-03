#include "Final.h"

//log in
void inputAcc(fstream& acc, student*& stuAcc, staff*& staAcc) {
    staff* stacur = 0;
    student* stucur = 0;

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
			if (staAcc == 0) {
				staAcc = new staff;
				stacur = staAcc;
			}
			else {
				stacur->next = new staff;
				stacur = stacur->next;
			}
			getline(ss, stacur->username, ',');
			getline(ss, stacur->password, ',');
            getline(ss, stacur->fullname, ',');
            getline(ss, stacur->gender, ',');
			stacur->next = 0;
        }
		else {
			if (stuAcc == 0) {
				stuAcc = new student;
				stucur = stuAcc;
			}
			else {
				stucur->next = new student;
				stucur = stucur->next;
			}
			ss >> stucur->id;
			ss >> mark;
			getline(ss, stucur->password, ',');
            getline(ss, stucur->firstname, ',');//fullname save tam
            getline(ss, stucur->gender, ',');
            ss >> stucur->dob.day;
            ss >> mark;
            ss >> stucur->dob.month;
            ss >> mark;
            ss >> stucur->dob.year;
			stucur->next = 0;
		}
	}
}

void login(student* stuAcc, staff* staAcc, student*& stuCur, staff*& staCur, bool& exit) {
	string u, p;
	if (stuAcc == 0 && staAcc == 0) {
		cout << "Input account failed" << endl;
		return;
	}

    bool logged = false;
	do {
		stuCur = stuAcc;
		staCur = staAcc;
		cout << "\nUsername (Press 0 to exit): ";
		cin >> u;
        if (u == "0") {
            exit = true;
            return;
        }
		cout << "Password: ";
		cin >> p;
        
		while (stuCur && to_string(stuCur->id) != u)
			stuCur = stuCur->next;
        if (!stuCur) {
            while (staCur && staCur->username != u)
                staCur = staCur->next;
            if (!stuCur && !staCur)
                cout << "Account does not exist\n";
            else if (staCur->password != p)
                cout << "Wrong password\n";
            else
                logged = true;
        }
        else if (to_string(stuCur->id) == u && stuCur->password != p)
            cout << "Wrong password\n";
        else {
            staCur = 0;
            logged = true;
        }
	} while (!logged);
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
    getline(myfile, fast_input);
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
void TCmenu(Sem srr[], int i, int year) {
    bool menuOn = true;
    int option;
    do {
        system("CLS");
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
            system("CLS");
            create_courselist(srr, i, year);
            break;
        case 2: 
            system("CLS");
            deleteCourse(srr);
            break;
        case 3:
            system("CLS");
            updateCourse(srr);
            break;
        case 4:
            system("CLS");
            displayCourseList(srr, i, year);
            break;
        default:
            cout << "Invalid option. Please enter again\n";
            system("pause");
            break;
        }
    } while (menuOn);
    write_data_CourseList(srr, i, year);
    write_data_course(srr, i, year);
}

void create_courselist(Sem srr[], int& i, int& year) {
    cout << "\t\t\t=================================================" << endl;
    cout << "\t\t\t=   Create a List of Course for this semester   =" << endl;
    cout << "\t\t\t=================================================" << endl;
    cout << "\t\t\tYear of Current semester: ";
    cin >> year;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhich season?" << endl;
    cout << "\t\t\t-> Press 1 for Fall" << endl;
    cout << "\t\t\t-> Press 2 for Summner" << endl;
    cout << "\t\t\t-> Press 3 for Autumn" << endl;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\t=> ";
    cin >> i; 
    cin.ignore(1000, '\n');
    i = i - 1;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhen does this semester start and end?" << endl;
    cout << "\t\t\t(Ex format: dd/mm/yyyy)" << endl;
    cout << "\t\t\tStarts on: ";
    getline(cin, srr[i].SemStart);
    cout << "\t\t\tEnds on: ";
    getline(cin, srr[i].SemEnd);
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhen does the registration start and end?" << endl;
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
        } 
        cin.ignore(32767, '\n');
        cout << "\t\t\tCourse ID: ";
        srr[i].cur->no = No;
        getline(cin, srr[i].cur->CoId);
        cout << "\t\t\tCourse name: ";
        getline(cin, srr[i].cur->CoName);
        cout << "\t\t\tLecturer in class: ";
        getline(cin, srr[i].cur->teacherName);
        cout << "\t\t\tNumber of credits: ";
        cin >> srr[i].cur->credit;
        cin.ignore(32767, '\n');
        for (int j = 0; j < 2; j++) {
            cout << "\t\t\tDay " << j + 1 << ": ";
            getline(cin, srr[i].cur->day[j]);
            cout << "\t\t\tS" << j + 1 << ": ";
            getline(cin, srr[i].cur->s[j]);
        }
        srr[i].cur->next = nullptr;
        cout << "\t\t\tNo: ";
        cin >> No;
    }
}

void displayCourseList(Sem srr[], int i, int year)//4
{
    srr[i].cur = srr[i].head;
    cout << endl << endl;
    cout << setfill(' ');
    cout << "Course list of semester " << i + 1 << " in " << year << " , beginning from ";
    cout << srr[i].SemStart << " to " << srr[i].SemEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << "Registration time starts from " << srr[i].regisStart << " to " << srr[i].regisEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << setw(10) << "ID";
    cout << setw(20) << "Name";
    cout << setw(20) << "Lecturer";
    cout << setw(7) << "Credit";
    cout << setw(8) << "Maximum";
    cout << setw(10) << "Day";
    cout << setw(8) << "Session";
    while (srr[i].cur != nullptr)
    {
        cout << endl;
        cout << setw(10) << srr[i].cur->CoId;
        cout << setw(20) << srr[i].cur->CoName;
        cout << setw(20) << srr[i].cur->teacherName;
        cout << setw(7) << srr[i].cur->credit;
        cout << setw(8) << srr[i].cur->maxSt;
        cout << setw(10) << srr[i].cur->day[0];
        cout << setw(8) << srr[i].cur->s[0];
        cout << endl << setw(65) << " " << setw(10) << srr[i].cur->day[1];
        cout << setw(8) << srr[i].cur->s[1];
        srr[i].cur = srr[i].cur->next;
    }
    cout << endl;
    system("pause");
}

void deleteCourse(Sem srr[]) {
    string ids;
    int m;
    cout << endl;
    cout << "\t\t\tSemester: ";
    cin >> m;
    m = m - 1;
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
        while (srr[m].cur->next->CoId != ids) 
            srr[m].cur = srr[m].cur->next;
        Course* link = srr[m].cur->next;
        srr[m].cur->next = srr[m].cur->next->next;
        delete link;
    }
}

void updateCourse(Sem srr[]) {
    int n;
    cout << "\t\t\tSemester: ";
    cin >> n;
    n = n - 1;
    cout << "\t\t\tEnter the ID of the course you want to adjust: ";
    string idfake; 
    cin >> idfake;
    srr[n].cur = srr[n].head;
    if (!srr[n].head) {
        cout << "\t\t\tList not available !";
        return;
    }
    if (srr[n].head->CoId != idfake) {
        while (srr[n].cur != nullptr && srr[n].cur->CoId != idfake) {
            srr[n].cur = srr[n].cur->next;
        }
    }
    if (!srr[n].cur) {
        cout << "\t\t\tData not found!";
        return;
    }
    
    int op;
    bool menuOn = true;
    do {
        cout << endl;
        cout << "\t\t\t===============================================" << endl;
        cout << "\t\t\t=  Which one of these do you want to adjust?  =" << endl;
        cout << "\t\t\t=    Press  1  for  ID                        =" << endl;
        cout << "\t\t\t=           2  for  NameCourse                =" << endl;
        cout << "\t\t\t=           3  for  Lecturer                  =" << endl;
        cout << "\t\t\t=           4  for  Credit                    =" << endl;
        cout << "\t\t\t=           5  for  MaxStudent                =" << endl;
        cout << "\t\t\t=           6  for  Day of week               =" << endl;
        cout << "\t\t\t=           7  for  Session of day            =" << endl;
        cout << "\t\t\t=           8  for  ALL                       =" << endl;
        cout << "\t\t\t=           0  to   Endtask                   =" << endl;
        cout << "\t\t\t===============================================" << endl;
        cin >> op;
        switch (op) {
        case 0:
            menuOn = false;
            break;
        case 1: 
            cout << "\t\t\tnew ID: "; cin >> srr[n].cur->CoId;
            break;
        case 2: 
            cout << "\t\t\tnew Course name: "; 
            cin.ignore(32767, '\n');
            getline(cin, srr[n].cur->CoName);
            break;
        case 3: 
            cout << "\t\t\tnew Lecturer: "; 
            cin.ignore(32767, '\n');
            getline(cin, srr[n].cur->CoName);
            break;
        case 4: 
            cout << "\t\t\tnew Credit: ";
            cin >> srr[n].cur->credit;
            break;
        case 5: 
            cout << "\t\t\tnew Max Student: "; 
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

void write_data_CourseList(Sem srr[], int i, int year) {
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
        }
        ofs << endl;
        srr[i].cur = srr[i].cur->next;
    } ofs.close();
}

void write_data_course(Sem srr[], int i, int year) {
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
    } 
    ofs << "0";
    ofs.close();
}

int checkRealTime(Sem srr[], int i) {
    if (i!=0 && i!=2 && i!=1) {
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

    int res;
    if (isInSem(SeStart, SeEnd, t, day, mon, year)) {
        if (isInRe(ReStart, ReEnd, t, day, mon, year, hour, min)) 
            res = 1;
        else 
            res = 2;
    } 
    else 
        res = 3;

    delete[]day;
    delete[]mon;
    delete[]year;
    delete[]hour;
    delete[]min;
    return res;
}

bool isInSem(string SeStart, string SeEnd, tm* t, int* day, int* mon, int* year) {
    for (int i = 0; i < 2; i++)
        day[i] = mon[i] = year[i] = 0; 
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
    if (1900 + t->tm_year < year[0] || 1900 + t->tm_year > year[1]) return false;
    else if (1 + t->tm_mon < mon[0] || 1 + t->tm_mon > mon[1]) return false;
    else if ((t->tm_mday < day[0] && 1 + t->tm_mon == mon[0]) || (t->tm_mday > day[1] && 1 + t->tm_mon == mon[1])) return false;
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
    else if ((t->tm_mday < day[0] && 1 + t->tm_mon == mon[0]) || (t->tm_mday > day[1] && 1 + t->tm_mon == mon[1])) 
        return false;
    else if ((day[0] == t->tm_mday && 1 + t->tm_mon == mon[0] && 1900 + t->tm_year == year[0]) ||
        (day[1] == t->tm_mday && 1900 + t->tm_year == year[1] && 1 + t->tm_mon == mon[1])) {
        if (7 + t->tm_hour<hour[0] || 7 + t->tm_hour>hour[1])
            return false;
        else if (hour[0] == 7 + t->tm_hour || hour[1] == 7 + t->tm_hour) {
            if (t->tm_min<min[0] || t->tm_min>min[1]) 
                return false;
        }
    }
    else return true; 
}

//3
void InputMyCourse(Course*& MyCo, int& n, student* Student)
{
    fstream fSoC;
    string filename;
    ifstream f;
    filename = to_string(Student->id) + "_Courses.txt";
    f.open(filename, ifstream::in);
    f >> n;
    Course* pcur = 0;
    if (!f.is_open())
    {
        cout << "Can't open Student's Courses file.\n";
        return;
    }
    while (!f.eof() && n != 0)
    {
        if (MyCo == nullptr)
        {
            MyCo = new Course;
            pcur = MyCo;
        }
        else
        {
            pcur->next = new Course;
            pcur = pcur->next;
        }
        f >> pcur->no;
        f >> pcur->CoId;
        string space;
        getline(f, space);
        getline(f, pcur->CoName);
        getline(f, pcur->teacherName);
        f >> pcur->credit;
        f >> pcur->maxSt;
        f >> pcur->day[0];
        f >> pcur->s[0];
        f >> pcur->day[1];
        f >> pcur->s[1];
        getline(f, space);
        pcur->next = nullptr;

        filename = pcur->CoId + ".txt";
        fSoC.open(filename, fstream::in);
        pcur->SofC = new StuofCourse;
        fSoC >> pcur->SofC->StuEnroll;
        student* ptmp = 0;
        while (!fSoC.eof())
        {
            if (pcur->SofC->Stu == nullptr)
            {
                pcur->SofC->Stu = new student;
                ptmp = pcur->SofC->Stu;
            }
            else
            {
                ptmp->next = new student;
                ptmp = ptmp->next;
            }
            fSoC >> ptmp->id;
            string space;
            getline(fSoC, space);
            getline(fSoC, ptmp->firstname);
            getline(fSoC, ptmp->gender);
            fSoC >> ptmp->dob.day;
            fSoC >> ptmp->dob.month;
            fSoC >> ptmp->dob.year;
            ptmp->next = nullptr;
        }

        fSoC.close();
    }
    f.close();
}

void InputAvailCourse(Sem srr[], Course* MyCo, int& i)
{
    fstream f, fSoC;
    f.open("CourseList.txt", fstream::in);
    string filename;

    int t;
    Course* pcur = nullptr;
    f >> i;
    i--;
    f >> srr[i].SemStart;
    f >> srr[i].SemEnd;
    f >> srr[i].regisStart;
    f >> srr[i].regisEnd;
    f >> t;
    while (t != 0)
    {
        if (srr[i].head == nullptr)
        {
            srr[i].head = new Course;
            pcur = srr[i].head;
        }
        else
        {
            pcur->next = new Course;
            pcur = pcur->next;
        }
        pcur->no = t;
        f >> pcur->CoId;
        string space;
        getline(f, space);
        getline(f, pcur->CoName);
        getline(f, pcur->teacherName);
        f >> pcur->credit;
        f >> pcur->maxSt;
        f >> pcur->day[0];
        f >> pcur->day[1];
        f >> pcur->s[0];
        f >> pcur->s[1];
        getline(f, space);

        filename = pcur->CoId + ".txt";
        fSoC.open(filename, fstream::in);
        if (!fSoC.is_open())
            return;
        pcur->SofC = new StuofCourse;
        fSoC >> pcur->SofC->StuEnroll;
        if (pcur->SofC->StuEnroll != 0) {
            student* ptmp = 0;
            while (!fSoC.eof())
            {
                if (pcur->SofC->Stu == nullptr)
                {
                    pcur->SofC->Stu = new student;
                    ptmp = pcur->SofC->Stu;
                }
                else
                {
                    ptmp->next = new student;
                    ptmp = ptmp->next;
                }
                fSoC >> ptmp->id;
                string space;
                getline(fSoC, space);
                getline(fSoC, ptmp->firstname);
                getline(fSoC, ptmp->gender);
                fSoC >> ptmp->dob.day;
                fSoC >> ptmp->dob.month;
                fSoC >> ptmp->dob.year;
                ptmp->next = nullptr;
            }
            pcur->next = nullptr;
        }
        else
            pcur->SofC = 0;
       
        fSoC.close();
        f >> t;
    }
    while (MyCo)
    {
        RemoveAlreadyCourses(srr[i].head, MyCo->no);
        MyCo = MyCo->next;
    }
    f.close();
}

void EnrollCourse(Sem S, Course*& MyCourse, int& count, student* Student, fstream& fSoC) // S la hoc ki voi cac course dc staff nhap vao
{
    if (count == 5)
    {
        cout << "You have met the limit of enrollment course!!!" << endl;
        return;
    }
    string ID;
    bool check;
    if (S.head == nullptr)
        return;
    cout << endl << "Please enter the Course ID you want to enroll" << endl;
    cout << "ID: ";
    cin >> ID;
    Course* pC = S.head;
    while (pC != nullptr && pC->CoId != ID) 
        pC = pC->next;
    if (MyCourse != nullptr)
    {
        Course* pCheck = MyCourse;
        while (pCheck != nullptr)
        {
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    if (pC->day[i] == pCheck->day[j])
                        if (pC->s[i] == pCheck->s[j])
                        {
                            check = false;
                            cout << " Enrollment fails. Session conflicts!" << endl;
                            return;
                        }
        }
    }

    if (pC == nullptr)
    {
        cout << "Wrong ID !!!";
        return;
    }

    Course* pcur = MyCourse;
    if (MyCourse == nullptr)
    {
        MyCourse = pC;
    }
    else
    {
        while (pcur->next != nullptr) 
            pcur = pcur->next;
        pcur->next = pC;
    }

    if (pC == S.head)
    {
        S.head = S.head->next;
    }
    else
    {
        Course* pLink = S.head;
        while (pLink->next != pC) 
            pLink = pLink->next;
        pLink->next = pC->next;
    }
    pC->next = nullptr;
    AddStutoCourse(pC, Student);
    StoreStusofCourse(pC, fSoC);
    count++;
    StoreCoursesofStu(MyCourse, count, Student);
}

void AddStutoCourse(Course*& MyCo, student* Student)
{
    student* pCur = 0;
    if (MyCo->SofC == nullptr)
    {
        MyCo->SofC = new StuofCourse;
        MyCo->SofC->Stu = new student;
        pCur = MyCo->SofC->Stu;
    }
    else
    {
        while (pCur->next != nullptr)
            pCur = pCur->next;
        pCur->next = new student;
        pCur = pCur->next;
    }
    MyCo->SofC->StuEnroll++;
    pCur->id = Student->id;
    pCur->dob.day = Student->dob.day;
    pCur->firstname = Student->firstname;
    pCur->lastname = Student->lastname;
    pCur->gender = Student->gender;
    pCur->dob.month = Student->dob.month;
    pCur->dob.year = Student->dob.year;
    pCur->socialid = Student->socialid;
    pCur->no = Student->no;
}

void ViewAvailableCourse(Sem S, int i)
{
    cout << setfill(' ');
    cout << "Course List of semester " << i+1 << " in " << S.year << " , beginning from ";
    cout << S.SemStart << " to " << S.SemEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << "Registration time starts from " << S.regisStart << " to " << S.regisEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << setw(10) << "ID";
    cout << setw(20) << "Name";
    cout << setw(20) << "Lecturer";
    cout << setw(7) << "Credit";
    cout << setw(8) << "Maximum";
    cout << setw(10) << "Day";
    cout << setw(8) << "Session";

    Course* pC = S.head;
    while (pC != nullptr)
    {
        cout << endl;
        cout << setw(10) << pC->CoId;
        cout << setw(20) << pC->CoName;
        cout << setw(20) << pC->teacherName;
        cout << setw(7) << pC->credit;
        cout << setw(8) << pC->maxSt;
        cout << setw(10) << pC->day[0];
        cout << setw(8) << pC->s[0];
        cout << endl << setw(75) << pC->day[1];
        cout << setw(8) << pC->s[1];
        pC = pC->next;
    }
}

void RemoveAlreadyCourses(Course*& pHead, int k)
{
    if (pHead == nullptr) return;
    Course* pCur = pHead;
    if (pHead->no == k) {
        pHead = pHead->next;
        delete pCur;
        return;
    }
    while (pCur->next != nullptr) {
        if (pCur->next->no == k) {
            Course* temp = pCur->next;
            pCur->next = pCur->next->next;
            delete temp;
            return;
        }
        pCur = pCur->next;
    }
}

void ViewMyCourse(Sem S, int i, Course* MyCo)
{
    cout << setfill(' ');
    cout << "Course List of semester " << i+1 << " in " << S.year << " , beginning from ";
    cout << S.SemStart << " to " << S.SemEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << "Registration time starts from " << S.regisStart << " to " << S.regisEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << setw(10) << "ID";
    cout << setw(20) << "Name";
    cout << setw(20) << "Lecturer";
    cout << setw(7) << "Credit";
    cout << setw(8) << "Maximum";
    cout << setw(10) << "Day";
    cout << setw(8) << "Session";
    if (MyCo == nullptr)
        return;
    Course* pC = MyCo;
    while (pC != nullptr)
    {
        cout << endl;
        cout << setw(10) << pC->CoId;
        cout << setw(20) << pC->CoName;
        cout << setw(20) << pC->teacherName;
        cout << setw(7) << pC->credit;
        cout << setw(8) << pC->maxSt;
        cout << setw(10) << pC->day[0];
        cout << setw(8) << pC->s[0];
        cout << endl << setw(75) << pC->day[1];
        cout << setw(8) << pC->s[1];
        pC = pC->next;
    }
    cout << endl;
    system("pause");
}

void DeleteCourse(Sem& S, Course*& MyCo, int& count, student* Student, fstream& fSoC){
    if (!MyCo) {
        cout << "There are no courses available to delete!!! \n";
        return;
    }

    Course* pC = S.head;
    if (S.head != nullptr)
        while (pC->next != nullptr) 
            pC = pC->next;

    string ID;
    cout << "Input the Course ID that you want to delete. \n";
    cout << "ID: ";
    cin >> ID;
    Course* pCur = MyCo;
    while (pCur != nullptr && pCur->CoId != ID) 
        pCur = pCur->next;

    RemoveStuofCo(pCur, Student);
    pCur->SofC->StuEnroll--;
    StoreStusofCourse(pCur, fSoC);

    if (S.head == nullptr)
    {
        S.head = pCur;
    }
    else
    {
        Course* pC = S.head;
        while (pC->next != nullptr) 
            pC = pC->next;
        pC->next = pCur;
    }

    if (pCur == MyCo)
    {
        MyCo = MyCo->next;
    }
    else
    {
        Course* pLink = MyCo;
        while (pLink->next != pCur) 
            pLink = pLink->next;
        pLink->next = pC->next;
    }
    pCur->next = nullptr;
    count--;
    StoreCoursesofStu(MyCo, count, Student);
}

void RemoveStuofCo(Course*& MyCo, student* Student)
{
    int x = Student->id;
    student* pCur = MyCo->SofC->Stu;

    if (MyCo->SofC->Stu->id == x) {
        MyCo->SofC->Stu = MyCo->SofC->Stu->next;
        delete pCur;
        return;
    }

    while (pCur->next != nullptr) {
        if (pCur->next->id == x) {
            student* temp = pCur->next;
            pCur->next = pCur->next->next;
            delete temp;
            return;
        }
        pCur = pCur->next;
    }
}

void OperateTask(Sem srr[], student* Student, int i)
{
    //preps
    int count = 0;
    Course* MyCourse = 0;
    fstream fSoC;

    InputMyCourse(MyCourse, count, Student);
    InputAvailCourse(srr, MyCourse,i);

    int option = 1;
    bool on = true;
    while (on)
    {
        system("CLS");
        cout << "\n\n";
        cout << "Course: " << endl;
        cout << "\t1. Enroll course.\n";
        cout << "\t2. Delete course.\n";
        cout << "\t3. View list of enrolled courses.\n";
        cout << "\t4. Exit\n";
        cout << "Choose your option (1-4): ";
        cin >> option;
        switch (option)
        {
        case 1:
        {
           if (checkRealTime(srr, i) == 1) {
                system("CLS");
                ViewAvailableCourse(srr[i], i);
                EnrollCourse(srr[i], MyCourse, count, Student, fSoC);
           }
            else {
               cout << "Registration session has ended\n";
               system("pause");
            }
            break;
        }
        case 2:
        {
            if (count != 0) {
                if (checkRealTime(srr, i) == 1) {
                    system("CLS");
                    ViewMyCourse(srr[i], i, MyCourse);
                    DeleteCourse(srr[i], MyCourse, count, Student, fSoC);
                }
                else {
                    cout << "Registration session has ended\n";

                }
            }
            else
                cout << "You have not enrolled any course\n";
            system("pause");
            break;
        }
        case 3:
        {
            if (count != 0) {
                system("CLS");
                if (checkRealTime(srr, i) == 1)
                     ViewMyCourse(srr[i], i, MyCourse);
                else
                ViewMyCourseAfterRegistrationOver(MyCourse, i);
            }
            else
                cout << "You have not enrolled any course\n";
            break;
        }
        case 4:
            on = false;
            break;
        default:
            cout << "Invalid option. Please enter again";
            system("pause");
            break;
        }
    }
}

void DeleteList(Course*& MyCo, Sem& S)
{
    while (MyCo != nullptr)
    {
        while (MyCo->SofC != nullptr)
        {
            student* pTmp1 = MyCo->SofC->Stu;
            MyCo->SofC->Stu = MyCo->SofC->Stu->next;
            delete pTmp1;
        }
        Course* pTmp = MyCo;
        MyCo = MyCo->next;
        delete pTmp;
    }
    while (S.head != nullptr)
    {
        while (S.head->SofC != nullptr)
        {
            student* pTmp1 = S.head->SofC->Stu;
            S.head->SofC->Stu = S.head->SofC->Stu->next;
            delete pTmp1;
        }
        Course* pTmp = S.head;
        S.head = S.head->next;
        delete pTmp;
    }
}

void StoreCoursesofStu(Course* MyCourse, int count, student* Student)
{
    string filename;
    filename = to_string(Student->id) + "_Courses.txt";
    ofstream f;
    f.open(filename, fstream::out);
    if (!f.is_open())
    {
        cout << "Can't open the Student's Courses file.\n";
        return;
    }
    f << count << endl;
    while (count != 0)
    {
        f << MyCourse->no << endl;
        f << MyCourse->CoId << endl;
        f << MyCourse->CoName << endl;
        f << MyCourse->teacherName << endl;
        f << MyCourse->credit << endl;
        f << MyCourse->maxSt << endl;
        f << MyCourse->day[0] << endl;
        f << MyCourse->s[0] << endl;
        f << MyCourse->day[1] << endl;
        f << MyCourse->s[1];
        MyCourse = MyCourse->next;
        count--;
        if (count != 0)
            f << endl;
    }
    f.close();
}

void StoreStusofCourse(Course* MyCourse, fstream& f)
{
    string filename;
    filename = MyCourse->CoId + ".txt";
    f.open(filename, fstream::out);
    if (!f.is_open())
    {
        cout << "Can't open the Student's Courses file.\n";
        return;
    }
    f << MyCourse->SofC->StuEnroll << endl;
    int count = MyCourse->SofC->StuEnroll;
    student* pCur = MyCourse->SofC->Stu;
    while (count != 0)
    {
        f << pCur->id << endl;
        f << pCur->firstname << endl;
        f << pCur->gender << endl;
        f << pCur->dob.day << endl;
        f << pCur->dob.month << endl;
        f << pCur->dob.year;
        count--;
        if (count != 0)
            f << endl;
        pCur = pCur->next;
    }
    f.close();
}

//4
void ViewMyCourseAfterRegistrationOver(Course* MyCo, int i)
{
    Course* cur = MyCo;
    cout << setfill(' ');
    cout << "Your course for this semester " << endl;
    cout << "==============================" << endl;
    cout << setw(5) << "ID";
    cout << setw(15) << "Name";
    cout << setw(15) << "Lecturer";
    cout << setw(5) << "Credit";
    cout << setw(5) << "Maximum";
    cout << setw(15) << "Day";
    cout << setw(15) << "Session";
    while (cur != nullptr) 
        {
        cout << endl;
        cout << setw(5) << cur->CoId;
        cout << setw(15) << cur->CoName;
        cout << setw(15) << cur->teacherName;
        cout << setw(5) << cur->credit;
        cout << setw(5) << cur->maxSt;
        cout << setw(15) << cur->day[0];
        cout << setw(15) << cur->s[0];
        cout << endl << setw(89) << cur->day[1];
        cout << endl << setw(15) << cur->s[1];
        cur = cur->next;
    }
    system("pause");
}

//5
void menuView(Sem srr[], int i, int year) {
    int option;
    bool on = true;
    do {
        system("CLS");
        cout << "Select what you want to view: \n"
            << "1. List of classes\n"
            << "2. List of students in a class\n"
            << "3. List of courses\n"
            << "4. List of students in a course\n"
            << "5. Exit View\n";
        cin >> option;
        switch (option) {
        case 1:
            system("CLS");
            ViewClass();
            break;
        case 2:
            system("CLS");
            ViewStudentofClass();
            break;
        case 3:
            system("CLS");
            displayCourseList(srr, i, year);
            break;
        case 4:
            system("CLS");
            ViewStudentsofCourse(srr[i]);
            break;
        case 5:
            on = false;
            break;
        default:
            cout << "Invalid option. Please enter again\n";
            system("pause");
            break;
        }
    } while (on);
}

void ViewClass() {
    string temp;
    ifstream myfile;
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

void ViewStudentofClass() {
    string temp, check;
    cout << "View student list of: ";
    cin >> temp;

    ifstream myfile;
    myfile.open("classes.csv");
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
    classfile.open(check + ".csv");
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
    myfile.close();
    classfile.close();
}

void ViewStudentsofCourse(Sem S) {
    string x;
    cout << "Enter Course ID: ";
    cin >> x;
    Course* pCur = S.head;
    if (pCur == nullptr)
    {
        cout << "No courses available\n";
        return;
    }
    while (pCur != nullptr && pCur->CoId != x)
        pCur = pCur->next;
    if (pCur == nullptr)
    {
        cout << "Wrong Course's ID.\n";
        return;
    }
    int count = 0;
    student* pC = S.head->SofC->Stu;
    cout << endl << "Total students: " << S.head->SofC->StuEnroll << endl;
    cout << setw(5) << "No";
    cout << setw(5) << "ID";
    cout << setw(15) << "First Name";
    cout << setw(15) << "Last Name";
    cout << setw(5) << "Gender";
    cout << setw(5) << "Day of Birth";
    while (pC != nullptr)
    {
        cout << setw(5) << count++;
        cout << setw(5) << pC->id;
        cout << setw(15) << pC->firstname;
        cout << setw(15) << pC->lastname;
        cout << setw(5) << pC->gender;
        cout << setw(5) << pC->dob.day << "/" << pC->dob.month << "/" << pC->dob.year << endl;
        pC = pC->next;
    }
}

//6
void export_student_in_courses(student* head, string* classs)
{
    ofstream output;
    output.open((*classs + "_math.csv").c_str());
    student* current = head;

    output << "No" << "," << "Student ID" << ',' << "Name" << "," << "Gender" << ", " << "Date of Birth" << "," << "Midterm Mark" << "," << "Final Mark" << "," << "Other Mark" << "," << "Total Mark" << endl;
    while (current)
    {
        output << current->no << ","
            << current->id << ","
            << current->firstname << ","
            << current->gender << ","
            << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << ","
            << ",,," << endl;

        if (current->next) 
            cout << endl;

        current = current->next;
    }
 
    current = head;

    while (head != nullptr)
    {
        head = head->next;
        delete current;
        current = head;
    }

    output.close();
}
//util
string choose_class(){
    course_class* head = nullptr;
    course_class* current = nullptr;
    fstream input;
    input.open("CourseList.txt", fstream::in);

    int t;
    string str;
    int no;
    input >> t;
    input >> str;
    input >> str;
    input >> str;
    input >> str;
    input >> no;
    while (no != 0)
    {
        if (head == nullptr)
        {
            head = new course_class;
            current = head;
        }
        else
        {
            current->next = new course_class;
            current = current->next;
        }

        getline(input, str);
        getline(input, current->data);
        getline(input, str);
        getline(input, str);
        input >> t;
        input >> t;
        getline(input, str);        
        getline(input, str);
        getline(input, str);
        input >> t;
        input >> t;
        input >> no;
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

    int key = 0; 
    cout << "Enter your option: ";
    cin >> key;
    for (int i = 1; i < key; i++) 
        current = current->next;
    string a(current->data.begin(), current->data.end());

    return a;
    input.close();
}

void load_stu_course_class(student*& head, string* classs)
{
    fstream data;
    data.open((*classs + ".txt").c_str(), fstream::in);
    if (!data.is_open()) {
        cout << "Failed";
        return;
    }        
    char temp;
    string str;
    student* current = nullptr;
    while (!data.eof())
    {
        if (head == nullptr)
        {
            head = new student;
            current = head;
        }
        else
        {
            current->next = new student;
            current = current->next;
        }

        data >> current->no;
        data >> current->id;
        getline(data, str);
        getline(data, current->firstname);
        getline(data, current->gender);
        data >> current->dob.day;
        data >> current->dob.month;
        data >> current->dob.year;
        getline(data, str);

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
    student* head = nullptr, * current = nullptr;
    string classs = choose_class();
    string* temp = &classs;
    cout << "Enter the address of mark file: ";
    while (getchar() != '\n');
    string a; 
    getline(cin, a);
    fstream import;

    char tempp;
    import.open(a, fstream::in);
    import.ignore(100000, '\n');
    while (!import.eof())
    {
        student* add = new student;
        import >> add->no;
        if (add->no < 0)break; 
        import >> tempp;
        import >> add->id;
        import >> tempp;
        getline(import, add->firstname, ',');
        getline(import, add->gender, ',');
        import >> add->dob.day; 
        import >> tempp;
        import >> add->dob.month;
        import >> tempp;
        import >> add->dob.year;
        import >> tempp;
        import >> add->midtermmark;
        import >> tempp;
        import >> add->finalmark;
        import >> tempp;
        import >> add->othermark; 
        import >> tempp;
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
    storage << "No" << "," << "Student ID" << ',' << "Name"  "," << "Gender" << ", " << "Date of Birth"  "," << "Midterm Mark" << "," << "Final Mark" << "," << "Other Mark" << "," << "Total Mark" << endl;
    while (current != nullptr)
    {
        storage << current->no << ","
            << current->id << ","
            << current->firstname << ","
            << current->gender << ","
            << current->dob.day << "/" << current->dob.month << "/" << current->dob.year << ","
            << current->midtermmark << ","
            << current->finalmark << ","
            << current->othermark << ","
            << current->totalmark;
        if (current->next)
            storage << endl;
        current = current->next;
    }
    storage.close();

    delete_linked_list(head);
}

void view_course_score() {
    string course_id;
    cout << "Enter the ID of the course you want to view score: ";
    cin >> course_id;
    ifstream f;
    f.open(course_id + "_math.csv");
    if (!f.is_open()) {
        cout << "Class " << course_id << " has not published its scoreboard\n";
        return;
    }
    cout << setw(2) << "No"
        << setw(10) << "ID"
        << setw(30) << "Name"
        << setw(14) << "Midterm mark"
        << setw(12) << "Final mark"
        << setw(12) << "Other mark"
        << setw(12) << "Total mark\n";

    char comma;
    string header;
    student* temp = new student;
    getline(f, header);
    while (!f.eof()) {
        f >> temp->no;
        f >> comma;
        f >> temp->id;
        f >> comma;
        getline(f, temp->firstname, ',');
        getline(f, temp->gender, ',');
        f >> temp->dob.day;
        f >> comma;
        f >> temp->dob.month;
        f >> comma;
        f >> temp->dob.year;
        f >> comma;
        f >> temp->midtermmark;
        f >> comma;
        f >> temp->finalmark;
        f >> comma;
        f >> temp->othermark;
        f >> comma;
        f >> temp->totalmark;
        getline(f, header);

        cout << setw(2) << temp->no << setw(10) << temp->id << setw(30) << temp->firstname 
            << setw(14) << fixed << setprecision(2) << temp->midtermmark 
            << setw(12) << fixed << setprecision(2) << temp->finalmark
            << setw(12) << fixed << setprecision(2) << temp->othermark
            << setw(12) << fixed << setprecision(2) << temp->totalmark << endl;
    }
    f.close();
    delete temp;
}

void update_res() {
    string course_id;
    cout << "Enter the ID of the course you want to update: ";
    cin >> course_id;
    ifstream f;
    f.open(course_id + "_math.csv");
    student* temp_h = 0;
    student* temp_c = 0;
    char comma;
    string str;
    getline(f, str);
    while (!f.eof()) {
        if (!temp_h) {
            temp_h = new student;
            temp_c = temp_h;
        }
        else {
            temp_c->next = new student;
            temp_c = temp_c->next;
        }

        f >> temp_c->no;
        f >> comma;
        f >> temp_c->id;
        f >> comma;
        getline(f, temp_c->firstname, ',');
        getline(f, temp_c->gender, ',');
        f >> temp_c->dob.day;
        f >> comma;
        f >> temp_c->dob.month;
        f >> comma;
        f >> temp_c->dob.year;
        f >> comma;
        f >> temp_c->midtermmark;
        f >> comma;
        f >> temp_c->finalmark;
        f >> comma;
        f >> temp_c->othermark;
        f >> comma;
        f >> temp_c->totalmark;
        getline(f, str);
    }

    temp_c = temp_h;
    int temp_id;
    cout << "Enter the ID of the student you want to update his/her results: ";
    cin >> temp_id;
    while (temp_c && temp_c->id != temp_id)
        temp_c = temp_c->next;
    if (!temp_c) {
        cout << "The student you are looking for is not in this course\n";
        return;
    }
        int option;
        bool on = true;
        do {
            cout << "Which score do you want to adjust?\n"
                << "1. Midterm mark\n"
                << "2. Final mark\n"
                << "3. Other mark\n"
                << "4. Total mark\n";
            cin >> option;
            switch (option) {
            case 1:
                cout << "Enter the new result: ";
                cin >> temp_c->midtermmark;
                on = false;
                break;
            case 2:
                cout << "Enter the new result: ";
                cin >> temp_c->finalmark;
                on = false;
                break;
            case 3:
                cout << "Enter the new result: ";
                cin >> temp_c->othermark;
                on = false;
                break;
            case 4:
                cout << "Enter the new result: ";
                cin >> temp_c->totalmark;
                on = false;
                break;
            default:
                cout << "Invalid option. Please enter again\n";
                system("pause");
                break;
            }
        } while (on);

        temp_c = temp_h;
        ofstream storage;
        storage.open(course_id + "_math.csv");
        storage << "No" << "," << "Student ID" << ',' << "Name" << "," << "Gender" << ", " << "Date of Birth" << ", " << "Social ID" << "," << "Midterm Mark" << "," << "Final Mark" << "," << "Other Mark" << "," << "Total Mark" << endl;
        while (temp_c != nullptr)
        {
            storage << temp_c->no << ","
                << temp_c->id << ","
                << temp_c->firstname << ","
                << temp_c->gender << ","
                << temp_c->dob.day << "/" << temp_c->dob.month << "/" << temp_c->dob.year << ","
                << temp_c->midtermmark << ","
                << temp_c->finalmark << ","
                << temp_c->othermark << ","
                << temp_c->totalmark;
            if (temp_c->next)
                storage << endl;
            temp_c = temp_c->next;
        }
        storage.close();
        f.close();
        delete_linked_list(temp_h);

}

void view_class_score() {
    string class_name;
    cout << "Enter the class you want to view score: ";
    cin >> class_name;
    ifstream f;
    f.open(class_name + ".csv");
    if (!f.is_open()) {
        cout << "Class " << class_name << "does not exist\n";
        return;
    }
    string str;
    getline(f, str);
    int t;
    char comma;
    student* temp = new student;
    while (!f.eof()) {
        int gpa = 0;
        int count_sub = 0;
        f >> t;
        f >> comma;
        f >> temp->id;
        getline(f, str);

        ifstream ID_Courses_ifs;
        ID_Courses_ifs.open(to_string(temp->id) + "_Courses.txt");
        if (!ID_Courses_ifs.is_open()) {
            cout << temp->id << ": This student has not enrolled any course\n";
            continue;
        }
        int count;
        string Course_name;
        ID_Courses_ifs >> count;
        while (count != 0) {
            ID_Courses_ifs >> t;//no
            ID_Courses_ifs >> str;//id
            getline(ID_Courses_ifs, Course_name);
            getline(ID_Courses_ifs, Course_name);
            ifstream math_ifs;
            math_ifs.open(str + "_math.csv");
            student* temp2 = new student;
            if (math_ifs.is_open()) {
                temp2->id = -1;
                while (temp2->id != temp->id && !math_ifs.eof()) {
                    getline(math_ifs, str);
                    math_ifs >> temp2->no;
                    math_ifs >> comma;
                    math_ifs >> temp2->id;
                }
                if (temp2->id == temp->id) {
                    math_ifs >> comma;
                    getline(math_ifs, temp2->firstname, ',');
                    getline(math_ifs, temp2->gender, ',');
                    math_ifs >> temp2->dob.day;
                    math_ifs >> comma;
                    math_ifs >> temp2->dob.month;
                    math_ifs >> comma;
                    math_ifs >> temp2->dob.year;
                    math_ifs >> comma;
                    math_ifs >> temp2->midtermmark;
                    math_ifs >> comma;
                    math_ifs >> temp2->finalmark;
                    math_ifs >> comma;
                    math_ifs >> temp2->othermark;
                    math_ifs >> comma;
                    math_ifs >> temp2->totalmark;
                    gpa += temp2->totalmark;
                    if (count_sub == 0)
                        cout << endl << temp->id << endl;
                    cout << Course_name << ": " << temp2->finalmark << endl;
                    count_sub++;
                }
                math_ifs.close();
            }
            getline(ID_Courses_ifs, str);//teacher name
            ID_Courses_ifs >> t;//credit
            ID_Courses_ifs >> t;//maxst
            ID_Courses_ifs >> str;//day0
            ID_Courses_ifs >> t;//s0
            ID_Courses_ifs >> str;//day1
            ID_Courses_ifs >> t;//s1
            count--;
            delete temp2;
            ID_Courses_ifs.close();
        }
        cout << "GPA this semester: " << gpa / float(count_sub) << endl;
    }

    delete temp;
    f.close();
}

void view_owner_score(student* Student) {
    int count;
    ifstream ifs;
    ifs.open(to_string(Student->id) + "_Courses.txt");
    if (!ifs.is_open()) {
        cout << "You have not enrolled any course\n";
        return;
    }
    int t;
    bool first = true;
    char comma;
    string course_id;
    string course_name;
    string str;
    ifs >> count;
    while (count != 0) {
        ifs >> t;//no
        ifs >> course_id;
        getline(ifs, course_name);
        getline(ifs, course_name);
        ifstream math_ifs;
        math_ifs.open(course_id + "_math.csv");
        student* temp = new student;
        if (math_ifs.is_open()) {
            temp->id = -1;
            while (temp->id != Student->id && !math_ifs.eof()) {
                getline(math_ifs, str);
                math_ifs >> temp->no;
                math_ifs >> comma;
                math_ifs >> temp->id;
            }
            if (temp->id == Student->id) {
                math_ifs >> comma;
                getline(math_ifs, temp->firstname, ',');
                getline(math_ifs, temp->gender, ',');
                math_ifs >> temp->dob.day;
                math_ifs >> comma;
                math_ifs >> temp->dob.month;
                math_ifs >> comma;
                math_ifs >> temp->dob.year;
                math_ifs >> comma;
                math_ifs >> temp->midtermmark;
                math_ifs >> comma;
                math_ifs >> temp->finalmark;
                math_ifs >> comma;
                math_ifs >> temp->othermark;
                math_ifs >> comma;
                math_ifs >> temp->totalmark;
                if (first) {
                    cout << endl << temp->id << endl;
                    first = false;
                }
                cout << course_name << ": " << temp->finalmark << endl;
            }
            math_ifs.close();
        }
        getline(ifs, str);//teacher name
        ifs >> t;//credit
        ifs >> t;//maxst
        ifs >> str;//day0
        ifs >> t;//s0
        ifs >> str;//day1
        ifs >> t;//s1
        count--;
        delete temp;
    }
    ifs.close();
}

void menuScore() {
    int option;
    bool on = true;
    do {
        system("CLS");
        cout << "Select what you want to do: \n"
            << "1. View scoreboard of a course\n"
            << "2. View scoreboard of a class\n"
            << "3. Update a student result\n"
            << "4. Exit Score\n";
        cin >> option;
        switch (option) {
        case 1:
            system("CLS");
            view_course_score();
            system("pause");
            break;
        case 2:
            system("CLS");
            view_class_score();
            system("pause");
            break;
        case 3:
            system("CLS");
            update_res();
            break;
        case 4:
            on = false;
            break;
        default:
            cout << "Invalid option. Please enter again\n";
            system("pause");
            break;
        }
    } while (on);
}