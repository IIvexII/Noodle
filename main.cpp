#include "lib/core/teacher.h"
#include "lib/core/student.h"

int main(){
    TeacherManagement teacher;
    StudentManagement student;
    student.listAll();
    // teacher.newRegistration();
    teacher.listAll();
    // teacher.fire();
    student.updatePasswd(22);
    return 0;
}
