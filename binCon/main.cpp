#include <iostream>
#include <string.h>
#include "MorseTranslator.h"

const int RUNTYPE = 1;
const int FILEIN = 2;
const int FILEOUT = 3;
const char* MORSEFILE = "morsecodes.txt";

void runProgram(const char* runtype, const char* filein, const char* fileout);

int main(int argc, char* argv[])
{
   std::cout << "Morse code converter by J Mann\n";
   if (argc == 4)
   {
      string fileinString = argv[FILEIN];
      string fileoutString = argv[FILEOUT];
      if (fileinString != fileoutString)
      {
         string runtype = argv[RUNTYPE];
         if (runtype.size() == 1 && (runtype == "e" || runtype == "d"))
            runProgram(argv[RUNTYPE], argv[FILEIN], argv[FILEOUT]);
         else 
         {
            std::cout << "\nERROR - Invalid first argument.  Expecting 'e' or 'd'.\n";
            std::cout << "SYNTAX - 'e' to encode + 'd' to decode\n";
         }
      }
      else
         std::cout << "\nERROR - filein[2nd arg] and fileout[3rd arg] must be different.\n";
   }
   else std::cout << "\nERROR - Expecting 3 arguments.\nSYNTAX - e|d filein fileout\n";
}

void runProgram(const char* runtype, const char* filein, const char* fileout)
{
   MorseTranslator translator;
   try
   {
      if (translator.loadEnglishMorseTranslations(MORSEFILE))
      {
         if (translator.loadList(filein))
         {
            switch (*runtype)
            {
            case 'e':
               translator.convertToMorse(fileout);
               break;
            case 'd':
               translator.convertToEnglish(fileout);
               break;
            }
         }
      }
   }
   catch (exception &ex)
   {
      std::cout << "\nERROR - Exception thrown: " << ex.what() << "\n";
   }
}
