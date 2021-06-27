#include "header.h"
#include "customInput.h"
#include "question.h"

#pragma once

#define FILENAME "resources/student.bin"

class Student{
  public:
    char name[50];
    int rollNo;
    char password[100]; 
    double marks=-1;
};
class StudentManagement{
  private:
    Student student, tmpStudent;
    QuestionHandler question;
    char choice;
    int marks;

    // Take input from user
    void input();

    // Write student data to file
    void writeFile();

    // Read student data from file
    // print in the form of table
    void readFile();

    // print student data 
    void output(Student);

    // set marks
    void setMarks(double);
  public:
    void banner();
    void header();
    void footer();
    void newRegistration();
    void listAll();
    void rusticate();
    void updateMarks(int, int);
    void updatePasswd(int);
    bool login();
    void mainMenu();
    void menuHandler();
};
void StudentManagement::banner(){
  system("cls");
  cout << "***********************************" << endl;
  cout << "          Student Panel" << endl;
  cout << "***********************************" << endl;
}
// Public
/***********************
    newRegistration()
************************/
void StudentManagement::newRegistration(){
  input();
  writeFile();
}
/***********************
        listAll()
************************/
void StudentManagement::listAll(){
  header();
  readFile();
  footer();
}
/**********************
      rusticate()
***********************/
void StudentManagement::rusticate(){
  int rn;
  bool isDeleted=0;
  char tempFilename[] = "resources/tmp.bin";
  cout << "Enter Roll Number: "; cin >> rn;

  ifstream inFile(FILENAME);
  ofstream outFile(tempFilename);

  while(inFile.read((char*)&student, sizeof(student))){
    if(student.rollNo != rn){
      outFile.write((char*)&student, sizeof(student));
    }else{
      isDeleted = 1;
    }
  }

  inFile.close();
  outFile.close();

  // delete the old file
  remove(FILENAME);

  // rename new file to the older file
  rename(tempFilename, FILENAME);

  if(isDeleted)
    cout << "Rusticated sucessfuly!";
  else
    cout <<"Unable to rusticate.";
  cout << endl;
}
void StudentManagement::updateMarks(int rn, int mk){
  fstream file(FILENAME, ios::binary | ios::in | ios::out);
  int pos;
  bool isSucessful=0;
  
  while(file.read((char*)&student, sizeof(student))){
    pos = file.tellg();
    if(student.rollNo == rn){
      student.marks = mk;     
      isSucessful=1;
      break; 
    }
  }
  file.seekp(pos-sizeof(student));
  file.write((char*)&student, sizeof(Student));

  if(isSucessful)
    cout << "Marks updated!" << endl;
  else
    cout << "Failed to update marks." << endl;

  file.close();
}
void StudentManagement::updatePasswd(int rn){
  fstream file(FILENAME, ios::binary | ios::in | ios::out);
  int pos;
  bool isSucessful=0;
  
  while(file.read((char*)&student, sizeof(student))){
    pos = file.tellg();
    if(student.rollNo == rn){
      cout << "Old Password: " << student.password << endl;
      cout << "New Password: ";passwdInput(student.password);
           
      isSucessful=1;
      break; 
    }
  }
  file.seekp(pos-sizeof(student));
  file.write((char*)&student, sizeof(student));

  if(isSucessful)
    cout << "Password Updated!" << endl;
  else
    cout << "Failed to update password." << endl;

  file.close();
}
bool StudentManagement::login(){
  int rn;
  char password[100];

  cin.clear();
  cin.ignore(124,'\n');

  banner();

  cout << "Enter Roll Number: "; cin >> rn;
  cout << "Password: "; passwdInput(password);

  ifstream inFile(FILENAME);

  while(inFile.read((char*)&tmpStudent,sizeof(Student))){
    if(rn == tmpStudent.rollNo){
      if(!strcmp(password, tmpStudent.password)){
        cout << "Logged in as " << tmpStudent.name << "...." << endl;
        return 1;
      }else{
        cout << "Username or Password is wrong." << endl;
      }
    }
  }

  inFile.close();
  return 0;
}
void StudentManagement::mainMenu(){
  banner();
  cout << "1. Solve Quiz" << endl;
  cout << "2. Change Password" << endl;
  cout << "3. Display Your Information" << endl;
  cout << "4. List all the Quiz Results" << endl;
  cout << "0. Logout" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='0');
}
void StudentManagement::menuHandler(){
  mainMenu();
  switch(choice){
    case '1':
      banner();
      marks = question.quiz()*10;
      updateMarks(tmpStudent.rollNo, marks);
      tmpStudent.marks = marks;
      getch();
      menuHandler();
      break;
    case '2':
      banner();
      updatePasswd(tmpStudent.rollNo);
      getch();
      menuHandler();
      break;
    case '3':
      banner();
      header();
      output(tmpStudent);
      footer();
      getch();
      menuHandler();
      break;
    case '4':
      banner();
      listAll();
      getch();
      menuHandler();
      break;
  }
}
// Private
void StudentManagement::input(){
  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');
  
  cout << "Name: "; cin.getline(student.name, 50);
  cout << "Roll Number: "; cin >> student.rollNo;

  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');

  cout << "Password: "; passwdInput(student.password);
}
void StudentManagement::writeFile(){
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    outFile.write((char*)&student, sizeof(student));
    outFile.close();
  }
}
void StudentManagement::readFile(){
  Student st;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&st, sizeof(st))){
      output(st);
    }
  }
  inFile.close();
  
}
void StudentManagement::output(Student st){
  cout << "|" << setw(30) << left << st.name << right << "|";
  cout << setw(5) << right << st.rollNo << setw(5) << "|";
  cout << setw(20) << right;
  if(st.marks==-1)
    cout << "NULL";
  else
    cout << st.marks;
  
  cout << setw(5) << "|" << endl;
}
void StudentManagement::setMarks(double marks){
  student.marks = marks;
}
void StudentManagement::header(){
  cout << " _________________________________________________________________" << endl;
  cout << "|" << setw(30) << left << "Name"
              << setw(10) << "Roll Number"  
              << setw(20) << right << "Marks" 
              << setw(5) << right << "|" << endl;
  cout << "|_________________________________________________________________|" << endl;
}
void StudentManagement::footer(){
  cout << "|_________________________________________________________________|" << endl;
}

#undef FILENAME 