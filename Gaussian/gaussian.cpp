#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int handle_program_arguments(int, char*[]);
float** read_input_file(string, int&);
void gaussian_elimination(float**);
void guassian_elimination_with_spp();

int main(int argc, char *argv[]) {
   int choice = handle_program_arguments(argc, argv);
   float **matrix = nullptr;
   int size_n;

   switch(choice) {
      case 0:
         cout << "Error, missing input file." << endl;
         return 1;
      case 1:
         cout << "Running gaussian elimination." << endl;

         matrix = read_input_file(argv[1], size_n);
         
         if (matrix != nullptr) {
            for (int row = 0; row < size_n + 1; row++) {
               for (int col = 0; col < size_n; col++) {
                  cout << matrix[row][col] << " ";
               }
               cout << endl;
            }


         }
         
         break;
      case 2:
         cout << "Running gaussian elimination with partial pivoting." << endl;
         break;
      default:
         cout << "Error, invalid argument(s)." << endl;
         return 1;
   }

   return 0;
}

int handle_program_arguments(int argc, char *argv[]) {
   string flag, input_file;

   // missing input file
   if (argc == 1) {
      return 0;
   }
   // check if argument is a input file with .lin extension
   else if (argc == 2) {
      input_file = argv[1];

      // missing input file
      if (input_file == "-spp") return 0;

      // invalid argument
      if (input_file.length() < 5) return -1;

      // invalid argument
      if (input_file.substr(input_file.length() - 4) != ".lin") return -1;
   }
   else if (argc == 3) {
      flag = argv[1];
      input_file = argv[2];

      // invalid argument
      if (flag != "-spp") return -1;

      // missing input file
      if (input_file.substr(input_file.length() - 4) != ".lin") return 0;

      // run gaussian elimination with partial pivoting
      return 2;
   }

   // run gaussian elimination by default
   return 1;
}

float** read_input_file(string file_name, int &size_n) {
   float **matrix = nullptr;
   string line;
   ifstream file (file_name);

   if (file.is_open()) {
      // read value of n
      if (!getline(file, line)) {
         cout << "Failed to read file." << endl;
         return nullptr;
      }

      // initialize matrix size
      size_n = stoi(line);
      matrix = new float*[size_n + 1];

      for (int index = 0; index < size_n + 1; index++) {
         matrix[index] = new float[size_n];
      }

      // read values into matrix
      int row = 0;
      int col = 0;

      while (getline(file, line)) {
         string float_value;
         istringstream matrix_row(line);

         while (getline(matrix_row, float_value, ' ')) {
            if (float_value != "") { 
               matrix[row][col] = stod(float_value);
               col++;        
            }
         }

         col = 0;
         row++;
      }
   } else {
      cout << "Failed to open file." << endl;
      return nullptr;
   }

   return matrix;
}

