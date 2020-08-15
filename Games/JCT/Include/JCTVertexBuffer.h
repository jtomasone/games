#ifndef JCTVertexBuffer_H
#pragma once
#include "JCTObject.h"

#define JCTVertexBuffer_H

class JCTVertexBuffer :
   public JCTObject
{
public:

   JCTVertexBuffer();
   JCTVertexBuffer(const string &name);
   ~JCTVertexBuffer(void);
};
#endif