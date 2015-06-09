#pragma once
#include "TownMap.h"
class TownMapUI
{
	TownMap map;
public:
	TownMapUI();
	
	void run();

	void printMenu() const;

	void openFile();

	void shortestPathBetween();
	void shortestPathTo();

	void checkPathBetween();
	void checkPathTo();

	void checkCycleWith();
	void checkCycle();

	void countDeadends();

	void checkEuler();
	void updateStreetStatus();

	void changePosition();
	void tellPosition();
private:
	void printError() const;
	bool validate(CrossPoint) const;
};

