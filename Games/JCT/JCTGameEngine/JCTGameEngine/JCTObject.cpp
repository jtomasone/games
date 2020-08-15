
#include "JCTObject.h"

JCTObject::JCTObject(const string &name)
{
   this->m_sName = name;
}

JCTObject::JCTObject(void)
{
}

JCTObject::~JCTObject(void)
{
}

void JCTObject::setName(const string &name)
{
   this->m_sName = name;
};

const string JCTObject::getName()
{
   return this->m_sName;
};
