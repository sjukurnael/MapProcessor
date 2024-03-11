//#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include "Stacks.h"
#include "Matrix Class.h"

using namespace std;

//Iterative Method
int validCoord(int x, int y, int n, int m)
{
 
    if (x < 0 || y < 0) {
        return 0;
    }
    if (x >= n || y >= m) {
        return 0;
    }
    return 1;
}


int objectFinder(int n, int m, Matrix& mat1, int x, int y, int& objCounter)
{
   int counter = 0;
 
   Stack<int> *obj = new Stack<int>;
   
   //If the element is 0, do not count it
   if(mat1.getInput(x, y).getContent() == '0'){
      return 0;
   }
  	
   //If the element is not zero, and it hasn't been processed, count it
   if(mat1.getInput(x, y).getProcessed() == 0){
   
      //We found another object so increment
      objCounter++;
  
      //Push the coordinates into the stack
      obj->push((x * m) + y);
      counter++;
   
      //Set as processed
      Element temp;
      temp = mat1.getInput(x, y);
      temp.setProcessed(1);
      mat1.setInput(x, y, temp);
      
  
     // Until stack is emppty
     while (!obj->isEmpty()) {
 
       // Extrat coordinates of object in stack
       int coord = obj->peek();
       int rowVal = coord / m;
       int colVal = coord % m;
    
       // Popping top object in stack
       obj->pop();
       Element temporary;
       
       if(validCoord(rowVal + 1, colVal, n, m) && mat1.getInput(rowVal + 1, colVal).getProcessed() == 0 && mat1.getInput(rowVal + 1, colVal).getContent() != '0'){
    	  obj->push((rowVal + 1) * m + colVal);
    	  temporary = mat1.getInput(rowVal + 1, colVal);
    	  temporary.setProcessed(1);
    	  mat1.setInput(rowVal + 1, colVal, temporary);
    	  counter++;
	   }
    
       if(validCoord(rowVal - 1, colVal, n, m) && mat1.getInput(rowVal - 1, colVal).getProcessed() == 0 && mat1.getInput(rowVal - 1, colVal).getContent() != '0'){
    	  obj->push((rowVal - 1) * m + colVal);
    	  temporary = mat1.getInput(rowVal - 1, colVal);
    	  temporary.setProcessed(1);
    	  mat1.setInput(rowVal - 1, colVal, temporary);
    	  counter++;
	   }
    
       if(validCoord(rowVal, colVal + 1, n, m) && mat1.getInput(rowVal, colVal + 1).getProcessed() == 0 && mat1.getInput(rowVal, colVal + 1).getContent() != '0'){
    	  obj->push((rowVal * m) + (colVal + 1));
    	  temporary = mat1.getInput(rowVal, colVal + 1);
    	  temporary.setProcessed(1);
    	  mat1.setInput(rowVal, colVal + 1, temporary);
    	  counter++;
	   }
    
       if(validCoord(rowVal, colVal - 1, n, m) && mat1.getInput(rowVal, colVal - 1).getProcessed() == 0 && mat1.getInput(rowVal, colVal - 1).getContent() != '0'){
    	  obj->push((rowVal * m) + (colVal - 1));
          temporary = mat1.getInput(rowVal, colVal - 1);
    	  temporary.setProcessed(1);
    	  mat1.setInput(rowVal, colVal - 1, temporary);
    	  counter++;
	   }
     }  
   }

   else{
	  return 0;
   }

return counter;
}

void IterativeSolution(Matrix mat1, int numRow, int numCol){
	 
	 int objCounter = 0;
     int walker = 0;
	 
	 for(int k = 1; k < numRow - 1; k++){
  	    for(int l = 1; l < numCol - 1; l++){
  	       if(mat1.getInput(k, l).getContent() != '0' && mat1.getInput(k, l).getProcessed() == 0){
			 walker = objectFinder(numRow, numCol, mat1, k, l, objCounter);
		     cout << "Object " << objCounter << ": ";
		     cout << walker << endl;
		   } 
	    }
     }
}

//Recursive Methods
void continueFind(Matrix& mat1, int x, int y, int numRow, int numCol, int&counter)
{
    // Base cases
    if (x < 0 || x >= numRow || y < 0 || y >= numCol)
        return;
    
    if(mat1.getInput(x, y).getContent() == '0')
        return;
    
    if(mat1.getInput(x, y).getProcessed() != 0)
        return;
 
    //If an element exists and it hasn't been visited:
    Element temp = mat1.getInput(x, y);
    temp.setProcessed(1);
    mat1.setInput(x, y, temp);
    counter++;
 
    // Recur for right, left, top and bottom
    continueFind(mat1, x + 1, y, numRow, numCol, counter);
    continueFind(mat1, x - 1, y, numRow, numCol, counter);
    continueFind(mat1, x, y + 1, numRow, numCol, counter);
    continueFind(mat1, x, y - 1, numRow, numCol, counter);
}
 

int findObject(Matrix& mat1, int x, int y, int numRow, int numCol)
{
    int counter = 0;
    if(mat1.getInput(x, y).getContent() != '0' && mat1.getInput(x, y).getProcessed() == 0){
       continueFind(mat1, x, y, numRow, numCol, counter);
       return counter;
	}
	else{ 
	   return 0;
	}
    
}

void RecursiveSolution(Matrix mat1, int numRow, int numCol){
   
   int objCounter = 0;
   int counter = 0;
   
   for(int k = 1; k < numRow - 1; k++){
      for(int l = 1; l < numCol - 1; l++){
         if(mat1.getInput(k, l).getContent() != '0' && mat1.getInput(k, l).getProcessed() == 0){
      	    counter = findObject(mat1, k, l, numRow, numCol);
      	    objCounter++;
            cout << "Object" << objCounter << ": " << counter << endl;
         }
	  }
   }
}

void resetMatrix(Matrix& mat1, int numRow, int numCol){
   Element temp;
   for(int i = 0; i < numRow; i++){
	  for(int j = 0; j < numCol; j++){
		temp = mat1.getInput(i, j);
		temp.setProcessed(0);
		mat1.setInput(i, j, temp); 
	    }
	}
	
}

// Main
int main(){
	
	int numRow = 0, numCol = 0;
	string filename = "";
    string whiteSpace;
    string string1;
     
    cout << "Enter filename: " << endl;
    cin >> filename;
    ifstream inFS;
    filename = filename + ".txt";
    inFS.open(filename.c_str());
    if(inFS.fail()){
      cout << "File Open Failure" << endl;
      exit(EXIT_FAILURE);
    }
    
	if(inFS.good()){
   	   cout << "Successfully Opened" << endl;
    }
   
   inFS >> numRow;
   inFS >> numCol;
   
   Matrix mat1(numRow, numCol);
   Element temp;
   char display;
   getline(inFS, whiteSpace);
   
	for(int i = 0; i < numRow; i++){
		getline(inFS, string1);
		for(int j = 0; j < numCol; j++){
		   temp = mat1.getInput(i, j);
		   temp.setContent(string1[j]);
		   mat1.setInput(i, j, temp); 
	    }
	}
	
 	inFS.close();
   
	char choice;
	do {
		cout << endl << "Enter \"I\" for Iterative method, \"R\" for Recursive method, and \"Q\" to Quit" << endl;
	    cin >> choice;
	    
	    if(choice == 'Q'){
	       cout << "Exited" << endl;
		}
		
	    if(choice == 'I'){
	       IterativeSolution(mat1, numRow, numCol);
	       resetMatrix(mat1, numRow, numCol);
	    }
	    
        else if(choice == 'R'){
           RecursiveSolution(mat1, numRow, numCol);
           resetMatrix(mat1, numRow, numCol);
		}
	     
	    else{
	    	"Invalid Choice!";
		}
		
	   } while(choice != 'Q');
	 

return 0;	
}


/*
Sample Output:

Enter filename
t0
Successfully Opened

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
I
Object 1: 6
Object 2: 9
Object 3: 1
Object 4: 17

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
R
Object1: 6
Object2: 9
Object3: 1
Object4: 17

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
Q
Exited

--------------------------------
Process exited after 8.066 seconds with return value 0
Press any key to continue . . .



Enter filename
t1
Successfully Opened

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
I
Object 1: 9
Object 2: 10
Object 3: 19
Object 4: 1
Object 5: 54

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
R
Object1: 9
Object2: 10
Object3: 19
Object4: 1
Object5: 54

Enter "I" for Iterative method, "R" for Recursive method, and "Q" to Quit
Q
Exited

--------------------------------
Process exited after 6.384 seconds with return value 0
Press any key to continue . . .
*/
