#include "lib/quiz.h"
#include "lib/student.h"


int main(){
    Student st;
    char choice;
    do{
        st.write();
        cout << "Want more? ";
        cin >> choice;
    }while(choice=='y');

    st.read();
    return 0;
}