#pragma once

#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _STRING_
#include <string>
#endif

using namespace std;


#pragma region Forward Declaration


int GetCinInt(const char* c);
string GetCinStr(const char* c);
bool CheckForCinFail();


#pragma endregion



/// <summary>
/// Loops until user inputs an integer
/// </summary>
/// <param name="c">- text to print out to user</param>
/// <returns>int</returns>
int GetCinInt(const char* c)
{
	int num;
	bool notNum = true;

	while (notNum)
	{
		cout << c;
		cin >> num;

		if (!CheckForCinFail())
		{
			notNum = true;
		}
		else notNum = false;
	}

	return num;
}

/// <summary>
/// Loops until user inputs an accepted string
/// </summary>
/// <param name="c">- text to print out to user</param>
/// <returns>string</returns>
string GetCinStr(const char* c)
{
	string str;
	bool accepted = false;

	while (!accepted)
	{
		cout << c;
		cin >> str;

		if (!CheckForCinFail())
		{
			accepted = false;
		}
		else accepted = true;
	}

	return str;
}

/// <summary>
/// Checks if std::cin fails to run correctly, and clears the input
/// </summary>
/// <returns>bool - Whether std::cin failed to run</returns>
bool CheckForCinFail()
{
	if (std::cin.fail())
	{
		std::cout << "That is not a valid option! \n\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		return false;
	}

	return true;
}