#include "core/question.h"
#include "core/teacher.h"
#include "core/student.h"
#include "core/admin.h"

class Noodle{
  public:
    void banner();
    void loginMenu();
    void menuHandler();
    void adminPanel();
    void studentPanel();
    void teacherPanel();
  private:
    TeacherManagement teacher;
    StudentManagement student;
    Admin admin;
    char choice;

};

void Noodle::menuHandler(){
  loginMenu();
  switch(choice){
    case '1':
      if(student.login()){
        studentPanel();
        menuHandler();
      }else{
        getch();
        menuHandler();
      }
      break;
    case '2':
      if(teacher.login()){
        teacherPanel();
        menuHandler();
      }else{
        getch();
        menuHandler();
      }
      break;
    case '3':
      if(admin.login()){
        adminPanel();
        menuHandler();
      }else{
        getch();
        menuHandler();
      }
      break;
  }
}

void Noodle::banner(){
  system("cls");
  cout << "******************************************" << endl;
  cout << "                Noodle Login" << endl;
  cout << "******************************************" << endl;
}

void Noodle::loginMenu(){
  banner();
  cout << "1. Login as Studnet" << endl;
  cout << "2. Login as Teacher" << endl;
  cout << "3. Login as Admin" << endl;
  cout << "0. Exit" << endl << endl;

  do{
    choice = getch();
  } while(choice!='1' && choice!='2' && choice!='3' && choice!='0');
}

void Noodle::adminPanel(){
  admin.menuHandler();
}

void Noodle::studentPanel(){
  student.menuHandler();
}
void Noodle::teacherPanel(){
  teacher.menuHandler();
}