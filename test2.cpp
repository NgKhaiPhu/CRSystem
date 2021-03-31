#include <iostream>
#include <iomanip>
using namespace std;
struct Course{
    int CoId;
    string CoName;
    string teacherName;
    int credit;
    int maxSt = 50;
    string day;
    string s;
    Course*next;
};
struct Sem{
    int year;
    string SemStart;
    string SemEnd;
    string regisStart;
    string regisEnd;
    Course s;
    Course*head=nullptr;
    Course*cur=nullptr;
};

void create_courselist(Sem &s, Sem srr[]);
void displaytest(Sem s, Sem srr[], int i, int year);

void create_courselist(Sem &s, Sem srr[]){
    int year, i;
    cout << "==========================================" << endl;
    cout << "=  Create a List of Course for this Sem  =" << endl;
    cout << "==========================================" << endl;
    cout << "The Year of Current Sem: "; cin >> year;
    cout << "---------------------------" << endl;
    cout << "Which Sem?" << endl;
    cout << "-> Press 0 for Fall" << endl;
    cout << "-> Press 1 for Summner" << endl;
    cout << "-> Press 2 for Autumn" << endl;
    cout << "---------------------------" << endl;
    cout << "=> "; cin >> i;
    cout << "---------------------------" << endl;
    cin.ignore(32727, '\n');
    cout << "When is this Sem start and end?" << endl;
    cout << "Start in: "; 
    getline(cin, srr[i].SemStart);
    cout << "End in: ";
    getline(cin, srr[i].SemEnd);
    cout << "---------------------------" << endl;
    cout << "When the registion start and end?" << endl;
    cout << "Start in: ";
    getline(cin, srr[i].regisStart);
    cout << "End in: ";
    getline(cin, srr[i].regisEnd);
    cout << "---------------------------" << endl;
    cout << "Enter 0 in No to stop!" << endl;
    int No;
    cout << "No: "; cin>>No;
    srr[i].cur=nullptr;
    while (No!=0){
        if (srr[i].head==nullptr){
            srr[i].head= new Course;
            srr[i].cur=srr[i].head;
        } else {
            srr[i].cur->next=new Course;
            srr[i].cur=srr[i].cur->next;
        } cout << "Id of Course: ";
        cin >> srr[i].cur->CoId;
        cin.ignore(32767, '\n');
        cout << "Name of course: ";
        getline(cin, srr[i].cur->CoName);
        cout << "Number of credits: "; 
        cin >> srr[i].cur->credit;
        cin.ignore(32767, '\n');
        cout << "Day of week: ";
        getline(cin, srr[i].cur->day);
        cout << "Seaon of day: ";
        getline(cin, srr[i].cur->s);
        srr[i].cur->next=nullptr;
        cout << "No: "; cin>>No;
    }
    displaytest(s, srr, i, year);
}
/*struct Sem{
    int year;
    string SemStart;
    string SemEnd;
    string regisStart;
    string regisEnd;
    Course s;
}
struct Course{
    int CoId;
    string CoName;
    string teacherName;
    int credit;
    int maxSt = 50;
    string day;
    string s;
}*/

void displaytest(Sem s, Sem srr[], int i, int year){
    cout << setfill(' ');
    cout << "Course List of Sem " << i+1 << " in the year of " << year << " ,which from ";
    cout << srr[i].SemStart << " to " << srr[i].SemEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << "Registion time is from " << srr[i].regisStart << " to " << srr[i].regisEnd << endl;
    cout << "==========================================================================================" << endl;
    cout << setw(5) << "ID";
    cout << setw(15) << "Name";
    cout << setw(15) << "Teacher";
    cout << setw(5)  << "Credit";
    cout << setw(5)  << "Maximum";
    cout << setw(15) << "Day";
    cout << setw(15) << "Season"; 
}


int main(){
    Sem s;
    Sem srr[3];
    create_courselist(s, srr);
    return 0;
}

