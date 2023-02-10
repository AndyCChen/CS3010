#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UNBIASED_EXPONENT = 127;
const int BINARY_EXPONENT_BITS = 8;
const int BINARY_MANTISSA_BITS = 23;

void float_to_binary_scientific(double, int);
void float_to_binary();
void int_to_binary(int, char*, int);
void fraction_to_binary(double);


int main() {
	string input;

	cout << "Enter a number in one of the following formats." << endl;
	cout << "1) a.b * 10^(e)      Ex: 3.14e2" << endl;
	cout << "2) a.b               Ex: 10.25" << endl;
	cout << "Input: ";
	cin >> input;

	string exponent_delimiter = "e";
	size_t exponent_position = input.find(exponent_delimiter);

	string decimal_delimiter = ".";
	size_t decimal_position = input.find(decimal_delimiter);

	// input is in a.b * 10^(e) format
	if (exponent_position != string::npos) {
		string decimal_string = input.substr(0, exponent_position);
		string power_string = input.substr(exponent_position + 1, input.length() - 1);

		double decimal = stod(decimal_string);
		int power = stoi(power_string);

		float_to_binary_scientific(decimal, power);

		//cout << "Scientific" << endl;
	}
	// input is in a.b format 
	else if (decimal_position != string::npos) {


		cout << "Float" << endl;
	}

	return 0;
}

void float_to_binary_scientific(double decimal, int power) {
	int exponent_bias;
	double mantissa;

	if (power < 0) {
		exponent_bias = -1;

		do {
			mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
			exponent_bias--;
		} while (abs((int) mantissa) != 1);

		exponent_bias++;	
	} else if (power > 0) {
		exponent_bias = 1;

		do {
			mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
			exponent_bias++;
		} while (abs((int) mantissa) != 1);

		exponent_bias--;
	} else {
		float_to_binary();
		
	}

	int biased_exponent = UNBIASED_EXPONENT + exponent_bias;
	double fractional_mantissa = mantissa - 1;

	char *binary_biased_exponent = new char[BINARY_EXPONENT_BITS];

	int_to_binary(biased_exponent, binary_biased_exponent, BINARY_EXPONENT_BITS);

	cout << "Mantissa: " << mantissa << endl;
	cout << "Fractional mantissa: " << fractional_mantissa << endl;
	cout << "Base two power: " << exponent_bias << endl;
	cout << "Biased Exponent: " << biased_exponent << endl;
	//cout << "Binary exponent: "<< binary_biased_exponent << endl;
}

void float_to_binary() {

}

void int_to_binary(int number, char *binary, int size) {
	double quotient = number;

	for (int index = size - 1; index >= 0; index--) {
		quotient /= 2;

		if (quotient - (int) quotient == 0 ) {
			binary[index] = '0';
		} else {
			binary[index] = '1';
		}

		quotient = floor(quotient);

		cout << binary[index] << " " << quotient << endl;
	}
}

void fraction_to_binary(double fraction) {

}