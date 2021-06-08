#include "header.h"

class Admin{
  public:
    void banner();
    void mainMenu();
    void studentMenu();
    void menuHandler();
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

  cout << "1. Update Password" << endl;
  cout << "2. Rusticate Student" << endl;
  cout << "3. New Registration" << endl;
  cout << "4. Back" << endl;

  do{
    choice = getch();
  }while(choice!='1' && choice!='2' && choice!='3' && choice!='4');
}
void Admin::menuHandler(){
  mainMenu();
  switch(choice){
    case '1':
      studentMenu();
      break;
  }
}
