#pragma once
#include "JCTCube.h"


JCTCube::JCTCube(void)// : JCTGeometryNode("")
{

}

JCTCube::JCTCube(const float &fSize)// : JCTGeometryNode("")
{
#ifdef _DEBUG

      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P0]   = new Vect (0.0f, 0.0f, fSize);
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P1]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P2]   = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P3]   = new Vect (0.0f,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P0]     = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P1]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P2]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P3]     = new Vect (fSize,   fSize,   0.0f); 
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P0]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P1]     = new Vect (0.0f,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P2]     = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P3]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P0]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P1]   = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P2]   = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P3]   = new Vect (fSize,   fSize,   fSize);
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P0]       = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P1]       = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P2]       = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P3]       = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P0] = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P1] = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P2] = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P3] = new Vect (0.0f,   0.0f,   fSize);
#else if
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P0]   = new Vect (0.0f, 0.0f, fSize);
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P1]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P2]   = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P3]   = new Vect (0.0f,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P0]     = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P1]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P2]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P3]     = new Vect (fSize,   fSize,   0.0f); 
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P0]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P1]     = new Vect (0.0f,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P2]     = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P3]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P0]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P1]   = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P2]   = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P3]   = new Vect (fSize,   fSize,   fSize);
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P0]       = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P1]       = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P2]       = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P3]       = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P0] = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P1] = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P2] = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P3] = new Vect (0.0f,   0.0f,   fSize);
#endif

      this->m_vColor[0].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[1].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[2].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[3].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[4].set(0.0f, 1.0f, 0.0f);
      this->m_fSize = .5f*fSize;

}


JCTCube::JCTCube(const float &fLength, const float &fWidth, const float &fDepth)// : JCTGeometryNode("")
{
#ifdef _DEBUG

      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P0]   = new Vect (0.0f, 0.0f,      fDepth);
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P1]   = new Vect (fLength,   0.0f,   fDepth);  
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P2]   = new Vect (fLength,   fWidth,   fDepth); 
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P3]   = new Vect (0.0f,   fWidth,   fDepth); 
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P0]     = new Vect (fLength,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P1]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P2]     = new Vect (0.0f,   fWidth,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P3]     = new Vect (fLength,   fWidth,   0.0f); 
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P0]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P1]     = new Vect (0.0f,   0.0f,   fDepth);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P2]     = new Vect (0.0f,   fWidth,   fDepth);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P3]     = new Vect (0.0f,   fWidth,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P0]   = new Vect (fLength,   0.0f,   fDepth);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P1]   = new Vect (fLength,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P2]   = new Vect (fLength,   fWidth,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P3]   = new Vect (fLength,   fWidth,   fDepth);
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P0]       = new Vect (0.0f,   fWidth,   fDepth);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P1]       = new Vect (fLength,   fWidth,   fDepth); 
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P2]       = new Vect (fLength,   fWidth,   0.0f);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P3]       = new Vect (0.0f,   fWidth,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P0] = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P1] = new Vect (fLength,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P2] = new Vect (fLength,   0.0f,   fDepth);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P3] = new Vect (0.0f,   0.0f,   fDepth);
#else if
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P0]   = new Vect (0.0f, 0.0f, fSize);
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P1]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P2]   = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_FRONT][JCTCUBE_FRONT_P3]   = new Vect (0.0f,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P0]     = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P1]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P2]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BACK][JCTCUBE_BACK_P3]     = new Vect (fSize,   fSize,   0.0f); 
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P0]     = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P1]     = new Vect (0.0f,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P2]     = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_LEFT][JCTCUBE_LEFT_P3]     = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P0]   = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P1]   = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P2]   = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_RIGHT][JCTCUBE_RIGHT_P3]   = new Vect (fSize,   fSize,   fSize);
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P0]       = new Vect (0.0f,   fSize,   fSize);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P1]       = new Vect (fSize,   fSize,   fSize); 
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P2]       = new Vect (fSize,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_TOP][JCTCUBE_TOP_P3]       = new Vect (0.0f,   fSize,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P0] = new Vect (0.0f,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P1] = new Vect (fSize,   0.0f,   0.0f);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P2] = new Vect (fSize,   0.0f,   fSize);  
      this->m_vCube[JCTCUBE_BOTTOM][JCTCUBE_BOTTOM_P3] = new Vect (0.0f,   0.0f,   fSize);
#endif

      this->m_vColor[0].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[1].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[2].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[3].set(0.0f, 1.0f, 0.0f);
      this->m_vColor[4].set(0.0f, 1.0f, 0.0f);

      this->m_fWidth = .5f*fWidth;
      this->m_fLength = .5f*fLength;
      this->m_fDepth = .5f*fDepth;
}

JCTCube::~JCTCube(void)
{
   /*for(int x=0; x<JCTCUBE_SIDECOUNT; x++)
   {
      //for(int y=0; y<JCTCUBE_POINTCOUNT; y++)
      {//
         if(this->m_vCube[x])
         {
            JCTMm::operator delete[] (this->m_vCube[x], JCTHEAP_GRAPHICS, __FILE__, __LINE__);
         }
      //}
   }//
   */
}

Vect JCTCube::getMin(Vect &vMove)
{
   Vect vMin;

   for(int x=0; x<JCTCUBE_SIDECOUNT; x++)
   {
      for(int y=0; y<JCTCUBE_POINTCOUNT; y++)
      {
         for(int z=0; z<3; z++)
         {
            if(((vMove.getElement(z) + this->m_vCube[x][y].getElement(z)) - (vMove.getElement(z) + vMin.getElement(z))) < DEF_TOLERANCE)
            {
               vMin.setElement(z,(vMove.getElement(z) + this->m_vCube[x][y].getElement(z)));
            }
         }
      }
   }
   return vMin;
}

Vect JCTCube::getMax(Vect &vMove)
{
   Vect vMax;

   for(int x=0; x<JCTCUBE_SIDECOUNT; x++)
   {
      for(int y=0; y<JCTCUBE_POINTCOUNT; y++)
      {
         for(int z=0; z<3; z++)
         {
            if(((vMove.getElement(z) + this->m_vCube[x][y].getElement(z)) - (vMove.getElement(z) + vMax.getElement(z))) > DEF_TOLERANCE)
            {
               vMax.setElement(z, (vMove.getElement(z) + this->m_vCube[x][y].getElement(z)));
            }
         }
      }
   }
   return vMax;
}

JCT_AABB JCTCube::getAABB(Vect &vMove)
{
   JCT_AABB aabbReturn;
   aabbReturn.min.set(this->getMin(vMove));
   aabbReturn.max.set(this->getMax(vMove));
   return aabbReturn;
}

bool JCTCube::Collide(JCT_AABB &aabbParam, Vect &vMove)
{
   JCT_AABB aabbLocal = this->getAABB(vMove);
   if(((aabbLocal.max.getElement(0) - aabbParam.min.getElement(0)) < DEF_TOLERANCE) || ((aabbLocal.min.getElement(0) - aabbParam.max.getElement(0)) > DEF_TOLERANCE)) 
   {
         return false;
   }
   if(((aabbLocal.max.getElement(1) - aabbParam.min.getElement(1)) < DEF_TOLERANCE) || ((aabbLocal.min.getElement(1) - aabbParam.max.getElement(1)) > DEF_TOLERANCE)) 
   {
         return false;
   }
   if(((aabbLocal.max.getElement(2) - aabbParam.min.getElement(2)) < DEF_TOLERANCE) || ((aabbLocal.min.getElement(2) - aabbParam.max.getElement(2)) > DEF_TOLERANCE)) 
   {
      return false;
   }

   return true;
   
}