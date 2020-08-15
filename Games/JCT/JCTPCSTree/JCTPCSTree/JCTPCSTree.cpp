#pragma once
#include "JCTPCSTree.h"

//Copy
JCTNode JCTNode::operator=(const JCTNode &B)
{
   this->m_Data = B.m_Data;
   this->m_Child = B.m_Child;
   this->m_Sibling = B.m_Sibling;
   this->m_Type = B.m_Type;
   this->m_Parent = B.m_Parent;
   return *this;
}

//Comparison Operator
bool JCTNode::operator!=(const JCTNode &B)
{
   if((this->m_Data.Name == B.m_Data.Name)       &&
     (this->m_Child == B.m_Child)     &&
     (this->m_Sibling == B.m_Sibling) &&
     (this->m_Type == B.m_Type)       &&
     (this->m_Parent == B.m_Parent))
   {
      return false;
   }
   else
   {
      return true;
   }
}

//Comparison Operator
bool JCTNode::operator==(const JCTNode &B)
{
   if((this->m_Data.Name == B.m_Data.Name)       &&
     (this->m_Child == B.m_Child)     &&
     (this->m_Sibling == B.m_Sibling) &&
     (this->m_Type == B.m_Type)       &&
     (this->m_Parent == B.m_Parent))
   {
      return true;
   }
   else
   {
      return false;
   }
}

//Constructor which requires a valid name
JCTNode::JCTNode(const string &name)
{
   if(name == "")
   {
      cout << "Error: A valid Node name is required";
      return;
   }
   else
   {
      //Set properties and reserves the preset amount of Children 
      //if this is not the ROOT node
      this->setNodeType(CHILD);
      this->setNodeName(name);
      this->setSibling(0);
      this->setChild(0);
      this->setParent(0);
      this->setState(ON);
      this->initCount();
      /*if(name != "ROOT")
      {
         this->m_vChildren.reserve(INIT_CHILDREN);
      };*/
   }
};

//Mutator for Name
void JCTNode::setNodeName(const string &name)
{
   this->m_Data.Name = name;
}

//Outputting the Name
void JCTNode::printName() const
{
   for(int x=0; x <= this->getLevel()-1; x++)
   {
      cout << "   ";
   }
   //cout << "Node Level ==>>" << this->getLevel() << endl; 
   cout << "Node Level ==>>" << this->getLevel() << "   Node Name ==>>" << m_Data.Name.c_str() << endl; 
};

//Mutator for Type
void JCTNode::setNodeType(const NodeType &type)
{
   this->m_Type = type;
};

//Accessor for Sibling
JCTNode* JCTNode::getSibling() const
{
   return this->m_Sibling;
};

JCTNode* JCTNode::getPriorSibling(const JCTNode *node) const
{
   JCTNode *pTemp, *pSibling;
   pTemp = this->getParent();
   pTemp = pTemp->getChild();
   bool bFound = false;
   if(node->getNodeName() == pTemp->getNodeName())
   {
      return 0;
   }
   else
   {
      //for(int x = this->m_Count-1; x>0; x--)
      while(pTemp)
      {
         pSibling = (JCTNode*)pTemp->getSibling();
         if(pSibling && (pSibling->getNodeName() == node->getNodeName()))
         {
            bFound = true;
            break;
         }
         pTemp = pSibling;
      }
      cout << "pTemp->getNodeName()==>>";
      
      if(!bFound)
      {
         pTemp = 0;
      }
      else
      {
         pTemp->printName();
      }
      return pTemp;

   }
}

JCTNode* JCTNode::getLastSibling() const
{
   JCTNode *pChild = 0;
   pChild = (JCTNode*)this;
   if(pChild)
   {
      while(pChild->getSibling())
      {
         pChild = pChild->getSibling();
      }
   }
   return pChild;
};

//Mutator for Sibling
void JCTNode::setSibling(const JCTNode* sibling)
{
   this->m_Sibling = (JCTNode*) sibling;
}

//Mutator for Parent
void JCTNode::setParent(const JCTNode* parent)
{
   this->m_Parent = (JCTNode*)parent;
}

//Mutator for Parent
const JCTNode JCTNode::setParent(const JCTNode& parent)
{
   this->m_Parent = (JCTNode*)&parent;
   return get(this->m_Parent);
}

//Accessor for Parent
JCTNode* JCTNode::getParent() const
{
   return this->m_Parent;
};

//Accessor for Count
int JCTNode::getCount(const bool &bRecursive) const
{
   if(bRecursive)
   {
      int iReturn = 0;
      JCTNode *pTemp;
      //if(this->m_Child)
      if(this->m_Child)
      {
         //Loop through the member vChildren Vector to count the Nodes
         //for(unsigned int x=0; x<this->m_vChildren.size(); x++)
         if(this->m_Child->m_Sibling)
         {
            pTemp = this->m_Sibling;
            while(pTemp)
            {
               iReturn += pTemp->getCount(true);
               pTemp = pTemp->m_Sibling;
            }
         }
         iReturn += this->getCount(false);
      }
      return iReturn;
   }
   else
   {
      return this->m_iChildCount;
   }
};

//Destructor which recursively deletes all descendants
// and clears the member vChildren Vector
JCTNode::~JCTNode()
{
//   this->deleteChildren(true);
//   this->m_vChildren.clear();
};

//Lookup for Child
JCTNode* JCTNode::ChildExists(const string &name, bool &bFound, unsigned int &iLevel, unsigned int &iReturn)
{
   JCTNode *pTemp = 0, *pChild = 0;
   pChild = this->m_Child;
   if(pChild)
   {
      unsigned int iSize=0, iHeader=0, iTemp=0, iBlockSize=0;
      
      iLevel++;

      pChild = this->m_Child;
      while(pChild)
      {
         //if found set it and break
         if(pChild->getNodeName() == name)
         {
            bFound = true;
            pTemp = pChild;
            break;
         }
         //Not found then recursively search the current Node's children
         else
         {  
            pTemp = pChild->ChildExists(name, bFound, iLevel, iReturn);
            //if found then break
            if(bFound)
            {
               break;
            }
         }
         pChild = pChild->m_Sibling;
      }
   }
   //return pointer to child node
   return pTemp;
};

void JCTNode::ChildLevel(unsigned int &iLevel) const
{
   JCTNode *pChild = 0;
   if(this->m_Child)
   {
      unsigned int iTempLevel=0; 
      pChild = this->m_Child;
      while(pChild)
      {
         pChild->ChildLevel(iTempLevel);
         iLevel = max(iTempLevel, iLevel);
         pChild = pChild->m_Sibling;
      }
   }
   else
   {
      iLevel = this->getLevel();
   }
}
//Output this Node's direct descendants or entire tree of descendants based 
//on the bRecursive bool
void JCTNode::dumpChildren(const bool &bRecursive) const
{
   JCTNode *pChild = 0;
   pChild = this->m_Child;
   if(pChild)
   {
      while(pChild)
      {
         printf("\n");
         pChild->printName();
         if(bRecursive)
         {
            pChild->dumpChildren();
         }
         pChild = pChild->m_Sibling;
      }
   }
}

//Remove a child
void JCTNode::deleteChild(const string &name)
{
   JCTNode *pChild = 0;
   if(this->m_Child)
   {
      pChild = this->m_Child;
      while(pChild)
      {
         //if found then use the erase function to remove this Node
         //then break from the loop
         if(pChild->getNodeName() == name)
         {
            //m_vChildren.erase(this->m_vChildren.begin()+x);
            this->decrementChildren();
            break;
         };
         pChild = pChild->m_Sibling;
      }
   }
};

//Remove all of this Node's direct descendants or entire tree of descendants 
//based on the bRecursive bool
void JCTNode::deleteChildren(const bool &bRecursive)
{
   JCTNode *pChild = 0;
   if(this->m_Child)
   {
      pChild = this->m_Child;
      while(pChild)
      {
         printf("\n");
         if(bRecursive)
         {
            pChild->deleteChildren(bRecursive);
         }
         //m_vChildren.erase(this->m_vChildren.end()-x);
         this->initCount();
         pChild = pChild->m_Sibling;
      }
   }
}

//Dump all of this Node's Siblings by getting the Parent Node and 
//dumping all of its direct descendants
void JCTNode::dumpSiblings() const
{
   JCTNode *pTemp = 0;
   pTemp = this->getParent();

   if(NULL != pTemp)
   {
      pTemp->dumpChildren(false);
   }
};

//Insert a Child Node given a name and an insertChildName for a location where
//to insert
void JCTNode::insertChildNode(JCTNode *node, const string &insertChildName, unsigned int &wReturnValue)
{
   unsigned int iReturn=0, iLevel=1;
   bool bExisted = false;
   JCTNode *pTemp=0, *pTemp2=0, *pTemp3=0;
   //Check to see if this name already exists
   if(node)
   {
      pTemp = ChildExists(node->getNodeName(), bExisted,  iLevel, iReturn);
      if(!bExisted)
      {
         pTemp2 = (JCTNode*)node;//new JCTNode(name);

         //Allocation succeeded?
         if(pTemp2)
         {
            bExisted = false;

            //insertChildName blank?
            if(insertChildName != "")
            {
               //Make sure the insertChildName sent over is a valid Node
               //iLevel=2;
               pTemp = this->ChildExists(insertChildName, bExisted, iLevel, iReturn);
               if(pTemp)
               {
                  pTemp3 = pTemp->getPriorSibling(pTemp);
               }
               //if so then set it to be the sibling to the newly allocated Child Node
               if(pTemp3)
               {
                  pTemp2->setSibling(pTemp);
                  pTemp3->setSibling(pTemp2);
               }
               else
               {
                  pTemp2->setSibling(pTemp);
                  this->setChild(pTemp2);

               }

               //Set the rest of its properties
               pTemp2->setLevel(this->getLevel()+1);
               pTemp2->setNodeType(CHILD);
               pTemp2->setParent(this);
            }
            else
            {
               //If the vChildren Vector is not empty then set the 
               //sibling of the last to be the newly allocated Node
               //Set the rest of its properties
               pTemp2->setParent(this);
               pTemp2->setLevel(this->getLevel()+1);
               pTemp2->setNodeType(CHILD);
               
               pTemp3 = this->m_Child->getLastSibling();
               if(pTemp3)
               {
                  pTemp3->setSibling(pTemp2);
               }
               else
               {
                  this->setChild(pTemp2);
               }

            }
            //if we are appending the Node based on the insertChildName being blank 
            //or that insertChildName not existing
            
            incrementChildren();
         }
         //Allocation failed
         else
         {
            wReturnValue = MSG_C_ALLOCFAIL;
         }
      }
      //Requested Child to create already exists
      else
      {
         wReturnValue = MSG_C_EXISTS;
      }
   }
   else
   {
      wReturnValue = MSG_C_EXISTS;
   }
};

//Tree Constructor
JCTTree::JCTTree(const string &name) :
JCTNode(name)
{
   //initializes the Node Counter
   this->initCount();
   //Sets the ROOT Level to 0
   this->setLevel(0);
   this->setChild(0);
   //Reserves the preset amount of parents
//   this->m_vParents.reserve(INIT_PARENTS);
};

//Destructor which recursively will 
JCTTree::~JCTTree()
{
   this->deleteTree();
//   this->m_vParents.clear();
}

//return a pointer to the Tree Node
const JCTNode JCTTree::getRoot() const
{
   return *this;
}
/*
//Insert a Parent given a name and an optional insertName for a location
void JCTTree::insertParent(const string &name, const string &insertName, unsigned int &wReturnValue)
{
   JCTNode *pTemp = 0, *pSibling = 0, *pTemp2 = 0;
   unsigned int iReturn = 0;
   unsigned int iLevel = 0;

   bool bExisted = false;
   //Does the requested Node name already exist in Parent Form?
   ParentExists(name, bExisted, iReturn);

   if(!bExisted)
   {
      iReturn=0;
      //Allocate a new Node with name
      pTemp2 = new JCTNode(name);
      //Allocation succeed?
      if(pTemp2)
      {
         //insertName blank?
         if(insertName != "")
         {
            //Make sure this Node sent over is valid in the tree.
            ParentExists(insertName, bExisted, iReturn);
            //if insertName is a name to a valid Node set its Sibling 
            //to the newly allocated Node and 
            if(bExisted)
            {
               pTemp2->setSibling(this->m_vParents[iReturn]->getSibling());
               this->m_vParents[iReturn]->setSibling(pTemp2);
            }
            pTemp2->setNodeType(PARENT);
            pTemp2->setLevel(2);
            pTemp2->setParent(this);
         }
         else
         {
            //Generate a new Noda and add it to the end.
            if(!m_vParents.empty())
            {
               //Generate a new Noda and add it to the end.
               this->m_vParents[(m_vParents.size()-1)]->setSibling(pTemp2);
            }
            pTemp2->setNodeType(PARENT);
            pTemp2->setLevel(2);
            pTemp2->setParent(this);
         }
         //if the insertName Node already existed then 
         //insert the new Node before it
         if(bExisted)
         {
            m_vParents.insert(m_vParents.begin()+iReturn, pTemp2);
         }
         //Otherwise append it to the end
         else
         {
            m_vParents.insert(m_vParents.end(), pTemp2);
         }
         incrementParents();
      }
      //Parent Allocation failed
      else
      {
         wReturnValue = MSG_P_ALLOCFAIL;
      }
   }
   else
   {
      //A Parent already exists as name
      wReturnValue = MSG_P_EXISTS;
   }
};

//InsertParent Method to allow an existing Node to be passed
void JCTTree::insertParent(const string &name, const JCTNode *node, unsigned int &wReturnValue)
{
   //Is node pointer valid
   if(node)
   {
      insertParent(name, node->getNodeName(), wReturnValue);
   }
   //Name is required
   else if(name == "")
   {
      wReturnValue = MSG_P_NAMEREQ;
   }
   //otherwise send a blank name to append the new Parent
   else
   {
      insertParent(name, "", wReturnValue);
   }
};

//Determine if a Parent Exists given a name
void JCTTree::ParentExists(const string &name, bool &bFound, unsigned int &iReturn)
{
   if(!m_vParents.empty())
   {
      unsigned int iSize=0, iHeader=0, iTemp=0, iBlockSize=0;
      unsigned int iLevel=0; 
      for(size_t x=0; x<m_vParents.size(); x++, iReturn++)
      {
         if(m_vParents[x]->getNodeName() == name)
         {
            bFound = true;
            break;
         }
      }
   }
};
*/
//Search the entire Tree for a Node given a name
void JCTTree::NodeLevel(unsigned int &iLevel)
{
   if(this->getChild())
   {
      unsigned int iTempLevel=0; 
      //for(size_t x=0; x<m_vParents.size(); x++)
      JCTNode *pTemp = 0;
      pTemp = this->getChild();
      while(pTemp)
      {
         pTemp->ChildLevel(iTempLevel);
         iLevel = max(iTempLevel, iLevel);
         pTemp = this->getSibling();
      }
   }
}

//Search the entire Tree for a Node given a name
JCTNode* JCTTree::NodeExists(const string &name, bool &bFound, unsigned int &iReturn)
{
   JCTNode *pTemp=0, *pChild;
   if(this->getNodeName() == name)
   {
      pTemp = this;
      bFound = true;
      iReturn = MSG_P_EXISTS;
   }
   else if(this->getChild())
   {
      unsigned int iSize=0, iHeader=0, iTemp=0, iBlockSize=0;
      unsigned int iLevel=0; 
      //for(size_t x=0; x<m_vParents.size(); x++, iReturn++)
      
      pChild = this->getChild();
      while(pChild)
      {
         if(pChild->getNodeName() == name)
         {
            pTemp = pChild;
            bFound = true;
            break;
         }
         else
         {
            pTemp = pChild->ChildExists(name, bFound, iLevel, iReturn);
            if(bFound)
            {
               bFound = true;
               break;
            }
         }
         pChild = pChild->getSibling();
         
      }
   }
   else
   {
      iReturn = MSG_T_EMPTY;
   }
   return pTemp;
};
/*
void JCTTree::insertChild(const JCTNode *node, const string &insertParentName, unsigned int &wReturnValue)
{
   if(node)
   {
      this->insertChild(node->getNodeName(), insertParentName, "", wReturnValue);
   }
   else
   {
      wReturnValue = MSG_P_NULLOBJPTR;
   }
}*/
//Insert a child given a name and an insertParentName to add this new Node to
void JCTTree::insertChild(JCTNode *node, const string &insertParentName, const string &insertChildName, unsigned int &wReturnValue)
{
   JCTNode *pTemp = 0, *pSibling = 0, *pTemp2 = 0;
   unsigned int iReturn = 0, iLevel = 1;
   bool bExisted = false;
   if(node && node->getNodeName() != "")
   {
      if(insertParentName != "")
      {
         pTemp = NodeExists(insertParentName, bExisted, iReturn);
      
         if(bExisted)
         {
            pTemp->insertChildNode(node, insertChildName, wReturnValue);
         }
         else
         {
            wReturnValue = MSG_C_EXISTS;
         }
      }
      else
      {
            wReturnValue = wReturnValue = MSG_P_NAMEREQ;
      }
   }
   else
   {
      wReturnValue = MSG_C_NAMEREQ;
   }
};

int JCTTree::getNodeCount() const
{
   JCTNode* pChild = 0;
   pChild = this->getChild();
   if(pChild)
   {
      unsigned int iNodes = this->getParentCount();

      //for(size_t x=0; x<m_vParents.size(); x++)
      while(pChild)
      {
         iNodes += pChild->getCount(true);
         pChild = pChild->getSibling();
      }
      return iNodes;
   }
   else
   {
      return 0;
   }
}

int JCTTree::getParentCount() const
{
   return this->m_iParentCount;
};

void JCTTree::deleteNode(const string &name)
{
   unsigned int iReturn = 0;
   bool bFound = false;
   JCTNode *pTemp = 0;
   pTemp = this->NodeExists(name, bFound, iReturn);
   if(bFound)
   {
      pTemp->deleteChildren(true);
      if(pTemp->getNodeType() == CHILD)
      {
         pTemp->getParent()->deleteChild(name);
      }
      else
      {
         //this->m_vParents.erase(this->m_vParents.begin()+iReturn);
      }
   }
};

//Remove a child
void JCTTree::deleteParent(const string &name)
{
   JCTNode *pChild=0, *pSibling=0;
   pChild = this->getChild();
//   for(size_t x=0; x < this->m_vParents.size(); x++)
   while(pChild)
   {
      //if found then use the erase function to remove this Node
      //then break from the loop
      pSibling = pChild->getSibling();
      if(pSibling && pSibling->getNodeName() == name)
      {
         pSibling->deleteChildren(true);
         //this->m_vParents.erase(this->m_vParents.begin()+x);
         pChild->setSibling(0);
         this->decrementParents();
         break;
      };
      pChild = pChild->getSibling();
   }
};

//Delete the entire tree
void JCTTree::deleteTree()
{
   JCTNode *pChild;
   pChild = this->getChild();
   //for(size_t x=m_vParents.size(); x>0; x--)
   while(pChild)
   {
      pChild->deleteChildren(true);
      this->deleteNode(pChild->getNodeName());
      pChild = pChild->getSibling();
   }
}

//Output the Parent Nodes
void JCTTree::dumpParents()
{
   bool bFound = false;
   JCTNode *pSibling = 0;
   pSibling = this->getChild();

   while (pSibling)
   {
      pSibling->printName();
      pSibling = pSibling->getSibling();
   }
}

//Output the Children Nodes given a Node Name
void JCTTree::dumpChildren(const string &name, const bool &bRecursive)
{
   bool bFound = false;
   unsigned int iReturn = 0;
   JCTNode *pTemp = 0;
   pTemp = this->NodeExists(name, bFound, iReturn);

   if(bFound)
   {
      pTemp->printName();
      pTemp->dumpChildren(bRecursive);
   }
};

//Dump the entire Tree
void JCTTree::dumpTree()
{
   JCTNode *pSibling = 0;
   pSibling = this->getChild();

   while (pSibling)
   {
      pSibling->printName();
      pSibling->dumpChildren();
      pSibling = pSibling->getSibling();
   }
   this->printName();
}

//Get the info, store it in a PCSInfo Structure and return it
PCSInfo JCTTree::getInfo()
{
   unsigned int iLevel = 0;
   this->NodeLevel(iLevel);
   PCSInfo sReturn;
   sReturn.m_iMaxNodeCount = INIT_PARENTS*INIT_PARENTS;
   sReturn.m_iNumLevels = iLevel;
   sReturn.m_iNumNodes = this->getNodeCount();

   return sReturn;
};
