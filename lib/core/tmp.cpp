#include "header.h"
#include "customInput.h"
// #pragma once

#define FILENAME "../../resources/teacher.dat"

struct Teacher{
    char name[50];
    int empID;
    char password[100];
};

class TeacherManagement{
  private:
    Teacher teacher, tmpTeacher, teacherSession;
  public:
    void input(){
      cout << "Name: ";cin.getline(teacher.name, 50);
      cout << "ID: ";cin >> teacher.empID;
      cout << "Password: ";passwdInput(teacher.password);
    }
    void output(){
      cout << "Name: " << tmpTeacher.name << endl;
      cout << "ID: " << tmpTeacher.empID << endl;
      cout << "Password: " << tmpTeacher.password << endl;
    }
    void writeFile(){
      ofstream outFile(FILENAME, ios::app);
      if(outFile.is_open()){
        outFile.write((char*)&teacher, sizeof(teacher));
        outFile.close();
      }
    }
    void list(){
      ifstream inFile(FILENAME);
      if(inFile.is_open()){
        while(inFile.read((char*)&tmpTeacher, sizeof(tmpTeacher)))
          output();
        inFile.close();
      }
    }

};
int main(){
  TeacherManagement t;
  t.input();
  t.writeFile();
  t.list();

  return 0;
}