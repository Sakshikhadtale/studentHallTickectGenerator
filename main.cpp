#include<iostream>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<ctime>
using namespace std;

class studentBranch{ //parent class
    public:
    int branch_type;
    char branch[50];
    studentBranch(){ //constrctor
    strcpy(branch,"Computer Engineering");  //Default
    }
    void SetstudentBranch(){ 
        while(1){ //if invalid input: again take input
        cout<<"\nSelect Student type: ";
        cout<<"\n1. Computer Science & Technology 2. Computer Engineering 3. Data Science 4. Information Technology : ";
        cin>>branch_type;
        if(branch_type==1){ // set pricing for each Student type
        strcpy(branch,"Computer Science & Technology");    break;
        }
        else if(branch_type==2){
        strcpy(branch,"Computer Engineering");
        break;
        }
        else if(branch_type==3){
        strcpy(branch,"Data Science");
        break;
        }
        else if(branch_type==4){
        strcpy(branch,"Information Technology");
        break;
        }
        else{
        cout<<"\nInvalid choice!!";
        }
        }
    }
    void ShowstudentBranch(){
    cout<<"Branch : "<<branch<<"\n";
    }
};

class Student:public studentBranch{ //inherited class
private:
int rollNo;
char student_name[60];
int year;
char semester[50];
char div[50];
int seatNo;
string roomNo;
char created_datetime[50];
char updated_dateime[50];
public:
Student(){ //constrctor
this->rollNo=0;
this->year=1;
strcpy(this->student_name,"not set");
strcpy(this->semester,"default");
strcpy(this->div,"default");
// strcpy(this->seatNo,"default");
this->roomNo="000";
this->seatNo=0;

time_t tt;
time(&tt);
strcpy(this->created_datetime,asctime(localtime(&tt)));
strcpy(this->updated_dateime,asctime(localtime(&tt)));
}
void sethallticket(){ //enter a new Student2
SetstudentBranch();
cout<<"\nEnter  Student Roll number: ";
cin>>rollNo;
cin.ignore();
cout<<"\nEnter Student Full Name : ";
cin.getline(student_name,60);
cout<<"\nEnter Student Year : ";
cin>>year;
cout<<"\nEnter Student semester: ";
cin>>semester;
cout<<"\nEnter Student Division: ";
cin>>div;
roomNo = to_string(year)+"0"+to_string(branch_type);    //BRANCH TYPE FOR DIFFERENT ROOM NO.
string seat_No;
seat_No = roomNo + to_string(rollNo);
this->seatNo=stoi(seat_No);
cout<<"\n Student HallTickect Generated Successfully \n\n ----------------------------------------------";
cout<<"\n Usha Mittal Institute of Technology \n ----------------------------------------------";
cout<<"\n HallTickect"<<"\n"<<" SeatNo.:\t"<<seatNo<<"\tRoom No.\t:\t"<<roomNo;
cout<<"\n Name\t:\t"<<student_name;
cout<<"\n Div\t:\t"<<div;
cout<<"\n Roll No. \t:\t"<<rollNo;
cout<<"\n Year\t:\t"<<year;
cout<<"\n Branch\t:\t"<<branch;
cout<<"\n Sem\t:\t"<<semester<<"\n ----------------------------------------------";

}
void showstudent(){ //print entered Student
cout<<"Roll no.\tSeatNo.\t\tStudent\t\t\t\tYear\tSemester\n--------------------------------------------------------------------------------------------------------\n";
cout<<rollNo<<"\t\t"<<seatNo<<"\t\t"<<student_name<<"\t\t\t"<<year<<"\t"<<semester<<"\t\t"<<endl;
ShowstudentBranch(); //inherited function

cout<<"Created date time-";
cout<<created_datetime;
cout<<"Updated date time-";
cout<<updated_dateime<<"\n";
}
void addHallticket(); //to add Student into file
void GetStudentList(); //to get all students in file
void searchHallticket(int sNo); //to search for a Student
void deleteHallticket(int sNo);
void updateHallticket(int sNo);
};
void Student::addHallticket(){          //storing
//this pointer contains address of pointer of current Student instance
ofstream fout;
fout.open("student.txt",ios_base::app| ios_base::binary); //opening file in append and binary mode
fout.write((char*)this,sizeof(*this)); //convert address in char type - Type casting
fout.close();
}
void Student::GetStudentList(){ //info of all students 
ifstream fin;
int records=0;
fin.open("student.txt",ios_base::in| ios_base::binary);
if(!fin){
cout<<" \n file not found!!";
}
else{
fin.read((char*)this,sizeof(*this));
while(!fin.eof()){ //read file until gets to its end
this->showstudent();
records++;
fin.read((char*)this,sizeof(*this));
}
fin.close();
if(records==0){
cout<<"\nfile has no record!! ";
}
}
}
void Student::searchHallticket(int sNo){
/*
1) search for given Student no. by opening file in read mode
2) when Student no. matches, print the record by showstudent() function
3) we use records var as a flag to know whether the record was found or not
*/
ifstream fin;
int records=0;
fin.open("student.txt",ios_base::in| ios_base::binary);
if(!fin){
cout<<" \n file not found!!";
}
else{
fin.read((char*)this,sizeof(*this));
while(!fin.eof()){ //read file until gets to its end eof-end of
if(this->seatNo==sNo){
this->showstudent();
records=1;
break;
}
fin.read((char*)this,sizeof(*this));
}
fin.close();
if(records==0){
cout<<"\nrecord not ound!! ";
}
}
}
void Student::deleteHallticket(int sNo){
/* here the logic we applied is1) open "student.txt" file in read mode
2) create a temporary file named as "tempstudent.txt" in write mode
3) copy all the data from 1st file except for which the record has been matched
4) remove 1st file and rename temp file as the 1st file*/
ifstream fin;
ofstream fout;
int flag=0;
fin.open("student.txt",ios_base::in| ios_base::binary);
if(!fin){
cout<<" \n file not found!!";
}
else{
fin.read((char*)this,sizeof(*this));
fout.open("tempstudent.txt",ios_base::out| ios_base::binary);
while(!fin.eof()){ //read file until gets to its end
if(this->seatNo==sNo){
flag=1;
}
else{
fout.write((char*)this,sizeof(*this));
}
fin.read((char*)this,sizeof(*this));
}
fin.close();
fout.close();
if(flag==0){
cout<<"\nrecord not found!! cannot delete \n";
remove("tempstudent.txt");
}
else{
cout<<"record deleted!!\n";
remove("student.txt");
rename("tempstudent.txt","student.txt");
}
}
}
void Student::updateHallticket(int sNo){
fstream foutin;
int flag=0;
foutin.open("student.txt",ios_base::in|ios_base::out|ios_base::ate| ios_base::binary);
foutin.seekg(0); //get pointer at start.. by default it is at last in append mode
if(!foutin){
cout<<" \n File not found!!";
}
else{
foutin.read((char*)this,sizeof(*this));
while(!foutin.eof()){//read file until gets to its end
if(this->seatNo==sNo){
cout<<"Update the data:- \n";

SetstudentBranch();

cout<<"\nEnter  Student Roll number: ";
cin>>rollNo;
cin.ignore();
cout<<"\nEnter Student Full Name : ";
cin.getline(student_name,60);
cout<<"\nEnter Student Year : ";
cin>>year;
cout<<"\nEnter Student semester: ";
cin>>semester;
cout<<"\nEnter Student Division: ";
cin>>div;
roomNo = to_string(year)+"0"+to_string(branch_type);    //BRANCH TYPE FOR DIFFERENT ROOM NO.
string seat_No;
seat_No = roomNo + to_string(rollNo);
this->seatNo=stoi(seat_No);

time_t tt;
time (&tt);
strcpy(updated_dateime,asctime(localtime(&tt)));
foutin.seekp(foutin.tellp()-std::streamoff(sizeof(*this))); //changes get pointer's location to previous location
foutin.write((char*)this,sizeof(*this));
cout<<"\nRecord updated!!";
flag=1;
break;
}
foutin.read((char*)this,sizeof(*this));
}
foutin.close();
if(flag==0){
cout<<"\nRecord not found!! ";
}
}
}
int menu(){
int ch;
printf("\n 1. Generate a Student Hallticket ");
printf("\n 2. Search Student Hallticket ");
printf("\n 3. Delete Student Hallticket ");
printf("\n 4. Update Student Hallticket ");
printf("\n 5. List all Student Halltickets ");
printf("\n 6. Exit ");
printf("\n Enter your choice: ");
scanf("%d",&ch);
return(ch);
}
int main(){
Student s;
int breakloop=0,sNO;
while(1){
switch(menu()){
case 1:
s.sethallticket();
s.addHallticket();
break;
case 2:
cout<<"\nEnter Hallticket number to search:";
cin>>sNO;
s.searchHallticket(sNO);
break;
case 3:
cout<<"\nEnter Hallticket number to delete:";
cin>>sNO;
s.deleteHallticket(sNO);
break;
case 4:
cout<<"\nEnter Hallticket number to update:";
cin>>sNO;
s.updateHallticket(sNO);
break;
case 5:
s.GetStudentList();
break;
case 6:
breakloop=1;
break;
default:
cout<<"\nInvalid input";
}
if (breakloop==1){
break;
}
}
return 0;
}