#include <vector>
#include <algorithm>
#include "bintree.h"
#include "Utility.h"
#include "MorseNode.h"
#include "EnglishMorsePair.h"

using namespace std;
class MorseTranslator
{
private:
   Utility util;
   vector<char> fileCharList;
   vector<EnglishMorsePair> engToMorseVector;
   treespc::bintree<MorseNode> morseToEngTree;

   void fillTree();

public:
   void convertToMorse(const char* filename);
   void convertToEnglish(const char* filename);
   bool loadEnglishMorseTranslations(const char* filename);
   bool loadList(const char* filename);
};
