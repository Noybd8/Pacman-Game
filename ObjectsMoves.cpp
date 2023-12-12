#include "ObjectsMoves.h"

objectsMoves::objectsMoves(int numOfGhosts) {
	this->ghostsNumber = numOfGhosts;
}


void objectsMoves:: writeToString(char direction,int objectNum,int counter,char fruitValue,int fruitLocX,int fruitLocY) {
	if (objectNum == ghostsNumber + 1 && direction == 5) { // cheacked if pacman had strike
		results += "There Was a strike here:\n";
		results += to_string(counter);
		results += "\n";
	}
	else if (objectNum == ghostsNumber && counter != 0) {
		if (direction == 5) {
			fruitResults += "\nEaten\n";
		}
		else {
			fruitResults += "\ncreated\n";
			fruitResults += direction + '0';
			fruitResults += '\n';
		}
		fruitResults += to_string(counter) += " ";
		fruitResults += to_string(fruitValue) += " ";
		fruitResults += to_string(fruitLocX) += " ";
		fruitResults += to_string(fruitLocY) += " ";
		fruitResults += "\n";

	}
	else {
		if (culCounter[objectNum] == 100) {
			Moves[objectNum] += "\n";
			culCounter[objectNum] = 0;
		}
		Moves[objectNum] += direction + '0';
		this->culCounter[objectNum]++;
	}
}
int objectsMoves:: makeStringToInt(string s,int startingLoc,int endLoc){
	int result = 0;
	for (int i = startingLoc; i <= endLoc; i++) {
		result *= 10;
		result += s[i] + '0';
}
	return result;
}

void objectsMoves:: takeResultFromLine(string s, char value, int& locX, int& locY) {
	int curr;
	int count = 1;
	int lastloc = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			curr = makeStringToInt(s, lastloc, i - 1);
			switch (count) {
			case 1: // for the counter
				break;
			case 2:
				value = curr;
				lastloc = i + 1;
				break;
			case 3:
				locX = curr;
				lastloc = i + 1;
				break;
			case 4:
				locY = curr;
				lastloc = i + 1;
				break;
			default:
				break;
			}
			count++;
		}
	}
}
