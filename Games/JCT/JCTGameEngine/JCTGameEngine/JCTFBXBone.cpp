#include "JCTFBXBone.h"

JCTFBXBone::JCTFBXBone(const string &name,const unsigned int &iCount) : JCTNode(name)
{
   this->m_pProperties = new JCTFBXBoneProps();
   this->m_pProperties->reserve(iCount);
}

JCTFBXBone::JCTFBXBone(void) : JCTNode("")
{
}

JCTFBXBone::~JCTFBXBone(void)
{
}

void JCTFBXBone::Render()
{
};

const float JCTFBXBone::getSize()
{
   return this->m_fSize;
};

void JCTFBXBone::setSize(const float &fSize)
{
   this->m_fSize = fSize;
};

const Vect JCTFBXBone::getColor()
{
   return this->m_vColor;
};

void JCTFBXBone::setColor(const Vect &vColor)
{
   this->m_vColor = vColor;
};

const Matrix JCTFBXBone::getAttri()
{
   return this->m_mAttrib;
};

void JCTFBXBone::setAttrib(const Matrix &mAttrib)
{
   this->m_mAttrib = mAttrib;
};
