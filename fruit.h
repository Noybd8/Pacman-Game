#ifndef _FRUIT_H
#define _FRUIT_H
#include "GameObject.h"

class Fruit : public GameObject {
	char fruitValue;

public:
	Fruit() {};
	Fruit(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int objectNum);
	void checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel = 1);
	void createRandomLocation();
	char createRandomValue();
	char getFruitValue() const{ return this->fruitValue; }


};




#endif _FRUIT_H
