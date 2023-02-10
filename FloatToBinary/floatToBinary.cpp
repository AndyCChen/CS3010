#include <iostream>
#include <string>

using namespace std;

void validateInput(string input) {
	string exponent_delimiter = "e";
	size_t exponent_position = input.find(exponent_delimiter);
	
	if (exponent_position == string::npos) return;

	string decimal_string = input.substr(0, exponent_position);
	string power_string = input.substr(exponent_position + 1, input.length() - 1);

	double decimal = stod(decimal_string);
	int power = stoi(power_string);

	cout << "decimal: " << decimal << endl;
	cout << "power: " << power << endl;
	
}

int main() {
	string input;

	cout << "Enter a number in one of the following formats." << endl;
	cout << "1) a.b * 10^(e)      Ex: 3.14e2" << endl;
	cout << "2) a.b               Ex: 10.25" << endl;
	cout << "Input: ";
	cin >> input;

	validateInput(input);

	return 0;
}