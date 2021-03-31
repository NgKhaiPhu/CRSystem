#include <iostream>
using namespace std;

struct Sem{
    int year;
    string SemStart;
    string SemEnd;
    string regisStart;
    string regisEnd;
    Course s;
    Course* head=nullptr;
}
struct Course{
    int CoId;
    string CoName;
    string teacherName;
    int credit;
    int maxSt = 50;
    string day;
    string s;
    Course*next;
}

void create_courselist(Sem &s, Sem srr[]){
    int year, i;
    cout << "==========================================" << endl;
    cout << "=  Create a List of Course for this Sem  ="
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
    getline(cin, regisStart);
    cout << "End in: ";
    getline(cin, regisEnd);
    cout << "---------------------------" << endl;
    cout << "Enter 0 in No to stop!" << endl;
    int No;
    cout << "No: "; cin>>No;
    Course*cur=nullptr;
    while (No!=0){
        if (head==nullptr){
            head= new Course;
            cur=head;
        } else {
            cur->next=new Course;
            cur=cur->next;
        } cout << ""
    }
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

int main(){
    Sem s;
    Sem srr[3];
    create_courselist(s, srr);
}