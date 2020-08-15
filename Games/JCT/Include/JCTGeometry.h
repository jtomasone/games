#pragma once

#include <string>
using namespace std;
static float DEF_TOLERANCE = (float)0.001;
#include "enum.h"
#include <xmmintrin.h>
#include <smmintrin.h> 

class Vect
{

public:
   Vect(const float &fX, const float &fY, const float &fZ, const float &fW=1.0f) : mX(fX), mY(fY), mZ(fZ), mW(fW){};
   //Vect(const float &fX, const float &fY, const float &fZ) : x((GLfloat)fX), y((GLfloat)fY), z((GLfloat)fZ), w((GLfloat)1.0f){};
   Vect() : mX(0.0), mY(0.0), mZ(0.0), mW(1.0f){};
   float operator[]( x_enum )const {return this->mX;}
   float& operator[](x_enum) {return this->mX;}
   float operator[]( y_enum )const {return this->mY;}
   float& operator[](y_enum) {return this->mY;}
   float operator[]( z_enum )const {return this->mZ;}
   float& operator[](z_enum) {return this->mZ;}
   float operator[]( w_enum )const {return this->mW;}
   float& operator[](w_enum) {return this->mW;}  

   const Vect Vect::operator = (const Vect *v2)
   {
     /*Vect *vTemp = new Vect();//v2->mX,v2->mY,v2->mX,v2->mW);
      vTemp->set(*v2);*/
      this->set(v2->mX,v2->mY,v2->mZ,1.0f);
      return *this;
   }
   //const Vect operator = (const Vect *v2);

   Vect::Vect(const Vect &v1)
   {
      this->set(v1);
      if(v1[w] == 0.0)
      {
         this->mW = 1.0f;
      }
   }
   

   void set(const Vect &v2)
   {
   this->mX = v2[x];
   this->mY = v2[y];
   this->mZ = v2[z];
   this->mW = v2[w];
   }

   void set(const float &fX, const float &fY, const float &fZ, const float &fW=1.0f)
   {
      this->mX = fX;
      this->mY = fY;
      this->mZ = fZ;
      this->mW = fW;
   }

   void Vect::setElement(const size_t &iPos, const float &fValue)
   {
      switch(iPos)
      {
      case 0:
         this->mX = fValue;
         break;
      case 1:
         this->mY = fValue;
         break;
      case 2:
         this->mZ = fValue;
         break;
      case 3:
         this->mW = fValue;
         break;
      }
   }

   float getElement(const size_t &iPos)
   {
      float fReturn = 0.0;

      switch(iPos)
      {
      case 0:
         fReturn = this->mX;
         break;
      case 1:
         fReturn = this->mY;
         break;
      case 2:
         fReturn = this->mZ;
         break;
      case 3:
         fReturn = this->mW;
         break;

      }
      return fReturn;
   }

   //Vect(float px, float py, float pz) : x((GLfloat)px), y((GLfloat)py), z((GLfloat)pz), w(1.0){};
private:
   // Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)
	// anonymous union
	union 
	{
		__m128	m;

		// anonymous struct
		struct 
			{
			float mX;
			float mY;
			float mZ;
			float mW;
			};
	};
};

struct JCT_AABB
{
   Vect min;
   Vect max;
};

class JCTGeometry //:
   //public JCTObject
{
public:
   string m_sName;
   JCTGeometry(const string &name);
   JCTGeometry(void);
   ~JCTGeometry(void);

};