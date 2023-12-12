#ifndef _GHOST_H
#define _GHOST_H
#include "GameObject.h"
class Ghost : public GameObject {
private:
	int gameLevel;
	int ghostNum;
	int smartDirection[2];
	bool gotStuck = false;
	int newSmartDirection[2];
	int pacmamLoc[2];
	int moveCounter = 1;
	bool goDumb = false;
	int stuckCounter = 0;
public:
	Ghost() {};
	Ghost(int locationX, int locationY, char ch, char direction, char*** map, int numOfRows, int numOfCuls, int level, int ghostNum);
	int chooseLastDirection();
	void moveGhost(char direction, int& nextLoc_x, int& nextLoc_Y, int currentLevel);
	void move(char direction, int& x, int& y);
	void Level_1_move(char direction, int& x, int& y);
	void Level_2_move(char direction, int& x, int& y);
	void Level_3_move(char direction, int& x, int& y);
	int takeDierctionByPacmanLoc(int pacman_Loc_x, int pacman_Loc_y);
	int ChooseDirectionWhileStuck(int direction_1, int direction_2);
	void checkValidMove(int& x, int& y, int chosen_x, int chosen_y, char direction, int currentLevel);
	int get_moveCounter() const { return this->moveCounter; }
	void set_moveCounter(int x) { this->moveCounter = x; }
	void set_pacmanLoc(int x, int y) { this->pacmamLoc[0] = x; this->pacmamLoc[1] = y; }



};



#endif  _GHOST_H


