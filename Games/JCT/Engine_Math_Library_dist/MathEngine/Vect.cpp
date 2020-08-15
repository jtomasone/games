#include "MathEngine.h"
#include <math.h>



Vect::Vect(const float &fX, const float &fY, const float &fZ, const float &fW)
{
   this->set(fX, fY, fZ, fW);
}

Vect::Vect(const double &fX, const double &fY, const double &fZ, const double &fW)
{
   this->set((float)fX, (float)fY, (float)fZ, (float)fW);
}

Vect::Vect(const Vect &v1)
{
   this->set(v1);
   if(v1[w] == 0.0)
   {
      this->mW = 1.0f;
   }

}

float Vect::getElement(const size_t &iPos)
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

Vect::Vect()
{
   this->set(0.0, 0.0, 0.0, 1.0f);
}

const Vect Vect::operator = (const Vect *v2)
{
  /*Vect *vTemp = new Vect();//v2->mX,v2->mY,v2->mX,v2->mW);
   vTemp->set(*v2);*/
   this->set(v2->mX,v2->mY,v2->mZ,1.0f);
   return *this;
}

const Vect Vect::operator += (const Vect &v2)
{
   this->mX += v2[x];
   this->mY += v2[y];
   this->mZ += v2[z]; 
   this->mW += v2[w];
   return *this;

 //  return new 
};
/*
Vect& Vect::operator += (const Vect *v2) const
{
   return new Vect((this->mX + v2[x]),
                (this->mY + v2[y]),
                (this->mZ + v2[z]), 
                (this->mW + v2[w]));
};
*/
const Vect Vect::operator -= (const Vect &v2)
{
   this->mX -= v2[x];
   this->mY -= v2[y];
   this->mZ -= v2[z]; 
   this->mW -= v2[w];
   return *this;


};

const Vect Vect::operator *= (const Vect &v2)
{
   this->mX *= v2[x];
   this->mY *= v2[y];
   this->mZ *= v2[z]; 
   this->mW *= v2[w];
   return *this;
};

const Vect Vect::operator *= (const float &fS)
{
   this->mX *= fS;
   this->mY *= fS;
   this->mZ *= fS; 
   this->mW *= fS;
   return *this;
};


const Vect Vect::operator /= (Vect &v2)
{
   if(DEF_TOLERANCE > fabsf(this->mX))
   {
      this->mX /= v2[x];
   }
   if(DEF_TOLERANCE > fabsf(this->mY))
   {
      this->mY /= v2[y];
   }
   if(DEF_TOLERANCE > fabsf(this->mZ))
   {
      this->mZ /= v2[z]; 
   }
   if(DEF_TOLERANCE > fabsf(this->mW))
   {
      this->mW /= v2[w];
   }
   return *this;
};

const Vect Vect::operator /= (const float &fM)
{
   if(!this->isZero())
   {
      return Vect((this->mX / fM),
                   (this->mY / fM),
                   (this->mZ / fM), 
                   (this->mW / fM));
   }
   else
   {
      return Vect();
   }

};

const Vect Vect::operator + (const Vect &v2)
{
   //this->mW += v2[w];
   //return this;

   return Vect(this->mX + v2[x], this->mY + v2[y], this->mZ + v2[z], 1.0f);
};

const Vect Vect::operator - (const Vect &v2)
{
   return Vect(this->mX - v2[x], this->mY - v2[y], this->mZ - v2[z], this->mW - v2[w]);
};

const Vect Vect::operator * (const Vect &v2)
{
   return Vect(this->mX * v2[x], this->mY * v2[y], this->mZ * v2[z], 1.0f);
};

const Vect Vect::operator * (const float &fS)
{
   return Vect(this->mX * fS, this->mY * fS, this->mZ * fS, this->mW * fS);
};

const Vect Vect::operator / (Vect &v2)
{
   if(!v2.isZero())
   {
      return Vect(this->mX / v2[x], this->mY / v2[y], this->mZ / v2[z], this->mW / v2[w]);
   }
   else
   {
      return Vect();
   }
   
};

const Vect Vect::operator / (const float &fM)
{
   if(!(DEF_TOLERANCE > fabs(fM)))
   {
      return Vect(this->mX / fM, this->mY / fM, this->mZ / fM, this->mW / fM);
   }
   else
   {
      return Vect();
   }
   
};

/*
float Vect::operator [](const unsigned int &i2) const
{
   //(4 < i2)
   float *fRet = new float(0.0f);

   switch(i2)
   {
   case 0:
      fRet =  (float*)&this->mX;

   case 1:
      fRet =  (float*)&this->mY;
      break;

   case 2:
      fRet =  (float*)&this->mZ;
      break;

   case 3:
      fRet =  (float*)&this->mW;
      break;
   }
   return fRet;

}


const bool Vect::operator ==(const float &fL, const float &fR) const
{
   if((fabs(fL - fR) < DEF_TOLERANCE))
   {
      return true;
   }
   else
   {
      return false;
   }

}
*/
const bool Vect::operator ==(const Vect &v2) const
{
   if((fabsf(this->mX - v2[x]) < DEF_TOLERANCE) &&
      (fabsf(this->mY - v2[y]) < DEF_TOLERANCE) &&
      (fabsf(this->mZ - v2[z]) < DEF_TOLERANCE))
   {
      return true;
   }
   else
   {
      return false;
   }

}

Vect Vect::Negate(const Vect &v2) const
{
   return Vect(-v2[x], -v2[y], -v2[z], -v2[w]);
}

void Vect::set(const float &fX, const float &fY, const float &fZ, const float &fW)
{
   this->mX = fX;
   this->mY = fY;
   this->mZ = fZ;
   this->mW = fW;
}

void Vect::set(const Vect &v2)
{
   this->mX = v2[x];
   this->mY = v2[y];
   this->mZ = v2[z];
   this->mW = v2[w];
};

bool Vect::isEqual(const Vect &v2, const float fTolerance) const
{
   if(fTolerance > fabsf(this->mX - v2[x]) &&
      fTolerance > fabsf(this->mY - v2[y]) &&
      fTolerance > fabsf(this->mZ - v2[z]) &&
      fTolerance > fabsf(this->mW - v2[w]))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Vect::isZero(const float fTolerance) const
{
   if((fTolerance > fabsf(this->mX)) &&
      (fTolerance > fabsf(this->mY)) &&
      (fTolerance > fabsf(this->mZ)) &&
      ((1.0 + fTolerance) > fabsf(this->mW)))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Vect::isZero(const Vect &v2, const float fTolerance) const
{
   if((fTolerance > fabsf(v2[x])) &&
      (fTolerance > fabsf(v2[y])) &&
      (fTolerance > fabsf(v2[z])) &&
      ((1.0 + fTolerance) > fabsf(v2[w])))
   {
      return true;
   }
   else
   {
      return false;
   }
}

float Vect::dot(const Vect &v2)
{
   return (this->mX * v2[x])+
          (this->mY * v2[y])+
          (this->mZ * v2[z]);
}

float Vect::dot(const Vect &v1, const Vect &v2) const
{
   return (v1[x] * v2[x])+
          (v1[y] * v2[y])+
          (v1[z] * v2[z]);
}

//a × b = (a2b3 − a3b2) i + (a3b1 − a1b3) j + (a1b2 − a2b1) k = (a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1).
const Vect Vect::cross(Vect &v2) const
{
   return Vect((this->mY * v2[z]) - (this->mZ * v2[y]),
                (this->mZ * v2[x]) - (this->mX * v2[z]),
                (this->mX * v2[y]) - (this->mY * v2[x]),
                1.0f);
}

Vect Vect::Scale(const float &fScalar)
{
   return Vect(((Vect)*this) * (fScalar));
}

Vect Vect::ScaleDiv(const float &fScalar)
{
   return (((Vect)*this) / (fScalar));
}
//sqrt((ax * ax) + (ay * ay) + (az * az)) 
float Vect::mag() const
{
   return sqrt((this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ));// + (this->mW * this->mW));
}

float Vect::magSqr() const
{
   float fTemp = this->mag();
   return fTemp*fTemp;
}

Vect Vect::getNorm() const
{
   float fTemp = this->mag();
   return Vect(this->mX/fTemp, this->mY/fTemp, this->mZ/fTemp);

}

void Vect::norm()
{
   float fTemp = this->mag();
   this->set(this->mX/fTemp, this->mY/fTemp, this->mZ/fTemp);//, this->mW/fTemp);
}

float Vect::getAngle(const Vect &v2)
{
   return acos(this->dot(this->getNorm(), v2.getNorm()));
}

void Vect::print()
{
  printf("Vector(%d, %d, %d, %d)", this->mX, this->mY, this->mZ, this->mW);
}
