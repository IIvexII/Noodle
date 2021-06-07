#include "header.h"
#include "customInput.h"

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
    Student student;

    // Take input from user
    void input();

    // Write student data to file
    void writeFile();

    // Read student data from file
    // print in the form of table
    void readFile();

    // print student data 
    void output(Student);
  public:
    void newRegistration();
    // Set Marks
    void setMarks(double);
};

/***********************
    newRegistration()
************************/
void StudentManagement::newRegistration(){
  input();
  writeFile();
}
void StudentManagement::input(){
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
    inFile.close();
  }
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

#undef FILENAME 