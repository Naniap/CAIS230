/*
Michael Coache									CAIS 230
This program starts with taking 5 name (string) and 5 vote (integer) inputs and then calculates the result of the election and displays both to console and an output file.
The output consists of a the name of the person running, how many votes the person has, percentage of total votes, total votes and the election winner.
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int NUM_OF_CANDIDATES = 5;
string names[NUM_OF_CANDIDATES];
int votes[NUM_OF_CANDIDATES];
// prototypes 
void getNameVotes();
int getCandidateWinner(int votes[]);
int totalVotes(string nanes[], int votes[]);
void displayInfo();
void reportResults(string names[], int votes[], int winner);

int main() {
	displayInfo();
	getNameVotes();
	reportResults(names, votes, getCandidateWinner(votes));
	system("PAUSE");
	return 0;
}
void getNameVotes() {
	for (int i = 0; i < NUM_OF_CANDIDATES; i++) {
		cout << "Enter a name: ";
		getline(cin, names[i]);
		cout << "Enter number of votes: ";
		cin >> votes[i];
		cin.ignore();
	}
}
void displayInfo() {
	cout << "Welcome to the election result calculator.\nYou will be prompted to enter one name at a time and then prompted for votes for that specific person."
	     << "\nAfter you have entered all that information a tally will be presented giving percentages as well as other infomation.\nOutput will also be saved to a file relative to your directory with outputs.\n";
}
int totalVotes(string names[NUM_OF_CANDIDATES], int votes[NUM_OF_CANDIDATES]) {
	int sum = 0;
	for (int i = 0; i < NUM_OF_CANDIDATES; i++) {
		sum += votes[i];
	}
	return sum;
}
int getCandidateWinner (int votes[NUM_OF_CANDIDATES]) {
	int winnerVotes = 0;
	int winnerIndex = 0;
	for (int i = 0; i < NUM_OF_CANDIDATES; i++) {
		if (votes[i] > winnerVotes) {
			winnerVotes = votes[i];
			winnerIndex = i;
		}
	}
	return winnerIndex;
}
void reportResults(string names[NUM_OF_CANDIDATES], int votes[NUM_OF_CANDIDATES], int winner) {
	ofstream outs;
	outs.open("output.txt", ofstream::out);
	int total = totalVotes(names, votes);
	outs << "Name of Candidate" << setw(27) << "Votes Received" << setw(24) << "% of Total Votes" << endl;
	outs << "-----------------" << setw(27) << "--------------" << setw(24) << "-----------------" << endl;
	cout << "Name of Candidate" << setw(27) << "Votes Received" << setw(24) << "% of Total Votes" << endl;
	cout << "-----------------" << setw(27) << "--------------" << setw(24) << "-----------------" << endl;
	for (int i = 0; i < NUM_OF_CANDIDATES; i++) {
		int space = names[i].size();
		cout << fixed << setprecision(1);
		outs << fixed << setprecision(1);
		cout << names[i] << setw(40 - space) << votes[i] << setw(22) << static_cast<double>(votes[i]) / total * 100.0 << "\%" << endl;
		outs << names[i] << setw(40 - space) << votes[i] << setw(22) << static_cast<double>(votes[i]) / total * 100.0 << "\%" << endl;
	}
	cout << "Total Votes                " << total << endl;
	cout << "Winner of Election         " << names[getCandidateWinner(votes)] << endl;
	outs << "Total Votes                " << total << endl;
	outs << "Winner of Election         " << names[getCandidateWinner(votes)] << endl;
	outs.close();
}