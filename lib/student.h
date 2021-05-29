#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
// #include "input.h"
using namespace std;

#define FILENAME "resources/student.bin"

class Student{
  protected:
    char *name = new char[50];
    char *address = new char[50];
    char *password = new char[50];
    int rollNo;
    int marks;
    int percentage;
  public:
    // Constructors
    Student();
    Student(char*, int, char*, char*);

    // Methods
    // Write to file
    void writeFile(Student);
    // Get input and store in file
    void write();
    // read from file
    void read();
    // Take input from user
    void input();
    // display student info
    void output();
    // table header.
    void showTableHead();
    // display error
    void displayError();
    // Password input
    void passwdInput();

    // Destructor
    ~Student();
};
/*********************
      Definition
*********************/
// Default Constructor
Student::Student(){
  strcpy(name, "");
  strcpy(address, "");
  rollNo = 0;
  marks = -1;
  percentage = 0;
}
// Parameterized Constructor
Student::Student(char *n, int r, char *a, char *p){
  strcpy(name, n);
  strcpy(address, a);
  strcpy(password, p);
  rollNo = r;
  marks=-1;
  percentage = 0;
}
/****************************
        writeFile()
*****************************
  This method is responsible
  for writing student file.
*****************************/
void Student::writeFile(Student st){
  // Open File
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    // Writing to file
    outFile.write(reinterpret_cast<char*>(&st), sizeof(st));
    outFile.close();
  }
  else{
    displayError();
  }
}
/******************************
            write()
*******************************
  This function uses other
  functions to get input from
  user and write it in file.
******************************/
void Student::write(){
  Student st;

  st.input();
  writeFile(st);
}
/****************************
          readFile()
*****************************
  This method can be use
  to write student object
  to the file.
****************************/
void Student::read(){
  Student st;
  // Open File
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    showTableHead();
    // Writing to file
    while(inFile.read(reinterpret_cast<char*>(&st), sizeof(st))){
      st.output();
    }
    // Closing File
    inFile.close();
  }
  else{
    displayError();
  }
}
/****************************
          input()
*****************************
  It takes input from user.
****************************/
void Student::input(){
  cout << "Name: "; cin.getline(name, 50);
  cout << "Roll Number: "; cin >> rollNo;
  
  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');

  cout << "Address: "; cin.getline(address, 50);
  cout << "Password: "; passwdInput();
}
/****************************
          output()
*****************************
  Show output to the user.
****************************/
void Student::output(){
  cout << name << "\t\t";
  cout << rollNo << "\t\t";
  cout << marks << "\t";
  cout << percentage << "%\t\t";
  cout << address << endl;
}
void Student::showTableHead(){
  cout << "Name\t\t\t" << "Roll Number\t" << "Marks\t" << "Percentage\t" << "Address" << endl;
  cout << "------------------------------------------------------------------------------------" << endl;
}

/****************************
        displayError()
*****************************
      It display error.
****************************/
void Student::displayError(){
  cout << "Error: Unable to open file." << endl;
}
void Student::passwdInput(){
  int index=0;
  char character;

  while(character!='\r' && index<50){
    character = getch();
    if(character!='\r'){
        if(character!='\b' && character!='\t'){
            cout << "*";
            password[index] = character;
            index++;
        }
        else if(index!=0 && character!='\t'){
            index--;
            password[index]= '\0';
            cout << '\b' << " " << '\b';
        }
    }
  }
  password[index] = '\0';
  cout << endl;
}
Student::~Student(){
  delete[] name;
  delete[] address;
  delete[] password;
}