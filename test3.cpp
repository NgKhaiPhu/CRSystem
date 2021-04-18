#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Course {
    int no;
    string CoId, CoName, teacherName;
    int credit, maxSt = 50;
    string day[2], s[2];
    Course* next;
};

struct Sem {
    string SemStart, SemEnd, regisStart, regisEnd;
    Course s;
    Course* head = nullptr, *cur = nullptr;
};

void TCmenu(Sem se, Sem srr[], int i, int year);
void create_courselist(Sem& se, Sem srr[], int& i, int& year);
void displayCourseList(Sem se, Sem srr[], int i, int year);
void deleteCourse(Sem& se, Sem srr[]);
void read_data(Sem se, Sem srr[], int i, int year);
void updateCourse(Sem &se, Sem srr[]);

void TCmenu(Sem se, Sem srr[], int i, int year) {
    int option;
    do {
        cout << endl;
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\t=          Press 0 to Endtask              =" << endl;
        cout << "\t\t\t=                1 to Create Courses       =" << endl;
        cout << "\t\t\t=                2 to Delete Courses       =" << endl;
        cout << "\t\t\t=                3 to Update Course        =" << endl;
        cout << "\t\t\t=                4 to Display List         =" << endl;
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\tOption => "; cin >> option;
        if (option == 1) { create_courselist(se, srr, i, year); }
        if (option == 2) { deleteCourse(se, srr); }
        if (option == 3) { updateCourse(se, srr); }
        if (option == 4) { displayCourseList(se, srr, i, year); }
    } while (option != 0);
}


void create_courselist(Sem& se, Sem srr[], int& i, int& year) {
    cout << "\t\t\t============================================" << endl;
    cout << "\t\t\t=   Create a List of Course for this Sem   =" << endl;
    cout << "\t\t\t============================================" << endl;
    cout << "\t\t\tThe Year of Current Sem: ";
    cin >> year;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhich Sem?" << endl;
    cout << "\t\t\t-> Press 1 for Fall" << endl;
    cout << "\t\t\t-> Press 2 for Summner" << endl;
    cout << "\t\t\t-> Press 3 for Autumn" << endl;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\t=> ";
    cin >> i; i = i - 1;
    cout << "\t\t\t---------------------------" << endl;
    cin.ignore(32727, '\n');
    cout << "\t\t\tWhen is this Sem start and end?" << endl;
    cout << "\t\t\tStart in: ";
    getline(cin, srr[i].SemStart);
    cout << "\t\t\tEnd in: ";
    getline(cin, srr[i].SemEnd);
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhen the registion start and end?" << endl;
    cout << "\t\t\tStart in: ";
    getline(cin, srr[i].regisStart);
    cout << "\t\t\tEnd in: ";
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
        cout << "\t\t\tId of Course: ";
        srr[i].cur->no = No;
        getline(cin, srr[i].cur->CoId);
        cout << "\t\t\tName of course: ";
        getline(cin, srr[i].cur->CoName);
        cout << "\t\t\tTeacher in class: ";
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
    cout << "Course List of Sem " << i + 1 << " in the year of " << year << " ,which from ";
    cout << srr[i].SemStart << " to " << srr[i].SemEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << "Registion time is from " << srr[i].regisStart << " to " << srr[i].regisEnd << endl;
    cout << "===================================================================================================" << endl;
    cout << setw(13) << left << "ID";
    cout << setw(15) << left << "Course";
    cout << setw(17) << left << "Teacher";
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
    cout << "\t\t\tSem: ";
    cin >> m;
    cin.ignore(32767, '\n');
    cout << "\t\t\tCourse ID that need to delete: ";
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

void updateCourse(Sem &se, Sem srr[]){
    int n;
    cout << "\t\t\tSem: "; cin>>n;
    cout << "\t\t\tId of course that need to adjusted: ";
    string idfake; cin>>idfake;
    srr[n].cur=srr[n].head;
    if (!srr[n].head) cout<<"\t\t\tList not available !";return;
    if (srr[n].head->CoId!=idfake){
        while (srr[n].cur!=nullptr&&srr[n].cur->CoId!=idfake){
            srr[n].cur=srr[n].cur->next;
        }
    } if (!srr[n].cur) cout << "\t\t\tNot found data!";return;
    int op;

    do{
        cout << endl;
        cout << "\t\t\t=====================================" << endl;
        cout << "\t\t\t=  which factor need to adjusted ?  =" << endl;
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
        cin>>op;
        switch (op){
            case 1: cout << "\t\t\tnew ID: "; cin>>srr[n].cur->CoId;
            case 2: cout << "\t\t\tnew NameCourse: "; cin.ignore(32767,'\n'); getline(cin, srr[n].cur->CoName);
            case 3: cout << "\t\t\tnew Lecture: "; cin.ignore(32767,'\n'); getline(cin, srr[n].cur->CoName);
            case 4: cout << "\t\t\tnew Credit: "; cin>>srr[n].cur->credit;
            case 5: cout << "\t\t\tnew MaxStudent: "; cin>>srr[n].cur->maxSt;
            case 6: cout << "\t\t\tnew Day of week"; 
                            for (int i=0; i<2; i++) {
                                cout<<"Day "<<i+1<<": ";
                                cin>>srr[n].cur->day[i];
                            }
            case 7: cout << "\t\t\tnew Session of day"; 
                            for (int i=0; i<2; i++) {
                                cout<<"Session "<<i+1<<": ";
                                cin>>srr[n].cur->s[i];
                            }
            case 8:
                cout << "\t\t\tnew Id: ";
                getline(cin, srr[n].cur->CoId);
                cout << "\t\t\tnew Name: ";
                getline(cin, srr[n].cur->CoName);
                cout << "\t\t\tnew Teacher: ";
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
        }
    } while (op!=0);
}



int main() {
    int i;
    int year;
    Sem se;
    Sem srr[3];
    TCmenu(se, srr, i, year);
    cout << "helloworld";
    return 0;
}