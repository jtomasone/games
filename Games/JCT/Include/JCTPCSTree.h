#pragma once

#include <stdio.h>
#include <tchar.h>
#include <iostream>
//#include <vector>
#include <string>
using namespace std;

#define INIT_PARENTS 10
#define INIT_CHILDREN 10

enum NodeType
{
   ROOT = 0,
   PARENT = 1,
   CHILD = 2
};

enum NODE_STATE
{
   OFF,
   ON
};

enum JCTMSG
{
   MSG_T_EMPTY,
   MSG_P_EXISTS,
   MSG_P_ALLOCFAIL,
   MSG_P_NAMEREQ,
   MSG_C_EXISTS,
   MSG_C_ALLOCFAIL,
   MSG_C_NAMEREQ,
   MSG_END
};

struct PCSInfo
{
   unsigned int m_iNumNodes;
   unsigned int m_iNumLevels;
   unsigned int m_iMaxNodeCount;
};

struct JCTData
{
   JCTData(){};
   JCTData(const string &name)
   {
      Name = name;
   };
   string Name;
};

class JCTNode;
//typedef std::vector<JCTNode*>vChildren;

class JCTNode
{
public:
   JCTNode(const string &name);
   ~JCTNode();
   string getNodeName() const{return m_Data.Name;};
   const enum NODE_STATE getState(){return m_eState;};
   void setState(const enum NODE_STATE &eState) {m_eState = eState;};

   JCTNode get(const JCTNode &pNode){return pNode;};
   JCTNode get(const JCTNode *pNode){return *pNode;};
   JCTNode* getChild()const {return this->m_Child;};

   int getParentCount() const;
   int getTotalCount() const;
   void ChildLevel(unsigned int &iLevel) const;

   virtual void setNodeName(const string &name);
   void printName() const;
   void setNodeType(const NodeType &type);
   const NodeType getNodeType() const {return m_Type;};
   JCTNode* getSibling() const;
   JCTNode* getLastSibling() const;


   JCTNode* getParent() const;
   //Mutators
   const JCTNode setSibling(const string &name);
   void setSibling(const string &name, const unsigned int &iIndex);
   void setSibling(const JCTNode* sibling);
   void setChild(const JCTNode* child){this->m_Child = (JCTNode*)child;};
   JCTNode* getPriorSibling(const JCTNode *node) const;

   void setParent(const JCTNode* parent);
   void setLevel(const int& iLevel){m_iLevel = iLevel;};
   void insertChildNode(JCTNode *node, const string &insertChildName, unsigned int &wReturnValue);
   const JCTNode setParent(const JCTNode& parent);
   void deleteChildren(const bool &bRecursive);
   void deleteChild(const string &name);
   
   //Utility
   JCTNode* ChildExists(const string &name, bool &bFound, unsigned int &iLevel, unsigned int &iReturn);
   JCTNode operator=(const JCTNode &B);
   
   //Accessors
   int getLevel() const {return m_iLevel;};
   int getCount(const bool &bRecursive) const;

   //Output
   void dumpChildren(const bool &bRecursive=true) const;
   void dumpSiblings() const;

   //Operators
   bool operator!=(const JCTNode &B);
   bool operator==(const JCTNode &B);

   friend bool operator!=(const JCTNode &A, const JCTNode &B)
   {
      if((A.m_Data.Name   == B.m_Data.Name)   &&
        (A.m_Child   == B.m_Child)  &&
        (A.m_Sibling == B.m_Sibling)&&
        (A.m_Type    == B.m_Type)   &&
        (A.m_Parent  == B.m_Parent))
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   friend bool operator==(const JCTNode &A, const JCTNode &B)
   {
      if((A.m_Data.Name   == B.m_Data.Name)   &&
        (A.m_Child   == B.m_Child)  &&
        (A.m_Sibling == B.m_Sibling)&&
        (A.m_Type    == B.m_Type)   &&
        (A.m_Parent  == B.m_Parent))
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   JCTNode operator = (const JCTNode* pRhs){return *pRhs;};

private:

   void incrementChildren(){this->m_iChildCount++;};
   void decrementChildren(){this->m_iChildCount++;};
   void initCount(){this->m_iChildCount=0;};
   //vChildren m_vChildren;
   JCTData m_Data;
   JCTNode* m_Sibling;
   JCTNode* m_Child;
   JCTNode* m_Parent;
   int m_iLevel;
   int m_iChildCount;
   enum NODE_STATE m_eState;
   NodeType m_Type;
};

//typedef std::vector<JCTNode*>vJCTParent;

class JCTTree : public JCTNode
{
public:
   JCTTree(const string &name);
   ~JCTTree();
   void insert(const JCTNode &node);
//   void insertParent(const string &name, const JCTNode *node, unsigned int &wReturnValue);
//   void insertParent(const string &name, const string &insertName, unsigned int &wReturnValue);
   void insertChild(JCTNode *node, const string &insertParentName, const string &insertChildName, unsigned int &wReturnValue);
   void deleteParent(const string &name);
   void deleteTree();
   void deleteNode(const string &name);

//   void ParentExists(const string &name, bool &bFound, unsigned int &iReturn);
   JCTNode* NodeExists(const string &name, bool &bFound, unsigned int &iReturn);

   //Accessors
   const JCTNode getParentNode(const string &name);
   
   const JCTNode& getPriorChild(const JCTNode &node) const;
   const JCTNode getRoot() const;
   PCSInfo getInfo();
   void getStatInfo(const string &info) const;
   void NodeLevel(unsigned int &iLevel);

   //Output
   void dumpTree() const;
   void dumpChildren(const string &name, const bool &bRecursive=true);
   void dumpSibling(const JCTNode &node) const;
   void dumpParents();
   void dumpTree();
   int getNodeCount() const;
   //void setRootName(const char *name){m_sRootName.assign(name);};
   //string getRootName() const{return m_sRootName;};

private:
   void incrementParents(){this->m_iParentCount++;};
   void decrementParents(){this->m_iParentCount++;};
   int getParentCount() const;
   void initCount(){this->m_iParentCount=0;};

   //vJCTParent m_vParents;
   int m_iParentCount;
};