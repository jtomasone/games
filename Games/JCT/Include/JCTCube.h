#pragma once
//#include "MathEngine.h"
#include "glut.h"
#include "JCTGeometry.h"

enum 
{
   JCTCUBE_FRONT,
   JCTCUBE_BACK,
   JCTCUBE_LEFT,
   JCTCUBE_RIGHT,
   JCTCUBE_TOP,
   JCTCUBE_BOTTOM,
   JCTCUBE_SIDECOUNT
};


enum 
{
   JCTCUBE_FRONT_P0,
   JCTCUBE_FRONT_P1,
   JCTCUBE_FRONT_P2,
   JCTCUBE_FRONT_P3
};
enum 
{   JCTCUBE_BACK_P0,
   JCTCUBE_BACK_P1,
   JCTCUBE_BACK_P2,
   JCTCUBE_BACK_P3
};

enum 
{  JCTCUBE_LEFT_P0,
   JCTCUBE_LEFT_P1,
   JCTCUBE_LEFT_P2,
   JCTCUBE_LEFT_P3
};
enum 
{
   JCTCUBE_RIGHT_P0,
   JCTCUBE_RIGHT_P1,
   JCTCUBE_RIGHT_P2,
   JCTCUBE_RIGHT_P3
};
enum 
{
   JCTCUBE_TOP_P0,
   JCTCUBE_TOP_P1,
   JCTCUBE_TOP_P2,
   JCTCUBE_TOP_P3
};
enum 
{
   JCTCUBE_BOTTOM_P0,
   JCTCUBE_BOTTOM_P1,
   JCTCUBE_BOTTOM_P2,
   JCTCUBE_BOTTOM_P3
};

const size_t JCTCUBE_POINTCOUNT = 4;

class JCTCube :
   public JCTGeometry
{
public:
   float m_fSize;
   float m_fWidth; 
   float m_fLength;
   float m_fDepth;

   JCTCube(void);
   JCTCube(const float &fSize);
   JCTCube(const float &fLength, const float &fWidth, const float &fDepth);
   ~JCTCube(void);
   
   Vect m_vCube[JCTCUBE_SIDECOUNT][JCTCUBE_POINTCOUNT];
   Vect m_vColor[JCTCUBE_SIDECOUNT];

   bool Collide(JCT_AABB &aabbParam, Vect &vMove);
   Vect getMin(Vect &vMove);
   Vect getMax(Vect &vMove);
   JCT_AABB getAABB(Vect &vMove);

   
};

