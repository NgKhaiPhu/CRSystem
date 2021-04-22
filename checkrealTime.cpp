#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void takeRealTime(string SemStart, string SemEnd, string ReStart, string ReEnd);
bool isInSem(string SemStart, string SemEnd, tm* t, int* day, int* mon, int*year);
bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int*year, int* hour, int*min);

void takeRealTime(string SemStart, string SemEnd, string ReStart, string ReEnd){
    time_t now = time(NULL);
    tm* t = localtime(&now);
    int* day = new int[2];
    int* mon = new int[2];
    int* year = new int[2];
    int* hour = new int[2];
    int* min = new int[2];
    
    if (isInSem(SemStart, SemEnd, t, day, mon, year)==true) {
        if (isInRe(ReStart, ReEnd, t, day, mon, year, hour, min)==true){
            cout << "Yes";
        } else cout << "Not this Time bitch!!!";
    }
    else cout << "Sem is end!";
       
    delete []day;
    delete []mon;
    delete []year;
    delete []hour;
    delete []min;
}

bool isInSem(string SemStart, string SemEnd, tm* t, int* day, int* mon, int*year){
    for (int i=0; i<2; i++) {day[i]=0; mon[i]=0; year[i]=0;}
    int n=SemStart.length();
    for (int i=0; i<n; i++){
        char c=SemStart[i];
        switch (i){
            case 0: {
                day[0] += (c-'0')*10;
                break;
            }
            case 1: {
                day[0] += c-'0';
                break;
            } 
            case 3: {
                mon[0] += (c-'0')*10;
                break;
            }
            case 4: {
                mon[0] += c-'0';
                break;
            } 
            case 6: {
                year[0] += (c-'0')*1000;
                break;
            }
            case 7: {
                year[0] += (c-'0')*100;
                break;
            } 
            case 8: {
                year[0] += (c-'0')*10;
                break;
            }
            case 9: {
                year[0] += c-'0';
                break;
            } 
            
            default: continue;
        };
    } 
    for (int i=0; i<n; i++){
        char c=SemEnd[i];
        switch (i){
            case 0: {
                day[1] += (c-'0')*10;
                break;
            }
            case 1: {
                day[1] += c-'0';
                break;
            } 
            case 3: {
                mon[1] += (c-'0')*10;
                break;
            }
            case 4: {
                mon[1] += c-'0';
                break;
            } 
            case 6: {
                year[1] += (c-'0')*1000;
                break;
            }
            case 7: {
                year[1] += (c-'0')*100;
                break;
            } 
            case 8: {
                year[1] += (c-'0')*10;
                break;
            }
            case 9: {
                year[1] += c-'0';
                break;
            } 
            
            default: continue;
        };
    } 
    /*cout << day[0] << " " << t->tm_mday << endl;
    cout << mon[0] << " " << 1+t->tm_mon << endl;
    cout << year[0] << " " << 1900+t->tm_year << endl;
    cout << day[1] << " " << t->tm_mday << endl;
    cout << mon[1] << " " << 1+t->tm_mon << endl;
    cout << year[1] << " " << 1900+t->tm_year << endl;*/
    
    if (1900+t->tm_year<year[0]||1900+t->tm_year>year[1]) return false;
    else if (1+t->tm_mon<mon[0]||1+t->tm_mon>mon[1]) return false;
    else if (t->tm_mday<day[0]||t->tm_mday>day[1]) return false;
    else return true;
}

bool isInRe(string ReStart, string ReEnd, tm* t, int* day, int* mon, int*year, int* hour, int*min){
    for (int i=0; i<2; i++) {day[i]=0; mon[i]=0; year[i]=0; hour[i]=0; min[i]=0;}
    int n=ReStart.length();
    for (int i=0; i<n; i++){
        char c=ReStart[i];
        switch (i){
            case 0: {
                day[0] += (c-'0')*10;
                break;
            }
            case 1: {
                day[0] += c-'0';
                break;
            } 
            case 3: {
                mon[0] += (c-'0')*10;
                break;
            }
            case 4: {
                mon[0] += c-'0';
                break;
            } 
            case 6: {
                year[0] += (c-'0')*1000;
                break;
            }
            case 7: {
                year[0] += (c-'0')*100;
                break;
            } 
            case 8: {
                year[0] += (c-'0')*10;
                break;
            }
            case 9: {
                year[0] += c-'0';
                break;
            } 
            case 11: {
                hour[0] += (c-'0')*10;
                break;
            }
            case 12: {
                hour[0] += c-'0';
                break;
            } 
            case 14: {
                min[0] += (c-'0')*10;
                break;
            }
            case 15: {
                min[0] += c-'0';
                break;
            }
            default: continue;
        };
    } 
    for (int i=0; i<n; i++){
        char c=ReEnd[i];
        switch (i){
            case 0: {
                day[1] += (c-'0')*10;
                break;
            }
            case 1: {
                day[1] += c-'0';
                break;
            } 
            case 3: {
                mon[1] += (c-'0')*10;
                break;
            }
            case 4: {
                mon[1] += c-'0';
                break;
            } 
            case 6: {
                year[1] += (c-'0')*1000;
                break;
            }
            case 7: {
                year[1] += (c-'0')*100;
                break;
            } 
            case 8: {
                year[1] += (c-'0')*10;
                break;
            }
            case 9: {
                year[1] += c-'0';
                break;
            } 
            case 11: {
                hour[1] += (c-'0')*10;
                break;
            }
            case 12: {
                hour[1] += c-'0';
                break;
            } 
            case 14: {
                min[1] += (c-'0')*10;
                break;
            }
            case 15: {
                min[1] += c-'0';
                break;
            }
            default: continue;
        };
    } 
    
    if (1900+t->tm_year<year[0]||1900+t->tm_year>year[1]) return false;
    else if (1+t->tm_mon<mon[0]||1+t->tm_mon>mon[1]) return false;
    else if (t->tm_mday<day[0]||t->tm_mday>day[1]) return false;
    else if (t->tm_hour<hour[0]||t->tm_hour>hour[1]) return false;
    else if (t->tm_min<min[0]||t->tm_min>min[1]) return false;
    else return true;
}

int main() {
    string SemStart = "10/08/2020";
    string SemEnd = "21/01/2021";
    string ReStart = "20/07/2020 18h30 ";
    string ReEnd = "05/08/2020 20h00";
    takeRealTime(SemStart, SemEnd, ReStart, ReEnd);
    return 0;
}