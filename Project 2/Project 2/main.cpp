/*
main.cpp			Michael Coache					CAIS 0230					2/23/16
This program allows you to enter 4 different divisions each with 4 quarterly sales, the program writes to a binary file
and then reads from and displays to console and it also writes to a regular text file with the results. Additionally, the sum is calculated for all quartery sales.
*/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int SIZE = 12;
const int NUM_OF_DIVISIONS = 4;
struct Division {
	char divName[SIZE];
	double sales[4];
};

void createCorporateFile(fstream &division);
void displayCorporateSales(fstream &division, ofstream& outs);
void displayInfo();

int main() {
	displayInfo();
	fstream division;
	ofstream outs;
	createCorporateFile(division);
	displayCorporateSales(division, outs);

	system("pause");
	return 0;
}
void displayInfo() {
	cout << "This program will allow you to enter a division name followed by four quarterly sales, this will repeat 4 times for 4 different divisions\n"
		<< "The program will then report the sum of the quarterly sales as well as the sales for each quarter.\nThis program also writes a file with the results called results.txt\n";
}
void createCorporateFile(fstream &division) {
	Division aDiv;
	division.open("division.dat", ios::out | ios::binary);
	if (division.fail())
	{
		cout << "Error on writing to student file!\n";
		system("PAUSE");
		return;
	}

	for (int i = 0; i < NUM_OF_DIVISIONS; i++) {
		cout << "Enter the name of the division: ";
		cin.getline(aDiv.divName, SIZE);
		for (int j = 0; j < 4; j++) {
			do
			{
				cout << "Enter the sales for quarter " << j + 1 << ": ";
				cin >> aDiv.sales[j];
				if (aDiv.sales[j] < 0)
					cout << "Negative sales are not allowed!\n";
			} while (cin && aDiv.sales[j] < 0);
		}
		cin.ignore();
		division.write(reinterpret_cast<char *>(&aDiv), sizeof(aDiv));
	}
	division.close();
}

void displayCorporateSales(fstream &division, ofstream& outs) {
	Division aDiv;
	division.open("division.dat", ios::in | ios::binary);
	if (division.fail())
	{
		cout << "Error on attempting to open file for reading!\n";
		system("PAUSE");
		return;
	}
	outs.open("results.txt", ios::out);
	outs << fixed << setprecision(2);
	for (int i = 0; i < NUM_OF_DIVISIONS; i++) {
		cout << fixed << setprecision(2);
		double sum = 0;
		division.read(reinterpret_cast<char *>(&aDiv), sizeof(aDiv));
		cout << "Here are the quarterly sales for division " << aDiv.divName << ":\n";
		outs << "Here are the quarterly sales for division " << aDiv.divName << ":\n";
		for (int j = 0; j < 4; j++) {
			outs << "       Quarter " << i + 1 << " Sales $" << aDiv.sales[j] << "\n";
			cout << "       Quarter " << i + 1 << " Sales $" << aDiv.sales[j] << "\n";
			sum += aDiv.sales[j];
		}
		cout << "\nTotal sales earned by the " << aDiv.divName << " division are $" << sum << "\n\n";
		outs << "\nTotal sales earned by the " << aDiv.divName << " division are $" << sum << "\n\n";
	}
	division.close();
	outs.close();
}