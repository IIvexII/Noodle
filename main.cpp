#include "lib/quiz.h"
#include "lib/student.h"


int main(){
    Student *st = new Student;

    st->write();

    st->read();

    delete st;
    return 0;
}