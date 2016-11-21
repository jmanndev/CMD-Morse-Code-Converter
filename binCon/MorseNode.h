#include <string>

#ifndef MORSENODE_H
#define MORSENODE_H

struct MorseNode
{
   char letter;
   std::string morse;

   bool operator==(const MorseNode& inputNode) const
   {
      return (morse == inputNode.morse);
   }

   bool operator<(const MorseNode& inputNode) const
   {
      return (morse < inputNode.morse);
   }

   bool operator>(const MorseNode& inputNode) const
   {
      return (morse > inputNode.morse);
   }

   bool operator!=(const MorseNode& inputNode) const
   {
      return (morse != inputNode.morse);
   }
};

#endif /* MORSENODE_H */
