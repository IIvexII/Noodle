#include <conio.h>
#include "customInput.h"

#define FILENAME "resources/teacher.bin"

struct Teacher{
  char name[50];
  int empID;
  char password[100];
};
class TeacherManagement{
  private:
    Teacher teacher;
  public:
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

void TeacherManagement::input(){
  cout << "Name: "; cin.getline(teacher.name, 50);
  cout << "Emplyee ID: "; cin >> teacher.empID;

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
  Teacher tch;
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&tch, sizeof(tch))){
      output(tch);
    }
    inFile.close();
  }
}
void TeacherManagement::output(Teacher tch){
  cout << tch.name << "\t\t";
  cout << tch.empID << "\t\t";
  cout << tch.password << endl;
}