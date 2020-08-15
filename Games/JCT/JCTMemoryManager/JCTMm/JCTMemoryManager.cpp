// JCTMm.cpp : Defines the entry point for the console application.
//

#include "JCTMm.h"
/*
Free Header   

Node Linkages
   Next pointer
   Previous pointer

Size
 Size of free block

Flags
   Miscellaneous flags and fields

   Any additional data that helps you with your design

Used Header
Node Linkages
   Next pointer
   Previous pointer
Size
   Size of free block
Flags
 Flags on adjacency
 Above block is Free or Used
 Below block is free or used
 Miscellaneous flags and fields that help you with your design

#define memMalloc(size)  JCTMemMalloc(size);
#define memCalloc(size)  JCTMemCalloc(size);
#define memRealloc(size) JCTMemRealloc(size);

*/

JCTHeader::JCTHeader()
{
   this->setBlockSize(0);
   this->setAboveUsed(false);
   this->setBelowUsed(false);
}

const unsigned int JCTHeader::getBlockSize()
{
   return this->m_iBlockSize;
};

void JCTHeader::setBlockSize(const unsigned int &size)
{
   this->m_iBlockSize = size;
};

const bool JCTHeader::getAboveUsed()
{
   return m_bAboveUsed;
};

void JCTHeader::setAboveUsed(const bool &used)
{
   this->m_bAboveUsed = used;
};

const bool JCTHeader::getBelowUsed()
{
   return this->m_bBelowUsed;
};

void JCTHeader::setBelowUsed(const bool &used)
{
   this->m_bBelowUsed = used;
};

JCTHeap::JCTHeap()
{
   this->m_header = new JCTHeader();
   this->m_Memory = 0;
   this->m_eType = JCTHEAP_SIZE;
   this->m_pNext = 0;
   this->m_pPrevious = 0;

};

unsigned int JCTHeap::getHeapType()
{
   return this->m_eType;
};

void JCTHeap::setHeapType(const enum JCTHEAP_TYPE &type)
{
   this->m_eType = type;
};

void* JCTHeap::Allocate(enum HEAP_TYPE type, const size_t &size, char* file, const unsigned int &uiLine, const bool &bArray)
{
      //search for type
      bool bFound = false;
      vJCTMemoryBlock::const_iterator	it			= m_pFree.begin();
      unsigned int iSize=0, iHeader=0, iTemp=0, iBlockSize=0, iNeededSize = size+(sizeof(JCTHeader));
      JCTMemoryChunk *pTemp = 0, *pHold = 0;
         while (it != m_pFree.end () && !bFound)
	      {
            pTemp = (JCTMemoryChunk*)&(*it);
            iBlockSize = pTemp->m_header->getBlockSize();

            if(iBlockSize <= iNeededSize)
            {
               bFound = true;
			      it = m_pFree.end ();
            }
            else
            {
               it++;
            }
            
            iSize+=iBlockSize;
            iHeader += (int)sizeof(JCTHeader);
         }
         iTemp = m_iSize - (iSize+iHeader);
         
         

         if(iTemp < size)
         {
            printf("Not enough space available\n");
         }
         else
         {

            pTemp->m_pPrevious->m_pNext = pTemp->m_pNext;
            pTemp->m_pNext->m_pPrevious = pTemp->m_pPrevious;

            JCTMemoryChunk *a = new JCTMemoryChunk();
            
            a->m_Memory = pTemp->m_Memory;

            a->m_header->setBlockSize(size);
            a->m_pNext = 0;
            a->m_pPrevious = (JCTMemoryChunk*)&(*m_pUsed.end());
            a->m_header->setAboveUsed(true);
            a->m_header->setBelowUsed(false);
            a->m_Memory = pTemp->m_Memory + iHeader + size;
            printf("Memory Block Allocated =>>%p\n", a);
            printf("Memory Block Address =>>%p\n", a->m_Memory);
            
            m_pUsed.push_back(*a);
            /*if(pTemp)
            {
               pTemp->m_header = new JCTHeader();
               pTemp->m_header->setBelowUsed(true);
               pTemp->m_pNext = a;
            }*/
            return a->m_Memory;
         }
      //}

};

void JCTHeap::DeAllocate(enum HEAP_TYPE type, char* file, const bool &bArray)
{
};
void JCTHeap::CoalesceFree()
{
};
void JCTHeap::CoalesceUsed()
{
};



/*When initializing the Heaps you must include a size
  If the size is greater than that of the total allocated for the entire JCTMm or
  if that which is left due to the prior Heaps that were created
  then the CreateHeap function will fail.
*/
JCTMm::JCTMm(size_t size)
{
   this->m_AllMemory = (char*)malloc(size + sizeof(JCTHeader));
   this->m_iSize = size;
   this->m_iUsedSize = 0;
};

JCTMm::~JCTMm()
{
   /*vJCTHeap::const_iterator	it			= vecHeap.begin ();
   while (it != vecHeap.end ())
   {
      if(it != vecHeap.end())
      {
         it++;
      }
      else
      {
         vecHeap.erase(it);
      }
   }*/
};

#ifdef _DEBUG
void JCTMm::CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size)
   {
      //search for type
      bool bFound = false;
      vJCTHeap::const_iterator	it			= vecHeap.begin ();
      unsigned int iSize=0, iHeader=0, iTemp=0;
      JCTHeap *pTemp = 0;
      if((this->getUsedSize() + (size+sizeof(JCTHeader)))>=this->getSize())//(int)(size+iHeader) >= (int)(m_iSize-m_iUsedSize))
      {
         printf("Requested size of %d \n exceeds the maximum capacity of %d.\n Available space is %d\n", size, m_iSize, this->getSize()-this->getUsedSize());
      }
      else
      {
         while (it != vecHeap.end () && !bFound)
	      {
            pTemp = (JCTHeap*)&(*it);
            if ((unsigned int)pTemp->getHeapType() == (unsigned int) type)
		      {
               bFound = true;
			      it = vecHeap.end ();
		      }
            else if(((pTemp->getHeapType() >= JCTHEAP_SIZE) || (pTemp->getHeapType() < 0)))
		      {
               if(pTemp->m_header->getBlockSize() <= (size+sizeof(JCTHeader)))
               {
                  bFound = true;
               }
		      }
            else
            {
               it++;
            }
            
            iSize+=pTemp->m_header->getBlockSize();
            iHeader += (int)sizeof(JCTHeader);
         }
         iTemp = m_iSize - (iSize+iHeader);
         
         if(!bFound)
         {
            if(iTemp < size)
            {
               printf("Not enough space available\n");
            }
            else
            {
               JCTHeap *a = new JCTHeap();
               a->setHeapType(type);
               a->m_header->setBlockSize(size);
               a->m_pNext = 0;
               a->m_pPrevious = pTemp;
               a->m_header->setAboveUsed(true);
               a->m_header->setBelowUsed(false);
               a->m_Memory = m_AllMemory + iHeader + iSize;
               printf("Heap Created =>>%p\n", a);
               printf("Heap Memory Address =>>%p\n", a->m_Memory);

               vecHeap.push_back(*a);
               if(pTemp)
               {
                  pTemp->m_header = new JCTHeader();
                  pTemp->m_header->setBelowUsed(true);
                  pTemp->m_pNext = a;
               }

               m_iUsedSize += (size + (sizeof(JCTHeader)));
			      printf("Size of Heap = %d\n", size);
			      printf("Used up total space = %d\n", m_iUsedSize);
            }
         }
         else
         {
            printf("Heap already exists\n");
         }
      }

   };

void JCTMm::DestroyHeap(enum JCTHEAP_TYPE type)
{
//search for type
   bool bFound = false;
   vJCTHeap::const_iterator	it			= vecHeap.begin ();
   JCTHeap *pTemp = 0;
   //if(vecHeap.)
   pTemp = (JCTHeap*)&(*it);

   while (it != vecHeap.end () && (unsigned int)pTemp->getHeapType() != (unsigned int)type)
   {
       bFound = true;
       it++;
       pTemp = (JCTHeap*)&(*it);
   }
   if(pTemp != 0)
   {
      if(pTemp->m_pPrevious != 0)
      {
         pTemp->m_pPrevious->m_pNext = pTemp->m_pNext;
         pTemp->m_pPrevious->m_header->setBelowUsed(false);
      }

      //pTemp->m_pNext->m_pPrevious = pTemp->m_pPrevious;
      m_iUsedSize -= ((pTemp->m_header->getBlockSize()) + (sizeof(JCTHeader)));
      vecHeap.erase(it);
   }
   else
   {
      //pTemp->m_pPrevious->m_header->m_bBelowUsed = false;
      //pTemp->m_pPrevious->m_pNext = 0;
      //m_iUsedSize -= pTemp->m_header->getBlockSize();
      vecHeap.erase(it);
   }
};
#else
 void JCTMm::CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size)
{
   //search for type
   bool bFound = false;
   vJCTHeap::const_iterator	it			= vecHeap.begin ();
   int iSize=0, iHeader=0;
   JCTHeap *pTemp = 0;
   //if(vecHeap.)
   while (it != vecHeap.end ())
   {
      pTemp = (JCTHeap*)&(it);
      if ((*it).m_eType == type)
	   {
         bFound = true;
		   it = vecHeap.end ();
	   }
	   else
	   {
		   it++;
	   }
      iSize+=pTemp->m_header->getBlockSize();
      iHeader += (int)sizeof(JCTHeader);
   }
   if(!bFound)
   {
      JCTHeap *a = new JCTHeap();
      a->m_eType = type;
      a->m_header->getBlockSize() = size;
      a->m_pNext = 0;
      a->m_pPrevious = pTemp;
      a->m_header->m_bAboveUsed = true;
      a->m_header->m_bBelowUsed = false;
      a->m_Memory = m_AllMemory + iHeader + iSize;
      printf("Heap Created =>>%p\n", a);
      printf("Heap Memory Address =>>%p\n", a->m_Memory);

      vecHeap.push_back(*a);
      if(pTemp)
      {
         pTemp->m_header = new JCTHeader();
         pTemp->m_header->m_bBelowUsed = true;
         pTemp->m_pNext = a;
      }
   }

};

void JCTMm::DestroyHeap(enum JCTHEAP_TYPE type)
{
//search for type
   bool bFound = false;
   vJCTHeap::const_iterator	it			= vecHeap.begin ();
   JCTHeap *pTemp = 0;
   //if(vecHeap.)
   while (it != vecHeap.end ())
   {
      if ((*it).m_eType == type)
	   {
         bFound = true;
         pTemp = (JCTHeap*)&(it);
		   it = vecHeap.end ();
	   }
	   else
	   {
		   it++;
	   }
   }
   if(pTemp != 0) 
   {
      pTemp->m_pPrevious->m_pNext = pTemp->m_pNext;
      pTemp->m_pNext->m_pPrevious = pTemp->m_pPrevious;

      vecHeap.erase(it);
   }

};
#endif

