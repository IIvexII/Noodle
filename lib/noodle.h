#include "core/teacher.h"
#include "core/student.h"
#include "core/admin.h"

class Noodle{
  public:
    void banner();
    void loginMenu();
    void menuHandler();
    void adminPanel();
  private:
    TeacherManagement teacher;
    StudentManagement student;
    Admin admin;
    char choice;

};
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

void Noodle::menuHandler(){
  loginMenu();
  switch(choice){
    case '3':
      if(admin.login()){
        adminPanel();
      }else{
        getch();
        menuHandler();
      }
      break;
  }
}

void Noodle::adminPanel(){
  admin.menuHandler();
}
