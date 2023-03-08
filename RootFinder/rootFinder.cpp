#include <iostream>

using namespace std;

const int MAX_IT = 10000;

int program_options(int, char *[]);
bool read_input_file(string);
float bisection();

int main (int argc, char *argv[]) {
   int options = program_options(argc, argv);

   switch (options) {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
      case 4:
         break;
      case 5:
         break;
      case 6:
         break;
      case 7:
         break;
      case 8:
         cout << options << endl;
         break;
      default:
         return -1;
   }

   return 0;
}  

int program_options(int argc, char *argv[]) {
   if (argc == 1) {
      cout << "Error, missing arguments." << endl;
      return -1;
   }

   if (strcmp(argv[1], "-newt") == 0) { 

      if (argc == 6) {
         cout << "Running newton's method with..." << endl;
         cout << "Max iterations: " << argv[3] << endl;
         cout << "Initial point: " << argv[4] << endl;
         cout << "Input file: " << argv[5] << endl;

         return 1;
      } else if (argc == 4) {
         cout << "Running newton's method with..." << endl;
         cout << "Max iterations: " << MAX_IT << endl;
         cout << "Initial point: " << argv[2] << endl;
         cout << "Input file: " << argv[3] << endl;

         return 2;
      } else {
         cout << "Error, invalid arguments." << endl;
      }

   } else if (strcmp(argv[1], "-sec") == 0) {

      if (argc == 7) {
         cout << "Running secant method with..." << endl;
         cout << "Max iterations: " << argv[3] << endl;
         cout << "Initial point 1: " << argv[4] << endl;
         cout << "Initial point 2: " << argv[5] << endl;
         cout << "Input file: " << argv[6] << endl;

         return 3;
      } else if (argc == 5) {
         cout << "Running secant method with..." << endl;
         cout << "Max iterations: " << MAX_IT << endl;
         cout << "Initial point 1: " << argv[2] << endl;
         cout << "Initial point 2: " << argv[3] << endl;
         cout << "Input file: " << argv[4] << endl;

         return 4;
      } else {
         cout << "Error, invalid arguments." << endl;
      }

   } else if (strcmp(argv[1], "-hybrid") == 0) {
      if (argc == 7) {
         cout << "Running hybrid method with..." << endl;
         cout << "Max iterations: " << argv[3] << endl;
         cout << "Initial point 1: " << argv[4] << endl;
         cout << "Initial point 2: " << argv[5] << endl;
         cout << "Input file: " << argv[6] << endl;

         return 5;
      } else if (argc == 5) {
         cout << "Running hybrid method with..." << endl;
         cout << "Max iterations: " << MAX_IT << endl;
         cout << "Initial point 1: " << argv[2] << endl;
         cout << "Initial point 2: " << argv[3] << endl;
         cout << "Input file: " << argv[4] << endl;

         return 6;
      } else {
         cout << "Error, invalid arguments." << endl;
      }
   } else {
      if (argc == 6) {
         cout << "Running bisection method with..." << endl;
         cout << "Max iterations: " << argv[2] << endl;
         cout << "Initial point 1: " << argv[3] << endl;
         cout << "Initial point 2: " << argv[4] << endl;
         cout << "Input file: " << argv[5] << endl;

         return 7;
      } else if (argc == 4) {
         cout << "Running bisection method with..." << endl;
         cout << "Max iterations: " << MAX_IT << endl;
         cout << "Initial point 1: " << argv[1] << endl;
         cout << "Initial point 2: " << argv[2] << endl;
         cout << "Input file: " << argv[3] << endl;

         return 8;
      } else {
         cout << "Error, invalid arguments." << endl;
      }
   }

   return -1;
}