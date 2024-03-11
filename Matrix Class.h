#ifndef CUSTOMER_H_
#define CUSTOMER_H_
 
#include <string>
#include <iostream>
using std::string;
using namespace std;


class Element{
   
   private:
   char value;
   int processed;
   
   public:
   Element(){
      value = 0;
      processed = 0;
      
  }
   
   void setContent(char cellValue){ value = cellValue; }
   void setProcessed(int num1){ processed = num1; }
   char getContent(){ return value; }
   int getProcessed(){ return processed; }
};


class Matrix{

   private:
   Element* matArray;
   int rows; 
   int cols;

   public:
   Matrix(int nRows, int nCols){ 
   matArray = new Element[nRows * nCols];
   rows = nRows;
   cols = nCols;
   }

   void setInput(int r, int c, Element input){
      matArray[(r * cols) + c] = input;
   }

   Element getInput(int r, int c){ 
      return matArray[(r * cols) + c];
   }
   
};

#endif
