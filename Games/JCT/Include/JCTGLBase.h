#pragma once
#include "gltools.h"   // GLTools
//#include <gl/gl.h>

class JCTGLBase
{
public:
   JCTGLBase(void);
   ~JCTGLBase(void);
   virtual void Render() = 0;
   virtual void SetupProjection(const int &width, const int &height) = 0;
   virtual void SetupPixelFormat() = 0;
   virtual void LoadStartup() = 0;
   virtual void SetupCamera() = 0;
};
