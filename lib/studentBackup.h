#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
using namespace std;

#define FILENAME "resources/student.bin"

struct Student{
  char *name = new char[50];
  char *address = new char[50];
  char *password = new char[50];
  int rollNo=0;
  int marks=-1;
  int percentage=0;
};
class StudentManagement{
  protected:
    Student student;
  public:
    // Constructors
    StudentManagement();
    StudentManagement(char*, int, char*, char*);

    // Methods
    // Write to file
    void writeFile();
    // Get input and store in file
    void write();
    // read from file
    void read();
    // Take input from user
    void input();
    // display student info
    void output(Student);
    // table header.
    void showTableHead();
    // display error
    void displayError();
    // Password input
    void passwdInput();

    // Destructor
    ~StudentManagement();
};
/*********************
      Definition
*********************/
// Default Constructor
StudentManagement::StudentManagement(){
  strcpy(student.name, "");
  strcpy(student.address, "");
  student.rollNo = 0;
  student.marks = -1;
  student.percentage = 0;
}
// Parameterized Constructor
StudentManagement::StudentManagement(char *n, int r, char *a, char *p){
  strcpy(student.name, n);
  strcpy(student.address, a);
  strcpy(student.password, p);
  student.rollNo = r;
  student.marks=-1;
  student.percentage = 0;
}
/****************************
        writeFile()
*****************************
  This method is responsible
  for writing student file.
*****************************/
void StudentManagement::writeFile(){
  // Open File
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    // Writing to file
    outFile.write((char*)&student, sizeof(student));
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
void StudentManagement::write(){
  input();
  writeFile();
}
/****************************
          readFile()
*****************************
  This method can be use
  to write student object
  to the file.
****************************/
void StudentManagement::read(){
  Student *st = new Student;
  // Open File
  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    showTableHead();
    // Writing to file
    while(inFile.read((char*)st, sizeof(*st))){
      output(*st);
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
void StudentManagement::input(){
  cout << "Name: "; cin.getline(student.name, 50);
  cout << "Roll Number: "; cin >> student.rollNo;
  
  // For the weird behaviour of getline()
  cin.clear();
  cin.ignore(124,'\n');

  cout << "Address: "; cin.getline(student.address, 50);
}
/****************************
          output()
*****************************
  Show output to the user.
****************************/
void StudentManagement::output(Student st){
  cout << st.name << "\t\t";
  cout << st.rollNo << "\t\t";
  cout << st.marks << "\t\t";
  cout << st.percentage << "%\t\t";
  cout << st.address << endl;
}
void StudentManagement::showTableHead(){
  cout << "Name\t\t\t" << "Roll Number\t" << "Marks\t" << "Percentage\t" << "Address" << endl;
  cout << "--------------------------------------------------------------------------" << endl;
}

/****************************
        displayError()
*****************************
      It display error.
****************************/
void StudentManagement::displayError(){
  cout << "Error: Unable to open file." << endl;
}
void StudentManagement::passwdInput(){
  int index=0;
  char character;

  while(character!='\r' && index<50){
    character = getch();
    if(character!='\r'){
        if(character!='\b' && character!='\t'){
            cout << "*";
            student.password[index] = character;
            index++;
        }
        else if(index!=0 && character!='\t'){
            index--;
            student.password[index]= '\0';
            cout << '\b' << " " << '\b';
        }
    }
  }
  student.password[index] = '\0';
  cout << endl;
}
StudentManagement::~StudentManagement(){
  delete[] student.name;
  delete[] student.address;
  delete[] student.password;
}