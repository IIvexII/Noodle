#include "header.h"
#include "customInput.h"

#pragma once

class Admin{
  public:
    void banner();
    void mainMenu();
    void studentMenu();
    void teacherMenu();
    void menuHandler();
    bool login();
  private:
    TeacherManagement teacher;
    StudentManagement student;
    char choice;
};
void Admin::banner(){
  system("cls");
  cout << "***********************************" << endl;
  cout << "           Admin Panel" << endl;
  cout << "***********************************" << endl;
}
void Admin::mainMenu(){
  banner();
  cout << "1. Student" << endl;
  cout << "2. Teacher" << endl;
  cout << "0. Exit" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='0');
}
void Admin::studentMenu(){
  banner();

  cout << "1. List All Students" << endl;
  cout << "2. Update Password" << endl;
  cout << "3. Rusticate Student" << endl;
  cout << "4. New Registration" << endl;
  cout << "0. Back" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='0');

  switch(choice){
    case '1':
      student.listAll();
      getch();
      studentMenu();
      break;
    case '2':
      int rn;
      cout << "Enter Roll Number: "; cin >> rn;
      student.updatePasswd(rn);
      getch();
      studentMenu();
      break;
    case '3':
      student.rusticate();
      getch();
      studentMenu();
      break;
    case '4':
      student.newRegistration();
      getch();
      studentMenu();
      break;
    case '0':
      menuHandler();
      break;
  }
}
void Admin::teacherMenu(){
  banner();

  cout << "1. List All Teacher" << endl;
  cout << "2. Update Password" << endl;
  cout << "3. Expel Teacher" << endl;
  cout << "4. New Registration" << endl;
  cout << "0. Back" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='0');

  switch(choice){
    case '1':
      teacher.listAll();
      getch();
      teacherMenu();
      break;
    case '2':
      int id;
      cout << "Enter Employee ID: "; cin >> id;
      teacher.updatePasswd(id);
      getch();
      teacherMenu();
      break;
    case '3':
      teacher.fire();
      getch();
      teacherMenu();
      break;
    case '4':
      teacher.newRegistration();
      getch();
      teacherMenu();
      break;
    case '0':
      menuHandler();
      break;
  }
}
void Admin::menuHandler(){
  mainMenu();
  switch(choice){
    case '1':
      studentMenu();
      break;
    case '2':
      teacherMenu();
      break;
  }
}
bool Admin::login(){
  char username[20], password[100];

  cout << "Enter Username: "; cin.getline(username, 20);
  cout << "Enter Password: "; passwdInput(password);

  if(!strcmp(username, "admin") && !strcmp(password, "ctfIsLove")){
    return 1;
  }
  else{
    cout << "Username or Password is wrong." << endl;
    return 0;
  }
}