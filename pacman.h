#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "GameObject.h"
#include "Board.h"

class Pacman : public GameObject {
private:
public:
	Pacman() {};
	Pacman(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int objectNum);
	void checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel);


};




#endif _PACMAN_H_
