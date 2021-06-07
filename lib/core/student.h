#include "header.h"
#include "customInput.h"

#pragma once

#define FILENAME "resources/student.bin"

class Student{
  public:
    char name[50];
    int rollNo;
    char password[100]; 
    double marks;
};
class StudentManagement{
  private:
    Student student;
  public:
    // Take input from user
    void input();

    // Write student data to file
    void writeFile();

    // Read student data from file
    // print in the form of table
    void readFile();

    // print student data 
    void output(Student);

    // Set Marks
    void setMarks(double);
};

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
  cout << st.name << "\t\t";
  cout << st.rollNo << "\t\t";
  cout << st.marks << "\t\t";
  cout << st.password << endl;
}
void StudentManagement::setMarks(double marks){
  student.marks = marks;
}

#undef FILENAME 