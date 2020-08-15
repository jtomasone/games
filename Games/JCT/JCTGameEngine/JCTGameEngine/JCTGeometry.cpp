
#include "JCTGeometry.h"

JCTGeometry::JCTGeometry(const string &name)
{
   this->m_sName = name;
};

JCTGeometry::JCTGeometry()
{
   this->m_sName = "Default";
};

JCTGeometry::~JCTGeometry(void)
{
}
