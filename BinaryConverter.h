#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "bintree.h"


using namespace std;
using namespace treespc;
class BinaryConverter
{
private:
   struct engToMorse
   {
      char letter;
      string morse;

	  bool operator==(const char& en) const
	  {
		  return (en == letter);
	  }
   };

   struct morseNode
   {
	   char letter;
	   string morse;

	   bool operator==(const morseNode& me) const
	   {
		   return (me.morse == morse);
	   }

	   bool operator<(const morseNode& me) const
	   {
		   return (morse < me.morse);
	   }

	   bool operator>(const morseNode& me) const
	   {
		   return (morse > me.morse);
	   }

	   bool operator!=(const morseNode& me) const
	   {
		   return (me.morse != morse);
	   }
   };

   vector<engToMorse> engToMorseVect;
   vector<char> characterList;
   bintree<morseNode> morseToEngTree;

public:
   void convertToMorse(const char* filename); 
   void convertToEnglish(const char* filename);
   bool loadEngToMorse(const char* filename);
   bool loadList(const char* filename);
   void fillTree();
   void outputString(const char* filename, string contents);
};
