/****************************************************************************
file Proj5.cpp		CAIS 230				Author:

PROGRAM  FARMER BROWN
=======  ============
Detailed Description of the program to the reader goes here.

********************************************************************************************/


#include<iostream>
#include<cctype>
#include<cstdlib>
#include<iomanip>
using namespace std;

struct Nodetype;
typedef Nodetype* Nodeptr;

struct Nodetype
{
	char bank;
	char name;
	int position;
	int numnodes;
	Nodeptr Right, Left;
};

int main()
{
	//I have provided you with the main function!

	Nodeptr EastList, WestList;
	char farmer_bank;
	char To_Bank, From_Bank;

	bool game_over = false;
	//Prototype functions used
	void DescribeProgram();
	Nodeptr InitializeHeader(char bank);
	void CreateList(Nodeptr Head);
	void PrintList(Nodeptr Head);
	void Deletenode(Nodeptr Head, char thing);
	Nodeptr Search(Nodeptr Head, char thing);
	bool Empty(Nodeptr Head);
	void CheckList(Nodeptr EastList, Nodeptr WestList, char farmer_bank, bool& game_over);
	void MakeMove(Nodeptr EastList, Nodeptr WestList, char& To_Bank, char& From_Bank, char& farmer_bank);
	DescribeProgram();
	EastList = InitializeHeader('E');
	WestList = InitializeHeader('W');
	//Create the list on the East Bank
	cout << "Okay, Farmer Brown, put your Chicken, Fox, and Grain on the East Bank, \n"
		<< "but be very, very careful!\n\n";
	CreateList(EastList);
	To_Bank = 'W';
	From_Bank = 'E';
	farmer_bank = 'E';
	cout << "Here are your entries for the East Bank:\n";
	PrintList(EastList);
	cout << "Here are your entries for the West Bank:\n";
	PrintList(WestList);
	while (!game_over)
	{
		MakeMove(EastList, WestList, To_Bank, From_Bank, farmer_bank);
		cout << "Here are your entries for the East Bank:\n";
		PrintList(EastList);
		cout << "Here are your entries for the West Bank:\n";
		PrintList(WestList);
		CheckList(EastList, WestList, farmer_bank, game_over);
	}


	system("PAUSE");
	return 0;
}

void DescribeProgram()
{

	return;
}

Nodeptr InitializeHeader(char bank)
{
	Nodeptr q;
	q = new Nodetype;
	q->Right = q;
	q->Left = q;
	q->numnodes = 0;
	q->position = 0;
	return q;
}

void CreateList(Nodeptr Head)
{
	Nodeptr p, q;
	for (int i = 0; i < 3; i++)
	{
		q = new Nodetype;
		switch (i) {
		case 0:
			q->name = 'C';
			break;
		case 1:
			q->name = 'G';
			break;
		case 2:
			q->name = 'F';
			break;
		}
		q->position = i;
		p = Head->Left;
		q->Right = Head;
		q->Left = p;
		p->Right = q;
		Head->Left = q;
		Head->numnodes++;
	}
	cout << "Farmer now has Chicken, Fox, and Grain on the East Bank!\n\n";
}


void PrintList(Nodeptr Head)
{
	Nodeptr p;
	bool Empty(Nodeptr List);

	p = Head;
	if (Empty(Head))
		cout << "Empty List!" << endl;
	else
	{
		do
		{
			p = p->Right;
			cout << p->name << " ";
		} while (p->Right != Head);
	}
	cout << endl;
}

Nodeptr Search(Nodeptr Head, char thing)
{
	bool found = false;
	Nodeptr p;
	bool Empty(Nodeptr List);

	if (Empty(Head))
		return NULL;
	else
	{
		p = Head->Right;
		do
		{
			if (thing == p->name)
				found = true;
			else
				p = p->Right;

		} while (!found && (p != Head));
		if (p != Head)
			return p;
		else
			return NULL;
	}
}


bool Empty(Nodeptr Head)
{
	if ((Head->Right == Head) && (Head->Left == Head))
		return true;
	else
		return false;
}

void Deletenode(Nodeptr Head, char thing)
{
	int count;
	Nodeptr p;
	Nodeptr Search(Nodeptr List, int id);
	bool Empty(Nodeptr List);

	if (Empty(Head))
		cout << "Empty List!" << endl;
	else
	{
		p = Search(Head, thing);
		if (p == NULL)
			cout << "The thing is not in the list!" << endl;
		else
		{
			p->Left->Right = p->Right;
			p->Right->Left = p->Left;
			delete p;
			Head->numnodes--;
			p = Head->Right;
			count = 0;
			while (p != Head)
			{
				count++;
				p->position = count;
				p = p->Right;
			}
		}
	}
}

void MakeMove(Nodeptr EastList, Nodeptr WestList, char& To_Bank, char& From_Bank, char& farmer_bank)
{
	int count = 0;
	char thing;
	Nodeptr p, q, r;
	bool Empty(Nodeptr Head);
	Nodeptr Search(Nodeptr Head, char thing);
	void Deletenode(Nodeptr Head, char thing);
	do {
		cout << "Enter which bank you wish to cross to \"W\" or \"E\": ";
		cin >> To_Bank;
	} while (toupper(To_Bank) != 'E' && toupper(To_Bank) != 'W');
	if (farmer_bank != To_Bank) {
		do {
			cout << "Enter what you want to bring with you, type \"N\" for nothing: ";
			cin >> thing;
		} while (toupper(thing) != 'C' && toupper(thing) != 'F' && toupper(thing) != 'G' && toupper(thing) != 'N');

		if (toupper(To_Bank) == 'W' && !Search(WestList, thing)) {
			farmer_bank = 'W';
			if (toupper(thing) != 'N') {
				q = new Nodetype;
				q->name = toupper(thing);
				q->position = WestList->numnodes;
				p = WestList->Left;
				q->Right = WestList;
				q->Left = p;
				p->Right = q;
				WestList->Left = q;
				WestList->numnodes++;
			}
			Deletenode(EastList, toupper(thing));
		}
		else if (toupper(To_Bank) == 'E' && !Search(EastList, thing)) {
			farmer_bank = 'E';
			if (toupper(thing) != 'N') {
				q = new Nodetype;
				q->name = toupper(thing);
				q->position = EastList->numnodes;
				p = EastList->Left;
				q->Right = EastList;
				q->Left = p;
				p->Right = q;
				EastList->Left = q;
				EastList->numnodes++;
			}

			Deletenode(WestList, toupper(thing));
		}
		else
			cout << "That is an invalid movement!\n";
	}
	else
		cout << "\nYou are already on that side of the bank...\n\n";
}

void CheckList(Nodeptr EastList, Nodeptr WestList, char farmer_bank, bool& game_over)
{
	cout << "*****" << farmer_bank << "*****" << endl;
	if (farmer_bank == 'W' && Empty(WestList)) {
		game_over = true;
		cout << "\nSorry, you lost!\n";
	}
	else if (farmer_bank == 'W' && (Search(EastList, 'C') && Search(EastList, 'F')) || (farmer_bank == 'W' && Search(EastList, 'C') && Search(EastList, 'G'))) {
		game_over = true;
		cout << "\nSorry, you lost!\n";
	}
	else if (farmer_bank == 'E' && (Search(WestList, 'C') && Search(WestList, 'F')) || farmer_bank == 'E' && (Search(WestList, 'C') && Search(WestList, 'G'))) {
		game_over = true;
		cout << "\nSorry, you lost!\n";
	}
	if (Empty(EastList)) {
		cout << "\nCongratulations! You won!\n";
		game_over = true;
	}
}
