#include "MathEngine.h"
#include <math.h>

Matrix::Matrix(const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3)
{
   this->set(v0, v1, v2, v3);
};

Matrix::Matrix(const Matrix &mParm)
{
   this->set(mParm.v0, mParm.v1, mParm.v2, mParm.v3);
};

void Matrix::set(const Matrix &mParm)
{
   this->set(mParm.v0, mParm.v1, mParm.v2, mParm.v3);
};

void Matrix::set(Matrix &mParm)
{
   this->set(mParm.v0, mParm.v1, mParm.v2, mParm.v3);
};

Matrix::Matrix(const enum MatrixSpecialType &eMType)
{
   switch(eMType)
   {
   case ZERO:
      this->set(ZERO);
      break;
   case IDENTITY:
      this->set(IDENTITY);
      break;
   }
};

Matrix::Matrix()
{
   this->set(ZERO);
};

Matrix::Matrix(const MatrixTransType &eMTrans, const float &fX, const float &fY, const float &fZ)
{
   this->set(eMTrans, fX, fY, fZ);
};

Matrix::Matrix(const MatrixScaleType &eMScale, const float &fX, const float &fY, const float &fZ)
{
   this->set(eMScale, fX, fY, fZ);
};

Matrix::Matrix(const MatrixRotType &eMRot, const float &fAngle)
{
   this->set(eMRot, fAngle);
};

void Matrix::set(const MatrixTransType &eMTrans, const float &fX, const float &fY, const float &fZ)
{
   this->set(IDENTITY);
   if(TRANS == eMTrans)
   {
      this->v3[x] = fX;
      this->v3[y] = fY;
      this->v3[z] = fZ;
   }
};

void Matrix::set(const MatrixScaleType &eMScale, const float &fX, const float &fY, const float &fZ)
{
   this->set(IDENTITY);
   if(SCALE == eMScale)
   {
      this->v0[x] = fX;
      this->v1[y] = fY;
      this->v2[z] = fZ;
   }
};

void Matrix::set(const MatrixRotType &eMRot, const float &fAngle)
{
   switch(eMRot)
   {
   case ROT_X:
      this->set(IDENTITY);
      this->v1.set(0, cosf(fAngle), sinf(fAngle), 0);
      this->v2.set(0, -sinf(fAngle), cosf(fAngle), 0);
      break;
   case ROT_Y:
      this->set(IDENTITY);
      this->v0.set(cosf(fAngle), 0, -sinf(fAngle), 0);
      this->v2.set(sinf(fAngle), 0, cosf(fAngle), 0);
      break;
   case ROT_Z:
      this->set(IDENTITY);
      this->v0.set(cosf(fAngle), sinf(fAngle), 0, 0);
      this->v1.set(-sinf(fAngle), cosf(fAngle), 0, 0);
      break;
   }
};

void Matrix::set(const Vect &v0, const Vect &v1, const Vect &v2, const Vect &v3)
{
   this->v0 = v0;
   this->v1 = v1;
   this->v2 = v2;
   this->v3 = v3;
};

void Matrix::set(const enum MatrixSpecialType &eType)
{
   switch(eType)
   {
   case ZERO:
      {
      this->v0.set(0.0, 0.0, 0.0, 0.0);
      this->v1.set(0.0, 0.0, 0.0, 0.0);
      this->v2.set(0.0, 0.0, 0.0, 0.0);
      this->v3.set(0.0, 0.0, 0.0, 0.0);
      }
      break;
   case IDENTITY:
      {
      this->v0.set(1.0, 0.0, 0.0, 0.0);
      this->v1.set(0.0, 1.0, 0.0, 0.0);
      this->v2.set(0.0, 0.0, 1.0, 0.0);
      this->v3.set(0.0, 0.0, 0.0, 1.0);
      }
   }
};

const Matrix Matrix::operator += (const Matrix &mParm)
{
   this->v0 += mParm.v0;
   this->v1 += mParm.v1;
   this->v2 += mParm.v2;
   this->v3 += mParm.v3;

   return *this;
};

void Matrix::set(const enum MatrixRowType eRow, const Vect &V)
{
   switch(eRow)
   {
   case ROW_0:
      this->v0.set(V);
      break;
   case ROW_1:
      this->v1.set(V);
      break;
   case ROW_2:
      this->v2.set(V);
      break;
   case ROW_3:
      this->v3.set(V);
      break;
   default:
      break;
   }
};

Vect Matrix::get(const enum MatrixRowType &eRow)
{
   switch(eRow)
   {
   case ROW_0:
      return this->v0;
      break;
   case ROW_1:
      return this->v1;
      break;
   case ROW_2:
      return this->v2;
      break;
   case ROW_3:
      return this->v3;
      break;
   default:
      return Vect();
   }
};

const Matrix Matrix::operator -= (const Matrix &mParm)
{
   this->v0 -= mParm.v0;
   this->v1 -= mParm.v1;
   this->v2 -= mParm.v2;
   this->v3 -= mParm.v3;
   return *this;
};

const Matrix Matrix::operator *= (const Matrix &mParm)
{
   Matrix mTemp = Matrix(this->v0, this->v1, this->v2, this->v3);
   mTemp = mTemp * mParm;
   this->set(mTemp.v0, mTemp.v1, mTemp.v2, mTemp.v3);
   return *this;
};

const Matrix Matrix::operator *= (const float &fS)
{
   this->v0 *= fS;
   this->v1 *= fS;
   this->v2 *= fS; 
   this->v3 *= fS;
   return *this;
};

const Matrix Matrix::operator /= (Matrix &mParm)
{

   this->v0 /= mParm.v0;
   this->v1 /= mParm.v1;
   this->v2 /= mParm.v2; 
   this->v3 /= mParm.v3;
   return *this;
};

const Matrix Matrix::operator /= (const float &fM)
{
   if(!Util::isZero(fM, DEF_TOLERANCE))
   {
      this->set((this->v0 / fM),
                (this->v1 / fM),
                (this->v2 / fM), 
                (this->v3 / fM));
      return *this;
   }
   else
   {
      return Matrix(this->v0, this->v1, this->v2, this->v3);
   }

};

const Matrix Matrix::operator + (const Matrix &mParm)
{
   return Matrix(this->v0 + mParm.v0, this->v1 + mParm.v1, this->v2 + mParm.v2, this->v3 + mParm.v3);
};

const Matrix Matrix::operator - (const Matrix &mParm)
{
   return Matrix(this->v0 - mParm.v0, this->v1 - mParm.v1, this->v2 - mParm.v2, this->v3 - mParm.v3);
};

const Matrix Matrix::operator * (const Matrix &mParm)
{
   return Matrix( Vect(((this->v0[x] * mParm.v0[x])+(this->v0[y] * mParm.v1[x]) + (this->v0[z] * mParm.v2[x]) + (this->v0[w] * mParm.v3[x])),
                       ((this->v0[x] * mParm.v0[y])+(this->v0[y] * mParm.v1[y]) + (this->v0[z] * mParm.v2[y]) + (this->v0[w] * mParm.v3[y])),
                       ((this->v0[x] * mParm.v0[z])+(this->v0[y] * mParm.v1[z]) + (this->v0[z] * mParm.v2[z]) + (this->v0[w] * mParm.v3[z])),
                       ((this->v0[x] * mParm.v0[w])+(this->v0[y] * mParm.v1[w]) + (this->v0[z] * mParm.v2[w]) + (this->v0[w] * mParm.v3[w]))),
                  Vect(((this->v1[x] * mParm.v0[x])+(this->v1[y] * mParm.v1[x]) + (this->v1[z] * mParm.v2[x]) + (this->v1[w] * mParm.v3[x])),
                       ((this->v1[x] * mParm.v0[y])+(this->v1[y] * mParm.v1[y]) + (this->v1[z] * mParm.v2[y]) + (this->v1[w] * mParm.v3[y])),
                       ((this->v1[x] * mParm.v0[z])+(this->v1[y] * mParm.v1[z]) + (this->v1[z] * mParm.v2[z]) + (this->v1[w] * mParm.v3[z])),
                       ((this->v1[x] * mParm.v0[w])+(this->v1[y] * mParm.v1[w]) + (this->v1[z] * mParm.v2[w]) + (this->v1[w] * mParm.v3[w]))),
                  Vect(((this->v2[x] * mParm.v0[x])+(this->v2[y] * mParm.v1[x]) + (this->v2[z] * mParm.v2[x]) + (this->v2[w] * mParm.v3[x])),
                       ((this->v2[x] * mParm.v0[y])+(this->v2[y] * mParm.v1[y]) + (this->v2[z] * mParm.v2[y]) + (this->v2[w] * mParm.v3[y])),
                       ((this->v2[x] * mParm.v0[z])+(this->v2[y] * mParm.v1[z]) + (this->v2[z] * mParm.v2[z]) + (this->v2[w] * mParm.v3[z])),
                       ((this->v2[x] * mParm.v0[w])+(this->v2[y] * mParm.v1[w]) + (this->v2[z] * mParm.v2[w]) + (this->v2[w] * mParm.v3[w]))),
                  Vect(((this->v3[x] * mParm.v0[x])+(this->v3[y] * mParm.v1[x]) + (this->v3[z] * mParm.v2[x]) + (this->v3[w] * mParm.v3[x])),
                       ((this->v3[x] * mParm.v0[y])+(this->v3[y] * mParm.v1[y]) + (this->v3[z] * mParm.v2[y]) + (this->v3[w] * mParm.v3[y])),
                       ((this->v3[x] * mParm.v0[z])+(this->v3[y] * mParm.v1[z]) + (this->v3[z] * mParm.v2[z]) + (this->v3[w] * mParm.v3[z])),
                       ((this->v3[x] * mParm.v0[w])+(this->v3[y] * mParm.v1[w]) + (this->v3[z] * mParm.v2[w]) + (this->v3[w] * mParm.v3[w]))));
};

Matrix Matrix::operator * ( const Matrix &A ) const
{
	return Matrix (

		Vect(	(m0 * A.m0) + (m1 * A.m4) + (m2 * A.m8) + (m3 * A.m12),
				(m0 * A.m1) + (m1 * A.m5) + (m2 * A.m9) + (m3 * A.m13),
				(m0 * A.m2) + (m1 * A.m6) + (m2 * A.m10) + (m3 * A.m14),
				(m0 * A.m3) + (m1 * A.m7) + (m2 * A.m11) + (m3 * A.m15) ),
		
		Vect(	(m4 * A.m0) + (m5 * A.m4) + (m6 * A.m8) + (m7 * A.m12),
				(m4 * A.m1) + (m5 * A.m5) + (m6 * A.m9) + (m7 * A.m13),
				(m4 * A.m2) + (m5 * A.m6) + (m6 * A.m10) + (m7 * A.m14),
				(m4 * A.m3) + (m5 * A.m7) + (m6 * A.m11) + (m7 * A.m15) ),
	
		Vect(	(m8 * A.m0) + (m9 * A.m4) + (m10 * A.m8) + (m11 * A.m12),
				(m8 * A.m1) + (m9 * A.m5) + (m10 * A.m9) + (m11 * A.m13),
				(m8 * A.m2) + (m9 * A.m6) + (m10 * A.m10) + (m11 * A.m14),
				(m8 * A.m3) + (m9 * A.m7) + (m10 * A.m11) + (m11 * A.m15) ),

		Vect(	(m12 * A.m0) + (m13 * A.m4) + (m14 * A.m8) + (m15 * A.m12),
				(m12 * A.m1) + (m13 * A.m5) + (m14 * A.m9) + (m15 * A.m13),
				(m12 * A.m2) + (m13 * A.m6) + (m14 * A.m10) + (m15 * A.m14),
				(m12 * A.m3) + (m13 * A.m7) + (m14 * A.m11) + (m15 * A.m15) )
		);
}
Vect operator * (const Vect &v1, const Matrix &m1)
{
   return Vect((m1.v0[x] * v1[x]) + (m1.v0[y] * v1[y]) + (m1.v0[z] * v1[z]) + (m1.v0[w] * v1[w]),
               (m1.v1[x] * v1[x]) + (m1.v1[y] * v1[y]) + (m1.v1[z] * v1[z]) + (m1.v1[w] * v1[w]),
               (m1.v2[x] * v1[x]) + (m1.v2[y] * v1[y]) + (m1.v2[z] * v1[z]) + (m1.v2[w] * v1[w]),
               (m1.v3[x] * v1[x]) + (m1.v3[y] * v1[y]) + (m1.v3[z] * v1[z]) + (m1.v3[w] * v1[w]));
}

Matrix operator * (const float &f1, const Matrix &m1)
{
   return Matrix(f1*m1.v0, f1*m1.v1, f1*m1.v2, f1*m1.v3);
}

Vect operator *= (Vect &v1, const Matrix &m1)
{
   v1.set(v1 * m1);
   return v1;
}

const Matrix Matrix::operator * (const float &fS)
{
   return Matrix(this->v0 * fS, this->v1 * fS, this->v2 * fS, this->v3 * fS);
};

const Matrix Matrix::operator / (Matrix &mParm)
{
   if(!mParm.isZero(DEF_TOLERANCE))
   {
      return Matrix(this->v0 / mParm.v0, this->v1 / mParm.v1, this->v2 / mParm.v2, this->v3 / mParm.v3);
   }
   else
   {
      return Matrix(Vect(), Vect(), Vect(), Vect());
   }
   
};

const Matrix Matrix::operator / (const float &fM)
{
   if(!Util::isZero(fM, DEF_TOLERANCE))
   {
      return Matrix(this->v0 / fM, this->v1 / fM, this->v2 / fM, this->v3 / fM);
   }
   else
   {
      return Matrix(Vect(), Vect(), Vect(), Vect());
   }   
};

const bool Matrix::operator ==(const Matrix &mParm) const
{
   if(this->v0 == mParm.v0 &&
      this->v1 == mParm.v1 &&
      this->v2 == mParm.v2)
   {
      return true;
   }
   else
   {
      return false;
   }
}

const bool Matrix::isEqual(const Matrix &mParm, const float &fE)
{
   if(this->v0.isEqual(mParm.v0, fE) &&
      this->v1.isEqual(mParm.v1, fE) &&
      this->v2.isEqual(mParm.v2, fE) &&
      this->v3.isEqual(mParm.v3, fE))
   {
      return true;
   }
   else
   {
      return false;
   }
};

const bool Matrix::isZero(const float &fE)
{
   if(this->v0.isZero(fE) &&
      this->v1.isZero(fE) &&
      this->v2.isZero(fE) &&
      this->v3.isZero(fE))
   {
      return true;
   }
   else
   {
      return false;
   }
};

const bool Matrix::isZero(const Matrix &mParam, const float &fE)
{
   if(mParam.v0.isZero(fE) &&
      mParam.v1.isZero(fE) &&
      mParam.v2.isZero(fE) &&
      mParam.v3.isZero(fE))
   {
      return true;
   }
   else
   {
      return false;
   }
};

const bool Matrix::isIdentity(const float &fE)
{
   Matrix mTemp(IDENTITY);
   return this->isEqual(mTemp, fE);
};

const bool Matrix::isIdentity()
{
   Matrix mTemp(IDENTITY);
   return this->isEqual(mTemp, DEF_TOLERANCE);
};

const bool Matrix::isIdentity(const Matrix &mParam, const float &fE)
{
   Matrix mTemp(IDENTITY);
   return mTemp.isEqual(mParam, fE);
};

void Matrix::T()
{
   this->set(Vect(this->m0, this->m4, this->m8, this->m12), 
                Vect(this->m1, this->m5, this->m9, this->m13), 
                Vect(this->m2, this->m6, this->m10, this->m14),
                Vect(this->m3, this->m7, this->m11, this->m15));
};

Matrix Matrix::getT()
{
   return Matrix(Vect(this->m0, this->m4, this->m8, this->m12), 
                 Vect(this->m1, this->m5, this->m9, this->m13), 
                 Vect(this->m2, this->m6, this->m10, this->m14),
                 Vect(this->m3, this->m7, this->m11, this->m15));
};

Matrix Matrix::getT(Matrix &mParam)
{
   mParam.set(Vect(mParam.m0, mParam.m4, mParam.m8, mParam.m12), 
                 Vect(mParam.m1, mParam.m5, mParam.m9, mParam.m13), 
                 Vect(mParam.m2, mParam.m6, mParam.m10, mParam.m14),
                 Vect(mParam.m3, mParam.m7, mParam.m11, mParam.m15));
   return mParam;
}
Matrix Matrix::getMinors()
{
   Matrix mMinors;
   mMinors.v0.set((((this->m5 * this->m10 * this->m15) + (this->m6 * this->m11 * this->m13) + (this->m7 * this->m9  * this->m14)) -
                   ((this->m7 * this->m10 * this->m13) + (this->m6 * this->m9  * this->m15) + (this->m5 * this->m11 * this->m14))),
                 -(((this->m4 * this->m10 * this->m15) + (this->m6 * this->m11 * this->m12) + (this->m7 * this->m8  * this->m14)) -
                   ((this->m7 * this->m10 * this->m12) + (this->m6 * this->m8  * this->m15) + (this->m4 * this->m11 * this->m14))),
                 (((this->m4 * this->m9  * this->m15) + (this->m5 * this->m11 * this->m12) + (this->m7 * this->m8  * this->m13)) -
                   ((this->m7 * this->m9  * this->m12) + (this->m5 * this->m8  * this->m15) + (this->m4 * this->m11 * this->m13))),
                 -(((this->m4 * this->m9  * this->m14) + (this->m5 * this->m10 * this->m12) + (this->m6 * this->m8  * this->m13)) -
                   ((this->m6 * this->m9  * this->m12) + (this->m5 * this->m8  * this->m14) + (this->m4 * this->m10 * this->m13))));

   mMinors.v1.set(-(((this->m1 * this->m10 * this->m15) + (this->m2 * this->m11 * this->m13) + (this->m3 * this->m9  * this->m14)) -
                    ((this->m3 * this->m10 * this->m13) + (this->m2 * this->m9  * this->m15) + (this->m1 * this->m11 * this->m14))),
                   (((this->m0 * this->m10 * this->m15) + (this->m2 * this->m11 * this->m12) + (this->m3 * this->m8  * this->m14)) -
                    ((this->m3 * this->m10 * this->m12) + (this->m2 * this->m8  * this->m15) + (this->m0 * this->m11 * this->m14))),
                  -(((this->m0 * this->m9  * this->m15) + (this->m1 * this->m11 * this->m12) + (this->m3 * this->m8  * this->m13)) -
                    ((this->m3 * this->m9  * this->m12) + (this->m1 * this->m8  * this->m15) + (this->m0 * this->m11 * this->m13))),
                   (((this->m0 * this->m9  * this->m14) + (this->m1 * this->m10 * this->m12) + (this->m2 * this->m8  * this->m13)) -
                    ((this->m2 * this->m9  * this->m12) + (this->m1 * this->m8  * this->m14) + (this->m0 * this->m10 * this->m13))));

   mMinors.v2.set((((this->m1 * this->m6  * this->m15) + (this->m2 * this->m7  * this->m13) + (this->m3 * this->m5  * this->m14)) -
                  ((this->m3 * this->m6  * this->m13) + (this->m2 * this->m5  * this->m15) + (this->m1 * this->m7  * this->m14))),
                 -(((this->m0 * this->m6  * this->m15) + (this->m2 * this->m7  * this->m12) + (this->m3 * this->m4  * this->m14)) -
                  ((this->m3 * this->m6  * this->m12) + (this->m2 * this->m4  * this->m15) + (this->m0 * this->m7  * this->m14))),
                 (((this->m0 * this->m5  * this->m15) + (this->m1 * this->m7  * this->m12) + (this->m3 * this->m4  * this->m13)) -
                  ((this->m3 * this->m5  * this->m12) + (this->m1 * this->m4  * this->m15) + (this->m0 * this->m7  * this->m13))),
                 -(((this->m0 * this->m6  * this->m14) + (this->m1 * this->m7  * this->m12) + (this->m2 * this->m4  * this->m13)) -
                  ((this->m2 * this->m6  * this->m12) + (this->m1 * this->m4  * this->m14) + (this->m0 * this->m6  * this->m13))));

   mMinors.v3.set(-(((this->m1 * this->m6  * this->m11) + (this->m2 * this->m7  * this->m9)  + (this->m3 * this->m5  * this->m10)) -
                  ((this->m3 * this->m6  * this->m9)  + (this->m2 * this->m5  * this->m11) + (this->m1 * this->m7  * this->m10))),
                 (((this->m0 * this->m6  * this->m11) + (this->m2 * this->m7  * this->m8)  + (this->m3 * this->m4  * this->m10)) -
                  ((this->m3 * this->m6  * this->m8)  + (this->m2 * this->m4  * this->m11) + (this->m0 * this->m7  * this->m10))),
                 -(((this->m0 * this->m5  * this->m11) + (this->m1 * this->m7  * this->m8)  + (this->m3 * this->m4  * this->m9 )) -
                  ((this->m3 * this->m5  * this->m8)  + (this->m1 * this->m4  * this->m11) + (this->m0 * this->m7  * this->m9 ))),
                 (((this->m0 * this->m5  * this->m10) + (this->m1 * this->m6  * this->m8)  + (this->m2 * this->m4  * this->m9 )) -
                  ((this->m2 * this->m5  * this->m8)  + (this->m1 * this->m4  * this->m10) + (this->m0 * this->m6  * this->m9 ))));

   return mMinors;
}

//Matrix Determinant
float Matrix::det()
{

   return (  this->m0*(((this->m5 * this->m10 * this->m15) + (this->m6 * this->m11 * this->m13) + (this->m7 * this->m9  * this->m14)) -
                       ((this->m7 * this->m10 * this->m13) + (this->m6 * this->m9  * this->m15) + (this->m5 * this->m11 * this->m14))) -
             this->m1*(((this->m4 * this->m10 * this->m15) + (this->m6 * this->m11 * this->m12) + (this->m7 * this->m8  * this->m14)) -
                       ((this->m7 * this->m10 * this->m12) + (this->m6 * this->m8  * this->m15) + (this->m4 * this->m11 * this->m14))) +
             this->m2*(((this->m4 * this->m9  * this->m15) + (this->m5 * this->m11 * this->m12) + (this->m7 * this->m8  * this->m13)) -
                       ((this->m7 * this->m9  * this->m12) + (this->m5 * this->m8  * this->m15) + (this->m4 * this->m11 * this->m13))) -
             this->m3*(((this->m4 * this->m9  * this->m14) + (this->m5 * this->m10 * this->m12) + (this->m6 * this->m8  * this->m13)) -
                       ((this->m6 * this->m9  * this->m12) + (this->m5 * this->m8  * this->m14) + (this->m4 * this->m10 * this->m13))));

};

void Matrix::inv()
{
   float fDet = this->det();
   Matrix mTemp(this->getMinors());

   if(!Util::isZero(fDet,DEF_TOLERANCE))
   {
      this->set(mTemp);
      this->T();
      *this/=fDet;
   }
};


Matrix Matrix::getInv()
{  
   float fDet = this->det();
   if(!Util::isZero(fDet,DEF_TOLERANCE))
   {
      Matrix mTemp(this->getMinors());
      mTemp.set(this->getT(mTemp));
      return mTemp/fDet;
   }
   else
   {
      return Matrix(IDENTITY);
   }
};
