#pragma once
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "jctobject.h"
#include <gl/gl.h>

enum JCTFBXTypes
{
   JCTFBX_MESH,
   JCTFBX_POLYGON,
   JCTFBX_MATERIAL,
   JCTFBX_PROPERTY,
   JCTFBX_SKELETON
};


class JCTFBXObject :
   public JCTObject
{
   enum JCTFBXTypes m_eType;
public:
   JCTFBXObject(void);
   ~JCTFBXObject(void);
   void setType(const enum JCTFBXTypes &eType);
   const enum JCTFBXTypes getType();
   virtual void Render() = 0;
};

