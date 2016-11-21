#include <string>

#ifndef ENGLISHMORSEPAIR_H
#define ENGLISHMORSEPAIR_H

struct EnglishMorsePair
{
   char letter;
   std::string morse;

   bool operator==(const char& inputLetter) const
   {
      return (letter == inputLetter);
   }
};

#endif /* ENGLISHMORSEPAIR_H */
