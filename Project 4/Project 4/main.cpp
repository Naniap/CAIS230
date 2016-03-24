#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

double* getScores(string*, int);
string* getStudentNames(int&);
void sort(string*, double*, int);
void displaySortedListAndAverageScore(string*, double*, int);
fstream outs;

int main() {
	outs << fixed << setprecision(2);
	cout << fixed << setprecision(2);
	outs.open("results.txt", ios::out);
	int numTestScores;
	string* namesPtr = getStudentNames(numTestScores);
	double* scoresPtr = getScores(namesPtr, numTestScores);
	cout << "                  Unsorted list\n---------------------------------------------------\n";
	outs << "                  Unsorted list\n---------------------------------------------------\n";
	for (int i = 0; i < numTestScores; i++) {
		cout << "                  " << namesPtr[i] << "\t" << scoresPtr[i] << "%\n";
		outs << "                  " << namesPtr[i] << "\t" << scoresPtr[i] << "%\n";
	}
	sort(namesPtr, scoresPtr, numTestScores);
	system("PAUSE");
}
string* getStudentNames(int& numTestScores) {
	cout << "Enter number of students in class: ";
	cin >> numTestScores;
	string* temp;
	temp = new string[numTestScores];
	cin.ignore();
	for (int i = 0; i < numTestScores; i++) {
		cout << "Enter name of student: ";
		getline(cin, temp[i]);
	}
	return temp;
}
double* getScores(string* namesPtr, int numTestScores) {
	double* ptr = new double[numTestScores];
	for (int i = 0; i < numTestScores; i++) {
		cout << "Enter grade of student " << namesPtr[i] << ": ";
		cin >> ptr[i];
	}
	return ptr;
}
void sort(string *names, double *score, int size)
{
	int startScan, minIndex;
	string minName;
	double minValue;

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		minValue = score[startScan];
		minName = names[startScan];

		for (int index = startScan + 1; index < size; index++)
		{
			if (score[index] < minValue)
			{
				minValue = score[index];
				minName = names[index];
				minIndex = index;
			}
		}

		score[minIndex] = score[startScan];
		names[minIndex] = names[startScan];

		score[startScan] = minValue;
		names[startScan] = minName;
	}
	displaySortedListAndAverageScore(names, score, size);
}
void displaySortedListAndAverageScore(string* namesPtr, double* testScorePtr, int numTestScores) {
	cout << fixed << setprecision(2);
	double sum = 0;
	cout << "\n                  Sorted List\n---------------------------------------------------\n";
	outs << "\n                  Sorted List\n---------------------------------------------------\n";
	for (int i = 0; i < numTestScores; i++) {
		cout << "                  " << namesPtr[i] << "\t" << testScorePtr[i] << "%\n";
		outs << "                  " << namesPtr[i] << "\t" << testScorePtr[i] << "%\n";
		sum += testScorePtr[i];
	}
	cout << "\nThe class average is: " << sum / numTestScores << "%\n";
	outs << "\nThe class average is: " << sum / numTestScores << "%\n";
	outs.close();
}