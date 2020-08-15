#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#pragma once
#include <xmmintrin.h>
#include <smmintrin.h> 

#include <stdio.h>
#include <tchar.h>
#include "enum.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <string>
#include "JCTMm.h"
// forward declare
class Matrix;

class Vect : public JCTMm
{
public:
   Vect(const float &fX, const float &fY, const float &fZ, const float &fW = 1.0f);
   Vect(const double &fX, const double &fY, const double &fZ, const double &fW);

   Vect(const Vect &v1);
   
   Vect();
	// do magic stuff here:
   const Vect operator += (const Vect &v2);
   Vect&  operator += (const Vect *v2);
   const Vect operator -= (const Vect &v2);
   const Vect operator *= (const Vect &v2);
   const Vect operator *= (const float &fS);
   const Vect operator /= (Vect &v2);
   const Vect operator /= (const float &fM);
   const Vect operator + (const Vect &v2);
   const Vect operator - (const Vect &v2);
   const Vect operator * (const Vect &v2);
   const Vect operator * (const float &fS);
   const Vect operator / (Vect &v2);
   const Vect operator / (const float &fM);
   const Vect operator = (const Vect *v2);

   const bool operator ==(const Vect &v2) const;
   
   float operator[]( x_enum )const {return this->mX;}
   float& operator[](x_enum) {return this->mX;}
   float operator[]( y_enum )const {return this->mY;}
   float& operator[](y_enum) {return this->mY;}
   float operator[]( z_enum )const {return this->mZ;}
   float& operator[](z_enum) {return this->mZ;}
   float operator[]( w_enum )const {return this->mW;}
   float& operator[](w_enum) {return this->mW;}

   Vect Negate(const Vect &v2) const;
   
   bool isEqual(const Vect &v2, const float fTolerance=MATH_TOLERANCE) const;
   bool isZero(const Vect &v2, const float fTolerance=MATH_TOLERANCE) const;
   bool isZero(const float fTolerance=MATH_TOLERANCE) const;
   Vect Scale(const float &fScalar);
   Vect ScaleDiv(const float &fScalar);
   float getElement(const size_t &iPos);
   void setElement(const size_t &iPos, const float &fValue);

   void set(const float &fX, const float &fY, const float &fZ, const float &fW=1.0f);
   void set(const Vect &v2);

   Vect getNorm() const;
   void norm();

   float dot(const Vect &v1, const Vect &v2) const;

   float dot(const Vect &v2);
   const Vect cross(Vect &v2) const;

   float mag() const;
   float magSqr() const;

   float getAngle(const Vect &v2);
   void print();

   friend const Vect operator * (const float &fS, const Vect &v2)
   {
      return Vect(fS * v2[x], fS * v2[y], fS * v2[z], fS * 1.0f);
   };

   friend Vect * operator *= (const float &fS, Vect &v2)
   {
      v2[x] *= fS;
      v2[y] *= fS;
      v2[z] *= fS; 
      v2[w] = 1.0f;
      return &v2;
   };

   friend Vect operator + (const Vect &v2)
   {
      return Vect(v2[x], v2[y], v2[z], 1.0f);
   };

   friend Vect operator - (const Vect &v2)
   {
      return Vect(-v2[x], -v2[y], -v2[z], 1.0f);
   };
   
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


#endif