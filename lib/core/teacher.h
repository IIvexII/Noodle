#include "header.h"
#include "customInput.h"

#pragma once

#define FILENAME "resources/teacher.bin"

struct Teacher{
  char name[50];
  int empID;
  char password[100];
};
class TeacherManagement{
  private:
    Teacher teacher;

    // Take input from user
    void input();

    // Write student data to file
    void writeFile();

    // Read student data from file
    // print in the form of table
    void readFile();

    // print student data 
    void output(Teacher);

  public:
    void newRegistration();
    void listAll();
    void fire();
    void updatePasswd(int);
};
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
  cout << "|" << setw(12) << left << tch.empID << setw(9) << left << "|";
  cout << left << setw(20) << tch.name;
  cout << right << setw(2) << "|" << endl;
}

#undef FILENAME 