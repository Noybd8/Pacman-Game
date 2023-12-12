#include "pacman.h"
Pacman::Pacman(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int objectNum)
	:GameObject(locationX, locationY, ch, direction, map, numOfRows, numOfCuls, objectNum) {
}
void Pacman::checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel) {
	char nextChar = this->getCharInMap(chosen_x, chosen_y);
	if (nextChar == '#' || nextChar == 'X' || chosen_x < 0 || chosen_y < 0 || chosen_x > this->getNumOfRows() - 1 || chosen_y>this->getNumOfCol() - 1) {
		move('s', x, y);
	}
	else
	{
		x = chosen_x;
		y = chosen_y;
		this->set_direction(direction);
	}
}
