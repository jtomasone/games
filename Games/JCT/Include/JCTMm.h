//The header file for the JCTMm Class as well as the supporting structures.
//Author Joe Tomasone

#ifndef JCTMM_H
#pragma once

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;


const enum JCTMEMORY_TYPE
{
   JCTTYPE_USED,
   JCTTYPE_FREE
};

const enum ALIGNMENT_SIZE
{
   MEM_ALIGN_4_BYTES=4,
   MEM_ALIGN_8_BYTES=8,
   MEM_ALIGN_16_BYTES=16,
   MEM_ALIGN_32_BYTES=32,
   MEM_ALIGN_64_BYTES=64,
   MEM_ALIGN_128_BYTES=128,
   MEM_ALIGN_256_BYTES=256
};

const enum JCTHEAP_TYPE
{
   JCTHEAP_GRAPHICS,
   JCTHEAP_PHYSICS,
   JCTHEAP_SOUND,
   JCTHEAP_AI,
   JCTHEAP_GENERAL,
   JCTHEAP_COUNT
};

#define JCTMm_NEW new (__FILE__,__LINE__)
#define JCTMm_DELETE delete (__FILE__,__LINE__)

struct JCTHeap;
class JCTMm;
struct JCTHeader
{
   JCTHeader();
   void setBlockSize(const size_t &size); 
   void setBlockAlign(const size_t &align); 
   void setAboveUsed(const bool &used);
   void setBelowUsed(const bool &used);
   const bool getAboveUsed();
   const bool getBelowUsed();
   const size_t getBlockSize();
   const size_t getBlockAlign();


//private:
   size_t m_iBlockSize;
   size_t m_iBlockAlign;
   bool m_bAboveUsed;
   bool m_bBelowUsed;
};

struct JCTMemoryChunk
{
   JCTHeader *m_Header;
   JCTMemoryChunk *m_pNext;
   JCTMemoryChunk *m_pPrevious;
   char* m_Memory;
   char* m_PreShiftMemory;

};

template<typename T, typename Allocator = allocator<T>>
   
class logging_allocator
{
private:
public:
   Allocator alloc;
   typedef typename Allocator::size_type size_type;
   typedef typename Allocator::difference_type difference_type;
   typedef typename Allocator::pointer pointer;
   typedef typename Allocator::const_pointer const_pointer;
   typedef typename Allocator::reference reference;
   typedef typename Allocator::const_reference const_reference;
   typedef typename Allocator::value_type value_type;
/*
   void * operator new(size_t size)
   {
      void *p = malloc(size);
      printf("Overloaded new(%p)\n",p);
      return p;
   }
   void operator delete(void *p)
   {
      printf("Overloaded delete(%p)\n", p);
      free(p);
   }
   void * operator new[](size_t size)
   {
      void *p = malloc(size);
      printf("Overloaded new[](%p)\n",p);
      return p;
   }
   void operator delete[](void *p)
   {
      printf("Overloaded delete[](%p)\n", p);
      free(p);
   }
*/
   template <typename U>struct rebind
   {
      typedef logging_allocator<U,typename Allocator::template rebind<U>::other> other;
   };

   logging_allocator()
   {
   };

   logging_allocator(const logging_allocator &x):alloc(x.alloc)
   {
   };
   
   template <typename U>
      logging_allocator(const logging_allocator<U,
   typename Allocator::template rebind<U>::other> &x)
      :alloc(x.alloc){};

      ~logging_allocator(){};

      pointer address(reference x) const
      {
         return alloc.address(x);
      };

      const_pointer address(const_reference x) const
      {
         return alloc.const_pointer(x);
      };

      size_type max_size() const
      {
         return alloc.max_size();
      };

      void construct( pointer p, const value_type &val)
      {
         alloc.construct(p, val);
      };

      void destroy(pointer p)
      {
         alloc.destroy(p);
      };

      /*
      pointer allocate(size_type n, const void *hint = 0)
      {
         pointer result = alloc.allocate(n, hint);

         //stl_mem_track tmp;
         printf("allocate() addr 0x%p num: %d \n", result, n);
         return result;
      };
      */
      pointer allocate(size_type n, const void *hint = 0)
      {
         //pointer result = static_cast<pointer>(logging_allocator::operator new (n*sizeof(T)));///((int *)_Allocate(n,hint));//allocate(n, hint);
         pointer result = static_cast<pointer>(JCTMm::Allocate(JCTHEAP_GRAPHICS, (n*sizeof(T)), __FILE__, __LINE__, false, MEM_ALIGN_256_BYTES));
         /*
            static void* Allocate(const enum JCTHEAP_TYPE type, const size_t &size, char* file, const size_t &uiLine, const bool &bArray, const enum ALIGNMENT_SIZE &align);
   static void DeAllocate(void *p, char* file, const size_t &uiLine, const bool &bArray);
   */
         //pointer result = static_cast<pointer> 
         //stl_mem_track tmp;
         printf("allocate() addr 0x%p num: %d \n", result, n);
         return result;
      };

      void deallocate(pointer p, size_type n)
      {
         //stl_mem_track tmp;
         printf("deallocate() addr 0x%p \n", p);
         logging_allocator::operator delete(p);
         //alloc.deallocate(p,n);
      };
};

template <typename T, typename Allocator1, typename U, typename Allocator2>
bool operator == (const logging_allocator<T, Allocator1>& x, const logging_allocator<U, Allocator2>& y)
{
   return x.alloc == y.alloc;
};

template <typename T, typename Allocator1, typename U, typename Allocator2>
bool operator != (const logging_allocator<T, Allocator1>& x, const logging_allocator<U, Allocator2>& y)
{
   return x.alloc = y.alloc;
};

typedef std::vector<JCTMemoryChunk*, logging_allocator<JCTMemoryChunk*>>vJCTMemoryBlock;


struct JCTHeap
{
   JCTHeap();
   const enum JCTHEAP_TYPE getHeapType();
   void setHeapType(const enum JCTHEAP_TYPE &type);
   void AddMemoryChunk(const size_t &iType, JCTMemoryChunk *pMemoryChunk);
   void RemoveMemoryChunk(const size_t &iType, JCTMemoryChunk *pMemoryChunk);
   
#ifdef _DEBUG
   void* Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray);
   void DeAllocate(void *p, const bool &bArray);
#else
   void* Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray);
   void DeAllocate(void *p, const bool &bArray);
#endif

   void CoalesceFree();
   void CoalesceUsed();

   JCTHeader *m_Header;
   JCTHeap *m_pNext;
   JCTHeap *m_pPrevious;
   char* m_Memory;
   size_t m_iSize;
   
   JCTMemoryChunk *m_pUsedTop;
   JCTMemoryChunk *m_pFreeTop;

   JCTMemoryChunk *m_pUsedEnd;
   JCTMemoryChunk *m_pFreeEnd;
   size_t m_iUsedSize;
   char* m_pBottom;
private:
   JCTHEAP_TYPE m_eType;
};


struct JCTFbmChunk
{
   JCTFbmChunk *m_pNext;
   char* m_Memory;
   char* m_PreShiftMemory;
};

typedef std::vector<JCTFbmChunk*>vJCTFbm;
/*
struct JCTFbh
{
   JCTFbh();
   const enum JCTHEAP_TYPE getHeapType();
   void setHeapType(const enum JCTHEAP_TYPE &type);

#ifdef _DEBUG
   void* Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray);
   void DeAllocate(void *p, const bool &bArray);
#else
   void* Allocate(const enum ALIGNMENT_SIZE &align, const size_t &size, const bool &bArray);
   void DeAllocate(void *p, const bool &bArray);
#endif

   JCTHeader *m_Header;
   char* m_Memory;
   size_t m_iSize;
   JCTFbmChunk *m_pUsedTop;
   JCTFbmChunk *m_pFreeTop;
//   vJCTFbm m_pUsedTop;
//   vJCTFbm m_pFreeTop;
   size_t m_iUsedSize;
   char* m_pBottom;
private:
   JCTHEAP_TYPE m_eType;
};
*/
typedef std::vector<JCTHeap*>vJCTHeap;


//So to initialize the JCTMm you must include a total size of memory you wish to use
class JCTMm
{
public:
   JCTMm();
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
   static void CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   static void JCTMm::AddHeap(JCTHeap *pHeap);

   static void DestroyHeap(enum JCTHEAP_TYPE type);
   static void CreateFixedBlockHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   static void DestroyFixedBlockHeap(enum JCTHEAP_TYPE type);
#else
   static void JCTMm::AddHeap(JCTHeap *pHeap);
   static void CreateHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   static void DestroyHeap(enum JCTHEAP_TYPE type);
   static void CreateFixedBlockHeap(const enum JCTHEAP_TYPE &type, const size_t &size);
   static void DestroyFixedBlockHeap(enum JCTHEAP_TYPE type);
#endif
   
   static void JCTMm::setSize(const size_t &size)
   {
      JCTMm::m_iSize = size;
   };
   
   static const size_t JCTMm::getSize()
   {
      return JCTMm::m_iSize;
   };

   static const size_t JCTMm::getAllocOverhead()
   {
      return JCTMm::m_AllocOverhead;
   };

   static void JCTMm::setUsedSize(const size_t &size)
   {
      m_iUsedSize = size;
   };

   static const size_t JCTMm::getUsedSize()
   {
      return m_iUsedSize;
   };

#ifdef _DEBUG
   static void* Allocate(const enum JCTHEAP_TYPE type, const size_t &size, char* file, const size_t &uiLine, const bool &bArray, const enum ALIGNMENT_SIZE &align);
   static void DeAllocate(void *p, char* file, const size_t &uiLine, const bool &bArray);
#else
    static void* JCTMm::Allocate(enum JCTHEAP_TYPE type, const size_t &size, const bool &bArray, const enum ALIGNMENT_SIZE &align);
    static void DeAllocate(void *p, const bool &bArray);
#endif

   static void InitMemory(const size_t &size);
   static void Cleanup();

#ifdef _DEBUG

void* operator new (size_t uiSize);
void* operator new[](size_t uiSize);

void* operator new (size_t uiSize, enum JCTHEAP_TYPE type = JCTHEAP_GENERAL, char* acFile = __FILE__, unsigned int uiLine = __LINE__, const enum ALIGNMENT_SIZE &align=MEM_ALIGN_4_BYTES);
void* operator new[] (size_t uiSize, enum JCTHEAP_TYPE type = JCTHEAP_GENERAL, char* acFile = __FILE__, unsigned int uiLine = __LINE__, const enum ALIGNMENT_SIZE &align=MEM_ALIGN_4_BYTES);
void operator delete (void* p);
void operator delete[] (void* p);
void operator delete (void* p, size_t uiSize, enum JCTHEAP_TYPE type, char* acFile, unsigned int uiLine, const enum ALIGNMENT_SIZE &align);

void operator delete (void* p, enum JCTHEAP_TYPE type, char* acFile, unsigned int uiLine);
void operator delete (void* p, char* acFile, unsigned int uiLine);
void operator delete[] (void* p, enum JCTHEAP_TYPE type, char* acFile, unsigned int uiLine);
void operator delete[] (void* p, char* acFile, unsigned int uiLine);


#else
   
void* JCTMm::operator new (size_t size);
void* JCTMm::operator new[](size_t size);
void* JCTMm::operator new (size_t size, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align);
void* JCTMm::operator new[](size_t size, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align);
void JCTMm::operator delete[] (void* p, enum JCTHEAP_TYPE type);
void JCTMm::operator delete (void* p);
void JCTMm::operator delete (void* p, size_t uiSize, enum JCTHEAP_TYPE type, const enum ALIGNMENT_SIZE &align);
void JCTMm::operator delete (void* p, enum JCTHEAP_TYPE type);
void JCTMm::operator delete[] (void* p);

#endif

private:
   static char* m_AllMemory;
   static size_t m_iUsedSize;
   static size_t m_iSize;
   //static vJCTHeap vecHeap;
   static size_t m_HeapOverhead;
   static size_t m_UsedSize;
   static size_t m_AllocOverhead;
   static size_t m_iHeapCount;

   static char* m_pBottom;
   static JCTHeap *m_pTopHeap;
   static JCTHeap *m_pBottomHeap;

   //static JCTHeader *m_pUsedTop;
   //static JCTHeader *m_pFreeTop;
};

#endif