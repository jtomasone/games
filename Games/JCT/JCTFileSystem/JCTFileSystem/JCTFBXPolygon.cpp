#include "JCTFBXPolygon.h"


JCTFBXPolygon::JCTFBXPolygon(void)
{
}


JCTFBXPolygon::~JCTFBXPolygon(void)
{
}

JCTFBXPolygon::JCTFBXPolygon(const int &iCount)
{
   this->m_pNormals = new M3DVector3d[iCount];
   this->m_pPoints = new float[(sizeof(float) * 3 * iCount)];
   this->m_pUVs = new float[(sizeof(float) * 2 * iCount)];
}