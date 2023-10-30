#pragma once

#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _WINDOWS.H_
#include <windows.h>
#endif
#ifndef _CINFUNCTIONS_
#include "cinfunctions.h"
#endif
#ifndef _STRING_
#include <string>
#endif

using namespace std;

#ifndef SUBFOLDERCOUNT
#define SUBFOLDERCOUNT 5
#endif
#ifndef SUBFILECOUNT
#define SUBFILECOUNT 10
#endif


#pragma region Forward Declaration

class File;
class Folder;

string GetNameOfFolderForFile(Folder* folder);
void RemoveFileIndexForFile(Folder* parent, int index);

bool AskUserForAction();
void NewFolder();
void NewFile();
void EnterFolder();
void ExitFolder();
void GetFileInfo();
void GetLargestFile();
void ChangeFolderName();
void ChangeFileName();
void RemoveFolder();
void RemoveFile();


#pragma endregion


Folder* currentFolder = 0;

class File
{
	string name;
	float size = rand() % (101);
	float creationDate;

	Folder* parentFolder = 0;
	int index = -1;

public:
	/// <summary>
	/// Constuctor for the File class
	/// </summary>
	/// <param name="name"></param>
	/// <param name="size"></param>
	/// <param name="creationDate"></param>
	/// <param name="parentFolder"></param>
	File(string name = "", float size = rand() % (101), float creationDate = 0, Folder* parentFolder = 0, int index = -1)
	{
		this->name = name;
		this->size = size;
		this->creationDate = creationDate;
		this->parentFolder = parentFolder;
		this->index = index;
	}

	/// <summary>
	/// Returns name of File
	/// </summary>
	/// <returns>string - name</returns>
	string GetName()
	{
		return name;
	}

	/// <summary>
	/// Returns path to File
	/// </summary>
	/// <returns>string - path</returns>
	string GetPathName()
	{
		if (parentFolder != 0)
		{
			//Program doesn't run if I write 'return parentFolder->GetPathName() + name + "\\"', so I've made another function that does it for me
			return GetNameOfFolderForFile(parentFolder) + name + "\\";
		}
		else return name + "\\";
	}

	/// <summary>
	/// Returns File size
	/// </summary>
	/// <returns>float - File size</returns>
	float GetSize()
	{
		return size;
	}

	/// <summary>
	/// Returns the creation date of File
	/// </summary>
	/// <returns>float - creation date</returns>
	float GetDate()
	{
		return creationDate;
	}

	/// <summary>
	/// Prints all primary info of the file to the console
	/// </summary>
	void PrintInfo()
	{
		cout << "Name: " << name << "\n"
			<< "Path: " << GetPathName() << "\n"
			<< "Size: " << size << "\n"
			<< "Date: " << creationDate << "\n" << endl;
	}

	/// <summary>
	/// Sets File name to input
	/// </summary>
	/// <param name="name"></param>
	void SetName(string name)
	{
		this-> name = name;
	}

	/// <summary>
	/// Deallocates this File's memory
	/// </summary>
	void Delete()
	{
		cout << "DELETING " << GetPathName() << "..." << endl;

		if (parentFolder != 0) RemoveFileIndexForFile(parentFolder, index);

		delete this;
	}
};

class Folder
{
	string name;
	float size = rand() % (101);
	float creationDate;

	Folder* subFolders[SUBFOLDERCOUNT] = { 0 };
	File* subFiles[SUBFILECOUNT] = { 0 };

	Folder* parentFolder = 0;
	int index = -1;

public:

	/// <summary>
	/// Constructor for the Folder class
	/// </summary>
	/// <param name="name"></param>
	/// <param name="size"></param>
	/// <param name="creationDate"></param>
	/// <param name="parentFolder"></param>
	/// <param name="index">-> Index in subFolders[] variable of the parent Folder</param>
	Folder(string name = "", float size = rand() % (101), float creationDate = 0, Folder* parentFolder = 0, int index = -1)
	{
		this->name = name;
		this->size = size;
		this->creationDate = creationDate;
		this->parentFolder = parentFolder;
		this->index = index;
	}

	/// <summary>
	/// Returns name of Folder
	/// </summary>
	/// <returns>string - name</returns>
	string GetName()
	{
		return name;
	}

	/// <summary>
	/// Returns path to Folder
	/// </summary>
	/// <returns>string - path</returns>
	string GetPathName()
	{
		if (parentFolder != 0)
		{
			return parentFolder->GetPathName() + name + "\\";
		}
		else return name + "\\";
	}

	/// <summary>
	/// Returns names of all sub Folders
	/// </summary>
	/// <param name="writeIndex"> -> Writes index before the name of every sub Folder</param>
	/// <param name="indexOffset"> -> Added to the printed index</param>
	/// <returns>string - sub Folder names</returns>
	string GetSubFolderNames(bool writeIndex = true, int indexOffset = 0)
	{
		string str;
		int i = 0;

		for (Folder* folder : subFolders)
		{
			if (writeIndex) str += to_string(i + indexOffset) + " ";

			if (folder != 0)
			{
				str += "'" + folder->GetName() + "'\n";
			}
			else str += "[empty]\n";

			i++;
		}

		return str;
	}

	/// <summary>
	/// Returns names of all Files in the folder
	/// </summary>
	/// <param name="writeIndex">-> Writes index before the name of every File</param>
	/// <param name="indexOffset">-> Added to the printed index</param>
	/// <returns>string - File names</returns>
	string GetFileNames(bool writeIndex = true, int indexOffset = 0)
	{
		string str;
		int i = 0;

		for (File* file : subFiles)
		{
			if (writeIndex) str += to_string(i + indexOffset) + " ";

			if (file != 0) str += "'" + file->GetName() + "'\n";
			else str += "[empty]\n";

			i++;
		}

		return str;
	}

	/// <summary>
	/// Returns Folder size
	/// </summary>
	/// <returns>float - size</returns>
	float GetSize()
	{
		return size;
	}

	/// <summary>
	/// Returns Folder creation date
	/// </summary>
	/// <returns>float - creation date</returns>
	float GetDate()
	{
		return creationDate;
	}

	/// <summary>
	/// Returns pointer to parent Folder
	/// </summary>
	/// <returns>Folder* - parent Folder</returns>
	Folder* GetParent()
	{
		return parentFolder;
	}

	/// <summary>
	/// Returns pointer to selected sub Folder
	/// </summary>
	/// <param name="index">-> target sub Folder</param>
	/// <returns>Folder* - sub Folder</returns>
	Folder* GetSubFolder(int index)
	{
		if (index < SUBFOLDERCOUNT && index >= 0)
		{
			if (subFolders[index] != 0) return (subFolders[index]);
			else
			{
				cout << "NO FOLDER AT INDEX " << index << "!" << endl;
				return 0;
			}
		}
		else
		{
			cout << "NO VALUE AT INDEX_" << index << endl;
			return 0;
		}
	}

	/// <summary>
	/// Returns pointer to selected File
	/// </summary>
	/// <param name="index">-> target File</param>
	/// <returns>File* - File</returns>
	File* GetFile(int index)
	{
		if (index < SUBFILECOUNT && index >= 0)
		{
			if (subFiles[index] != 0) return subFiles[index];
			else
			{
				cout << "NO FILE AT INDEX " << index << "!" << endl;
				return 0;
			}
		}
		else
		{
			cout << "TARGETED FILE IS OUT OF RANGE!" << endl;
			return 0;
		}
	}

	/// <summary>
	/// Returns pointer to largest File
	/// </summary>
	/// <returns>File* - largest File</returns>
	File* GetLargestFile()
	{
		File* largest = 0;

		for (File* file : subFiles)
		{
			if (file == 0) continue;
			else
			{
				if (largest == 0) largest = file;
				else if (file->GetSize() > largest->GetSize()) largest = file;
			}
		}

		return largest;
	}

	/// <summary>
	/// Sets Folder name to input
	/// </summary>
	/// <param name="name"></param>
	void SetName(string name)
	{
		this->name = name;
	}

	/// <summary>
	/// Creates a sub Folder at inputted index
	/// </summary>
	/// <param name="index"></param>
	/// <param name="name"></param>
	/// <param name="size"></param>
	/// <param name="creationDate"></param>
	void NewSubFolder(int index, string name = "", float size = rand() % (101), float creationDate = 0)
	{
		if (index < SUBFOLDERCOUNT && index >= 0)
		{
			if (subFolders[index] != 0)
			{
				subFolders[index]->DestroyFolder();
			}

			subFolders[index] = new Folder(name, size, creationDate, this, index);
			cout << "Created new folder at '" << GetSubFolder(index)->GetPathName() << "'!\n" << endl;
		}
		else cout << "FOLDER CANNOT BE CREATED AT INDEX " << index << "!" << endl;
		
	}

	/// <summary>
	/// Creates a File at inputted index
	/// </summary>
	/// <param name="index"></param>
	/// <param name="name"></param>
	/// <param name="size"></param>
	/// <param name="creationDate"></param>
	void NewFile(int index, string name = "", float size = rand() % (101), float creationDate = 0.0F)
	{
		if (index < SUBFILECOUNT && index >= 0)
		{
			if (subFiles[index] != 0) subFiles[index]->Delete();

			subFiles[index] = new File(name, size, creationDate, this);
			cout << "Created new file at '" << GetFile(index)->GetPathName() << "'!\n" << endl;
		}
		else cout << "FILE CANNOT BE CREATED AT INDEX " << index << "!" << endl;
	}

	/// <summary>
	/// Goes through all sub Folders and Files, and deallocates the memory they use
	/// </summary>
	/// <param name="destroySelf">-> Deallocates this Folder's memory</param>
	/// <returns></returns>
	void DestroyFolder(bool destroySelf = true)
	{
		for (auto folder : subFolders)
		{
			if (folder != 0) folder->DestroyFolder();
		}

		for (auto file : subFiles)
		{
			if (file != 0) file->Delete();
		}

		if (destroySelf) Delete();
	}

	/// <summary>
	/// Removes pointer from 'subFolder[]'
	/// </summary>
	/// <param name="index"></param>
	void RemoveSubFolderIndex(int index)
	{
		if (index < SUBFOLDERCOUNT && index >= 0) subFolders[index] = 0;
	}

	/// <summary>
	/// Removes pointer from 'subFiles[]';
	/// </summary>
	/// <param name="index"></param>
	void RemoveFileIndex(int index)
	{
		if (index < SUBFILECOUNT && index >= 0) subFiles[index] = 0;
	}

	/// <summary>
	/// Deallocates this Folder's memory
	/// </summary>
	void Delete()
	{
		cout << "DELETING " << GetPathName() << " ..." << endl;

		delete this;
	}

	~Folder()
	{
		for (auto folder : subFolders)
		{
			if (folder != 0) folder->DestroyFolder();
		}

		for (auto file : subFiles)
		{
			if (file != 0) file->Delete();
		}

		if (parentFolder != 0) parentFolder->RemoveSubFolderIndex(index);
	}
};



#pragma region Class Functions


/// <summary>
/// Returns path to Folder
/// </summary>
/// <param name="folder"></param>
/// <returns>string - path</returns>
string GetNameOfFolderForFile(Folder* folder)
{
	return folder->GetPathName();
}

/// <summary>
/// Removes pointer from 'subFiles[]'
/// </summary>
/// <param name="folder">-> parent folder</param>
/// <param name="index"></param>
void RemoveFileIndexForFile(Folder* folder, int index)
{
	folder->RemoveFileIndex(index);
}


#pragma endregion


#pragma region Interface Functions

/// <summary>
/// Gets user input and runs the corresponding code
/// </summary>
/// <returns>bool - User wants to do more actions</returns>
bool AskUserForAction()
{
	bool runningProgram = true;

	int action = GetCinInt("What do you want to do?\n1 -> Create new folder\n2 -> Create new file\n3 -> Go into folder\n4 -> Go back\n5 -> Get file info\n6 -> Get largest file\n7 -> Change folder name\n8 -> Change file name\n9 -> Delete folder\n10 -> Delete file\n0 -> Exit program\n");

	switch (action)
	{
	case 1:
		NewFolder();
		break;
	case 2:
		NewFile();
		break;
	case 3:
		EnterFolder();
		break;
	case 4:
		ExitFolder();
		break;
	case 5:
		GetFileInfo();
		break;
	case 6:
		GetLargestFile();
		break;
	case 7:
		ChangeFolderName();
		break;
	case 8:
		ChangeFileName();
		break;
	case 9:
		RemoveFolder();
		break;
	case 10:
		RemoveFile();
		break;
	case 0:
		runningProgram = false;
		break;
	default:
		cout << "That is not a valid option! Choose a value between 0 and 10\n" << endl;

		break;
	}

	return runningProgram;
}

/// <summary>
/// User creates a new Folder / sub Folder
/// </summary>
void NewFolder()
{
	if (currentFolder == 0)
	{
		string n = GetCinStr("What should the folder be called?");

		currentFolder = new Folder(n);

		cout << "Created folder named '" + n + "'\n" << endl;
	}
	else
	{
		cout << currentFolder->GetSubFolderNames(true);

		int i = GetCinInt("At what index would you like to create a folder? Keep the number between 0 - 4\n");

		if (i > SUBFOLDERCOUNT || i < 0)
		{
			cout << "Index is out of range! Keep the number between 0 - 4!\n" << endl;
			return;
		}

		string n = GetCinStr("What should the folder be called? ");

		currentFolder->NewSubFolder(i, n);
	}
}

/// <summary>
/// User creates a new File
/// </summary>
void NewFile()
{
	if (currentFolder != 0)
	{
		cout << currentFolder->GetFileNames(true);

		int i = GetCinInt("At what index would you like to create a folder? Keep the number between 0 - 9\n");

		if (i > SUBFILECOUNT || i < 0)
		{
			cout << "Index is out of range! Keep the number between 0 - 9!\n" << endl;
			return;
		}

		string n = GetCinStr("What should the file be called? ");

		currentFolder->NewFile(i, n);
	}
	else
	{
		cout << "You cannot create a file without creating a folder first!\n" << endl;
	}
}

/// <summary>
/// User changes currentFolder to selected Folder
/// </summary>
void EnterFolder()
{
	if (currentFolder == 0)
	{
		cout << "You have to create a folder first!\n" << endl;

		return;
	}

	cout << currentFolder->GetSubFolderNames(true);

	int i = GetCinInt("Which folder would you like to enter? Keep the number between 0 - 4\n");

	Folder* targetFolder = currentFolder->GetSubFolder(i);

	if (targetFolder == 0) return;
	

	currentFolder = targetFolder;
}

/// <summary>
/// User exits currentFolder, and goes to its parent
/// </summary>
void ExitFolder()
{
	if (currentFolder == 0)
	{
		cout << "You cannot go farther back since you haven't created any folders yet!\n" << endl;
		return;
	}

	Folder* parent = currentFolder->GetParent();

	if (parent == 0)
	{
		cout << "You cannot go farther back in the hierarchy!\n"
			<< "You are currently located at '" << currentFolder->GetPathName() << "'\n" << endl;
		return;
	}

	currentFolder = parent;

	cout << "Moved back to '" << currentFolder->GetPathName() << "'\n" << endl;
}

/// <summary>
/// User prints info of selected File
/// </summary>
void GetFileInfo()
{
	if (currentFolder == 0)
	{
		cout << "There are no files since you haven't created a folder yet!\n" << endl;
		return;
	}

	cout << currentFolder->GetFileNames(true);

	int i = GetCinInt("At which index would you like to get file info from? Keep the number between 0 - 9\n");

	if (i > SUBFILECOUNT || i < 0)
	{
		cout << "That index is not valid! It has to be between 0 - 9!\n" << endl;
		return;
	}

	File* targetFile = currentFolder->GetFile(i);

	if (targetFile == 0)
	{
		cout << "There is no file at index " << i << "\n" << endl;
	}
	else targetFile->PrintInfo();
}

/// <summary>
/// User prints info of largest File
/// </summary>
void GetLargestFile()
{
	if (currentFolder == 0)
	{
		cout << "There are no files since you haven't created a folder yet!\n" << endl;
		return;
	}

	File* largest = currentFolder->GetLargestFile();

	if (largest != 0) largest->PrintInfo();
	else cout << "There are no files in this folder!\n" << endl;
}

/// <summary>
/// User changes name of Folder
/// </summary>
void ChangeFolderName()
{
	if (currentFolder == 0)
	{
		cout << "You have to create a folder first!\n" << endl;
		return;
	}

	cout << "0 '" << currentFolder->GetPathName() << "'\n";

	cout << currentFolder->GetSubFolderNames(true, 1);

	int i = GetCinInt("Which index would you like to change the name of? Keep the number between 0 - 4\n");

	Folder* folder = 0;

	if (i != 0) folder = currentFolder->GetSubFolder(i);
	else folder = currentFolder;

	if (folder == 0)
	{
		cout << "There is no folder at index " << i << "!\n" << endl;
		return;
	}

	string str = GetCinStr("What should the new folder name be? ");
	string oldName = folder->GetName();

	folder->SetName(str);

	cout << "Changed name from '" << oldName << "' to '" << str << "'\n" << endl;
}

/// <summary>
/// User changes name of File
/// </summary>
void ChangeFileName()
{
	if (currentFolder == 0)
	{
		cout << "You have to create a folder first!\n" << endl;
		return;
	}

	cout << currentFolder->GetFileNames(true);

	int i = GetCinInt("Which index would you like to change the name of? Keep the number between 0 - 9\n");

	File* file = currentFolder->GetFile(i);

	if (file == 0)
	{
		cout << "There is no file at index " << i << "!\n" << endl;
		return;
	}

	string str = GetCinStr("What should the new file name be? ");
	string oldName = file->GetName();

	file->SetName(str);

	cout << "Changed file name from '" << oldName << "' to '" << str << "'\n" << endl;
}

/// <summary>
/// User deletes Folder and all it's sub Folders and Files
/// </summary>
void RemoveFolder()
{
	if (currentFolder == 0)
	{
		cout << "There are no files or folders to delete. Please create a new folder\n" << endl;
		return;
	}

	cout << "0 '" << currentFolder->GetPathName() << "'\n" << currentFolder->GetSubFolderNames(true, 1);

	int i = GetCinInt("Which index would you like to PERMANENTLY DELETE? Keep the number between 0 - 5\n");

	Folder* folder = (i == 0 ) ? currentFolder : currentFolder->GetSubFolder(i-1);
	
	if (folder == 0)
	{
		cout << "The folder doesn't exist, so it is already deleted!\n" << endl;
		return;
	}

	string path = folder->GetPathName();

	cout << "Are you sure you want to PERMANENTLY DELETE '" << path << "'? Type 'DELETE' to confirm. Type anything else to go back\n";

	string str = GetCinStr("");

	if (str == "DELETE")
	{
		Folder* parent = currentFolder->GetParent();

		if (parent == 0) currentFolder = 0;
		else currentFolder = parent;

		folder->DestroyFolder();

		cout << "Deletion completed!\n" << endl;
	}
	else cout << "Did not delete anything!\n" << endl;
}

/// <summary>
/// User deletes selected File
/// </summary>
void RemoveFile()
{
	if (currentFolder == 0)
	{
		cout << "You have not created a folder yet! Create a new folder first!\n" << endl;
		return;
	}
	else if (currentFolder->GetLargestFile() == 0)
	{
		cout << "There are no files in this folder!\n" << endl;
		return;
	}

	cout << currentFolder->GetFileNames(true);

	int i = GetCinInt("Which index would you like to PERMANENTLY DELETE? Keep the number between 0 - 9\n");

	File* file = currentFolder->GetFile(i);

	if (file == 0)
	{
		cout << "The folder doesn't exist, so it is already deleted!\n" << endl;
		return;
	}

	string path = file->GetPathName();

	cout << "Are you sure you want to PERMANENTLY DELETE '" << path << "' ? Type 'DELETE' to confirm. Type anything else to go back\n";

	string str = GetCinStr("");

	if (str == "DELETE")
	{
		file->Delete();

		cout << "Deletion completed!\n" << endl;
	}
	else cout << "Did not delete anything!\n" << endl;
}

/// <summary>
/// Prints out path to currentFolder
/// </summary>
void WriteCurrentPath()
{
	if (currentFolder != 0)
	{
		cout << "Currently located at '" << currentFolder->GetPathName() << "'\n" << endl;
	}
	else
	{
		cout << "Currently located at ''\n" << endl;
	}
}

#pragma endregion