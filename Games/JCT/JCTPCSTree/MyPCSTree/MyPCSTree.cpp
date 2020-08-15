// MyPCSTree.cpp : Defines the entry point for the console application.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include "JCTPCSTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
   JCTTree myTree;
   
   JCTNode *pTemp = NULL, *pTemp2 = NULL, *pTemp3 = NULL;
   JCTNode *pA = 0, *pB = 0, *pC = 0;
   bool bReturn = false;

/*

insertParent
   positive tests
      passed NODE exists, insert before

   negative tests
      passed NODE address is NULL or <> a valid NODE
      already exists


*/
   unsigned int iReturn = 0, iLevel  = 0;
   
   myTree.insertChild("C", "ROOT", "", iReturn);
   myTree.ChildExists("C", bReturn, iLevel, iReturn);
   myTree.dumpParents();
   if(bReturn)
   {
      myTree.insertChild("C", "ROOT", "", iReturn);
      myTree.insertChild("A", "ROOT", "C", iReturn);
   }
   printf("Inserting A before C\n");
   myTree.dumpParents();

   myTree.ChildExists("C", bReturn, iLevel, iReturn);

   if(bReturn)
   {
      myTree.insertChild("B", "ROOT", "C", iReturn);
   }

   printf("Inserting B before C\n");
   myTree.dumpParents();

//   myTree.insertParent("Z", "", iReturn);
   printf("Add Z to the end C\n");
   myTree.dumpParents();

   JCTNode *pAChild = new JCTNode("D");

   myTree.insertChild("D", "A", "", iReturn);
   myTree.insertChild("E", "A", "", iReturn);
   myTree.insertChild("I", "A", "", iReturn);

   myTree.insertChild("F", "D", "", iReturn);
   myTree.insertChild("G", "I", "", iReturn);
   myTree.insertChild("J", "I", "", iReturn);
   myTree.insertChild("H", "F", "", iReturn);

   printf("Add all children to Parent A\n");
   myTree.dumpChildren("A");


   myTree.insertChild("K", "B", "", iReturn);
   myTree.insertChild("L", "B", "", iReturn);
   myTree.insertChild("M", "L", "", iReturn);
   myTree.insertChild("N", "L", "", iReturn);

   printf("Add all children to Parent B\n");
   myTree.dumpChildren("B");

   myTree.insertChild("R", "C", "", iReturn);
   myTree.insertChild("O", "R", "", iReturn);
   myTree.insertChild("P", "R", "", iReturn);
   myTree.insertChild("Q", "R", "", iReturn);
   myTree.insertChild("S", "P", "", iReturn);
   myTree.insertChild("T", "S", "", iReturn);
   myTree.insertChild("U", "S", "", iReturn);
   myTree.insertChild("V", "S", "", iReturn);
   myTree.insertChild("W", "S", "", iReturn);

   printf("Add all children to Parent B\n");
   myTree.dumpChildren("C");

   printf("Tree\n");
   myTree.dumpTree();
   PCSInfo p = myTree.getInfo();
   printf("p.m_iMaxNodeCount=%d\n", p.m_iMaxNodeCount);
   printf("p.m_iNumLevels=%d\n", p.m_iNumLevels);
   printf("p.m_iNumNodes=%d\n", p.m_iNumNodes);

   pTemp = myTree.NodeExists("D", bReturn, iReturn);
   if(bReturn)
   {
      printf("Siblings of D\n");
      pTemp->dumpSiblings();
   }

   printf("Direct Children of C\n");
   myTree.dumpChildren("C", false);

   printf("All descendants of C\n");
   myTree.dumpChildren("C", true);
   myTree.deleteNode("A");

   //pTemp->deleteNode(true);
   printf("Siblings of D after D deleted\n");
   myTree.dumpTree();

   myTree.insertChild("D", "A", "E", iReturn);
   myTree.insertChild("F", "D", "", iReturn);
   myTree.insertChild("H", "F", "", iReturn);

   printf("Children of D after reinserted\n");
   myTree.dumpChildren("D", true);
   printf("Tree\n");
   myTree.dumpTree();
   myTree.deleteTree();
   printf("Tree\n");
   myTree.dumpTree();


    /*
   pAChild = 0;
   pTemp = 0;
   pTemp2 = 0;




  
   JCTTree *myTree2 = new JCTTree();
   myTree2->insertParent("C", NULL, iReturn);
   myTree2->ParentExists("C", bReturn, iReturn);
   myTree2->dumpParents();
   if(bReturn)
   {
      myTree2->insertParent("A", "C", iReturn);
   }
   printf("Inserting A before C\n");
   myTree2->dumpParents();

   myTree2->ParentExists("C", bReturn, iReturn);

   if(bReturn)
   {
      myTree2->insertParent("B", "C", iReturn);
   }

   printf("Inserting B before C\n");
   myTree2->dumpParents();

//   myTree2->insertParent("Z", "", iReturn);
   printf("Add Z to the end C\n");
   myTree2->dumpParents();

   pAChild = new JCTNode("D");

   myTree2->insertChild("D", "A", "", iReturn);
   myTree2->insertChild("E", "A", "", iReturn);
   myTree2->insertChild("I", "A", "", iReturn);

   myTree2->insertChild("F", "D", "", iReturn);
   myTree2->insertChild("G", "I", "", iReturn);
   myTree2->insertChild("J", "I", "", iReturn);
   myTree2->insertChild("H", "F", "", iReturn);

   printf("Add all children to Parent A\n");
   myTree2->dumpChildren("A");


   myTree2->insertChild("K", "B", "", iReturn);
   myTree2->insertChild("L", "B", "", iReturn);
   myTree2->insertChild("M", "L", "", iReturn);
   myTree2->insertChild("N", "L", "", iReturn);

   printf("Add all children to Parent B\n");
   myTree2->dumpChildren("B");

   myTree2->insertChild("R", "C", "", iReturn);
   myTree2->insertChild("O", "R", "", iReturn);
   myTree2->insertChild("P", "R", "", iReturn);
   myTree2->insertChild("Q", "R", "", iReturn);
   myTree2->insertChild("S", "P", "", iReturn);
   myTree2->insertChild("T", "S", "", iReturn);
   myTree2->insertChild("U", "S", "", iReturn);
   myTree2->insertChild("V", "S", "", iReturn);
   myTree2->insertChild("W", "S", "", iReturn);

   printf("Add all children to Parent B\n");
   myTree2->dumpChildren("C");

   printf("Tree\n");
   myTree2->dumpTree();
   pTemp = myTree2->NodeExists("D", bReturn, iReturn);
   if(bReturn)
   {
      printf("Siblings of D\n");
      pTemp->dumpSiblings();
   }

   printf("Direct Children of C\n");
   myTree2->dumpChildren("C", false);

   printf("All descendants of C\n");
   myTree2->dumpChildren("C", true);
   myTree2->deleteNode("A");

   //pTemp->deleteNode(true);
   printf("Siblings of D after D deleted\n");
   myTree2->dumpTree();

   myTree2->insertChild("D", "A", "E", iReturn);
   myTree2->insertChild("F", "D", "", iReturn);
   myTree2->insertChild("H", "F", "", iReturn);

   printf("Children of D after reinserted\n");
   myTree2->dumpChildren("D", true);
   printf("Tree\n");
   myTree2->dumpTree();
   myTree2->deleteTree();
   printf("Tree\n");
   myTree2->dumpTree();
*/
   /*
   if(pA != 0)
   {
      myTree.insertChild(
   }

   pTemp = myTree.insertParent("3");
   myTree.insertParent("4");
   myTree.insertParent("5");
   pTemp2 = myTree.insertParent("6", pTemp);
   
//   pTemp3 = myTree.insertChild("6", *pTemp2);
   myTree.dumpParents();
   pTemp2 = myTree.insertParent("7", pTemp2);
   cout << endl << endl;

   myTree.dumpParents();
   cout << endl << endl;
   myTree.getLastSibling();
   */
	return 0;
}
