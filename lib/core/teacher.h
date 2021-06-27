#include "header.h"
#include "customInput.h"
#include "question.h"
#include "student.h"

#pragma once

#define FILENAME "resources/teacher.bin"

class Teacher{
  public:
    char name[50];
    int empID;
    char password[100];
};
class TeacherManagement{
  private:
    Teacher teacher, tmpTeacher;
    QuestionHandler question;
    StudentManagement student;
    char choice;

  public:
    void banner();
    void newRegistration();
    bool login();
    void listAll();
    void fire();
    void updatePasswd(int);
    void mainMenu();
    void menuHandler();
    
    // Take input from user
    void input();

    // Write student data to file
    void writeFile();

    // Read student data from file
    // print in the form of table
    void readFile();

    // print student data 
    void output(Teacher);
};

void TeacherManagement::banner(){
  system("cls");
  cout << "*****************************" << endl;
  cout << "*      Teacher Portal       *" << endl;
  cout << "*****************************" << endl;
}
void TeacherManagement::mainMenu(){
  banner();
  cout << "1. Add Question" << endl;
  cout << "2. Update Question" << endl;
  cout << "3. Change Password" << endl;
  cout << "4. List Students" << endl;
  cout << "5. Update Marks" << endl;
  cout << "0. Logout" << endl;

  do{
    choice = getch();
  }while(choice != '0' && choice !='1' && choice != '2' && choice !='3' &&choice != '4' && choice !='5');
}
void TeacherManagement::menuHandler(){
  mainMenu();
  switch(choice){
    case '1':
      question.addQuestion();
      getch();
      menuHandler();
      break;
    case '2':
      question.updateQuestion();
      getch();
      menuHandler();
      break;
    case '3':
      updatePasswd(tmpTeacher.empID);
      getch();
      menuHandler();
      break;
    case '4':
      student.listAll();
      getch();
      menuHandler();
      break;
    case '5':
      double marks;
      int rn;
      cout << "Enter Roll Number: "; cin >> rn;
      cout << "Enter Marks: "; cin >> marks;
      student.updateMarks(rn,marks);
      getch();
      menuHandler();
      break;
  }
}
/***********************
    newRegistration()
************************/
void TeacherManagement::newRegistration(){
  input();
  writeFile();
}
/***********************
        listAll()
************************/
void TeacherManagement::listAll(){
  cout << " __________________________________________" << endl;
  cout << "|" << setw(25) << left << "Employee ID"
              << setw(15) << "Name"  
              << setw(3) << right << "|" << endl;
  cout << "|__________________________________________|" << endl;
  readFile();
  cout << "|____________|_____________________________|" << endl;

}
/**********************
        fire()
***********************/
void TeacherManagement::fire(){
  int id;;
  bool isDeleted=0;
  char tempFilename[] = "resources/tmp.bin";
  cout << "Enter Employee ID: "; cin >> id;

  ifstream inFile(FILENAME);
  ofstream outFile(tempFilename);

  while(inFile.read((char*)&teacher, sizeof(teacher))){
    if(teacher.empID != id){
      outFile.write((char*)&teacher, sizeof(teacher));
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
void TeacherManagement::updatePasswd(int id){
  fstream file(FILENAME, ios::binary | ios::in | ios::out);
  int pos;
  bool isSucessful=0;
  
  while(file.read((char*)&teacher, sizeof(teacher))){
    pos = file.tellg();
    if(teacher.empID == id){
      cout << "Old Password: " << teacher.password << endl;
      cout << "New Password: ";passwdInput(teacher.password);
           
      isSucessful=1;
      break; 
    }
  }
  file.seekp(pos-sizeof(teacher));
  file.write((char*)&teacher, sizeof(Teacher));

  if(isSucessful)
    cout << "Password Updated!" << endl;
  else
    cout << "Failed to update password." << endl;

  file.close();
}
void TeacherManagement::output(Teacher tch){
  cout << "|" << setw(12) << left << tch.empID << setw(9) << left << "|";
  cout << left << setw(20) << tch.name;
  cout << right << setw(2) << "|" << endl;
}
bool TeacherManagement::login(){
  int id;
  char password[100];

  cin.clear();
  cin.ignore(124,'\n');

  banner();

  cout << "Enter Roll Number: "; cin >> id;
  cout << "Password: "; passwdInput(password);

  ifstream inFile(FILENAME);

  while(inFile.read((char*)&tmpTeacher,sizeof(Teacher))){
    if(id == tmpTeacher.empID){
      if(!strcmp(password, tmpTeacher.password)){
        cout << "Logged in as " << tmpTeacher.name << "...." << endl;
        getch();
        return 1;
      }else{
        cout << "Username or Password is wrong." << endl;
      }
    }
  }

  inFile.close();
  return 0;
}
void TeacherManagement::input(){
  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');
  
  cout << "Name: "; cin.getline(teacher.name, 50);
  cout << "Roll Number: "; cin >> teacher.empID;

  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');

  cout << "Password: "; passwdInput(teacher.password);
}
void TeacherManagement::writeFile(){
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    outFile.write((char*)&teacher, sizeof(teacher));
    outFile.close();
  }
}
void TeacherManagement::readFile(){
  Teacher st;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&st, sizeof(Teacher))){
      output(st);
    }
  }
  inFile.close();
  
}
#undef FILENAME 