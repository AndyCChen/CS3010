#include<iostream>

using namespace std;

char handle_program_arguments(int argc, char *argv[]) {
   if (argc == 1) {
      return '0';
   }

   if (argc == 2) {
      if (strcmp(argv[1], "--spp") != 0) {
         return '0';
      }
   }

   return '1';
}

int main(int argc, char *argv[]) {
   char choice = handle_program_arguments(argc, argv);

   switch(choice) {
      case '0':
         cout << "Error, missing input file." << endl;
         return 1;
      
   }

   return 0;
}