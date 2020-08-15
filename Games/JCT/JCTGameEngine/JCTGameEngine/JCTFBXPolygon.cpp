#include "JCTFBXPolygon.h"


JCTFBXPolygon::JCTFBXPolygon(void)
{
   this->setType(JCTFBX_POLYGON);
}


JCTFBXPolygon::~JCTFBXPolygon(void)
{
}


JCTFBXPolygon::JCTFBXPolygon(const unsigned int &iCount)
{
   /*this->m_pNormals = new JCTPolyComponents;
   this->m_pPoints = new JCTPolyComponents;
   this->m_pUVs = new JCTPolyComponents;
*/
   this->m_pNormals.reserve(iCount);// = new M3DVector3d[iCount];
   this->m_pPoints.reserve(iCount);
   this->m_pUVs.reserve(iCount);
   this->setVertCount(iCount);
};

void JCTFBXPolygon::setVertCount(const unsigned int &iCount)
{
   this->m_iVertCount = iCount;
};

unsigned int JCTFBXPolygon::getVertCount()
{
   return this->m_iVertCount;
};

void JCTFBXPolygon::Render()
{
   for(size_t x=0; x<this->getVertCount(); x++)
   {
      Vect* pTemp = this->m_pPoints[x];
      //Vect* pTemp2 = this->m_pNormals[x];
      if(pTemp)
      {
         glVertex3fv((GLfloat*)pTemp);//, &pTemp[1], &pTemp[2]);//, (GLfloat)this->m_pPoints[x][1], (GLfloat)this->m_pPoints[x][2]);
      }
      if(this->m_pUVs.size())
      {
         Vect* pTemp3 = this->m_pUVs[x];
         if(pTemp3)
         {//glNormal3fv((const GLfloat *)pTemp2);
            glTexCoord2fv((GLfloat*)pTemp3);
         }
      }
      /*      if(pTemp3)
      {
         glTexCoord2fv((GLfloat *)this->m_pUVs[x]);
      }
*/
   }

}
