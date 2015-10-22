/*****************************************************************************
 * Program Name: Asses.cpp
 * Author: William Buffum
 * Date: 3/5/15
 * Input: txt file or integers for rows and columns 
 * Output: the largest product of 4 adjacent numbers
 * **************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string.h>
#include <string>


using namespace std;
// prototypes for all of my functions
void test(int argc, char *argv[], int** Array);
void rowcol(int &row, int &col);
int** create_array(int y, int x);
int** fill_array(int** Array, int row, int column);
int** fill_input_array(int** Array, int row, int column);
void output_array(int** Array, int row, int column);
void orientation_functions(int** Array, int row, int col);
void product(int** Array, int row, int column, int &product, int b,
      int c, int d, int e, int f, int g, int h, int i, int j, string msg,
      string &z, int &xstart, int &ystart);
int digit_checker(char* input);


int main(int argc, char *argv[]) { //3
   int **Array = NULL, row, column;
   test(argc, argv, Array);// does the whole thing
   return 0;
}

/******************************************************************************
 * Function: test
 * description: determines if the user wants to use a file or randomly
 *              generate a array, runs appropriate functions for each
 * paramaters: command line
 * ***************************************************************************/
void test(int argc, char *argv[], int** Array) { //16
   int row, column;
   if(argc == 1) { // determines if an option is used or not
      rowcol(row, column);// error handling to check only numbers
      Array = create_array(row, column);// generates
      Array = fill_array(Array, row, column);// fills array
      output_array(Array, row, column);// outputs the array
      orientation_functions(Array, row, column);// checks greatest product
   }
   else if(!strcmp(argv[1], "-test")) { // makes sure that the user only 
      cin >> row >> column;             //entered "test" as an option
      Array = create_array(row, column);// generates array
      Array = fill_input_array(Array, row, column);// fills array
      output_array(Array, row, column);// outputs array
      orientation_functions(Array, row, column);// checks greatest product
   }
   else { // prints error if they did not
      cout << "error: no good input!" << endl;
      exit(0);
   }
}

/******************************************************************************
 *Function: orientation_functions
 *Description: runs through the different shapes to see which has
 *              the largest product
 *parameters: runs through entire array
 *****************************************************************************/
void orientation_functions(int** Array, int row, int col) { //13
   string shape;
   int prod, xstart, ystart;
                           // b c d e f g h i j
   product(Array,row,col,prod,0,0,3,0,1,0,2,0,3,"Horiz",shape, xstart, ystart);
   product(Array,row,col,prod,3,0,0,1,0,2,0,3,0,"Vert",shape,xstart,ystart);
   product(Array,row,col,prod,3,0,3,1,1,2,2,3,3,"Dia-R",shape,xstart,ystart);
   product(Array,row,col,prod,1,0,1,0,1,1,0,1,1,"Box",shape,xstart,ystart);
   product(Array,row,col,prod,1,0,2,0,1,1,1,1,2,"Zig-horz",shape,xstart,ystart);
   product(Array,row,col,prod,2,0,1,1,0,1,1,2,1,"Zig-vert",shape,xstart,ystart);
   product(Array,row,col,prod,2,0,1,1,0,2,0,2,1,"L",shape,xstart,ystart);
   product(Array,row,col,prod,3,3,0,1,-1,2,-2,3,-3,"Dia-L",shape,xstart,ystart);
   //^^ different shapes
   cout << "Starting point: Array[" << ystart << "][" << xstart << "]" << endl;
   cout << "The shape is: " << shape << endl;
   cout << "The greatest product is: " << prod << endl;
}

/******************************************************************************
 *Function: rowcol
 *Description: checks to make sure inputs are integers
 *parameters: runs through character arrays to check for integer inputs
 *****************************************************************************/
void rowcol(int &row, int &col) {

   char temp_row[25];// character array
   char temp_col[25];// character array

   cout << "Enter the number of rows: ";
   cin >> temp_row;
   while(digit_checker(temp_row)) {// goes into function to check string
      cout << "error: integers only" << endl;
      cin >> temp_row;
   }
   cout << "Enter the number of columns: ";
   cin >> temp_col;
   while(digit_checker(temp_col)) {// goes into function to check string
      cout << "error: integers only" << endl;
      cin >> temp_col;
   }
   row = atoi(temp_row);// sends row the int values of c-string
   col = atoi(temp_col);// sends col the int values of c-string
}

/******************************************************************************
 *Function: digit_checker
 *Description: function to check each element of c-string
 *parameters: runs through entire c-string
 *****************************************************************************/
int digit_checker(char* input) {
   for(int i = 0; i < strlen(input); i++) {// indexes through 
      if(!isdigit(input[i])) {// checks if character is an integer
	 return 1;
      }
   }
   return 0;
}

/******************************************************************************
 *Function: product 
 *Description: finds the largest product given the shape orientation passed in
 *parameters: good input starts function, checks four element points
 *****************************************************************************/
void product(int** Array,int row,int column,int &product,int b,int c,int d,
      int e,int f,int g,int h,int i,int j,string msg,string &z,
      int &xstart,int &ystart) { //12

   int temp; //temp holds the temporary product
   for(int y = 0; (y + b) < row; y++) {
      for(int x = c; (x + d) < column; x++) {
	 temp = Array[y][x];//following lines check differ elements
	 temp *= Array[y+e][x+f];// based on arguments passed into
	 temp *= Array[y+g][x+h];// this function
	 temp *= Array[y+i][x+j];
	 if(product < temp) {
	    product = temp;
	    xstart = x;
	    ystart = y;
	    z = msg;// passes by reference the shape type
	 }
      }
   }
}
/******************************************************************************
 *Function: fill_input_array 
 *Description: fills array from the text file
 *parameters: a good text file needs to be provided
 *****************************************************************************/
int** fill_input_array(int** Array, int row, int column) { //3
   for(int x = 0; x < row; ++x) {// tells which row to fill
      for(int y = 0; y < column; ++y) {// tells which column to fill
	 cin >> Array[x][y];// drops file through buffer into array at elements
      }
   }
   return Array;// returns array filled by file
}

/******************************************************************************
 *Function: create_array 
 *Description: builds dynamic 2D array using row/column input
 *parameters: builds array using row/column input, must be good input
 *****************************************************************************/
int** create_array(int y, int x) { //5
   int **BuiltArray;// declares double pointer
   BuiltArray = new int *[y];// initialize dble pntr to 1d arry of pntrs on heap
   for(int i = 0; i < y; i++) {// goes to each pointer in array of pointers
      BuiltArray[i] = new int[x];// creates array from array of pointers
   }
   return BuiltArray;// returns array filled with garbage
}
/******************************************************************************
 *Function: fill_array
 *Description: randomly fills array using time seed
 *parameters: an array must have been built
 *****************************************************************************/
int** fill_array(int** Array, int row, int column) { //5
   srand(time(NULL));// srand uses time as a seed for rand
   for(int i = 0; i < row; i++) {// loops through rows
      for(int j = 0; j < column; j++) {// loops through columns
	 Array[i][j] = rand() % 50 + 1;// rand generates pseudorandom numbers
      }
   }
   return Array;// returns filled in array
}
/******************************************************************************
 *Function: output_array
 *Description: outputs each element of the array
 *parameters: an array must be built and filled
 *****************************************************************************/
void output_array(int** Array, int row, int column) { //5
   for(int i = 0; i < row; i++) {// loops through rows
      for(int j = 0; j < column; j++) {// loops through columns
	 cout << setw(5) << Array[i][j];// prints array at element [i][j]
      }
      cout << endl;
   }
   cout << endl;
}
