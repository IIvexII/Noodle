#include "header.h"
// #include "student.h"
#pragma once

#define FILENAME "quesBank/questions.bin"

class Question{
  public:
    char subject[10];
    int questionNo=-1;
    char question[200];
    char options[4][100];
    char answer;
};
class QuestionHandler{
  private:
    char optArray[5] = "ABCD";

  public:
    Question question;
    void input();
    void display(Question);
    void writeFile();
    void readFile();
    int countBySubject(char*);
    Question searchQuestion(char*, int);
    bool askQuestion(char*, int);
    void updateQuestion();
    void displayError();
    int quiz();
    void addQuestion();
};
void QuestionHandler::input(){
  cin.clear();
  cin.ignore(124, '\n');
  
  char tmpSubject[3] = "GK";

  strcpy(question.subject, tmpSubject);
  cout << "Question Number: "; cin >> question.questionNo;

  // To avoid weird behavior of cin
  cin.clear();
  cin.ignore(124, '\n');

  cout << "Question: "; cin.getline(question.question, 200);

  for(int i=0; i<4; i++){
    cout << "Option " << optArray[i] << ": ";
    cin.getline(question.options[i], 100);
  }
  cout << "Answer: "; cin >>question.answer;
}
void QuestionHandler::display(Question question){
  cout << "Subject: " << question.subject << endl;
  cout << "Question No.: " << question.questionNo << endl;
  cout << "Question: " << question.question << endl;
  for(int i=0; i<4; i++){
    cout << optArray[i] << ": " << question.options[i] << endl;
  }
  cout << "Answer: " << question.answer << endl;
}
void QuestionHandler::writeFile(){
  ofstream outFile(FILENAME, ios::app);

  if(outFile.is_open()){
    outFile.write((char*)&question, sizeof(question));
    outFile.close();
  }
  else{
    displayError();
  }
}
/***********************
        readFile()
***********************/
void QuestionHandler::readFile(){
  Question ques;

  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&ques, sizeof(ques))){
      display(ques);
    }
    inFile.close();
  }
  else{
    displayError();
  }
}
int QuestionHandler::countBySubject(char* subjectName){
  Question ques;
  int count=0;

  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&ques, sizeof(ques))){
      if(strcpy(subjectName, ques.subject)){
        count++;
      }
    }
    inFile.close();
  }

  return count;
}

Question QuestionHandler::searchQuestion(char* subjectName, int questionNumber){
  Question ques;
  int count=1;

  ifstream inFile(FILENAME, ios::in);

  if(inFile.is_open()){
    while(inFile.read((char*)&ques, sizeof(ques))){
      if(strcpy(subjectName, ques.subject)){
        if(count == questionNumber){
          return ques;
        }
        count++;
      }
    }
    inFile.close();
  }
  return Question();
}

bool QuestionHandler::askQuestion(char* subject, int questionNo){
  Question ques = searchQuestion(subject, questionNo);
  char character='\0';
  cout << "Q" << questionNo << ": " << ques.question << endl;
  
  for(int i=0; i<4; i++)
    cout << optArray[i] << ": " << ques.options[i] << endl;
  
  while(
    character!='a' && character!='b' && character!='c' && character!='d' &&
    character!='A' && character!='B' && character!='C' && character!='D'
      ){
        character = getch();
      }
    if(ques.answer == character || ques.answer == (character+32) ){
      cout << "Correct" << endl;
      return 1;
    }
    else{
      cout << "Wrong!!! " << ques.answer << " is the right option." << endl;
      return 0;
    }
}

void QuestionHandler::updateQuestion(){
  Question ques, tmp;
  char subjectName[10] = "GK"; 
  int questionNo, count=1, choice, pos;
  
  cout << "Enter Question Number: "; cin >> questionNo;


  fstream file(FILENAME, ios::binary | ios::in | ios::out);
  file.seekg(0);
  
  while(file.read((char*)&ques, sizeof(ques))){
    pos = file.tellg();
    if(strcmp(subjectName, ques.subject)==0){
      if(count == questionNo){
        display(ques);
        break;
      }
      count++;
    }
  }
  tmp = ques;

  cout << "What do you want to edit?" << endl;
  cout << "1. Question" << endl;
  cout << "2. Options" << endl;
  cout << "3. Answer" << endl;
  cout << "4. Full Question" << endl;
  do{
    cout << "Choose: "; cin >> choice;
  }
  while(choice<1 && choice>4 );

  switch(choice){
    case 1:
      // To avoid weird behavior of cin
      cin.clear();
      cin.ignore(124, '\n');
      cout << "Question: "; cin.getline(tmp.question, 200);
      break;
    case 2:
      for(int i=0; i<4; i++){
        // To avoid weird behavior of cin
        cin.clear();
        cin.ignore(124, '\n');
        cout << "Option " << optArray[i] << ": "; cin.getline(tmp.options[i], 100);
      }
      break;
    case 3:
      // To avoid weird behavior of cin
      cin.clear();
      cin.ignore(124, '\n');
      
      cout << "Answer: "; cin >> ques.answer;
      break;
    // case 4:
    //   input(tmp);
    //   break;
  }
  
  file.seekp(pos-sizeof(tmp));
  file.write((char*)&tmp, sizeof(Question));

  file.close();
}
void QuestionHandler::displayError(){ 
  cout << "Unable to open file..." << endl; 
}
int QuestionHandler::quiz(){
  char tmpSubject[3] = "GK";
  int points = 0;
  for(int i=1; i<=10; i++ )
    points += askQuestion(tmpSubject, i);
    cout << points << endl;
  return points;
}
void QuestionHandler::addQuestion(){
  input();
  writeFile();
}


#undef FILENAME 