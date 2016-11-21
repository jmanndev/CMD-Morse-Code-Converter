#include <iostream>
#include "BinaryConverter.h"

const int RUNTYPE = 1;
const int FILEIN = 2;
const int FILEOUT = 3;
const char* MORSEFILE = "morsecodes.txt";

void runProgram(const char* runtype, const char* filein, const char* fileout);

int main(int argc, char* argv[])
{
   std::cout << "\nBinary converter by J Mann\n";
   if (argc == 4)
   {
	  char tempChar = *argv[RUNTYPE];
      if (tempChar == 'e' || tempChar == 'd')
      {
         runProgram(argv[RUNTYPE], argv[FILEIN], argv[FILEOUT]);
      } else std::cout << "\nERROR - Invalid first arg.  Expecting 'e' or 'd'.";
   } else std::cout << "\nERROR - Expecting 3 command line arguments.\n";
}

void runProgram(const char* runtype, const char* filein, const char* fileout)
{
   BinaryConverter binCon;
   try
   {
	   if (binCon.loadEngToMorse(MORSEFILE))
	   {
		   if (binCon.loadList(filein))
		   {
			   switch (*runtype)
			   {
			   case 'e':
				   binCon.convertToMorse(fileout);
				   break;
			   case 'd':
				   binCon.fillTree();
				   binCon.convertToEnglish(fileout);
				   break;
			   }
		   }
	   }
   }
   catch (exception &ex)
   {
      std::cout << "\nERROR - Exception thrown Main\n" << ex.what() << "\n";
   }
}
