/*
file: main.cpp					author: Michael Coache						CAIS230
This program uses recursion in order to convert an inputted decimal number into binary, octal and hexidecimal.
The output is dislay on the console window as well as a file in this program's directory called "conversions.txt"
*/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//prototypes
void getDecimalNumber(int&);
void dectoBin(const int, fstream&);
void dectoOctal(const int, fstream&);
void dectoHex(const int, fstream&);
void reportConversions(int, fstream&);
void description();
bool again();


int main() {
	fstream outs;
	outs.open("conversions.txt", ofstream::out);
	outs.close(); // clean file for each run
	description();
	int n = 0;
	do {
		getDecimalNumber(n);
		reportConversions(n, outs);
	} while (again());
	system("PAUSE");
}
void description() {
	cout << "This program takes a decimal number and converts it into binary, octal, and hexidecimal and reports it to the screen and to a file." << endl;
}
bool again()
{
	char ch;
	do
	{
		cout << endl << "Run the program again?:";
		cin >> ch;
		ch = toupper(ch);
		if (ch != 'Y'&&ch != 'N')
			cout << "Illegal response! Answer Y(YES) or N(NO).\n";
	} while (ch != 'Y'&&ch != 'N');
	if (ch == 'Y') {
		cout << endl;
		return true;
	}
	else return false;
}
void getDecimalNumber(int &n) {
	cout << "Enter number in decimal: ";
	cin >> n;
	cout << endl;
}

void dectoBin(const int n, fstream &outs) {
	if (n == 0)
		return;
	else {
		dectoBin(n / 2, outs);
		cout << n % 2;
		outs << n % 2;
	}
}

void dectoOctal(const int n, fstream &outs) {
	if (n == 0)
		return;
	else {
		dectoOctal(n / 8, outs);
		cout << n % 8;
		outs << n % 8;
	}
}

void dectoHex(const int n, fstream &outs) {
	if (n == 0)
		return;
	else {
		dectoHex(n / 16, outs);
		
		switch (n % 16) {
		case 10:
			outs << 'a';
			cout << 'a';
			break;
		case 11:
			outs << 'b';
			cout << 'b';
			break;
		case 12:
			outs << 'c';
			cout << 'c';
			break;
		case 13:
			outs << 'd';
			cout << 'd';
			break;
		case 14:
			outs << 'e';
			cout << 'e';
			break;
		case 15:
			outs << 'f';
			cout << 'f';
			break;
		default:
			outs << n % 16;
			cout << n % 16;
			break;

		}
	}
}

void reportConversions(int n, fstream &outs) {
	outs.open("conversions.txt", ofstream::out | ios::app);
	cout << "Decimal number is: " << setw(20) << n;
	outs << "Decimal number is: " << setw(20) << n;
	outs << endl;
	cout << endl;
	cout << "Binary conversion: " << setw(19);
	outs << "Binary conversion: " << setw(19);
	dectoBin(n, outs);
	outs << endl;
	cout << endl;
	outs << "Octal conversion: " << setw(20);
	cout << "Octal conversion: " << setw(20);
	dectoOctal(n, outs);
	outs << endl;
	cout << endl;
	outs << "Hex conversion: " << setw(22);
	cout << "Hex conversion: " << setw(22);
	dectoHex(n, outs);
	cout << endl;
	outs << endl << endl;
	outs.close();
}