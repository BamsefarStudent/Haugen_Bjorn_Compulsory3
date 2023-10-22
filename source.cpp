#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

#include "header.h"

int main()
{
	bool runningProgram = true;

	while (runningProgram)
	{
		runningProgram = AskUserForAction();

		WriteCurrentPath();
	}

	return 0;
}