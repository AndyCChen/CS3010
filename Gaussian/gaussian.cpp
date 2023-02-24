#include <iostream>
#include <string>

using namespace std;

int handle_program_arguments(int, char*[]);
void read_input_file(string);
void gaussian_elimination();
void guassian_elimination_with_spp();

int main(int argc, char *argv[]) {
   int choice = handle_program_arguments(argc, argv);

   switch(choice) {
      case 0:
         cout << "Error, missing input file." << endl;
         return 1;
      case 1:
         cout << "Running gaussian elimination." << endl;
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

