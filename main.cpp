#include "lib/quiz.h"
#include "lib/student.h"

int main(){
    StudentManagement *st = new StudentManagement;

    st->input();
    st->writeFile();
    st->readFile();

    delete st;
    return 0;
}