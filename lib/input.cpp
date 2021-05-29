#include <iostream>

int main(){
  char str[20];
  char character;
  int counter=0;
  do{
    std::cin.get(character);
    if(counter<20){
      str[counter]=character;
      counter++;
    }
  }while(character!='\r');
  std::cout << str;
}