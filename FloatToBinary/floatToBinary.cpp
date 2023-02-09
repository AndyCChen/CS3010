#include <iostream>

using namespace std;

int main() {
	int choice;

	do {
		cout << "Select one of the following formating for input." << endl;
		cout << "1) a.b * 10^(e)      Ex: 3.14e2" << endl;
		cout << "2) a.b               Ex: 10.25" << endl;
		cout << "Choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2);

	

	return 0;
}