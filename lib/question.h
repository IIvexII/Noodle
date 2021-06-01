#include "header.h"

#define FILENAME "quesBank/questions.bin"

class Question{
  public:
    char subject[10];
    int questionNo;
    char question[200];
    char options[4][100];
    char answer;
};
class QuestionHandler{
  private:
    Question question;
    char optArray[5] = "ABCD";

  public:
    void input();
    void display();
};
void QuestionHandler::input(){
  cout << "Subject: "; cin.getline(question.subject, 10);
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
void QuestionHandler::display(){
  cout << "Subject: " << question.subject << endl;
  cout << "Question No.: " << question.questionNo << endl;
  cout << "Question: " << question.question << endl;
  for(int i=0; i<4; i++){
    cout << optArray[i] << ": " << question.options[i] << endl;
  }
  cout << "Answer: " << question.answer << endl;
}