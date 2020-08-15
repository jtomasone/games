// JCTMm.cpp : Defines the entry point for the console application.
//

#include "JCTMm.h"


extern const enum JCTHEAP_TYPE;

char* JCTMm::m_AllMemory         = 0;
size_t JCTMm::m_iSize            = 0;
size_t JCTMm::m_iUsedSize        = 0;
//vJCTHeap JCTMm::vecHeap;
size_t JCTMm::m_AllocOverhead = sizeof(JCTMemoryChunk)+sizeof(JCTHeader);
size_t JCTMm::m_HeapOverhead = sizeof(JCTHeap)+sizeof(JCTHeader);
size_t JCTMm::m_UsedSize = 0;
char* JCTMm::m_pBottom = 0;
size_t JCTMm::m_iHeapCount;
JCTHeap * JCTMm::m_pTopHeap;
JCTHeap * JCTMm::m_pBottomHeap;


static char* JCTHEAP_TYPEString(const enum JCTHEAP_TYPE type)
{
   switch(type)
   {
   case 0: return "JCTHEAP_GRAPHICS";
   break;
   case 1: return "JCTHEAP_PHYSICS";
   break;
   case 2: return "JCTHEAP_SOUND";
   break;
   case 3: return "JCTHEAP_AI";
   break;
   case 4: return "JCTHEAP_GENERAL";
   break;
   default: return "";
   };
};


JCTHeader::JCTHeader():
m_iBlockSize(0),
m_bAboveUsed(false),
m_bBelowUsed(false)
{
}

const size_t JCTHeader::getBlockSize()
{
   return this->m_iBlockSize;
};

const size_t JCTHeader::getBlockAlign()
{
   return this->m_iBlockAlign;
};

void JCTHeader::setBlockSize(const size_t &size)
{
   this->m_iBlockSize = size;
};

void JCTHeader::setBlockAlign(const size_t &align)
{
   this->m_iBlockAlign = align;
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

JCTHeap::JCTHeap():m_iUsedSize(0),m_Memory(0)
,m_pNext(0)
,m_pPrevious(0)

{
   //this->m_pFreeTop.reserve(10);
   //this->m_pUsedTop.reserve(10);

};

void JCTHeap::AddMemoryChunk(const size_t &iType, JCTMemoryChunk *pMemoryChunk)
{
   JCTMemoryChunk *pTarget=0;
   if(iType == JCTTYPE_USED)
   {
      pTarget = m_pUsedTop;
   }
   else
   {
      pTarget = m_pFreeTop;
   }
   if(0 == pTarget)
   {
      pTarget = pMemoryChunk;
      pTarget->m_pNext = 0;
      pTarget->m_pPrevious = 0;
      if(iType == JCTTYPE_USED)
      {
         m_pUsedTop = pTarget;
      }
      else
      {
         m_pFreeTop = pTarget;
      }
   }
   else
   {
      while((void*)(this->m_pNext + this->m_iUsedSize) == pTarget->m_pNext)
      {
         pTarget = pTarget->m_pNext;
      };
      pTarget->m_pNext = pMemoryChunk;
      pMemoryChunk->m_pNext = 0;
      //pMemoryChunk->m_pNext->m_pPrevious = pMemoryChunk;
      pMemoryChunk->m_pPrevious = pTarget;
   }
/*
   //first element
   if(0 != pTarget->m_pNext && 0 == pTarget->m_pPrevious)
   {
      pMemoryChunk->m_pNext = 0;
      //pMemoryChunk->m_pNext->m_pPrevious = pMemoryChunk;
      pMemoryChunk->m_pPrevious = pTarget;
   }
   //middle element
   else if(0 != pTarget->m_pNext && 0 != pTarget->m_pPrevious)
   {
      pMemoryChunk->m_pNext = 0;
      pMemoryChunk->m_pNext->m_pPrevious = pMemoryChunk;
      pTarget->m_pNext = pMemoryChunk;
      pMemoryChunk->m_pPrevious = pTarget;   
   }
   //end element
   else if(0 != pTarget->m_pPrevious && 0 == pTarget->m_pNext)
   {
      pMemoryChunk->m_pNext = 0;
      pTarget->m_pNext = pMemoryChunk;
      pMemoryChunk->m_pPrevious = pTarget;
   }
   //Initial element
   else
   {
      pTarget->m_pNext = 0;
      pTarget->m_pPrevious = 0;
   }
   */
   
}

void JCTHeap::RemoveMemoryChunk(const size_t &iType, JCTMemoryChunk *pMemoryChunk)
{
   JCTMemoryChunk *pTarget=0;
   if(!iType)
   {
      pTarget = m_pUsedTop;
   }
   else
   {
      pTarget = m_pFreeTop;
   }

   //first element
   if(0 != pMemoryChunk->m_pNext && 0 == pMemoryChunk->m_pPrevious)
   {
      pMemoryChunk->m_pNext->m_pPrevious = 0;
      pTarget = pMemoryChunk->m_pNext;
      if(!iType)
      {
         m_pUsedTop = pTarget;
      }
      else
      {
         m_pFreeTop = pTarget;
      }
   }
   //middle element
   else if(0 != pMemoryChunk->m_pNext && 0 != pMemoryChunk->m_pPrevious)
   {
      pMemoryChunk->m_pPrevious->m_pNext = pMemoryChunk->m_pNext;
      pMemoryChunk->m_pNext->m_pPrevious = pMemoryChunk->m_pPrevious;
   }
   //end element
   else if(0 != pMemoryChunk->m_pPrevious && 0 == pMemoryChunk->m_pNext)
   {
      pMemoryChunk->m_pPrevious->m_pNext = 0;
      pMemoryChunk->m_pPrevious = 0;
   }
   //Only element
   else
   {
      if(!iType)
      {
         m_pUsedTop = 0;
      }
      else
      {
         m_pFreeTop = 0;
      }
   }
}

const enum JCTHEAP_TYPE JCTHeap::getHeapType()
{
   return this->m_eType;
};

void JCTHeap::setHeapType(const enum JCTHEAP_TYPE &type)
{
   this->m_eType = type;
};
#ifdef _DEBUG
void* JCTHeap::Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray)
{
#else
void* JCTHeap::Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray)
{
#endif
      //search for type
      bool bFound = false;
      size_t iFound = 0;
      size_t iSize=0, iHeader=0, iBlockSize=0, iNeededSize = (size+JCTMm::getAllocOverhead()+align-1);
      int iTemp = 0;
      JCTMemoryChunk *pTemp = 0, *pHold = 0, *pFound = 0;
      
      if(this->m_pFreeTop)
      {
         //for(size_t x=0; x<this->m_pFreeTop.size() && !bFound; x++)
         pFound = this->m_pFreeTop;
         while(pFound)
         {
            iBlockSize = pFound->m_Header->getBlockSize();

            if(iBlockSize >= iNeededSize)
            {
               bFound = true;
               iHeader += (int)sizeof(JCTHeader);
               break;
            }
            else
            {
               iSize+=iBlockSize+align-1;
               iHeader += (int)sizeof(JCTHeader);
            }
            pFound = pFound->m_pNext;
         }
         iTemp = (int)(this->m_iSize - (iSize+iHeader));
         
         if((int)iTemp < (int)(size+align-1))
         {
            printf("Not enough space available\n");
            return NULL;
         }
         else
         {

            JCTMemoryChunk *a=0;
            //Found a JCTMemoryChunk which fits the requested size 
            if(bFound)
            {
               JCTHeader *pHeader = new (pFound->m_Memory) JCTHeader;
               a = (JCTMemoryChunk*)new (pHeader+sizeof(JCTHeader)) JCTMemoryChunk;
               this->m_iUsedSize += sizeof(JCTMemoryChunk);

               //Is the pointer a pointing to a valid JCTMemoryChunk
               if(a)
               {
                  a->m_Header = pHeader;
                  //a->m_Header = new (a+sizeof(JCTMemoryChunk)) JCTHeader;
                  this->m_iUsedSize += sizeof(JCTHeader);

                  a->m_Header->setBlockAlign(align);
                  a->m_Header->setBlockSize(size);
                  a->m_Memory = new (a+sizeof(JCTHeader)) char[size+align];
                  this->m_iUsedSize += sizeof(size);
                  a->m_PreShiftMemory = a->m_Memory;

                  //Memory Align to requested spec
                  uintptr_t mask = ~(uintptr_t)(align - 1);
                  a->m_Memory = (char*)(((uintptr_t)a->m_Memory+(align-1)) & mask);
                  
                  pFound->m_Memory += iNeededSize;
                  pFound->m_Header->setBlockSize(pFound->m_Header->getBlockSize()-iNeededSize);
               }
               else
               {
                  return NULL;
               }

               if(this->m_pUsedTop)
               {
                  
                  //a->m_Header->setAboveUsed(false);
               }
               else
               {
                  /*m_pUsedTop[(m_pUsedTop.size()-1)]->m_pNext = a;
                  a->m_pPrevious = m_pUsedTop[(m_pUsedTop.size()-1)];
                  a->m_Header->setAboveUsed(true);*/
               }

               printf("Memory Block Allocated =>>%p\n", a);
               printf("Memory Block Address =>>%p\n", a->m_Memory);
               this->AddMemoryChunk(JCTTYPE_USED, a);
               //this->m_pUsedTop.push_back(a);
               return a->m_Memory;
            }
            else
            {
               return NULL;
            }
         }
      }
      else
      {
         return NULL;
      }

};

#ifdef _DEBUG
   void JCTHeap::DeAllocate(void *p, const bool &bArray)
   {
      cout << "Dellocate from Heap=> " << JCTHEAP_TYPEString(this->getHeapType()) << endl;

#else
   void JCTHeap::DeAllocate(void *p, const bool &bArray)
   {
#endif
/*pFound = this->m_pFreeTop;
         while(pFound)
         {
            iBlockSize = pFound->m_Header->getBlockSize();

            if(iBlockSize >= iNeededSize)
            {
               bFound = true;
               iHeader += (int)sizeof(JCTHeader);
            }
            else
            {
               iSize+=iBlockSize+align-1;
               iHeader += (int)sizeof(JCTHeader);
            }
            pFound = pFound->m_pNext;
         }
*/
   JCTMemoryChunk *pTemp = 0, *pFound = 0;
   size_t iAlign=0;
   pFound = this->m_pUsedTop;
//   for(size_t x=0; x < this->m_pUsedTop.size(); x++)
   while(pFound)
   {
      if(pFound->m_Header->getBlockAlign() == MEM_ALIGN_128_BYTES)
      {
         iAlign = 4;
      }
      else
      {
         iAlign = 0;
      }
      if(p == (pFound->m_Memory + iAlign))
      {
		   memset(pFound->m_PreShiftMemory, 0, pFound->m_Header->getBlockSize());
       	pFound->m_Header->setBlockSize(pFound->m_Header->getBlockSize()+pFound->m_Header->getBlockAlign());
		   pFound->m_Header->setBlockAlign(0);
         RemoveMemoryChunk(JCTTYPE_USED, pFound);
         AddMemoryChunk(JCTTYPE_FREE, pFound);
		   //this->m_pFreeTop.push_back(this->m_pUsedTop[x]);
         //this->m_pUsedTop.erase(this->m_pUsedTop.begin() + x);
         break;
      }
      pFound = pFound->m_pNext;
   }
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
JCTMm::JCTMm()
{

};

JCTMm::~JCTMm()
{
   
};

void JCTMm::Cleanup()
{
/*   for(int x=(int)vecHeap.size()-1; x>=0; x--)
   {
      JCTHeap *pTemp = vecHeap[x];
      if(!vecHeap[x]->m_pFreeTop.empty())
      {
         vecHeap[x]->m_pFreeTop.clear();
      }
      if(!vecHeap[x]->m_pUsedTop.empty())
      {
         vecHeap[x]->m_pUsedTop.clear();
      }
      vecHeap.erase((vecHeap.begin()+x));
   }
   vecHeap.clear();*/
   memset(JCTMm::m_AllMemory, 0, JCTMm::m_iSize);
   free(JCTMm::m_AllMemory);
   //delete []JCTMm::m_AllMemory;
}


void JCTMm::InitMemory(const size_t &size)
{
   JCTMm::m_AllMemory = (char*)new char[((size+(JCTHEAP_COUNT*JCTMm::m_HeapOverhead)))];
   memset(JCTMm::m_AllMemory, 0, ((size+(JCTHEAP_COUNT*JCTMm::m_HeapOverhead))));
   /*for(size_t x=0; x<size; x++)
   {
      strcpy((m_AllMemory+x), "0");
   }*/
   //JCTMm::vecHeap.reserve(JCTHEAP_COUNT);
   JCTMm::setSize(((size+(JCTHEAP_COUNT*JCTMm::m_HeapOverhead))));
   JCTMm::m_pBottom = JCTMm::m_AllMemory+JCTMm::getSize();
};

#ifdef _DEBUG

void* JCTMm::Allocate(enum JCTHEAP_TYPE type, const size_t &size, char* file, const size_t &uiLine, const bool &bArray, const enum ALIGNMENT_SIZE &align)
{
   cout << "Allocate on Heap=> " << JCTHEAP_TYPEString(type) << endl;
   cout << "  requested File=> " << file << endl;
   cout << "  requested Line=> " << uiLine << endl;
#else

void* JCTMm::Allocate(enum JCTHEAP_TYPE type, const size_t &size, const bool &bArray, const enum ALIGNMENT_SIZE &align)
{
#endif
   JCTHeap *pHeap=0;
   size_t iReturn = 0;
   //for(size_t x=0; x<vecHeap.size(); x++)
   pHeap = m_pTopHeap;
   while(pHeap)
   {
      if(pHeap->getHeapType() == type)
      {
         break;
      }
      pHeap = pHeap->m_pNext;
   }

   void *a = pHeap->Allocate(align, size, bArray);
   return a;
};

#ifdef _DEBUG

void JCTMm::DeAllocate(void *p, char* file, const size_t &uiLine, const bool &bArray)
{
   cout << "  Is this an Array=> " << bArray << endl;
   cout << "    requested File=> " << file << endl;
   cout << "    requested Line=> " << uiLine << endl;

#else

void JCTMm::DeAllocate(void *p, const bool &bArray)
{
#endif

   JCTHeap *pHeap=0;
   size_t iReturn = 0;
   //for(size_t x=0; x<vecHeap.size(); x++)
   pHeap = m_pTopHeap;
   while(pHeap)
   {
      if((void*)p >= (void*)pHeap->m_Memory && (void*)p < (void*)(pHeap->m_pBottom))
      {
         pHeap->DeAllocate(p, bArray);
         break;
      }
      pHeap = pHeap->m_pNext;
   }

};

void JCTMm::CreateFixedBlockHeap(const enum JCTHEAP_TYPE &type, const size_t &size)  
{
   //search for type
   bool bFound = false;

   size_t iHeader=0, iTemp=0, iFound=0;
   int iSize=0;
   JCTHeap *pTemp = 0;
   iHeader = 0;

   if((JCTMm::getUsedSize() + (size+sizeof(JCTHeader)))>=JCTMm::getSize())//(int)(size+iHeader) >= (int)(m_iSize-m_iUsedSize))
   {
      printf("Requested size of %d \n exceeds the maximum capacity of %d.\n Available space is %d\n", size, JCTMm::m_iSize, getSize()-getUsedSize());
   }
   else
   {
      char *pLastBottom=0;
		if(m_pTopHeap)
		{
         JCTHeap *pTemp=0, *pHeap=0;
			//for(size_t x=0; x<JCTMm::vecHeap.size(); x++)
         pHeap = m_pTopHeap;
         while(pHeap)
			{
            pTemp = pHeap; 
				if (pHeap->getHeapType() == (size_t) type)
				{
					bFound = true;
	            iHeader += (int)sizeof(pHeap->m_Header);
				}
            else
            {
				/*else if(((JCTMm::vecHeap[x]->getHeapType() >= JCTHEAP_SIZE) || (JCTMm::vecHeap[x]->getHeapType() < 0)))
				{
					if(JCTMm::vecHeap[x]->m_Header->getBlockSize() <= (size+sizeof(JCTHeader)))
					{
						iFound = x;
						bFound = true;
					}
				}*/
	         pLastBottom = pHeap->m_pBottom+1;
            pHeap = pHeap->m_pNext;
				//iSize+=(int)((size_t)JCTMm::vecHeap[x]->m_Header->getBlockSize());// + (size_t)JCTMm::vecHeap[x]->m_Header->getBlockAlign());
				//iHeader += (int)sizeof(JCTMm::vecHeap[x]->m_Header);
            }
			}
		}
      if(0 == pLastBottom)
      {
         pLastBottom = JCTMm::m_AllMemory+iSize+iHeader;
      }
      iTemp = JCTMm::m_iSize - (iSize+iHeader);
      
      if(!bFound)
      {
         if(iTemp < size)
         {
            printf("Not enough space available\n");
         }
         else
         {
            
            JCTHeap *a = new (pLastBottom)JCTHeap;//[JCTMm::m_AllMemory+(iSize+iHeader)]JCTHeap;//(reinterpret_cast <JCTHeap*>(JCTMm::m_AllMemory+(iSize+iHeader)));
            JCTMm::m_UsedSize += sizeof(JCTHeap);

            a->m_Header = new (a) JCTHeader;//char[(reinterpret_cast <JCTHeader*>(a))]JCTHeader;//a-sizeof(JCTHeader);

            JCTMm::m_UsedSize += sizeof(JCTHeader);

            //memset(a, 0x99, 1);
            //memset(a->m_Header, 0x98, 1);
            //memset((char*)a+size, 0x98, 1);
//            memset(0x0078A9B4, 0x99, 1)
//               (a+size-1)-(iSize+iHeader), 0x99, 1);

            

            if(JCTMm::m_pTopHeap)
            {
               a->m_pPrevious = JCTMm::m_pBottomHeap;
            }
            //a->m_header = (JCTHeader*)JCTMm::m_AllMemory;
            a->setHeapType(type);
            a->m_Header->setBlockSize(size);
            a->m_Header->setAboveUsed(bFound);
            a->m_Header->setBelowUsed(bFound);
            a->m_iSize = size;
            a->m_iUsedSize = 0;
            a->m_pNext = 0; 
            a->m_Memory = new ((char*)pLastBottom+JCTMm::m_HeapOverhead+JCTMm::m_HeapOverhead) char[size];
            //a->m_iUsedSize += size;
            //memset((char*)a->m_Memory, 0x77, 1);

            JCTMemoryChunk *b = new (a->m_Memory)JCTMemoryChunk;//(a->m_Memory);
            a->m_iUsedSize += sizeof(JCTMemoryChunk);
            //memset((char*)b, 0x74, 1);
            b->m_Header = new (b+sizeof(JCTMemoryChunk))JCTHeader;//,__LINE__, __FILE__) JCTHeader;//(reinterpret_cast <JCTHeader*>(b));
            a->m_iUsedSize += sizeof(JCTHeader);

            //memset((char*)b->m_Header, 0x72, 1);
            b->m_Memory = new ((char*)a->m_Memory+JCTMm::m_AllocOverhead) char[(size-JCTMm::m_AllocOverhead)];//new (a->m_Memory) char[size];// JCTMm::m_AllMemory+sizeof(JCTHeap)+(iSize+iHeader);
            b->m_Header->setBlockSize(size-JCTMm::m_AllocOverhead);
            //b->m_Memory = (char*)(b+sizeof(JCTMemoryChunk));
				//memset(b->m_Memory, 0xFF, size);
            a->m_pBottom = (char*)a+a->m_iUsedSize + size;

            a->AddMemoryChunk(JCTTYPE_FREE, b);
            //m_pFreeTop.push_back(b);
            //a->m_Memory = (char*)(JCTMm::m_AllMemory + (iHeader + iSize));
            //a->m_Header->setBlockSize(size);
            //a->Allocate(size, __FILE__, __LINE__, false);
            printf("Heap Created =>>%p\n", a);
            printf("Heap Memory Address =>>%p\n", a->m_Memory);
            JCTMm::AddHeap(a);

//            JCTMm::vecHeap.push_back(a);
            /*if(pTemp)
            {
               pTemp->m_header = (JCTHeader*)pTemp;//new JCTHeader();
               pTemp->m_Header->setBelowUsed(true);
               pTemp->m_pNext = a;
            }
            */

            JCTMm::m_iUsedSize += (size + (sizeof(JCTHeader)));
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
   static void DestroyFixedBlockHeap(enum JCTHEAP_TYPE type);

void JCTMm::CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size)
{
   //search for type
   bool bFound = false;

   size_t iHeader=0, iTemp=0, iFound=0;
   int iSize=0;
   JCTHeap *pTemp = 0;
   iHeader = 0;

   if((JCTMm::getUsedSize() + (size+sizeof(JCTHeader)))>=JCTMm::getSize())//(int)(size+iHeader) >= (int)(m_iSize-m_iUsedSize))
   {
      printf("Requested size of %d \n exceeds the maximum capacity of %d.\n Available space is %d\n", size, JCTMm::m_iSize, getSize()-getUsedSize());
   }
   else
   {
      char *pLastBottom=0;
		if(JCTMm::m_pTopHeap)
		{
         JCTHeap *pTemp = 0, *pHeap = 0;
//			for(size_t x=0; x<JCTMm::vecHeap.size(); x++)
         pHeap = JCTMm::m_pTopHeap;
         while(pHeap)
			{
            pTemp = pHeap; 
				if (pHeap->getHeapType() == (size_t) type)
				{
					//iFound = x;
					bFound = true;
	            iHeader += (int)sizeof(pHeap->m_Header);
				}
            else
            {
				/*else if(((JCTMm::vecHeap[x]->getHeapType() >= JCTHEAP_SIZE) || (JCTMm::vecHeap[x]->getHeapType() < 0)))
				{
					if(JCTMm::vecHeap[x]->m_Header->getBlockSize() <= (size+sizeof(JCTHeader)))
					{
						iFound = x;
						bFound = true;
					}
				}*/
	         pLastBottom = pHeap->m_pBottom+1;
				iSize+=(int)((size_t)pHeap->m_Header->getBlockSize());// + (size_t)JCTMm::vecHeap[x]->m_Header->getBlockAlign());
				iHeader += (int)sizeof(pHeap->m_Header);
            pHeap = pHeap->m_pNext;
            }
			}
		}
      if(0 == pLastBottom)
      {
         pLastBottom = JCTMm::m_AllMemory+iSize+iHeader;
      }
      iTemp = JCTMm::m_iSize - (iSize+iHeader);
      
      if(!bFound)
      {
         if(iTemp < size)
         {
            printf("Not enough space available\n");
         }
         else
         {
            
            JCTHeap *a = new (pLastBottom)JCTHeap;//[JCTMm::m_AllMemory+(iSize+iHeader)]JCTHeap;//(reinterpret_cast <JCTHeap*>(JCTMm::m_AllMemory+(iSize+iHeader)));
            JCTMm::m_UsedSize += sizeof(JCTHeap);

            a->m_Header = new (a+sizeof(JCTHeap)) JCTHeader;//char[(reinterpret_cast <JCTHeader*>(a))]JCTHeader;//a-sizeof(JCTHeader);

            JCTMm::m_UsedSize += sizeof(JCTHeader);

            //memset(a, 0x99, 1);
            //memset(a->m_Header, 0x98, 1);
            //memset((char*)a+size, 0x98, 1);
//            memset(0x0078A9B4, 0x99, 1)
//               (a+size-1)-(iSize+iHeader), 0x99, 1);

            

            if(JCTMm::m_pTopHeap)
            {
               a->m_pPrevious = JCTMm::m_pBottomHeap;
            }
            
            //a->m_header = (JCTHeader*)JCTMm::m_AllMemory;
            a->setHeapType(type);
            a->m_Header->setBlockSize(size);
            a->m_Header->setAboveUsed(bFound);
            a->m_Header->setBelowUsed(bFound);
            a->m_iSize = size;
            a->m_iUsedSize = 0;
            a->m_pNext = 0; 
            a->m_Memory = new ((char*)pLastBottom+JCTMm::m_HeapOverhead+JCTMm::m_HeapOverhead) char[size];
            //a->m_iUsedSize += size;
            //memset((char*)a->m_Memory, 0x77, 1);

            JCTMemoryChunk *b = new (a->m_Memory)JCTMemoryChunk;//(a->m_Memory);
            a->m_iUsedSize += sizeof(JCTMemoryChunk);
            //memset((char*)b, 0x74, 1);
            b->m_Header = new (b+sizeof(JCTMemoryChunk))JCTHeader;//,__LINE__, __FILE__) JCTHeader;//(reinterpret_cast <JCTHeader*>(b));
            a->m_iUsedSize += sizeof(JCTHeader);

            //memset((char*)b->m_Header, 0x72, 1);
            b->m_Memory = new ((char*)a->m_Memory+JCTMm::m_AllocOverhead) char[(size-JCTMm::m_AllocOverhead)];//new (a->m_Memory) char[size];// JCTMm::m_AllMemory+sizeof(JCTHeap)+(iSize+iHeader);
            b->m_Header->setBlockSize(size-JCTMm::m_AllocOverhead);
            //b->m_Memory = (char*)(b+sizeof(JCTMemoryChunk));
				//memset(b->m_Memory, 0xFF, size);
            a->m_pBottom = (char*)a+a->m_iUsedSize + size;

            //a->m_pFreeTop.push_back(b);
            a->AddMemoryChunk(JCTTYPE_FREE, b);
            //a->m_Memory = (char*)(JCTMm::m_AllMemory + (iHeader + iSize));
            //a->m_Header->setBlockSize(size);
            //a->Allocate(size, __FILE__, __LINE__, false);
            printf("Heap Created =>>%p\n", a);
            printf("Heap Memory Address =>>%p\n", a->m_Memory);

            //JCTMm::vecHeap.push_back(a);
            JCTMm::AddHeap(a);
            
            
            /*if(pTemp)
            {
               pTemp->m_header = (JCTHeader*)pTemp;//new JCTHeader();
               pTemp->m_Header->setBelowUsed(true);
               pTemp->m_pNext = a;
            }
            */

            JCTMm::m_iUsedSize += (size + (sizeof(JCTHeader)));
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

void JCTMm::AddHeap(JCTHeap *pHeap)
{
   if(m_pTopHeap == 0)
   {
      pHeap->m_pNext = 0;
      pHeap->m_pPrevious = 0;
      m_pTopHeap = pHeap;
      m_pBottomHeap = pHeap;
   }
   else
   {
      m_pBottomHeap->m_pNext = pHeap;
      pHeap->m_pPrevious = m_pBottomHeap;
      pHeap->m_pNext = 0;
      m_pBottomHeap = pHeap;
   }
   JCTMm::m_iHeapCount++;

}

void JCTMm::DestroyHeap(enum JCTHEAP_TYPE type)
{
//search for type
   bool bFound = false;
   size_t iFound = 0;
   JCTHeap *pTemp = 0, *pHeap = 0;

   //for(size_t x=0; x<vecHeap.size(); x++)
   pHeap = JCTMm::m_pTopHeap;
   while(pHeap)
   {
      if((size_t)pHeap->getHeapType() == (size_t)type)
      {
         //iFound = x;
         pTemp = pHeap;
         bFound = true;
         break;
      }
      pHeap = pHeap->m_pNext;
   }

   if(bFound)
   {
      if(pTemp->m_pPrevious != 0)
      {
         pTemp->m_pPrevious->m_pNext = pTemp->m_pNext;
         pTemp->m_pPrevious->m_Header->setBelowUsed(false);
      }

      //pTemp->m_pNext->m_pPrevious = pTemp->m_pPrevious;
      m_iUsedSize -= ((pTemp->m_Header->getBlockSize()) + (sizeof(JCTHeader)));
      //pTemp->m_pFreeTop.clear();
      //pTemp->m_pUsedTop.clear();
      //vecHeap.erase(vecHeap.begin()+iFound);

   }
   else
   {
      //pTemp->m_pPrevious->m_Header->m_bBelowUsed = false;
      //pTemp->m_pPrevious->m_pNext = 0;
      m_iUsedSize -= pTemp->m_Header->getBlockSize();
      //vecHeap.erase(vecHeap.begin()+iFound);
   }
};
#ifdef _DEBUG 
//----------------------------------------------------------------------------
void* JCTMm::operator new (size_t size)
{
   return JCTMm::Allocate(JCTHEAP_GENERAL, size, __FILE__, __LINE__, false, MEM_ALIGN_4_BYTES);
}
//----------------------------------------------------------------------------
void* JCTMm::operator new[](size_t size)
{
    return JCTMm::Allocate(JCTHEAP_GENERAL, size, __FILE__, __LINE__, true, MEM_ALIGN_4_BYTES);
}

//----------------------------------------------------------------------------
void* JCTMm::operator new (size_t size, enum JCTHEAP_TYPE type, char* file, unsigned int line, const enum ALIGNMENT_SIZE &align)
{
    return JCTMm::Allocate(type, size, file, line, false, align);
}

//----------------------------------------------------------------------------
void* JCTMm::operator new[](size_t size, enum JCTHEAP_TYPE type, char* file, unsigned int line, const enum ALIGNMENT_SIZE &align)
{
    return JCTMm::Allocate(type, size, file, line, true, align);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete[] (void* p, enum JCTHEAP_TYPE type, char* file, unsigned int line)
{
    JCTMm::DeAllocate((char*)p, file, line, true);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete (void* p, char* file, unsigned int line)
{
    JCTMm::DeAllocate((char*)p, file, line, false);
}
void JCTMm::operator delete (void* p, size_t uiSize, enum JCTHEAP_TYPE type, char* file, unsigned int line, const enum ALIGNMENT_SIZE &align)
{
    JCTMm::DeAllocate((char*)p, file, line, false);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete (void* p, enum JCTHEAP_TYPE type, char* file, unsigned int line)
{
    JCTMm::DeAllocate((char*)p, file, line, false);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete[] (void* p, char* file, unsigned int line)
{
    JCTMm::DeAllocate((char*)p, file, line, true);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete (void* p)
{
    JCTMm::DeAllocate((char*)p, __FILE__, __LINE__, false);
}
//----------------------------------------------------------------------------
void JCTMm::operator delete[] (void* p)
{
    JCTMm::DeAllocate((char*)p, __FILE__, __LINE__, true);
}


#else
 
//----------------------------------------------------------------------------
void* JCTMm::operator new (size_t size)
{
   return JCTMm::Allocate(JCTHEAP_GENERAL, size, false, MEM_ALIGN_4_BYTES);
}
//----------------------------------------------------------------------------
void* JCTMm::operator new[](size_t size)
{
    return JCTMm::Allocate(JCTHEAP_GENERAL, size, true, MEM_ALIGN_4_BYTES);
}

//----------------------------------------------------------------------------
void* JCTMm::operator new (size_t size, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align)
{
    return JCTMm::Allocate(type, size, false, align);
}

//----------------------------------------------------------------------------
void* JCTMm::operator new[](size_t size, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align)
{
    return JCTMm::Allocate(type, size, true, align);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete[] (void* p, enum JCTHEAP_TYPE type)
{
    JCTMm::DeAllocate((char*)p, true);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete (void* p)
{
    JCTMm::DeAllocate((char*)p, false);
}
void JCTMm::operator delete (void* p, size_t uiSize, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align)
{
    JCTMm::DeAllocate((char*)p, false);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete (void* p, enum JCTHEAP_TYPE type)
{
    JCTMm::DeAllocate((char*)p, false);
}

//----------------------------------------------------------------------------
void JCTMm::operator delete[] (void* p)
{
    JCTMm::DeAllocate((char*)p, true);
}

#endif

