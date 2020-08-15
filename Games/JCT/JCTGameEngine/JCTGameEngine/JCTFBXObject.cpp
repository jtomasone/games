#include "JCTFBXObject.h"


JCTFBXObject::JCTFBXObject(void)
{
}


JCTFBXObject::~JCTFBXObject(void)
{
}

void JCTFBXObject::setType(const enum JCTFBXTypes &eType)
{
   this->m_eType = eType;
}

const enum JCTFBXTypes JCTFBXObject::getType()
{
   return this->m_eType;
};