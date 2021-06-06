#include "lib/question.h"

int main(){
    QuestionHandler question;

    // question.input(question.question);
    // question.writeFile();

    question.updateQuestion();

    question.readFile();

    return 0;
}
