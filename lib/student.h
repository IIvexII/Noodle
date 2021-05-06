#include <iostream>
#include <fstream>
using namespace std;

#define FILENAME "resources/student.bin"

class Student{
  public:
    string name;
    string address;
    int rollNo;

    // Constructors
    Student();
    Student(string, int, string);

    // Methods
    void writeFile(Student);
    void write();
    void read();
    void input();
    void output();
    void showTableHead();
    void displayError();
};
/*********************
      Definition
*********************/
// Default Constructor
Student::Student(){
  name = "";
  address = "";
  rollNo = 0;
}
// Parameterized Constructor
Student::Student(string n, int r, string a){
  name = n;
  address = a;
  rollNo = r;
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
  // For the weird behaviour of getline()
  cin.clear();
  cin.sync();

  cout << "Name: "; getline(cin, name);
  cout << "Roll Number: "; cin >> rollNo;

  // For the weird behaviour of getline()
  cin.clear();
  cin.sync();

  cout << "Address: "; getline(cin, address);

  // For the weird behaviour of getline()
  cin.clear();
  cin.sync();
}
/****************************
          output()
*****************************
  Show output to the user.
****************************/
void Student::output(){
  cout << name << "\t\t";
  cout << rollNo << "\t";
  cout << address << endl;
}
void Student::showTableHead(){
  cout << "Name\t\t" << "Roll Number\t" << "Address" << endl;
  // cout << "---------------------------------------" << endl;
}

/****************************
        displayError()
*****************************
      It display error.
****************************/
void Student::displayError(){
  cout << "Error: Unable to open file." << endl;
}
