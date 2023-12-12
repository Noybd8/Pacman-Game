#ifndef _OBJECTSMOVES_
#define _OBJECTSMOVES_
#include "tools.h"

class objectsMoves {
private:
	string Moves[6]; //taking the worst case that there is 4 ghosts.
	//similar to the GameManager ea ghost will be with his number the fruit will be in [ghostNum] and the pacman will be in [ghostNum + 1].
	string results; // for pacman
	string fruitResults;
	int ghostsNumber;
	int culCounter[6] = {0,0,0,0,0,0}; // in ea Line we will cheack that there are no more than 100 ch writen to single row in the txt
	string winningTime;

public:
	objectsMoves() {};
	objectsMoves(int numOfGhosts);
	string getSringByLoc(int i) { return Moves[i]; }
	string getResults() { return results; }
	void writeToString(char direction, int objectNum, int counter = 0, char fruitValue = 1, int fruitLocX = 1, int fruitLocY = 1);
	string getFruitResult() { return fruitResults; }
	void takeResultFromLine(string s, char value, int& locX, int& locY);
	int makeStringToInt(string s, int startingLoc, int endLoc);
	void TakeWinningTime(int counter) { this->winningTime = to_string(counter); }
	string getWinningTime() { return this->winningTime; }


};


#endif _OBJECTSMOVES_

