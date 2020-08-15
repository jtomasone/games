#pragma once
//#include "MathEngine.h"
#include "glut.h"
#include "JCTGeometry.h"

const size_t JCTSPHERE_POINTCOUNT = 4;

class JCTSphere :
   public JCTGeometry
{
public:
   float m_fSize;
   float m_fWidth; 
   float m_fLength;
   float m_fDepth;

   JCTSphere(void);
   JCTSphere(const float &fRadius);
   ~JCTSphere(void);
   

   bool Collide(JCT_AABB &aabbParam, Vect &vMove);
   Vect getMin(Vect &vMove);
   Vect getMax(Vect &vMove);
   JCT_AABB getAABB(Vect &vMove);

   
};

