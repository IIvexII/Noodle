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

    // set marks
    void setMarks(double);
  public:
    void newRegistration();
    void listAll();
    void rusticate();
    void updateMarks();
};
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
  cout << " _________________________________________________________________" << endl;
  cout << "|" << setw(30) << left << "Name"
              << setw(10) << "Roll Number"  
              << setw(20) << right << "Marks" 
              << setw(5) << right << "|" << endl;
  cout << "|_________________________________________________________________|" << endl;
  readFile();
  cout << "|_________________________________________________________________|" << endl;

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
    cout << "Deleted sucessfuly!";
  else
    cout <<"Unable to delete.";
  cout << endl;
}
void StudentManagement::updateMarks(){
  fstream file(FILENAME, ios::binary | ios::in | ios::out);
  int pos, rn;

  cout << "Enter Roll Number: "; cin >> rn;
  while(file.read((char*)&student, sizeof(student))){
    pos = file.tellg();
    if(student.rollNo == rn){
      cout << "Enter Marks: "; cin >> student.marks;     
      break; 
    }
  }
  file.seekp(pos-sizeof(student));
  file.write((char*)&student, sizeof(Student));

  file.close();
}

// Private
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