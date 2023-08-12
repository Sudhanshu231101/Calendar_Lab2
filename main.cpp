#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

string daysOfWeek[]={"saturday","sunday","monday","tuesday","wednesday","thursday","friday"};
int daysOfMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};

class Date{
  private:
  string dayOfWeek;
  int month;
  int dayOfMonth;
  int year;

  public:
  int getdayOfMonth(){
    return dayOfMonth;
  }
  int getmonth(){
    return month;
  }
  int getyear(){
    return year;
  }
  Date(){
    dayOfMonth=1;
    month=1;
    year=2023;
  }

  Date(int m, int y, int doM){
  dayOfMonth=doM;
  month=m;
  year=y;  
  }
  void putValue(int m, int y, int doM){
    month=m;
    year=y;
    dayOfMonth=doM;
  }

  void displayDate(){
    cout<<"DATE is "<<dayOfMonth<<"/"<<month<<"/"<<year<<endl;
  }

};

class Notes{
  public:
  Date d;
  string note;

  Notes(Date d1,string note1){
    d=d1;
    note=note1;
  }
  Date getDateofNotes(){
    return d;
  }
  string getNotes(){
    return note;
  }
};


class calender{
  private:
  vector<Date> holidayList;
  vector< pair< Date , string> > notes;
  public:
  int getDayCode(string day){
    int h;
    if(day=="sunday"){
      h=1;
    }
    else if(day=="monday"){
      h=2;
    }
    else if(day=="tuesday"){
      h=3;
    }
    else if(day=="wednesday"){
      h=4;
    }
    else if(day=="thursday"){
      h=5;
    }
    else if(day=="friday"){
      h=6;
    }
    else{
      h=7;
    }
    return h;
  }
  //-------------------------------------------------------------//
  string getDay(Date d){
    int q=d.getdayOfMonth();
    int m=d.getmonth();
    int y=d.getyear();

    if(m<3){
      m=m+12;
      y--;
    }

    int k,j;
    k=y%100;
    j=y/100;

    int h;
    // Zeller’s congruence formula//
    h=(q+(13*(m+1))/5+k+(k/4)+(j/4)+(5*j))%7;

    return daysOfWeek[h];
  }
  // ------------------------------------------------------------//
  Date getNextWeekDay(Date d){
    int q=d.getdayOfMonth();
    int m=d.getmonth();
    int y=d.getyear();
    q=q+1;
    if(q>daysOfMonth[m-1]){
      q=1;
      m++;
      if(m>12){
        m=1;
        y++;
      }
    }
    if(m<3){
      m=m+12;
      y--;
    }

    int k,j;
    k=y%100;
    j=y/100;

    int h;
    h=(q+(13*(m+1))/5+k+(k/4)+(j/4)+(5*j))%7;
    d.putValue(m,y,q);
    if(h>=2){
      return d;
    }
    else{
      return getNextWeekDay(d);
    }
  }
  //-------------------------------------------------------------//
  void displayAllHolidays(){
    for(auto it:holidayList){
        cout<<it.getdayOfMonth()<<"/"<<it.getmonth()<<"/"<<it.getyear()<<endl;
      }
  }
  bool isHolidayAdded(Date d){
    int q=d.getdayOfMonth();
    int m=d.getmonth();
    int y=d.getyear();
    for(auto it:holidayList){
        if((it.getdayOfMonth()==q)&&(it.getmonth()==m)&&(it.getyear()==y)){
          return true;
        }
      }
    return false;
  }

  Date getNextHoliday(Date d){
    int q=d.getdayOfMonth();
    int m=d.getmonth();
    int y=d.getyear();
    q=q+1;
    if(q>daysOfMonth[m-1]){
      q=1;
      m++;
        if(m>12){
          m=1;
          y++;
        }
      }
    d.putValue(m,y,q);
    if(getDay(d)=="saturday" || getDay(d)=="sunday"){
      return d;
    }
    else if(isHolidayAdded(d)){
      return d;
    }
    else{
      return getNextHoliday(d);
    }
  }
  //-------------------------------------------------------------//
  void addHoliday(Date d){
    holidayList.push_back(d);
  }
  //-------------------------------------------------------------//
  Date iterateDate(Date d, int t){
    while(t--){
      int q=d.getdayOfMonth();
      int m=d.getmonth();
      int y=d.getyear();
      q=q+1;
      if(y%400==0 || y%4==0){
        daysOfMonth[1]=29;
      }
      if(q>daysOfMonth[m-1]){
      q=1;
      m++;
        if(m>12){
          m=1;
          y++;
        }
      }
      d.putValue(m,y,q);
    }
    return d;
  }
  //-------------------------------------------------------------//
  int getNumberOfHolidays(int month, int year){
    int q=1;
    int m=month;
    int y=year;
    int count=0;
    Date tempDate(m,y,q);
    if(y%400==0 || y%4==0){
      daysOfMonth[1]=29;
    }
    while(q<=daysOfMonth[month-1]){
      tempDate.putValue(m,y,q);
      string currDay;
      currDay=getDay(tempDate);
      if(currDay=="sunday" || currDay=="saturday"){
        count++;
        q=q+1;
        continue;
      }
      for(auto it:holidayList){
        if((it.getdayOfMonth()==q)&&(it.getmonth()==m)&&(it.getyear()==y)){
          count++;
        }
      }
      q=q+1;
    }
    return count;
  }
  //-------------------------------------------------------------//
  bool isPreceded(Date d1, Date d2){
    if(d1.getyear()<d2.getyear()){
      return true;
    }
    else if(d1.getmonth()<d1.getmonth()){
      return true;
    }
    else if(d1.getdayOfMonth()<d2.getdayOfMonth()){
      return true;
    }
    else{
      return false;
    }
    return false;
  }
  //-------------------------------------------------------------//
  void addNoteToDate(Date d, string note){
    notes.push_back(make_pair(d,note));
  }
  //-------------------------------------------------------------//
  bool removeNoteFromDate(Date d){
    for (auto it = notes.begin(); it != notes.end(); it++) {
        if (it->first.getmonth() == d.getmonth() && it->first.getdayOfMonth() == d.getdayOfMonth() && it->first.getyear() == d.getyear()) {
            notes.erase(it);
            return true;
        }
    }
    
    return false;
  }
  //-------------------------------------------------------------//
  vector<Notes> getNotesFromDateTillN(Date d, int n){
    vector<Notes> ans;
    int q1=d.getdayOfMonth();
    int m1=d.getmonth();
    int y1=d.getyear();
    Date temp;
    temp.putValue(m1,y1,q1);
    while(n>0){
      for (auto it = notes.begin(); it != notes.end(); it++) {
        if (( it->first.getmonth() == temp.getmonth() ) && ( it->first.getdayOfMonth() == temp.getdayOfMonth() ) && ( it->first.getyear() == temp.getyear())) {
          Date t(m1,y1,q1);
          Notes n1(t,it->second);
          cout<<"Date is added"<<m1<<" "<<y1<<" "<<q1;
          ans.push_back(n1);
          q1++;
          if(q1>daysOfMonth[m1-1]){
            q1=1;
            m1++;
              if(m1>12){
                m1=1;
                y1++;
              }
          }
          temp.putValue(m1,y1,q1);
        }
      }
      n--;
    }
    return ans;
  }
  //-------------------------------------------------------------//
  int getDistanceBetweenDates(Date d1, Date d2){
      int q1=d1.getdayOfMonth();
      int m1=d1.getmonth();
      int y1=d1.getyear();
      int q2=d2.getdayOfMonth();
      int m2=d2.getmonth();
      int y2=d2.getyear();
      int count=0;
      while((q1!=q2)||(m1!=m2)||(y1!=y2)){
        q1=q1+1;
        if(y1%400==0 || y1%4==0){
          daysOfMonth[1]=29;
        }
        if(q1>daysOfMonth[m1-1]){
          q1=1;
          m1++;
          if(m1>12){
            m1=1;
            y1++;
          }
        }
        count++;
      }
      return count;
  }
  //-------------------------------------------------------------//
  void printMonthOfYear(int month, int year){
    int q=1;
    int m=month;
    int y=year;
    Date tempDate(m,y,q);
    // s m t w t f s//
    string day = getDay(tempDate);
    int h=getDayCode(day);
    for(int i=1;i<h;i++){
      cout<<"   ";
    }
    if(y%400==0 || y%4==0){
      daysOfMonth[1]=29;
    }
    while(q<=daysOfMonth[m-1]){
      if(q>=0 && q<=9){
        cout<<"0"<<q<<" ";
      }
      else{
        cout<<q<<" ";
      }
      tempDate.putValue(m,y,q+1);
      day=getDay(tempDate);
      h=getDayCode(day);
      if(h==1){
        cout<<endl;
      }
      q++;
    }
  }
  //-------------------------------------------------------------//

};

vector<Date> getFreeDates(calender c1, calender c2, int month, int year) {
    vector<Date> freeDates;
    if((year%400==0) || (year%4==0)){
      daysOfMonth[1]=29;
    }
    for (int day = 1; day <= daysOfMonth[month - 1]; ++day) {
        Date tempDate(month, year, day);
        string dayOfWeek = c1.getDay(tempDate);
        if (dayOfWeek != "saturday" && dayOfWeek != "sunday" &&
            !c1.isHolidayAdded(tempDate) && !c2.isHolidayAdded(tempDate) &&
            c1.getNotesFromDateTillN(tempDate, 1).empty() &&
            c2.getNotesFromDateTillN(tempDate, 1).empty()) {
            freeDates.push_back(tempDate);
        }
    }
  return freeDates;
}


int main(){
  char ch1='a';
  char ch2='a';
  int function=1;
  calender c1;
  calender c2;
  char x='a';
  while(x!='#'){
    int id;
    cout<<"Enter the user id (i.e either 1 or 2)";
    cin>>id;
    if(id==1){
      while(ch1!='e'){
        cout<<"Enter function code"<<endl;
        cin>>function;
        // 1. Find the Day of the week for given date.
        // 2. Find the next week day.
        // 3. Find the next holiday.
        // 4. add holiday.
        // 5. iterate dates
        // 6. add note to a date.
        // 7. remove note from a date.
        // 8. Print all notes from date untill next n days.
        // 9. Get number of holidays.
        // 10. Given date is preceeded or not with given second date.
        // 11. Find the number of days between given two dates.
        // 12. Show the calendar of the month of an year.

        if(function==1){
          // successfully running 
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          string ans=c1.getDay(temp1);
          cout<<"The day of the week for given day is "<<ans<<endl;
        }
        else if(function==2){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2;
          temp2=c1.getNextWeekDay(temp1);
          cout<<"The next week day date after given ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==3){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2;
          temp2=c1.getNextHoliday(temp1);
          cout<<"Next holiday ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==4){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          c1.addHoliday(temp1);
          cout<<"Holiday Added Successfully"<<endl;
        }
        else if(function==5){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          int t;
          cout<<"Enter number of days to iterate";
          cin>>t;
          Date temp2;
          temp2=c1.iterateDate(temp1,t);
          cout<<"After iteration of "<<t<<" days ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==6){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          string note;
          //cin.getline(note);
          cin>>note;
          c1.addNoteToDate(temp1,note);
          cout<<"Notes added successfully !"<<endl;
        }
        else if(function==7){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          if(c1.removeNoteFromDate(temp1)){
            cout<<"Notes successfully removed"<<endl;
          }
          else{
            cout<<"No notes present"<<endl;
          }
        }
        else if(function==8){
          vector<Notes> notesList;
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          int n;
          cout<<"Enter number of days ";
          cin>>n;
          notesList=c1.getNotesFromDateTillN(temp1,n);
          for (auto it = notesList.begin(); it != notesList.end(); it++){
            temp1 = it->getDateofNotes();
            cout<< "Date is ";
            temp1.displayDate();
            cout<<endl;
            cout<< "Notes for this date is " << it->getNotes() <<endl;
          }
        }
        else if(function==9){
          //sucessfully running
          int month,year;
          cin>>month>>year;
          int ans;
          ans=c1.getNumberOfHolidays(month,year);
          cout<<"Number of holidays in the given month and year is ";
          cout<<ans<<endl;
        }
        else if(function==10){
          // successfully running
          int d1,m1,y1,d2,m2,y2;
          cout<<"Enter date 1 in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          cout<<"Enter date 2 in dd/mm/yyyy ";cin>>d2>>m2>>y2;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2(m2,y2,d2);
          cout<<" Date 1 is preceded by Date 2 is ";
          if(c1.isPreceded(temp1,temp2)){
            cout<<"true"<<endl;
          }
          else{
            cout<<"false"<<endl;
          }

        }
        else if(function==11){
          // sucessfully running
          int d1,m1,y1,d2,m2,y2;
          cout<<"Enter date 1 in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          cout<<"Enter date 2 in dd/mm/yyyy ";cin>>d2>>m2>>y2;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2(m2,y2,d2);
          cout<<"The number of days between given two dates are ";
          int ans=c1.getDistanceBetweenDates(temp1,temp2);
          cout<<ans<<endl;
        }
        else if(function==12){
          // succesfully running
          int month;
          int year;
          cout<<"enter month and year";
          cin>>month>>year;
          cout<<"Following shows the calender for "<<month<<"/"<<year<<endl;
          cout<<"su mo tu we th fr sa"<<endl;
          c1.printMonthOfYear(month,year);
          cout<<endl;
        }
        else if (function == 13) {
            int month, year;
            cin >> month >> year;

            vector<Date> freeDates = getFreeDates(c1, c2, month, year);

            cout << "Free dates for scheduling a meeting:" << endl;
            for (auto date : freeDates) {
                date.displayDate();
            }
        }
        cout<<"Press e to exit or any other character for moving further";
        cin>>ch1;
        if(ch1!='e'){
          ch1='a';
        }
      }
    }
    else if(id==2){
      while(ch2!='e'){
        cout<<"Enter function code"<<endl;
        cin>>function;
        // 1. Find the Day of the week for given date.
        // 2. Find the next week day.
        // 3. Find the next holiday.
        // 4. add holiday.
        // 5. iterate dates
        // 6. add note to a date.
        // 7. remove note from a date.
        // 8. Print all notes from date untill next n days.
        // 9. Get number of holidays.
        // 10. Given date is preceeded or not with given second date.
        // 11. Find the number of days between given two dates.
        // 12. Show the calendar of the month of an year.

        if(function==1){
          // successfully running 
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          string ans=c2.getDay(temp1);
          cout<<"The day of the week for given day is "<<ans<<endl;
        }
        else if(function==2){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2;
          temp2=c2.getNextWeekDay(temp1);
          cout<<"The next week day date after given ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==3){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2;
          temp2=c2.getNextHoliday(temp1);
          cout<<"Next holiday ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==4){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          c2.addHoliday(temp1);
          cout<<"Holiday Added Successfully"<<endl;
        }
        else if(function==5){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          int t;
          cout<<"Enter number of days to iterate";
          cin>>t;
          Date temp2;
          temp2=c2.iterateDate(temp1,t);
          cout<<"After iteration of "<<t<<" days ";
          temp2.displayDate();
          cout<<endl;
        }
        else if(function==6){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          string note;
          //cin.getline(note);
          cin>>note;
          c2.addNoteToDate(temp1,note);
          cout<<"Notes added successfully !"<<endl;
        }
        else if(function==7){
          // sucessfully running
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          if(c2.removeNoteFromDate(temp1)){
            cout<<"Notes successfully removed"<<endl;
          }
          else{
            cout<<"No notes present"<<endl;
          }
        }
        else if(function==8){
          vector<Notes> notesList;
          int d1,m1,y1;
          cout<<"Enter date in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          Date temp1(m1,y1,d1);
          int n;
          cout<<"Enter number of days ";
          cin>>n;
          notesList=c2.getNotesFromDateTillN(temp1,n);
          for (auto it = notesList.begin(); it != notesList.end(); it++){
            temp1 = it->getDateofNotes();
            cout<< "Date is ";
            temp1.displayDate();
            cout<<endl;
            cout<< "Notes for this date is " << it->getNotes() <<endl;
          }
        }
        else if(function==9){
          //sucessfully running
          int month,year;
          cin>>month>>year;
          int ans;
          ans=c2.getNumberOfHolidays(month,year);
          cout<<"Number of holidays in the given month and year is ";
          cout<<ans<<endl;
        }
        else if(function==10){
          // successfully running
          int d1,m1,y1,d2,m2,y2;
          cout<<"Enter date 1 in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          cout<<"Enter date 2 in dd/mm/yyyy ";cin>>d2>>m2>>y2;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2(m2,y2,d2);
          cout<<" Date 1 is preceded by Date 2 is ";
          if(c2.isPreceded(temp1,temp2)){
            cout<<"true"<<endl;
          }
          else{
            cout<<"false"<<endl;
          }

        }
        else if(function==11){
          // sucessfully running
          int d1,m1,y1,d2,m2,y2;
          cout<<"Enter date 1 in dd/mm/yyyy ";cin>>d1>>m1>>y1;cout<<endl;
          cout<<"Enter date 2 in dd/mm/yyyy ";cin>>d2>>m2>>y2;cout<<endl;
          Date temp1(m1,y1,d1);
          Date temp2(m2,y2,d2);
          cout<<"The number of days between given two dates are ";
          int ans=c2.getDistanceBetweenDates(temp1,temp2);
          cout<<ans<<endl;
        }
        else if(function==12){
          // succesfully running
          int month;
          int year;
          cout<<"enter month and year";
          cin>>month>>year;
          cout<<"Following shows the calender for "<<month<<"/"<<year<<endl;
          cout<<"su mo tu we th fr sa"<<endl;
          c2.printMonthOfYear(month,year);
          cout<<endl;
        }
        else if (function == 13) {
            int month, year;
            cin >> month >> year;

            vector<Date> freeDates = getFreeDates(c1, c2, month, year);

            cout << "Free dates for scheduling a meeting:" << endl;
            for (auto date : freeDates) {
                date.displayDate();
            }
        }
        cout<<"Press e to exit or any other character for moving further";
        cin>>ch2;
        if(ch2!='e'){
          ch2='a';
        }
      }
    }
    else{
      cout<<"INVALID USER ID"<<endl;
    }
    cout<<"Enter # to exit or any other char for moving further"<<endl;
    cin>>x;
    if(x!='#'){
      x='a';
    }
  }
  return 0;
}

