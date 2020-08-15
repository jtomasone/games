#include "JCTFBXMesh.h"

JCTFBXMesh::JCTFBXMesh(void)
{
}

JCTFBXMesh::~JCTFBXMesh(void)
{

}

JCTFBXMesh::JCTFBXMesh(const int &iCPointCount, const int &iPolyCount)
{
   this->m_pPolygons = new JCTFBXPolygon[iPolyCount];
   //this->m_pVertices = new Vect[iCPointCount];
}
