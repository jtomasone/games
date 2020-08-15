#ifndef JCTTexture_H

#pragma once
#include "JCTObject.h"

class JCTTexture :
   public JCTObject
{
public:
   JCTTexture();
   JCTTexture(const string &name);
   ~JCTTexture(void);
   char* name;
   size_t m_uiGLBind;

};

#endif
