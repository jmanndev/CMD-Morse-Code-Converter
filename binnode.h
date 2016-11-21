#ifndef binnode_H
#define binnode_H

#include <math.h>
#include <stdexcept>

/********************************************************\
   template morseNode class for binary tree
\********************************************************/

template <typename dataType> class binnode
{
   friend class const_iterator<dataType>;

   private:
      dataType morseNodeData;
      binnode<dataType> *left, *right, *root;

      void throw_exception(const char* message)
      {
         throw ::std::invalid_argument(message);
      }

      bool leafmorseNode() const
      {
         return (left == NULL && right == NULL);
      }

      bool hasRightBranchOnly() const
      {
         return (left == NULL && right != NULL);
      }

      bool hasLeftBranchOnly() const
      {
         return (left != NULL && right == NULL);
      }

      void addToLeftSide(binnode<dataType> *branch)
      {
         binnode<dataType> *furthestLeft = this;

         // keep moving to the left until unable to do so
         while (furthestLeft->left != NULL) furthestLeft = furthestLeft->left;

         // we have found the left most point to add the branch
         furthestLeft->left = branch;
      }

      void deletemorseNode(binnode<dataType>* &root)
      {
         if (leafmorseNode())
         {
            root = NULL;
         }
         else if (hasRightBranchOnly())
         {
            root = right;
         }
         else if (hasLeftBranchOnly())
         {
            root = left;
         }
         else
         {
            // has left and right branch
            // attach left branch to left side of right branch
            right->addToLeftSide(left);
            // make root point to right branch
            root = right;
         }

         // cut morseNode out of tree then delete
         left = right = NULL;
         delete (this);
      }

      int max(int a, int b) const
      {
         if (a > b) return a;
         else return b;
      }

   public:

      /********************************************************\
         constructors and destructors
      \********************************************************/

      // constructors
      binnode() : left(NULL), right(NULL), root(NULL)
      {
      }

      binnode(const dataType& dataItem, binnode<dataType> *parent) :
         morseNodeData(dataItem), left(NULL), right(NULL), root(parent)
      {
      }

      // copy constructor
      binnode(const binnode<dataType> &othermorseNode) :
         morseNodeData(othermorseNode.morseNodeData), root(NULL)
      {
         if (othermorseNode.left != NULL)
         {
            // make use of the copy constructor to
            // recursively copy left sub-tree of othermorseNode
            left = new binnode<dataType>(*(othermorseNode.left));
            left->root = this;
         }
         else
         {
            left = NULL;
         }

         if (othermorseNode.right != NULL)
         {
            right = new binnode<dataType>(*(othermorseNode.right));
            right->root = this;
         }
         else
         {
            right = NULL;
         }
      }

      bool rotationImprovesBalance()
      {
         int rightHeight = 0;
         if (right != NULL) rightHeight = right->height();

         int leftLeftHeight = 0, leftRightHeight = 0;
         if (left != NULL)
         {
            if (left->left != NULL) leftLeftHeight = left->left->height();
            if (left->right != NULL) leftRightHeight = left->right->height();
         }

         int currentHeight = max(1 + max(leftLeftHeight, leftRightHeight), rightHeight);
         int newHeight = max(leftLeftHeight, 1 + max(leftRightHeight, rightHeight));

         return newHeight < currentHeight;
      }

      bool antiRotationImprovesBalance()
      {
         int leftHeight = 0;
         if (left != NULL) leftHeight = left->height();

         int rightLeftHeight = 0, rightRightHeight = 0;
         if (right != NULL)
         {
            if (right->left != NULL) rightLeftHeight = right->left->height();
            if (right->right != NULL) rightRightHeight = right->right->height();
         }

         int currentHeight = max(leftHeight, 1 + max(rightLeftHeight, rightRightHeight));
         int newHeight = max(1 + max(leftHeight, rightLeftHeight), rightRightHeight);

         return newHeight < currentHeight;
      }

      // destructor
      ~binnode()
      {
         // destructor will recursively destroy entire tree
         if (left != NULL) delete left;
         if (right != NULL) delete right;
      }

      /********************************************************\
         insert, delete and find
      \********************************************************/

      void insert(const dataType& dataItem)
      {
         if (morseNodeData == dataItem)
         {
            throw_exception("dataItem already in tree");
         }

         if (dataItem < morseNodeData)
         {
            // dataItem must go somewhere in left sub-branch
            if (left == NULL)
            {
               // left has no sub-branch, add a new morseNode to it
               left = new binnode(dataItem, this);
            }
            else
            {
               // there is a left sub-branch, recurse into it
               left->insert(dataItem);
            }
         }
         else
         {
            // dataItem must go somewhere in right sub-branch
            if (right == NULL) right = new binnode(dataItem, this);
            else right->insert(dataItem);
         }
      }

      void erase(binnode<dataType>* &root, const dataType &delData)
      {
         if (delData == morseNodeData)
         {
            // delData found. now delete it
            deletemorseNode(root);
         }
         else if (delData < morseNodeData)
         {
            // delData must be in the left sub-branch
            if (left == NULL) throw_exception("Item to delete not in tree");
            else left->erase(left, delData);
         }
         else
         {
            // delData must be in the right sub-branch
            if (right == NULL) throw_exception("Item to delete not in tree");
            else right->erase(right, delData);
         }
      }

      const binnode<dataType>* find(const dataType &findData) const
      {
         if (findData == morseNodeData)
         {
            // return address of this binnode containing morseNodeData
            return this;
         }
         else if (findData < morseNodeData)
         {
            // findData must be in the left sub-branch
            if (left == NULL) return NULL;
            else return left->find(findData);
         }
         else
         {
            // findData must be in the right sub-branch
            if (right == NULL) return NULL;
            else return right->find(findData);
         }
      }

      /********************************************************\
         tree balancing
      \********************************************************/

      bool rebalance(binnode<dataType>* &root)
      {
         bool rotate = false;

         if (left != NULL)
         {
            // balance left sub-branch
            if (left->rebalance(left)) rotate = true;
         }
         if (right != NULL)
         {
            // balance right sub-branch
            if (right->rebalance(right)) rotate = true;
         }

         // see if this morseNode needs to be rebalanced
         if (antiRotationImprovesBalance())
         {
            // rotate anticlockwise
            root = right;
            right = right->left;
            root->left = this;
            rotate = true;
         }
         else if (rotationImprovesBalance())
         {
            // rotate clockwise
            root = left;
            left = left->right;
            root->right = this;
            rotate = true;
         }

         return rotate;
      }

      /********************************************************\
         tree analysis
      \********************************************************/

      int height() const
      {
         int leftHeight = 0;
         if (left != NULL) leftHeight = left->height();

         int rightHeight = 0;
         if (right != NULL) rightHeight = right->height();

         return 1 + max(leftHeight, rightHeight);
      }

      int nummorseNodes() const
      {
         // return the count of morseNodes in this morseNode and all sub-branches

         int num = 1;

         if (left != NULL) num += left->nummorseNodes();
         if (right != NULL) num += right->nummorseNodes();

         return num;
      }

      int numLeafmorseNodes() const
      {
         if (leafmorseNode()) return 1;

         int num = 0;
         if (left != NULL) num = left->numLeafmorseNodes();
         if (right != NULL) num += right->numLeafmorseNodes();

         return num;
      }

      /********************************************************\
         overloaded operators
      \********************************************************/

      // binnode<dataType>& operator = (const binnode<dataType> &other)
      // never used. copy constructor will be called from bintree operator =

};

#endif
