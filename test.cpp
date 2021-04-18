#include <iostream>
using namespace std;
struct Course{
    int CoId;
    string CoName;
    string teacherName;
    int credit;
    int maxSt = 50;
    string day[2];
    string s[2];
    Course*next;
};
struct Sem{
    int year;
    string SemStart;
    string SemEnd;
    string regisStart;
    string regisEnd;
    Course*head=nullptr;
    Course*cur=nullptr;
};

void TCmenu(Sem se, Sem srr[], int i, int year, int season);
void create_courselist(Sem &se, Sem srr[], int &i, int &year, int &season);
void displayCourseList(Sem se, Sem srr[], int i, int year, int season);
void deleteCourse(Sem &se, Sem srr[], int i);

void TCmenu(Sem se, Sem srr[], int i, int year, int season){
    int option;
    do{
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\t=          Press 0 to Endtask              =" << endl;
        cout << "\t\t\t=                1 to Create Courses       =" << endl;
        cout << "\t\t\t=                2 to Delete Courses       =" << endl;
        cout << "\t\t\t=                3 to Display List         =" << endl;
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\tOption => "; cin>> option;
        if (option==1){create_courselist(se, srr, i, year, season);}
        if (option==2){deleteCourse(se, srr, i);}
        if (option==3){displayCourseList(se, srr, i, year, season);}
    } while (option!=0);
}



void create_courselist(Sem &se, Sem srr[], int &i, int &year, int&season){
    cout << "\t\t\t==========================================" << endl;
    cout << "\t\t\t=  Create a List of Course for this Sem  =" << endl;
    cout << "\t\t\t==========================================" << endl;
    cout << "\t\t\tThe Year of Current Sem: "; 
    cin >> year;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\tWhich Sem?" << endl;
    cout << "\t\t\t-> Press 1 for Fall" << endl;
    cout << "\t\t\t-> Press 2 for Summner" << endl;
    cout << "\t\t\t-> Press 3 for Autumn" << endl;
    cout << "\t\t\t---------------------------" << endl;
    cout << "\t\t\t=> ";
    cin >> i; i=i-1;
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
    cin>>No;
    srr[i].cur=nullptr;
    while (No!=0){
        if (srr[i].head==nullptr){
            srr[i].head= new Course;
            srr[i].cur=srr[i].head;
        } else {
            srr[i].cur->next=new Course;
            srr[i].cur=srr[i].cur->next;
        } cout << "\t\t\tId of Course: ";
        cin >> srr[i].cur->CoId;
        cin.ignore(32767, '\n');
        cout << "\t\t\tName of course: ";
        getline(cin, srr[i].cur->CoName);
        cout << "\t\t\tTeacher in class: ";
        getline(cin, srr[i].cur->teacherName);
        cout << "\t\t\tNumber of credits: "; 
        cin >> srr[i].cur->credit;
        cin.ignore(32767, '\n');
        cout << "\t\t\tDay of week: ";
        getline(cin, srr[i].cur->day);
        cout << "\t\t\tHow many season of a day?: ";
        cin>>season;
        cin.ignore(32767, '\n');
        for (int j=0; j<season; j++){
            cout << "\t\t\tS" << j+1 << ": ";
            getline(cin, srr[i].cur->s[j]);
        }
        srr[i].cur->next=nullptr;
        cout << "\t\t\tNo: "; 
        cin>>No;
    }
}

void displayCourseList(Sem se, Sem srr[], int i, int year, int season){
    cout << endl << endl;
    cout << setfill(' ');
    cout << "Course List of Sem " << i+1 << " in the year of " << year << " ,which from ";
    cout << srr[i].SemStart << " to " << srr[i].SemEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << "Registion time is from " << srr[i].regisStart << " to " << srr[i].regisEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << setw(13) << left << "ID";
    cout << setw(15) << left <<  "Course";
    cout << setw(17) << left <<  "Teacher";
    cout << setw(10) << left <<  "Credit";
    cout << setw(10) << left <<  "Maximum";
    cout << setw(10) << left <<  "Day";
    cout << "Season"; 
    cout << endl;
    while (srr[i].head!=nullptr){
        cout << setfill(' ');
        cout << setw(13) << left <<  srr[i].head->CoId;
        cout << setw(15) << left <<  srr[i].head->CoName;
        cout << setw(17) << left <<  srr[i].head->teacherName;
        cout << setw(10) << left <<  srr[i].head->credit;
        cout << setw(10) << left <<  srr[i].head->maxSt;
        cout << setw(10) << left <<  srr[i].head->day;
        for (int j=0; j<season; j++){
            cout << "S" << j+1 << ": ";
            cout << srr[i].head->s[j];
            cout << "  ";
        }
        cout << endl;
        srr[i].head=srr[i].head->next;
    }
}

void deleteCourse(Sem &se, Sem srr[], int i){
    int ids, m;
    cout << endl;
    cout << "\t\t\tSem: "; cin>>m;
    cout << "\t\t\tCourse ID that need to delete: "; cin>>ids;
    if (!srr[m].head){
        cout << "List not available!" << endl;
        return;
    }
    srr[m].cur=srr[m].head;
    if (srr[m].head->CoId==ids){
        srr[m].head=srr[m].head->next;
        delete srr[m].cur;
        srr[m].cur=nullptr;
    } else {
        while (srr[m].cur->next->CoId!=ids){
            srr[m].cur=srr[m].cur->next;
        } Course*link=srr[m].cur->next;
        srr[m].cur->next=srr[m].cur->next->next;
        delete link;
    }
}


int main(){
    int i, year;
    Sem se;
    Sem srr[3];
    int season;
    TCmenu(se, srr, i, year, season);
    return 0;
}
