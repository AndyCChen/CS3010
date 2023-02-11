#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UNBIASED_EXPONENT = 127;
const int BINARY_EXPONENT_BITS = 8;
const int BINARY_MANTISSA_BITS = 23;

void float_to_binary_scientific(double, int, char*, char*, char*);
void float_to_binary(double, char*, char*, char*);
void int_to_binary(int, char*, int);
void fraction_to_binary(double, char*, int);


int main() {
	string input;

	cout << "Enter a number in one of the following formats." << endl;
	cout << "1) a.b * 10^(e)      Ex: 3.14e2" << endl;
	cout << "2) a.b               Ex: 10.25" << endl;
	cout << "Input: ";
	cin >> input;

	size_t exponent_position = input.find("e");

	char signed_bit;
	char *binary_exponent = new char[BINARY_EXPONENT_BITS + 1];
	char *binary_mantissa = new char[BINARY_MANTISSA_BITS + 1];

	// input is in a.b * 10^(e) format
	if (exponent_position != string::npos) {
		string decimal_string = input.substr(0, exponent_position);
		string power_string = input.substr(exponent_position + 1, input.length() - 1);

		double decimal = stod(decimal_string);
		int power = stoi(power_string);

		float_to_binary_scientific(decimal, power, &signed_bit, binary_exponent, binary_mantissa);
	}
	// input is in a.b format 
	else {
		float_to_binary(stod(input), &signed_bit, binary_exponent, binary_mantissa);
	}

	cout << endl << "IEEE 754 single precision representation of " << input << " is: " << endl;
	cout << signed_bit << " " << binary_exponent << " " << binary_mantissa << endl;

	return 0;
}

void float_to_binary_scientific(double decimal, int power, char *signed_bit, char *binary_exponent, char *binary_mantissa) {
	int exponent_bias;
	double mantissa;

	if (power < 0) {
		exponent_bias = -1;

		do {
			mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
			exponent_bias--;
		} while (abs((int) mantissa) != 1);
	} else if (power > 0) {
		exponent_bias = 1;

		do {
			mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
			exponent_bias++;
		} while (abs((int) mantissa) != 1);
	} else {
		mantissa = (decimal * pow(10, power)) / pow(2, 1);
		cout << mantissa << endl;

		if (mantissa < decimal) {
			exponent_bias = 1;

			do {
				mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
				exponent_bias++;
			} while (abs((int) mantissa) != 1);
		} else {
			exponent_bias = -1;

			do {
				mantissa = (decimal * pow(10, power)) / pow(2, exponent_bias);
				exponent_bias--;
			} while (abs((int) mantissa) != 1);
		}
	}
	cout << mantissa << endl;
	exponent_bias--;

	int biased_exponent = UNBIASED_EXPONENT + exponent_bias;

	if (decimal > 0) *signed_bit = '0';
	else if (decimal < 0) *signed_bit = '1';
	int_to_binary(biased_exponent, binary_exponent, BINARY_EXPONENT_BITS + 1);
	fraction_to_binary(abs(mantissa), binary_mantissa, BINARY_MANTISSA_BITS + 1);
}

void float_to_binary(double input, char *signed_bit, char *binary_exponent, char *binary_mantissa) {
	int power = 0;
	input = input * pow(10, power);
	cout << input << endl;
	float_to_binary_scientific(input, power, signed_bit, binary_exponent, binary_mantissa);
}

void int_to_binary(int number, char *binary, int size) {
	double quotient = number;

	// null terminate end
	binary[size -1] =  '\0';

	for (int index = size - 2; index >= 0; index--) {
		quotient /= 2;

		if (quotient - (int) quotient == 0 ) {
			binary[index] = '0';
		} else {
			binary[index] = '1';
		}

		quotient = floor(quotient);
	}
}

void fraction_to_binary(double fraction, char *binary, int size) {
	fraction = fraction > 1 ? fraction - (int) fraction : fraction;
	double product = fraction;

	for (int index = 0; index < size - 1; index++) {
		product *= 2;
		binary[index] = (int) product ? '1' : '0';
		product = (int) product >= 1 ? product - 1 : product;
	}

	binary[size - 1] = '\0';
}