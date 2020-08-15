#include "JCTFBXMesh.h"

JCTFBXMesh::JCTFBXMesh(void)
{
   this->setType(JCTFBX_MESH);
}

JCTFBXMesh::JCTFBXMesh(const unsigned int &iCPointCount, const unsigned int &iPolyCount)
{
   this->m_iVertCount = iCPointCount;
   this->m_iPolyCount = iPolyCount;
   this->m_pPolygons.reserve(iPolyCount);
   this->m_pVertices.reserve(iCPointCount);
   this->setType(JCTFBX_MESH);
}

JCTFBXMesh::~JCTFBXMesh(void)
{

}
void JCTFBXMesh::setVertCount(const unsigned int &iCount)
{
   this->m_iVertCount = iCount;
};

void JCTFBXMesh::setPolyCount(const unsigned int &iCount)
{
   this->m_iPolyCount = iCount;
};

unsigned int JCTFBXMesh::getVertCount()
{
   return this->m_iVertCount;
};

unsigned int JCTFBXMesh::getPolyCount()
{
   return this->m_iPolyCount;
};

void JCTFBXMesh::Render()
{
   for(size_t x=0; x<this->m_iPolyCount; x++)
   {
   glBegin(GL_POLYGON);//GL_LINE_LOOP );
      this->m_pPolygons[x]->Render();
   glEnd();
   }
}