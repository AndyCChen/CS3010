#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_IT = 10000;
const float EPS = 0.00000001;
const float DELTA = 0.00000001;

class Polynomial {
   int degree;
   float *coefficients;

   public:
      Polynomial (int deg, float *values) {
         degree = deg;
         coefficients = new float[deg + 1];

         for (int i = 0; i < deg + 1; i++) {
            coefficients[i] = values[i];
         }
      } 

      ~Polynomial () {
         delete[] coefficients;
      }

      void printP() {
         for (int i = 0; i < degree + 1; i++) {
            cout << coefficients[i] << " ";
         }
         cout << endl;
      }

      float f(float input) {
         float sum = 0;

         for (int i = 0; i < degree + 1; i++) {
            sum += coefficients[i] * pow(input, degree - i);
         }

         return sum;
      }

      Polynomial* get_derivative() {
         float *temp_coefficients = new float[degree];

         for(int i = 0; i < degree; i++) {
            temp_coefficients[i] = coefficients[i] * (degree - i);
         }

         Polynomial *polynomial = new Polynomial(degree - 1, temp_coefficients);
         delete[] temp_coefficients;
         
         return polynomial;
      }
};

int program_options(int, char *[]);
Polynomial* read_input_file(string, int&);
void output_solution(float, int, string);
float bisection(Polynomial*, float, float, int, float);
float newton(Polynomial*, float, int, float, float);
float secant(Polynomial*, float, float, int, float);
float hybrid(Polynomial*, float, float, int, float);

int main (int argc, char *argv[]) {
   int options = program_options(argc, argv);
   int degree;
   Polynomial *polynomial;

   switch (options) {
      case 1:
         polynomial = read_input_file(argv[5], degree);
         
         if (polynomial != nullptr) {
            newton(polynomial, stof(argv[4]), stoi(argv[3]), EPS, DELTA);
         }

         break;
      case 2:
         polynomial = read_input_file(argv[3], degree);
         
         if (polynomial != nullptr) {
            newton(polynomial, stof(argv[2]), MAX_IT, EPS, DELTA);
         }

         break;
      case 3:
         polynomial = read_input_file(argv[6], degree);
         
         if (polynomial != nullptr) {
            secant(polynomial, stof(argv[4]), stof(argv[5]), stoi(argv[3]), EPS);
         }

         break;
      case 4:
         polynomial = read_input_file(argv[4], degree);
         
         if (polynomial != nullptr) {
            secant(polynomial, stof(argv[2]), stof(argv[3]), MAX_IT, EPS);
         }

         break;
      case 5:
         polynomial = read_input_file(argv[6], degree);
         
         if (polynomial != nullptr) {
            hybrid(polynomial, stof(argv[4]), stof(argv[5]), stoi(argv[3]), EPS);
         }

         break;
      case 6:
         polynomial = read_input_file(argv[4], degree);
         
         if (polynomial != nullptr) {
            hybrid(polynomial, stof(argv[2]), stof(argv[3]), MAX_IT, EPS);
         }

         break;
      case 7:
         polynomial = read_input_file(argv[5], degree);
         
         if (polynomial != nullptr) {
            bisection(polynomial, stof(argv[3]), stof(argv[4]), stoi(argv[2]), EPS);
         }

         break;
      case 8:
         polynomial = read_input_file(argv[3], degree);
         
         if (polynomial != nullptr) {
            bisection(polynomial, stof(argv[1]), stof(argv[2]), MAX_IT, EPS);
         }
         
         break;
   }

   delete polynomial;
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

Polynomial* read_input_file(string file_name, int &degree) {
   string line;
   ifstream file (file_name);

   if (file.is_open()) {
      // read value of n
      if (!getline(file, line)) {
         cout << "Failed to read file." << endl;
         return nullptr;
      }

      degree = stoi(line);
      float *values = new float[degree + 1];

      int index = 0;
      
      while (getline(file, line)) {
         string float_value;
         istringstream polynomial(line);

         while (getline(polynomial, float_value, ' ')) {
            if (float_value != "") { 
               values[index] = stof(float_value);
               index++;
            }
         }
      }

      Polynomial *poly = new Polynomial(degree, values);

      delete[] values;
      file.close();

      return poly;
   } else {
      cout << "Failed to open file." << endl;
      return nullptr;
   }
}

void output_solution(float root, int interations, string outcome) {
   ofstream solution_file;
   solution_file.open("fun1.sol");

   solution_file << root << " ";
   solution_file << interations << " ";
   solution_file << outcome;

   solution_file.close();
}

float bisection(Polynomial *polynomial, float a, float b, int maxIter, float eps) {
   float fa = polynomial->f(a);
   float fb = polynomial->f(b);
   float c;
   int iterations = 1;
   
   if (fa * fb >= 0) {
      cout << "Inadequate values for a and b." << endl;

      return -1.0;
   }

   float error = b - a;

   while (iterations <= maxIter) {
      error = error / 2;
      c = a + error;
      float fc = polynomial->f(c);

      if (abs(error) < eps || fc == 0) {
         cout << "Algorithm has converged after #" << iterations << " iterations!" << endl;
         output_solution(c, iterations, "Success");
         return c;
      }
      
      if (fa * fc < 0) {
         b = c;
         fb = fc;
      } else {
         a = c;
         fa = fc;
      }

      iterations++;
   }

   cout << "Max iterations reached without convergence..." << endl;
   output_solution(c, iterations, "Failure");

   return c;
}

float newton(Polynomial *polynomial, float x, int maxIter, float eps, float delta) {
   Polynomial *derF = polynomial->get_derivative();
   float fx = polynomial->f(x);
   int iterations = 1;

   while (iterations <= maxIter) {
      float fd = derF->f(x);

      if (abs(fd) < delta) {
         cout << "Small slope!" << endl;
         return x;
      }

      float d = fx / fd;
      x = x - d;
      fx = polynomial->f(x);

      if (abs(d) < eps) {
         cout << "Algorithm has converged after #" << iterations << " iterations!" << endl;
         output_solution(x, iterations, "Success");
         return x;
      }

      iterations++;
   }

   cout << "Max iterations reached without convergence..." << endl;
   output_solution(x, iterations - 1, "Failure");
   delete derF;

   return x;
}

float secant(Polynomial *polynomial, float a, float b, int maxIter, float eps) {
   float fa = polynomial->f(a);
   float fb = polynomial->f(b);
   int iterations = 1;

   while (iterations <= maxIter) {
      if (abs(fa) > abs(fb)) {
         swap(a, b);
         swap(fa, fb);
      }

      float d = (b - a) / (fb - fa);
      b = a;
      fb = fa;
      d = d * fa;

      if (abs(d) < eps) {
         cout << "Algorithm has converged after #" << iterations << " iterations!" << endl;
         output_solution(a, iterations, "Success");
         return a;
      }

      a = a - d;
      fa = polynomial->f(a);

      iterations++;
   }

   cout << "Maximum number of iterations reached!" << endl;
   output_solution(a, iterations - 1, "Failure");

   return a;
}

float hybrid(Polynomial *polynomial, float a, float b, int maxIter, float eps) {
   float root = bisection(polynomial, a, b, 10, eps);

   if (root != -1.0) {
      root = newton(polynomial, root, maxIter, eps, DELTA);
   } else {
      return -1.0;
   }

   return root;
}