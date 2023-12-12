#ifndef _BOARD_H
#define _BOARD_H
#include "tools.h"
class Board
{
private:
	bool fileChosen = false;
	int breadCount = 0;
	char** boardGame;
	int numOfRows;
	int numOfCul;
	int pacman_starting_position[2];
	int ghost_starting_position[4][2];
	int loc_of_legend[2];
	int numOfGhosts = 0;



public:
	Board() {};
	Board(const char* fileName);
	Board(const Board&) = delete;
	~Board();
	bool ifLegenedLastChar = false;
	int getNumOfRows() const { return this->numOfRows; }
	int getNumOfCul() const { return this->numOfCul; }
	char*** getBoardGame() { return &boardGame; }
	void printBoard();
	void buildBoard(const char* fileName);
	void goOverFile(const char* fileName);
	void buildRow(string s, int counter);
	void BuildLegendRow(string s, int counter);
	void Legend(int legened_loc_x, int legend_loc_y);
	void FillEmptySpots();
	char getCharInBoard(int x, int y) const { return this->boardGame[x][y]; }
	int getBreadCount() const { return this->breadCount; }
	void SetCharInBoard(int x, int y, char ch) { this->boardGame[x][y] = ch; }
	void buildRow(string s, int numLine, int len);
	void cheackAndRepairValidTunnels();
	int* get_Pacman_Starting_position() { return this->pacman_starting_position; }
	int* get_Ghost_Starting_position(int ghostNum) { return this->ghost_starting_position[ghostNum]; }
	int getNumOfGhost()const { return this->numOfGhosts; }
	int getLocOfLegendX()const { return this->loc_of_legend[0]; }
	int getLocOfLegendY()const { return this->loc_of_legend[1]; }


};


#endif _BOARD_H


	