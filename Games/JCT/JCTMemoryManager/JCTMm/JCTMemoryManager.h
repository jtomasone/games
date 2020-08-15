//The header file for the JCTMm Class as well as the supporting structures.
//Author Joe Tomasone

enum JCTHEAP_TYPE
{
   JCTHEAP_GRAPHICS,
   JCTHEAP_PHYSICS,
   JCTHEAP_SOUND,
   JCTHEAP_AI,
   JCTHEAP_GENERAL,
   JCTHEAP_SIZE
};


struct JCTHeap;

struct JCTHeader
{
   JCTHeader();
   const unsigned int JCTHeader::getBlockSize();
   void setBlockSize(const unsigned int &size); 
   const bool getAboveUsed();
   void setAboveUsed(const bool &used);
   const bool getBelowUsed();
   void setBelowUsed(const bool &used);

private:
   unsigned int m_iBlockSize;
   bool m_bAboveUsed;
   bool m_bBelowUsed;
};

struct JCTMemoryChunk
{
   JCTHeader *m_header;
   JCTMemoryChunk *m_pNext;
   JCTMemoryChunk *m_pPrevious;
   char* m_Memory;
};

typedef std::vector<JCTMemoryChunk>vJCTMemoryBlock;

struct JCTHeap
{
   JCTHeap::JCTHeap();;
   unsigned int JCTHeap::getHeapType();
   void JCTHeap::setHeapType(const enum JCTHEAP_TYPE &type);
   void* Allocate(enum HEAP_TYPE type, const size_t &size, char* file, const unsigned int &uiLine, const bool &bArray);
   void DeAllocate(enum HEAP_TYPE type, char* file, const bool &bArray);
   void CoalesceFree();
   void CoalesceUsed();

   JCTHeader *m_header;
   JCTHeap *m_pNext;
   JCTHeap *m_pPrevious;
   char* m_Memory;
private:
   JCTHEAP_TYPE m_eType;
   unsigned int m_iSize;
   vJCTMemoryBlock m_pUsed;
   vJCTMemoryBlock m_pFree;


};

typedef std::vector<JCTHeap>vJCTHeap;


//So to initialize the JCTMm you must include a total size of memory you wish to use
class JCTMm
{
public:
   JCTMm(size_t size);
   ~JCTMm();

/*When allocating to a heap and the heap has not been initialized yet or there is no more space 
  for this particular Heap the function will fail.
*/

/*When initializing the Heaps you must include a size
  If the size is greater than that of the total allocated for the entire JCTMm or
  if that which is left due to the prior Heaps that were created
  then the CreateHeap function will fail.
*/
#ifdef _DEBUG
   void CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   void DestroyHeap(enum JCTHEAP_TYPE type);
#else
   void CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   void DestroyHeap(enum JCTHEAP_TYPE type);
#endif

#ifdef _DEBUG
   void * operator new(size_t size, const enum JCTHEAP_TYPE &type)
   {
      //create new memory space
      
      if(type)
      {
      }
         void *p = malloc(size);
      //tracking print
      printf("Overloaded new(%p) \n", p);
      //return the pointer, constructor is called after this operation
      return p;
   }

   void operator delete(void *p, const enum JCTHEAP_TYPE &type)
   {
      if(type)
      {
      }
      //destructor is called first, then tenter this operation
      printf("Overloaded delete(%p) \n", p);
      //release memory
      free(p);
   }

   void *operator new[](size_t size, const enum JCTHEAP_TYPE &type)
   {
      if(type)
      {
      }
      //creates memory page size
      void *p = malloc(size);
      //tracking pointer
      //constructor is called after this operation
      return p;
   }

   void operator delete[](void *p, const enum HEAP_TYPE &type)
   {
      if(type)
      {
      }
      //estructor is called first, then enter this operator
      printf("Overloaded delete[](%p) \n",p);
      //release memory
      free(p);
   }
#else
   void * operator new(size_t size, const enum JCTHEAP_TYPE &type)
   {
      //create new memory space
      
      if(type)
      {
      }
         void *p = malloc(size);
      //tracking print
      printf("Overloaded new(%p) \n", p);
      //return the pointer, constructor is called after this operation
      return p;
   }

   void operator delete(void *p, const enum JCTHEAP_TYPE &type)
   {
      if(type)
      {
      }
      //destructor is called first, then tenter this operation
      printf("Overloaded delete(%p) \n", p);
      //release memory
      free(p);
   }

   void *operator new[](size_t size, const enum JCTHEAP_TYPE &type)
   {
      if(type)
      {
      }
      //creates memory page size
      void *p = malloc(size);
      //tracking pointer
      //constructor is called after this operation
      return p;
   }

   void operator delete[](void *p, const enum HEAP_TYPE &type)
   {
      if(type)
      {
      }
      //estructor is called first, then enter this operator
      printf("Overloaded delete[](%p) \n",p);
      //release memory
      free(p);
   }
#endif

   void JCTMm::setSize(const unsigned int &size)
   {
      this->m_iSize = size;
   };
   
   const unsigned int JCTMm::getSize()
   {
      return m_iSize;
   };

   void JCTMm::setUsedSize(const unsigned int &size)
   {
      this->m_iUsedSize = size;
   };

   const unsigned int JCTMm::getUsedSize()
   {
      return m_iUsedSize;
   };

private:
   char* m_AllMemory;
   unsigned int m_iSize;
   unsigned int m_iUsedSize;
   vJCTHeap vecHeap;
   JCTHeader *m_pUsed;
   JCTHeader *m_pFree;
};