#include "lib/registration.h"
#include "lib/core/question.h"

int main(){
    QuestionHandler question;

    question.updateQuestion();
    question.readFile();
    
    return 0;
}
