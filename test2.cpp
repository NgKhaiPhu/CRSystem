#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

void view_class_score(){
    ifstream ifs;
    ifs.open("Math.csv");
    string header;
    getline(ifs, header);
    int comma=0;
    cout << setfill(' ');

    //offerences
    cout << "\t\t\tWhich class that you need to view: ";
    string option; cin>>option;

    //trình bày header
    for (int i=0; i<header.length(); i++){
        if (header[i]==',') {
            comma++;
            cout << setw(10);
        }
        else cout << header[i];
    } 
    cout << endl;

    //đếm dấu phẩy để suy ra số môn đang có, và 1 biến course đang học
    //giá trị course in learn sẽ đc điều chỉnh lại bên dưới
    int totalcourse=comma-3;
    int courseInLearn=totalcourse;

    //struct local
    struct st{
        int id;
        string name, cls;
        string course;
        st* next;
    };
    st* head=nullptr;
    st* cur=nullptr;

    //đọc file local struct st
    while (ifs.good()){
        if (head==nullptr){
            head=new st;
            cur=head;
        } else {
            cur->next=new st;
            cur=cur->next;
        }
        ifs>>cur->id;
        ifs.ignore(32767, ',');
        getline(ifs, cur->name, ',');
        getline(ifs, cur->cls, ',');
        getline(ifs, cur->course, '\n');
        
        cur->next=nullptr;
    } ifs.close();  


    //find out answer
    cur=head;
    bool check = false;
    while (cur){
        if (option==cur->cls){
            cout << left << setw(11) << cur->id;
            cout << left << setw(22) << cur->name;
            cout << left << setw(13) << cur->cls;
            for (int i=0; i<cur->course.length(); i++){
                if (cur->course[i]=='1'&&cur->course[i-1]=='-') {
                    cout << left << setw(6) << "none";
                    courseInLearn--;
                } else if (cur->course[i]==',') cout << right << setw(7);
                else cout << cur->course[i];
            }

            //tính GPA
            float total, final, mid, other;
            char slash;
            float GPA=0;

            //tách string lấy điểm từng phần
            stringstream ss(cur->course);
            for (int count=totalcourse; count>=0; count--){
                ss>>total;
                ss>>slash;
                if (total!=-1){
                    ss>>final;
                    ss>>slash;
                    ss>>mid;
                    ss>>slash;
                    ss>>other;
                    GPA+=(final+mid+other)/3.0;
                } ss>>slash;
            }

            cout << right << setw(10) << GPA/(float)courseInLearn;


            cout << endl;
            check=true;
        }
        
        cur=cur->next;
    }

    //check there no info
    if (!check) cout << "\t\t\tWrong name class or class is not available!!" <<endl;

    cur=head;
    while (head){
        head=head->next;
        delete cur;
        cur=head;
    }
}

void view_owner_score(){
    ifstream ifs;
    ifs.open("test2.csv");
    string header;
    getline(ifs, header);
    int comma=0;
    cout << setfill(' ');

    //offerences
    string option = "Nguyen Duy Thinh";

    //trình bày header
    for (int i=0; i<header.length(); i++){
        if (header[i]==',') {
            comma++;
            cout << setw(10);
        }
        else cout << header[i];
    } cout << endl;

    //đếm dấu phẩy để suy ra số môn đang có
    int totalcourse=comma-2;

    //struct local
    struct st{
        int id;
        string name, cls;
        string course;
        st* next;
    };
    st* head=nullptr;
    st* cur=nullptr;

    //đọc file local struct st
    while (ifs.good()){
        if (head==nullptr){
            head=new st;
            cur=head;
        } else {
            cur->next=new st;
            cur=cur->next;
        }
        ifs>>cur->id;
        ifs.ignore(32767, ',');
        getline(ifs, cur->name, ',');
        getline(ifs, cur->cls, ',');
        getline(ifs, cur->course, '\n');
        
        cur->next=nullptr;
    } ifs.close();  


    //find out answer
    cur=head;
    bool check = false;
    while (cur){
        if (option==cur->cls){
            cout << left << setw(11) << cur->id;
            cout << left << setw(22) << cur->name;
            cout << left << setw(13) << cur->cls;
            for (int i=0; i<cur->course.length(); i++){
                if (cur->course[i]=='1'&&cur->course[i-1]=='-') {
                    cout << left << setw(6) << "none";
                } else if (cur->course[i]==',') cout << right << setw(7);
                else cout << cur->course[i];
            } cout << endl;
            check=true;
        }
        cur=cur->next;
    }

    //check there no info
    if (!check) cout << "\t\t\tWrong name class or class is not available!!" <<endl;

    cur=head;
    while (head){
        head=head->next;
        delete cur;
        cur=head;
    }
}


int main(){
    view_class_score();
    return 0;
}