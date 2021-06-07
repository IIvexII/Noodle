#pragma once
#include "core/header.h"
#include "core/student.h"
#include "core/teacher.h"

// Prototypes
void registrStudent();
void registrTeacher();

void registrStudent(){
  cout << "******************************" << endl;
  cout << "    Student Registration      " << endl;
  cout << "******************************" << endl;
  StudentManagement newStudent;
  newStudent.input();
  newStudent.writeFile();
}

void registrTeacher(){
  cout << "******************************" << endl;
  cout << "    Teacher Registration      " << endl;
  cout << "******************************" << endl;
  TeacherManagement newTeacher;
  newTeacher.input();
  newTeacher.writeFile();
}