#include <iostream>
#include <fstream>
using namespace std;

#define FILENAME "resources/student.bin"

class Student{
  private:
    string name;
    string address;
    int rollNo;
  public:
    // Constructors
    Student();
    Student(string, int, string);

    // Methods
    void writeFile(Student);
    void readFile();
    void input();
    void output();
    void displayError(){}
};
// Definition
Student::Student(){
  // Default Constructor
  name = "";
  address = "";
  rollNo = 0;
}
Student::Student(string n, int r, string a){
  // Parameterized Constructor
  name = n;
  address = a;
  rollNo = r;
}
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
/****************************
          readFile()
*****************************
  This method can be use
  to write student object
  to the file.
****************************/
void Student::readFile(){
  Student st;
  // Open File
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    // Writing to file
    while(inFile){
      inFile.read(reinterpret_cast<char*>(&st), sizeof(st));
      st.output();
    }
  }
  else{
    displayError();
  }
}
void Student::input(){
  Student st;

  cout << "Name: "; cin.getline(st.name);
  cin.ignore();
  cout << "Roll Number: "; cin >> st.rollNo;
  cout << "Name: "; cin.getline(st.name);
  cin.ignore();
}
void Student::output(){
  cout << name << "\t";
  cout << rollNo << "\t\t";
  cout << address << endl;
}
