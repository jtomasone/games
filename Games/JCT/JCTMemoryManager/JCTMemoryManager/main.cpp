
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <string>

#include <Windows.h>

#include "JCTMm.h"

class Dog : public JCTMm
{
public:

   Dog()
   {
      printf("Dog(%p):constructor \n", this);
   };

   ~Dog()
   {
      printf("Dog(%p):destructor\n", this);
   };

   size_t a;
   size_t b;
   size_t c;
   size_t d;
};

struct sTest
{
   int iA;
   char cB;
};

DWORD fnGetHi(char* pTemp)
{
   return ((WORD)((DWORD)(pTemp) >> 16) & 0xFFFF);
}

DWORD fnGetLo(char* pTemp)
{
   return ((BYTE)pTemp);
}

#include <assert.h>
//#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/*
int main(void)
{
    test_mask(16);
    test_mask(32);
    test_mask(64);
    test_mask(128);

    return iFn();
}
*/
int _tmain(int argc, _TCHAR* argv[])
{

   printf("argc=%i\n", argc);
   printf("argv=%i\n", argv);
/*   HANDLE a = HeapCreate(HEAP_NO_SERIALIZE,  30000000, 30000000); // 30MB
   HANDLE b = HeapCreate(HEAP_NO_SERIALIZE,  30000000, 30000000); // 30MB
   HANDLE c = HeapCreate(HEAP_NO_SERIALIZE,  30000000, 30000000); // 30MB
   char* cA = reinterpret_cast<char*>(HeapAlloc(a, HEAP_ZERO_MEMORY, 1024));
   //void* cB = cA;
   //char *pPointer = new char[16] = "00000000";
   //long Addy = (long)cA;
   //ltoa((long)cA, pPointer, 8);
   //cA+=(sizeof(char*)40;

   memset(cA, 0xBB, 64);
//   cA = (char*)((char*)cA + 40);
//   cA = (char*)((char*)cA + 72);
   cA = (char*)((char*)cA + 136);
   memset(cA, 0xFF, 64);

   /*for(size_t x=0; x<32; x++)
   {
      cA++;
   }*/

   //cA += 32;

   //return 0;
   //HeapAlloc(b, HEAP_ZERO_MEMORY, 3000000);
   

   size_t iTotal     = 100000;
   size_t iGraphics  = 20000;
   size_t iPhysics   = 20000;
   size_t iSound     = 20000;
   size_t iAI        = 15000;
   size_t iGeneral   = 20000;
   JCTMm::InitMemory(iTotal);
   
   JCTMm::CreateHeap(JCTHEAP_GRAPHICS, iGraphics);
   JCTMm::CreateHeap(JCTHEAP_PHYSICS, iPhysics);
   JCTMm::CreateHeap(JCTHEAP_SOUND, iSound);
   JCTMm::CreateHeap(JCTHEAP_AI, iAI);
   JCTMm::CreateHeap(JCTHEAP_GENERAL, iGeneral);
   
   //Test duplicate detection functionality
/*   JCTMm::CreateHeap(JCTHEAP_PHYSICS, iPhysics);
   //Test the DestroyHeap functionality
NEED TO FIX   JCTMm::DestroyHeap(JCTHEAP_PHYSICS);
   //Test Heap Recreation
   JCTMm::CreateHeap(JCTHEAP_PHYSICS, iPhysics+1);
   JCTMm::DestroyHeap(JCTHEAP_GRAPHICS);
   JCTMm::CreateHeap(JCTHEAP_GRAPHICS, iGraphics+1);
   JCTMm::CreateHeap(JCTHEAP_SOUND, iSound);
*/   

#ifdef _DEBUG
      Dog *pDog2 = new (JCTHEAP_GRAPHICS, __FILE__, __LINE__, MEM_ALIGN_256_BYTES) Dog();
      Dog *pDog3 = new (JCTHEAP_PHYSICS, __FILE__, __LINE__, MEM_ALIGN_64_BYTES) Dog();
      Dog *pDog = new (JCTHEAP_SOUND, __FILE__, __LINE__, MEM_ALIGN_16_BYTES) Dog();
      Dog *p = new (JCTHEAP_GRAPHICS, __FILE__, __LINE__, MEM_ALIGN_128_BYTES) Dog[3];
      Dog *p7 = new (JCTHEAP_GRAPHICS, __FILE__, __LINE__, MEM_ALIGN_128_BYTES) Dog[1300];
#else
      Dog *pDog2 = new (JCTHEAP_GRAPHICS, MEM_ALIGN_256_BYTES) Dog();
      Dog *pDog3 = new (JCTHEAP_PHYSICS, MEM_ALIGN_64_BYTES) Dog();
      Dog *pDog = new (JCTHEAP_SOUND, MEM_ALIGN_16_BYTES) Dog();
      Dog *p = new (JCTHEAP_GRAPHICS, MEM_ALIGN_128_BYTES) Dog[3];
      Dog *p7 = new (JCTHEAP_GRAPHICS, MEM_ALIGN_128_BYTES) Dog[300];
#endif

   if(pDog2)
   {
      pDog2->a = 1;
      pDog2->b = 2;
      pDog2->c = 3;
      pDog2->d = 4;
   }
   else
   {
      cout << "Not enough free space in JCTHEAP_GRAPHICS Heap" << endl;
   }

   if(pDog3)
   {
      pDog3->a = 1;
      pDog3->b = 2;
      pDog3->c = 3;
      pDog3->d = 4;
   }
   else
   {
      cout << "Not enough free space in JCTHEAP_PHYSICS Heap" << endl;
   }

   if(pDog)
   {
      pDog->a = 1;
      pDog->b = 2;
      pDog->c = 3;
      pDog->d = 4;
   }
   else
   {
      cout << "Not enough free space in JCTHEAP_SOUND Heap" << endl;
   }

   if(p)
   {
      p[0].a = 17;
      p[0].b = 11;
      p[0].c = 22;
      p[0].d = 35;

      p[1].a = 31;
      p[1].b = 43;
      p[1].c = 77;
      p[1].d = 87;

      p[2].a = 64;
      p[2].b = 28;
      p[2].c = 97;
      p[2].d = 29;
   }
   else
   {
      cout << "Not enough free space in JCTHEAP_GRAPHICS Heap" << endl;
   }

   if(p7)
   {
      p7[0].a = 17;
      p7[0].b = 11;
      p7[0].c = 22;
      p7[0].d = 35;

      p7[1].a = 31;
      p7[1].b = 43;
      p7[1].c = 77;
      p7[1].d = 87;

      p7[2].a = 64;
      p7[2].b = 28;
      p7[2].c = 97;
      p7[2].d = 29;
   }
   else
   {
      cout << "Not enough free space in JCTHEAP_GRAPHICS Heap" << endl;
   }
   if(p7)
   {
      //void* operator new[] (size_t uiSize, enum JCTHEAP_TYPE type = JCTHEAP_GENERAL, char* acFile = __FILE__, unsigned int uiLine = __LINE__, const enum ALIGNMENT_SIZE &align=MEM_ALIGN_4_BYTES);
      //Dog *p7 = new (JCTHEAP_GRAPHICS, __FILE__, __LINE__, MEM_ALIGN_128_BYTES) Dog[300];
      //void operator delete[] (void* p, enum JCTHEAP_TYPE type, char* acFile, unsigned int uiLine);
      JCTMm::operator delete[](p7, JCTHEAP_GRAPHICS, __FILE__, __LINE__);
      
      p7=0;
   }
   if(pDog)
   {
      JCTMm::operator delete (pDog, JCTHEAP_SOUND, __FILE__, __LINE__);
      pDog = 0;
   }
   if(pDog2)
   {
      //Dog *pDog2 = new (JCTHEAP_GRAPHICS, __FILE__, __LINE__, MEM_ALIGN_256_BYTES) Dog();
      JCTMm::operator delete(pDog2, JCTHEAP_GRAPHICS, __FILE__, __LINE__);
      pDog2 = 0;
   }
   if(pDog3)
   {
      JCTMm::operator delete (pDog3, JCTHEAP_PHYSICS, __FILE__, __LINE__);
      pDog3 = 0;
   }
   if(p)
   {
      JCTMm::operator delete[](p, JCTHEAP_GRAPHICS, __FILE__, __LINE__);
      p = 0;
   }

   printf("----Default Allocator---\n");
   JCTMm::Cleanup();

   
   //Test duplicate detection functionality
   //JCTMm::CreateHeap(JCTHEAP_PHYSICS, iPhysics);
   //Test the DestroyHeap functionality
   //JCTMm::DestroyHeap(JCTHEAP_PHYSICS);
   //Test Heap Recreation
   //JCTMm::CreateHeap(JCTHEAP_PHYSICS, iPhysics+1);
//   JCTMm::DestroyHeap(JCTHEAP_GRAPHICS);
//   JCTMm::CreateHeap(JCTHEAP_GRAPHICS, iGraphics+1);

//   JCTMm::CreateHeap(JCTHEAP_SOUND, iSound);
   
//   Dog *pA
   /*
MEM_ALIGN_4_BYTES
MEM_ALIGN_8_BYTES
MEM_ALIGN_16_BYTES
MEM_ALIGN_32_BYTES
MEM_ALIGN_64_BYTES
MEM_ALIGN_128_BYTES
MEM_ALIGN_256_BYTES
   

/*
size_t iAlign[7] = {4,8,16,32,64,128,256};//{1,2,4,8,16,32,64};//
   int iInitialAlloc = 2054;

   mask = ~(uintptr_t)(iAlign[0] - 1);
   char*p4   = (char*)new char[(iInitialAlloc+(size_t)iAlign[0]-1)]; 
   p4 = (char *)(((uintptr_t)p4+iAlign[0]) & mask);

   mask = ~(uintptr_t)(iAlign[1] - 1);
   char*p8   = (char*)new char[(iInitialAlloc+(size_t)iAlign[1]-1)]; 
   p8 = (char *)(((uintptr_t)p8+iAlign[1]) & mask);

   mask = ~(uintptr_t)(iAlign[2] - 1);
   char*p16   = (char*)new char[(iInitialAlloc+(size_t)iAlign[2]-1)]; 
   p16 = (char *)(((uintptr_t)p16+iAlign[2]) & mask);

   mask = ~(uintptr_t)(iAlign[3] - 1);
   char*p32   = (char*)new char[(iInitialAlloc+(size_t)iAlign[3]-1)]; 
   p32 = (char *)((((uintptr_t)p32+iAlign[3]) & mask));

   mask = ~(uintptr_t)(iAlign[4] - 1);
   char*p64   = (char*)new char[(iInitialAlloc+(size_t)iAlign[4]-1)]; 
   p64 = (char *)(((uintptr_t)p64+iAlign[4]) & mask);

   mask = ~(uintptr_t)(iAlign[5] - 1);
   char*p128   = (char*)new char[(iInitialAlloc+(size_t)iAlign[5]-1)]; 
   p128 = (char *)(((uintptr_t)p128+iAlign[5]) & mask);

   mask = ~(uintptr_t)(iAlign[6] - 1);
   char*p256   = (char*)new char[(iInitialAlloc+(size_t)iAlign[6]-1)]; 
   p256 = (char *)(((uintptr_t)p128+iAlign[6]) & mask);

   //p4 = ((char*)p4 + (size_t)iAlign[0]));
   //p4 = ((reinterpret_cast)p4) & ~ 0x0F;

//   void *mem = malloc(1024+15);

   DWORD iHi = fnGetHi(p4);
   DWORD iLo = fnGetLo(p4);
   size_t iLoFactor = iAlign[0];
   
   if(iLo != iAlign[0])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[0];
      }
      iLoFactor = iLoFactor-iLo;

      p4 = (char*)((char*)p4 + iLoFactor);
   }
   memset(p4, 0x04, iInitialAlloc);

   char*p8   = (char*)new char[(iInitialAlloc+(size_t)iAlign[1])];
   iHi = fnGetHi(p8);
   iLo = fnGetLo(p8);
   iLoFactor = iAlign[1];
   
   if(iLo != iAlign[1])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[1];
      }
      iLoFactor = iLoFactor-iLo;

      p8 = (char*)((char*)p8 + iLoFactor);
   }
   memset(p8, 0x08, iInitialAlloc);

   char*p16  = (char*)new char[(iInitialAlloc+(size_t)iAlign[2])];
   iHi = fnGetHi(p16);//((WORD)((DWORD)(p16) >> 16) & 0xFFFF);//HIWORD(p16);
   iLo = fnGetLo(p16);//((BYTE)p16);//LOWORD(p16);
   iLoFactor = iAlign[2];

   if(iLo != iAlign[2])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[2];
      }
      iLoFactor = iLoFactor-iLo;

      p16 = (char*)((char*)p16 + iLoFactor);
   }
   memset(p16, 0x16, iInitialAlloc);

   char*p32  = (char*)new char[(iInitialAlloc+ (size_t)iAlign[3])];
   iHi = fnGetHi(p32);//((WORD)((DWORD)(p32) >> 16) & 0xFFFF);//HIWORD(p32);
   iLo = fnGetLo(p32);//((BYTE)p32);//LOWORD(p32);
   iLoFactor = iAlign[3];

   if(iLo != iAlign[3])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[3];
      }
      iLoFactor = iLoFactor-iLo;
      p32 = (char*)((char*)p32 + iLoFactor);
   }
   memset(p32, 0x32, iInitialAlloc);

   char*p64  = (char*)new char[(iInitialAlloc+((size_t)iAlign[4]))];
   iHi = fnGetHi(p64);//((WORD)((DWORD)(p64) >> 16) & 0xFFFF);//HIWORD(p64);
   iLo = fnGetLo(p64);//((BYTE)p64);//LOWORD(p64);
   iLoFactor = iAlign[4];   

   if(iLo != iAlign[4])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[4];
      }
      iLoFactor = iLoFactor-iLo;
      p64 = (char*)((char*)p64 + iLoFactor);
   }
   memset(p64, 0x64, iInitialAlloc);

   char*p128 = (char*)new char[(iInitialAlloc+(size_t)iAlign[5])];
   iHi = fnGetHi(p128);//((WORD)((DWORD)(p128) >> 16) & 0xFFFF);//HIWORD(p128);
   iLo = fnGetLo(p128);//((BYTE)p128);//LOWORD(p128);
   iLoFactor = iAlign[5];

   if(iLo != iAlign[5])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[5];
      }
      iLoFactor = iLoFactor-iLo;
      p128 = (char*)((char*)p128 + iLoFactor+iAlign[5]);
   }
   memset(p128, 0x128, iInitialAlloc);

   char*p256 = new char[(iInitialAlloc+((size_t)iAlign[6]*2))];
   iHi = fnGetHi(p256);//((WORD)((DWORD)(p256) >> 16) & 0xFFFF);//HIWORD(p256);
   iLo = fnGetLo(p256);//((BYTE)p256);//LOWORD(p256);
   DWORD dwAddress = (DWORD)p256;
   iLoFactor = iAlign[6];   

   if(iLo != iAlign[6])
   {
      while(iLoFactor<=iLo)
      {
         iLoFactor+=iAlign[6];
      }
      iLoFactor = iLoFactor-iLo;

      p256 = (char*)((char*)p256 + (size_t)iLoFactor+(size_t)iAlign[6]);
   }
   memset(p256, 0x256, iInitialAlloc);
   */
/*   free(p4);
   free(p8);
   free(p16);
   free(p32);
   free(p64);
   free(p128);
   free(p256);
*/
   return 1;
   /*
   memset(p1, 0xAA, 116);
   p1+=40;
   char*p2 = (char*)malloc(116);
   memset(p2, 0xBB, 100);
   char*p7 = new(p2) char[32];
   p7[0] = 0x32;
   p7[1] = 0x31;
   p7[2] = 0x30;
   p7[3] = 0x29;
   p7[4] = 0x28;
   p7[5] = 0x27;
   p7[6] = 0x26;
   p7[7] = 0x25;
   p7[8] = 0x24;
   p7[9] = 0x23;
   p7[10] = 0x22;
   p7[11] = 0x21;
   p7[12] = 0x20;
   p7[13] = 0x19;
   p7[14] = 0x18;
   p7[15] = 0x17;
   p7[16] = 0x16;
   p7[17] = 0x15;
   p7[18] = 0x14;
   p7[19] = 0x13;
   p7[20] = 0x12;
   p7[21] = 0x11;
   p7[22] = 0x10;
   p7[23] = 0x9;
   p7[24] = 0x8;
   p7[25] = 0x7;
   p7[26] = 0x6;
   p7[27] = 0x5;
   p7[28] = 0x4;
   p7[29] = 0x3;
   p7[30] = 0x2;
   p7[31] = 0x1;
*/
/*
   char*p3 = (char*)malloc(100);
   memset(p3, 3, 100);
*/
/*
   sTest*p4 = new(p2) sTest[4];
   //memset(p4, 4, sizeof(sTest[16]));
   p4[0].iA = 0x60708090;
   p4[0].cB = 0x50;
   p4[1].iA = 0x61718191;
   p4[1].cB = 0x51;
   p4[2].iA = 0x62728292;
   p4[2].cB = 0x52;
   p4[3].iA = 0x63738393;
   p4[3].cB = 0x53;

   printf("p1==%p\n", p1);
   //   printf("p2==%p\n", p2);
//   printf("p3==%p\n", p3);
*/
//   return 0;

   /*   std::vector<int>v1;
   for(int i=0; i<10; i++)
   {
      printf("Inserting %d\n", i);
      v1.push_back(i);
   }
   printf("----Done---\n");


   printf("----Custom Allocator---\n");
   std::vector<int, logging_allocator<int>>v2;
   for(int i=0; i<10; i++)
   {
      printf("Inserting %d\n", i);
      v2.push_back(i);
   }
   printf("----Done---\n");

	HANDLE hTest = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE,5000000000,10000000000);

	malloc(10000000000);

	if(hTest == 0)
	{
		printf("Failed HeapCreate\n");
		return 0;
	}
	else
	{
		printf("HeapCreate Successful\n");

		Dog *pDog = (Dog*)HeapAlloc(hTest, HEAP_ZERO_MEMORY, sizeof(Dog));
		if(pDog == 0)
		{
			printf("Dog HeapAlloc failed\n");
		}
		else
		{
			printf("Dog HeapAlloc Succeeded\n");		
		}
	}
   */
   
}

