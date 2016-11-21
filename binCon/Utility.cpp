#include "Utility.h"

void Utility::saveFileContents(const char* filename, std::string contents)
{
   std::ofstream myFile;

   myFile.open(filename);
   if (myFile.is_open())
      myFile << contents;
   else std::cout << "\nERROR - Unable to access '" << filename << "' to output translation.\n";
   myFile.close();
}
