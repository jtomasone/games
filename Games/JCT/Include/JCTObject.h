#pragma once

#include <string>
using namespace std;

class JCTObject
{
   string m_sName;
public:
   JCTObject(const string &name);

   JCTObject(void);
   ~JCTObject(void);
   virtual const string getName();
   virtual void setName(const string &name);

};
