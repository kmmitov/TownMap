#include "TownMapUI.h"
using namespace std;
#include <string>

const int EXIT_CODE = 13;

TownMapUI::TownMapUI()
	:map(cout)
{
}


void TownMapUI::run()
{
	cout << "Welcome to TownMapForU! The following menu presents the options available to you.";
	cout << " If you need to recall them, enter help.\n";
	printMenu();
	openFile();
	int choice = 1;
	do
	{
		char c = cin.peek();
		while(c == '\n')
		{
			cin.get();
			c = cin.peek();
		}
		if(c >= '0' && c <= '9')
		{
			cin >> choice;
			switch(choice)
			{
			case 1: openFile(); break;
			case 2: shortestPathBetween(); break;
			case 3: shortestPathTo(); break;
			case 4: checkPathBetween(); break;
			case 5: checkPathTo(); break;
			case 6: checkCycleWith(); break;
			case 7: checkCycle(); break;
			case 8: countDeadends(); break;
			case 9: checkEuler(); break;
			case 10: updateStreetStatus(); break;
			case 11: changePosition(); break;
			case 12: tellPosition(); break;
			case EXIT_CODE: break;
			default: cerr << "Invalid command! Press help to see menu options!" << endl;
			}
		} else
		{
			string command;
			cin >> command;
			if(command == "help")
			{
				printMenu();
			}
			else
			{
				cerr << "Invalid command! Press help to see menu options!" << endl;
			}
		}
	} while(choice != EXIT_CODE);
	
	exit(0);
}


void TownMapUI::openFile()
{
	string fileName;
	cout << "Please enter file name: ";
	cin >> fileName;
	map.deserialize(fileName);
	cout << "Loading complete!" << endl;
}

void TownMapUI::shortestPathBetween()
{
	CrossPoint first, second;
	cout << "Enter start crossroads: ";
	cin >> first;
	cout << "Enter end crossroads: ";
	cin >> second;
	if(validate(first) && validate(second))
	{
		map.shortestPath(first,second);
	}
	else
	{
		printError();
	}
}

void TownMapUI::tellPosition()
{
	cout << "Current position is: " << map.getCurrent() << endl;
}

void TownMapUI::shortestPathTo()
{
	CrossPoint other;
	cout << "Enter destination point: ";
	cin >> other;
	if(validate(other))
	{
		map.shortestPathTo(other);
	}
	else
	{
		printError();
	}
}

void TownMapUI::checkPathBetween()
{
	CrossPoint first, second;
	cout << "Enter start crossroads: ";
	cin >> first;
	cout << "Enter end crossroads: ";
	cin >> second;
	if(validate(first) && validate(second))
	{
		map.checkPath(first,second);
	}
	else
	{
		printError();
	}
}

void TownMapUI::checkPathTo()
{
	CrossPoint other;
	cout << "Enter destination point: ";
	cin >> other;
	if(validate(other))
	{
		map.checkPathTo(other);
	}
	else
	{
		printError();
	}
}

void TownMapUI::checkCycleWith()
{
	CrossPoint other;
	cout << "Enter start point: ";
	cin >> other;
	if(validate(other))
	{
		map.checkForCycle(other);
	}
	else
	{
		printError();
	}
}

void TownMapUI::checkCycle()
{
	map.checkForCycle();
}

void TownMapUI::checkEuler()
{
	map.checkForEulerPath();
}

void TownMapUI::updateStreetStatus()
{
	CrossPoint start, end;
	cout << "Enter start of street: ";
	cin >> start;
	cout << "Enter end of street: ";
	cin >> end;
	int status;
	cout << "Press 0 if repairs are over, 1 if they are beginning: ";
	cin >> status;
	if(validate(start) && validate(end))
	{
		if(status)
			map.startRepairs(start,end);
		else
			map.endRepairs(start,end);
	}
	else
	{
		printError();
	}
}

void TownMapUI::changePosition()
{
	CrossPoint newPosition;
	cout << "Please enter new desired position: ";
	cin >> newPosition;
	if(validate(newPosition))
	{
		map.goTo(newPosition);
	}
	else
	{
		printError();
	}
}

void TownMapUI::countDeadends()
{
	map.tellDeadends();
}

void TownMapUI::printMenu() const
{
	cout << "\n\n";
	cout << "You can choose one of the following options: "<<endl;
	cout << "1. Load map from file" << endl;
	cout << "2. Find shortest path between crosspoints: " << endl;
	cout << "3. Go somewhere along shortest path from current position: " << endl;
	cout << "4. Check for path between two positions: " << endl;
	cout << "5. Check for path from current position: " << endl;
	cout << "6. Check for a cycle tour containing vertex:" << endl;
	cout << "7. Check for a cycle tour from current position:"<<endl;
	cout << "8. Calculate number of deadends in town: "<<endl;
	cout << "9. Check for a cycle through all streets with no repetitions: "<<endl;
	cout << "10. Update info for street repair status: "<<endl;
	cout << "11. Change current position: "<<endl;
	cout << "12. Show current position: " << endl;
	cout << "13. Exit" <<endl; 
}

void TownMapUI::printError() const
{
	cerr << "Invalid input! You must enter a correct crosspoint name!" << endl;
}

bool TownMapUI::validate(CrossPoint p) const
{
	return map.validateCrossPoint(p);
}