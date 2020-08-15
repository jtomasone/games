#ifndef JCTVertexBufferNode_H
#pragma once
#include "JCTPCSTree.h"

#define JCTVertexBufferNode_H

class JCTVertexBufferNode :
   public JCTNode
{
public:

   JCTVertexBufferNode();
   JCTVertexBufferNode(const string &name);
   ~JCTVertexBufferNode(void);
};
#endif