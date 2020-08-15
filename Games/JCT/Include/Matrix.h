#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

// SIMD includes
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "util.h"

class Matrix
{
public:
   Matrix();
   Matrix(const Vect &v0, const Vect &v1, const Vect &mParm, const Vect &v3);
   Matrix(const Matrix &mParm);
   Matrix(const enum MatrixSpecialType &eMType);
   Matrix(const enum  MatrixTransType &eMTrans, const float &fX, const float &fY, const float &fZ);
   Matrix(const enum  MatrixScaleType &eMScale, const float &fX, const float &fY, const float &fZ);
   Matrix(const enum  MatrixRotType &eMRot, const float &fAngle);

   void set(const enum  MatrixTransType &eMTrans, const float &fX, const float &fY, const float &fZ);
   void set(const enum  MatrixScaleType &eMScale, const float &fX, const float &fY, const float &fZ);
   void set(const enum  MatrixRotType &eMRot, const float &fAngle);

   void set(const Vect &v0, const Vect &v1, const Vect &mParm, const Vect &v3);
   void set(const Matrix &mParm);
   void set(Matrix &mParm);

   void set(const enum MatrixRowType eRow, const Vect &V);
   void set(const enum MatrixSpecialType &eType);
   Vect get(const enum MatrixRowType &eRow);

   void T();
   Matrix getT();
   Matrix getT(Matrix &mParam);

   Matrix getMinors();

   float det();

   void inv();
   Matrix getInv();

	// do magic stuff here
   const Matrix operator += (const Matrix &mParm);
   //Matrix&  operator += (const Matrix &mParm);
   const Matrix operator -= (const Matrix &mParm);
   const Matrix operator *= (const Matrix &mParm);
   const Matrix operator *= (const float &fS);
   const Matrix operator /= (Matrix &mParm);
   const Matrix operator /= (const float &fM);
   const Matrix operator + (const Matrix &mParm);
   const Matrix operator - (const Matrix &mParm);
   const Matrix operator * (const Matrix &mParm);
   const Matrix operator * (const float &fS);
   const Matrix operator / (Matrix &mParm);
   const Matrix operator / (const float &fM);
   const Matrix operator = (const Matrix *mParm);


//   Vect * operator [] (const unsigned int &i2) const;
   float operator [] (m0_enum) const {return this->m0;};
   float& operator [] (m0_enum) {return this->m0;};
   float operator [] (m1_enum) const {return this->m1;};
   float& operator [] (m1_enum) {return this->m1;};
   float operator [] (m2_enum) const {return this->m2;};
   float& operator [] (m2_enum) {return this->m2;};
   float operator [] (m3_enum) const {return this->m3;};
   float& operator [] (m3_enum) {return this->m3;};
   float operator [] (m4_enum) const {return this->m4;};
   float& operator [] (m4_enum) {return this->m4;};
   float operator [] (m5_enum) const {return this->m5;};
   float& operator [] (m5_enum) {return this->m5;};
   float operator [] (m6_enum) const {return this->m6;};
   float& operator [] (m6_enum) {return this->m6;};
   float operator [] (m7_enum) const {return this->m7;};
   float& operator [] (m7_enum) {return this->m7;};
   float operator [] (m8_enum) const {return this->m8;};
   float& operator [] (m8_enum) {return this->m8;};
   float operator [] (m9_enum) const {return this->m9;};
   float& operator [] (m9_enum) {return this->m9;};
   float operator [] (m10_enum) const {return this->m10;};
   float& operator [] (m10_enum) {return this->m10;};
   float operator [] (m11_enum) const {return this->m11;};
   float& operator [] (m11_enum) {return this->m11;};
   float operator [] (m12_enum) const {return this->m12;};
   float& operator [] (m12_enum) {return this->m12;};
   float operator [] (m13_enum) const {return this->m13;};
   float& operator [] (m13_enum) {return this->m13;};
   float operator [] (m14_enum) const {return this->m14;};
   float& operator [] (m14_enum) {return this->m14;};
   float operator [] (m15_enum) const {return this->m15;};
   float& operator [] (m15_enum) {return this->m15;};
   //Vect& operator [] (const MatrixRowType eRow);
	Matrix operator * (const Matrix &A) const;

   const bool operator ==(const Matrix &mParm) const;
   friend Vect operator * (const Vect &v1, const Matrix &m1);
   friend Vect operator *= (Vect &v1, const Matrix &m1);
   friend Matrix operator * (const float &f1, const Matrix &m1);

   friend Matrix operator + (const Matrix &mParam)
   {
      return Matrix(mParam.v0, mParam.v1, mParam.v2, mParam.v3);
   };

   friend Matrix operator - (const Matrix &mParam)
   {
      return Matrix(-mParam.v0, -mParam.v1, -mParam.v2, -mParam.v3);
   };



   const bool isEqual(const Matrix &mParm, const float &fE = DEF_TOLERANCE);
   const bool isEqual(const float &fE = DEF_TOLERANCE);
   const bool isZero(const float &fE);
   const bool isZero(const Matrix &mParm, const float &fE = DEF_TOLERANCE);

   const bool isIdentity();
   const bool isIdentity(const float &fE);
   const bool isIdentity(const Matrix &mParam, const float &fE);


   void Transpose();

private:

// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)

union 
		{
		struct 
			{
			Vect v0;
			Vect v1;
			Vect v2;
			Vect v3;
			};

		struct 
			{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;	
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
			};
		};
};

#endif