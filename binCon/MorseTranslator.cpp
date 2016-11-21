#include "MorseTranslator.h"

void MorseTranslator::convertToMorse(const char* filename)
{
   vector<EnglishMorsePair>::const_iterator itrPair;
   vector<char>::const_iterator itr;
   string fileContents;

   for (itr = fileCharList.begin(); itr != fileCharList.end(); itr++)
   {
      if (islower(*itr))
      {
         itrPair = find(engToMorseVector.begin(), engToMorseVector.end(), *itr);
         if (itrPair != engToMorseVector.end())
            fileContents = fileContents +  itrPair->morse + " ";
      }
      else fileContents = fileContents + *itr;
   }
   util.saveFileContents(filename, fileContents);
}

void MorseTranslator::convertToEnglish(const char* filename)
{
   vector<char>::const_iterator itr;
   treespc::const_iterator<MorseNode> treeNodeItr;
   MorseNode tempNode;
   string fileContents;
   string tempString = "";

   fillTree();
   for (itr = fileCharList.begin(); itr != fileCharList.end(); itr++)
   {
      if (*itr == '*' || *itr == '-')
         tempString = tempString + *itr;
      else if (isspace(*itr) && tempString != "")
      {
         tempNode.morse = tempString;
         tempString = "";
         treeNodeItr = morseToEngTree.find(tempNode);

         if (treeNodeItr != morseToEngTree.end())
            fileContents = fileContents + treeNodeItr->letter;

         if (*itr == '\n')
            fileContents = fileContents + *itr;
      }
      else fileContents = fileContents + *itr;
   }
   util.saveFileContents(filename, fileContents);
}

void MorseTranslator::fillTree()
{
   MorseNode tempNode;
   vector<EnglishMorsePair>::const_iterator itr;

   for (itr = engToMorseVector.begin(); itr != engToMorseVector.end(); itr++)
   {
      tempNode.letter = itr->letter;
      tempNode.morse = itr->morse;
      morseToEngTree.insert(tempNode);
   }
   morseToEngTree.rebalance();
}

bool MorseTranslator::loadEnglishMorseTranslations(const char* filename)
{
   bool loadStatus = false;
   char tempChar;
   ifstream myFile;
   string tempMorseString = "";
   EnglishMorsePair tempEngToMorse;

   myFile.open(filename);
   if (myFile.is_open())
   {
      while (myFile >> noskipws >> tempChar)
      {
         if (islower(tempChar))
         {
            tempEngToMorse.letter = tempChar;
            tempMorseString = "";
         }
         else if (tempChar == '*' || tempChar == '-')
            tempMorseString = tempMorseString + tempChar;
         else if (iscntrl(tempChar) && tempMorseString != "")
         {
            tempEngToMorse.morse = tempMorseString;
            engToMorseVector.push_back(tempEngToMorse);
            tempMorseString = "";
         }
      }
      tempEngToMorse.morse = tempMorseString;
      engToMorseVector.push_back(tempEngToMorse); //needed to add last translation ('z') to Vector

      loadStatus = true;
   }
   else cout << "\nERROR - Unable to load '" << filename << "'\n";
   return loadStatus;
}

bool MorseTranslator::loadList(const char* filename)
{
   bool loadStatus = false;
   char tempChar;
   ifstream myFile;

   myFile.open(filename);
   if (myFile.is_open())
   {
      while (myFile >> noskipws >> tempChar)
         fileCharList.push_back(tempChar);

      if (fileCharList.size() != 0)
         loadStatus = true;
      else cout << "\nERROR - " << filename << " is empty\n";
   }
   else cout << "\nERROR - Unable to load '" << filename << "'\n";
   return loadStatus;
}
