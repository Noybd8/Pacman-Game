#include "Board.h"
#include "tools.h"
Board::~Board() {
	for (int i = 0; i < numOfRows; i++)
	{
		delete[] boardGame[i];
	}
	delete[] boardGame;
}
Board::Board(const char* fileName) {
	buildBoard(fileName);
}

void Board::buildBoard(const char* fileName) {
	int counter = 0;
	std::string line;
	goOverFile(fileName);
	std::ifstream file(fileName, std::ios::in);
	while (!file.eof())
	{
		getline(file, line);
		buildRow(line, counter);
		counter++;

	}
	Legend(this->loc_of_legend[0], this->loc_of_legend[1]);
	file.close();
	if (ifLegenedLastChar) {
		FillEmptySpots();
	}
	cheackAndRepairValidTunnels();
	this->breadCount += numOfGhosts + 1; 
}

void Board::goOverFile(const char* fileName)
{
	std::ifstream file(fileName, ios::in);
	if (file.fail()) {
		std::cout << "Couldn't open file. try different file name" << endl;
		string str;
		cin >> str;
		buildBoard(str.c_str());
	}
	int numLines = 0;
	int width = 0;
	std::string line;
	while (!file.eof()) {
		std::getline(file, line);

		if (numLines == 0)
			width = line.length();
		numLines++;
	}
	file.seekg(-1, ios::end);
	char ch;
	file >> ch;
	if (ch == '&') {
		numLines += 2;
		this->ifLegenedLastChar = true;

	}

	this->boardGame = new char* [numLines];
	for (int i = 0; i < numLines; i++)
	{
		boardGame[i] = new char[width];
	}
	this->numOfCul = width;
	this->numOfRows = numLines;

	file.close();
}
void Board::FillEmptySpots() {
	for (int j = 0; j < 3; j++) {
		for (int i = 20 + this->loc_of_legend[1]; i < this->numOfCul; i++) {
			this->boardGame[this->numOfRows - 3 + j][i] = ' ';
		}
	}
}
void Board::Legend(int legened_loc_x, int legend_loc_y) {
	for (int x = legened_loc_x; x < legened_loc_x + 3; x++) {
		for (int y = legend_loc_y; y < legend_loc_y + 20; y++) {
			boardGame[x][y] = 'X';
		}
	}

}
void Board::BuildLegendRow(string s, int counter) {
	char* newStr = new char[numOfCul];
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		newStr[i] = s[i];
	}
	for (int i = len; i < numOfCul; i++)
	{
		newStr[i] = ' ';
		this->breadCount -= 1;
	}
	buildRow(newStr, counter);


}


void Board::buildRow(string s, int counter) {
	if (s.length() < this->numOfCul) {
		BuildLegendRow(s, counter);
	}
	else {
		for (int i = 0; i < this->numOfCul; i++) {
			if (s[i] == '&') {
				this->loc_of_legend[0] = counter;
				this->loc_of_legend[1] = i;
			}


			if (s[i] == ' ') {
				if (counter == 0 || counter == numOfRows - 1 || i == 0 || i == numOfCul - 1) {
					boardGame[counter][i] = '~';
				}
				else {
					boardGame[counter][i] = '.';
					this->breadCount++;
				}
			}
			if (s[i] == '@') {
				this->boardGame[counter][i] = '@';
				this->pacman_starting_position[0] = counter;
				this->pacman_starting_position[1] = i;

			}
			if (s[i] == '$') {
				if (numOfGhosts >= 4) {
					this->boardGame[counter][i] = '.';
				}
				else {
					this->boardGame[counter][i] = '$';
					this->ghost_starting_position[numOfGhosts][0] = counter;
					this->ghost_starting_position[numOfGhosts][1] = i;
					numOfGhosts++;
				}
			}
			if (s[i] == '%') {
				this->boardGame[counter][i] = ' ';
			}
			if (s[i] == '#') {
				this->boardGame[counter][i] = '#';
			}
		}
	}
}
void Board::printBoard()
{
	gotoxy(0, 0);
	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCul; j++)
		{
			if (this->boardGame[i][j] == 'X') {
				cout << ' ';
			}
			else {
				cout << this->boardGame[i][j];
			}
		}
		cout << endl;
	}

}
void Board::cheackAndRepairValidTunnels() {
	for (int j = 0; j < this->numOfCul; j++) {
		if ((boardGame[0][j] == '~' && boardGame[this->numOfRows - 1][j] != '~') || (boardGame[0][j] != '~' && boardGame[this->numOfRows - 1][j] == '~')) {
			this->boardGame[0][j] = '#';
			this->boardGame[this->numOfRows - 1][j] = '#';
		}
	}
	for (int i = 0; i < this->numOfRows; i++) {
		if ((boardGame[i][0] == '~' && boardGame[i][numOfCul - 1] != '~') || (boardGame[i][0] != '~' && boardGame[i][numOfCul - 1] == '~')) {
			this->boardGame[i][0] = '#';
			this->boardGame[i][this->numOfCul - 1] = '#';
		}
	}
}





