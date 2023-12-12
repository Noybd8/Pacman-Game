
#include "GameManager.h"
#include <filesystem>

string makeString() {
	string i = "hello";
	i += " world";
	return i;
}

void main(int argc, char** argv)
{
	srand((unsigned)time(0));
	if (argv[1]) {
		if (strcmp(argv[1], "-load") == 0)
		{
			if (argv[2]) {
				if (strcmp(argv[2], "[-silent]") == 0)
				{
					GameManager g = GameManager(true);
					g.run(true, true);
				}
			}
			else
			{
				GameManager g = GameManager(true);
				g.run(true, false);
			}
		}
		else if (strcmp(argv[1], "-save") == 0)
		{
			GameManager g = GameManager(false);
			g.run(false, false);
		}
		else {
			cout << "wrong input" << endl;
			return;
		}
	}
	else {
		GameManager g = GameManager(false);
		g.run(false, false);
	}
		



	




    
	
	
}
