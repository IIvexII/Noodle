#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Quiz{
    private:
        // This is the question filename.
        string QFILENAME = "quesBank/questions.txt";

    public:
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
            **************************************/
            int countLine=0;

            while(getline(quesFile,line)){
                if( ((int)line[0]-48) == quesNo){
                    question = line;
                    for(int i=1; i<=4;i++){
                        question += "\n" + getByLineNumber(countLine+i);
                    }
                }
                countLine++;
            }
            quesFile.close();

            return question;
        }

};