#include "Menu.h"

char Menu::GetMenu() {
	std::cout << "Welcome to PacMan game" << endl;
	std::cout << "Choose option:" << endl;
	std::cout << "1. Start a new game" << endl;
	std::cout << "8. Rules and keys" << endl;
	std::cout << "9. EXIT" << endl;
	char KeyStroke = _getch();
	if (KeyStroke == '8') {
		printRulesAndKeys();
	}
	else if (KeyStroke == '1') {
		setGameLevel();
	}
	else if (KeyStroke != '1' && KeyStroke != '9') {
		cout << "not a valid choise" << endl;
	}
	else {
		this->endGame = true;
	}
	const char* d = UploadFile();
	this->FileName = d;

	return KeyStroke;

}
char* Menu::UploadFile() {
	string str;
	char* d;
	cout << "if you want to uploads file name please insert the file name." << endl;
	cout << "if you want to countinu press 'b' and then enter" << endl;
	cout << "please enter a valid fileName if not" << endl;
	cin >> str;
	int size = str.length();
	d = new char[size+1];
	if (str == "b" ) {
		this->mapChosen = false;
		strcpy_s(d, size + 1, str.c_str());
		return d;

	}
	this->mapChosen = true;
	//strcpy(d, str.c_str());
	strcpy_s(d, size+1, str.c_str());
	return d;

}

void Menu::printRulesAndKeys() {
	std::cout << "Welcome to PacMan game\n"
		"the rules are very simple:\n"
		"You are playing as the pacman, his symbol is: @ \nTo win the game you "
		"need to eat all the breadcrumbs that will shown as: .\n"
		"There are ghosts on the board they will shown as : $ \n"
		"The ghosts will try to catch you, if they succed you will lose 1 life "
		"There are fruits that going to be appear on the board"
		"you going to start with 3 lifes,\n"
		"If you lose all of them a notice will show that the game is over\n"
		"If you succed to eat all the breadcrumbs before your lifes are finished "
		"you will win the game.\n"
		"To go up you press: w\n"
		"To go down you press: x\n"
		"to go right you press: d\n"
		"To stay you press : s\n"
		"To go left you press: a\n"
		"To exit in any point of esc\n\n\n"
		"To countinue to the game please press 1" << endl;
	char getKey = 'c';
	while (getKey != '1') {
		getKey = _getch();
	}
	setGameLevel();
}

void Menu::setGameLevel() {
	std::cout << "To start the game please choose one of the option:\n"
		"1.For easy mode : The Ghost will move randomly in the board.\n"
		"2.For medium mode: The ghost will chase the PacMan but evrey 20 move he will change they direction randomly for 5 moves\n"
		"3.For hard mode: the ghost consistnly will chase the PacMan\n"
		"Please enter your choise by the numbers:" << endl;
	char KeyStroke = _getch();
	while (KeyStroke > 3 && KeyStroke < 1) {
		cout << "not a valid option please choose valid option" << endl;
		char KeyStroke = _getch();
	}
	int gameLevel = KeyStroke - '0';
	this->gameLevel = gameLevel;

}
int Menu::getGameLevel() {
	return this->gameLevel;
}

