#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Quiz{
    private:
        // This is the question filename.
        string QFILENAME = "quesBank/questions.txt";
        string questions[20];
    public:
        Quiz(){
            for(int i=0; i<20; i++){
                questions[i] = getQuestion(i+1);
            }
        }
        /*********************************
                getByLineNumber()
        **********************************
            This method has the ability
            to  return the line by line
            number.
        *********************************/
        string getByLineNumber(int lineNo){
            // Opening the file
            ifstream quesFile(QFILENAME);

            /*******************************
                     line <string>
            ********************************
             line variable is use to store
             the  line  got from search in
             a file. 
            *******************************/
            string line;

            /*******************************
                  Search By Line Number
            *******************************/
            for (int i = 0; getline (quesFile,line) && i<900; i++)
                if (i == lineNo){
                    return line;
                }
            
            // Closing the file
            quesFile.close();

            // If that line does not exist.
            return "Not Found!";
        }
        /**********************************
                    getQuestion()
        ***********************************
            This function  will return 
            a question and its options
            if the question  number is
            given.
        **********************************/
        string getQuestion(int quesNo){
            ifstream quesFile(QFILENAME);

            // Store Question
            string question;
            // Store line, got from the file
            string line;

            /*************************************
                        countLine <int>
            **************************************
                It will count lines as we read 
                the lines in file.
            *************************************/
            int countLine=0;

            /**************************************
                This portion of code will search
                for  question  and  add  it  the 
                question   variable   with   its 
                options as well.
            **************************************/
            while(getline(quesFile,line)){
                // Check if the first character is a number
                // and = to the qiven question number.
                if( 
                    (int)line[0]-48 == quesNo && line[1] == '.' ||

                    // 12 -> 12/10 = 1 & 12%10 = 2
                    // this logic will compare each digit.
                    (int)line[0]-48==quesNo/10 && (int)line[1]-48 == quesNo%10
                ){
                    question = line;
                    for(int i=1; i<=5;i++){
                        question += "\n" + getByLineNumber(countLine+i);
                    }
                    break;
                }

                countLine++;
            }

            // Closing file
            quesFile.close();

            return question;
        }
};