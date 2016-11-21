#include "BinaryConverter.h"
void BinaryConverter::convertToMorse(const char* filename)
{
	vector<engToMorse>::iterator itrDict;
	vector<char>::iterator itr;
	string fileContents;

	for (itr = characterList.begin(); itr != characterList.end(); itr++)
	{
		if (islower(*itr))
		{
			itrDict = find(engToMorseVect.begin(), engToMorseVect.end(), *itr);
			fileContents = fileContents +  itrDict->morse + " ";
		}
		else fileContents = fileContents + *itr;
	}
	outputString(filename, fileContents);
}

void BinaryConverter::convertToEnglish(const char* filename)
{
	morseNode tempNode;
	vector<char>::iterator itr;
	string fileContents = "";
	string tempString = "";

	for (itr = characterList.begin(); itr != characterList.end(); itr++)
	{
		if (*itr == '*' || *itr == '-')
		{
			tempString = tempString + *itr;
		}
		else if (isspace(*itr) && tempString != "")
		{
			tempNode.morse = tempString;
			tempString = "";
			fileContents = fileContents + morseToEngTree.find(tempNode)->letter;
		}
		else
			fileContents = fileContents + *itr;
	}
	outputString(filename, fileContents);
	
}

void BinaryConverter::fillTree()
{
	morseNode tempMorseToEng;
	for (vector<engToMorse>::iterator itr = engToMorseVect.begin(); itr != engToMorseVect.end(); itr++)
	{
		tempMorseToEng.letter = itr->letter;
		tempMorseToEng.morse = itr->morse;
		morseToEngTree.insert(tempMorseToEng);
	}
	morseToEngTree.rebalance();
}

bool BinaryConverter::loadEngToMorse(const char* filename)
{
	bool loadStatus = false;
	try
	{
		char tempChar;
		string tempString;
		ifstream myFile;
		engToMorse tempEngToMorse;

		myFile.open(filename);
		if (myFile.is_open())
		{
			while (myFile >> noskipws >> tempChar)
			{
				if (islower(tempChar))
				{
					tempEngToMorse.letter = tempChar;
					tempString = "";
				}
				else if (tempChar == '*' || tempChar == '-')
					tempString = tempString + tempChar;
				else if (iscntrl(tempChar) && tempString != "")
				{
					tempEngToMorse.morse = tempString;
					engToMorseVect.push_back(tempEngToMorse);
					tempString = "";
				}
			}
			tempEngToMorse.morse = tempString;
			engToMorseVect.push_back(tempEngToMorse); //needed to add morse to 'Z'
			loadStatus = true;
		}
		else cout << "\nERROR - Unable to load '" << filename << "'\n";
	}
	catch (exception &ex)
	{
		std::cout << "\nERROR - Exception thrown in LoadEngToMorse\n" << ex.what() << "\n";
	}
	return loadStatus;
}

bool BinaryConverter::loadList(const char* filename)
{
	bool loadStatus = false;
	try
	{
		char tempChar;
		ifstream myFile;

		myFile.open(filename);
		if (myFile.is_open())
		{
			while (myFile >> noskipws >> tempChar)
				characterList.push_back(tempChar);

			if (characterList.size() != 0)
				loadStatus = true;
			else cout << "\nERROR - " << filename << " is empty\n";
		}
		else cout << "\nERROR - Unable to load '" << filename << "'\n";
	}
	catch (exception &ex)
	{
		std::cout << "\nERROR - Exception thrown in LoadList\n" << ex.what() << "\n";
	}
	return loadStatus;
}

void BinaryConverter::outputString(const char* filename, string contents)
{
	try
	{
		ofstream myFile;

		myFile.open(filename);
		if (myFile.is_open())
			myFile << contents;
		else cout << "\nERROR - Unable to access '" << filename << "'\n";
		myFile.close();
	}
	catch (exception &ex)
	{
		std::cout << "\nERROR - Exception thrown in Output\n" << ex.what() << "\n";
	}
}
