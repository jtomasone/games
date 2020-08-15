#pragma once
#include "JCTFBXProperty.h"
/*
 Display Name: Show
            Internal Name: Show
            Type: Bool
            Is Animatable: false
            Is Temporary: false
            Default Value: true
*/
JCTFBXProperty::JCTFBXProperty(const string &sPType)// : JCTFBXObject()
{
   if(JCT_PTYPENAMENAME_COLOR              == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_COLOR;
   }
   else if(JCT_PTYPENAME_NUMBER            == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeFloat();
      this->m_ePType = JCT_PTYPE_NUMBER;
   }
   else if(JCT_PTYPENAME_BOOL              == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeBool();
      this->m_ePType = JCT_PTYPE_BOOL;
   }
   else if(JCT_PTYPENAME_ENUM              == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeString();
      this->m_ePType = JCT_PTYPE_ENUM;
   }
   else if(JCT_PTYPENAME_VECTOR            == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_VECTOR;
   }
   else if(JCT_PTYPENAME_OBJECT            == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeString();
      this->m_ePType = JCT_PTYPE_OBJECT;
   }
   else if(JCT_PTYPENAME_INTEGER           == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeInteger();
      this->m_ePType = JCT_PTYPE_INTEGER;
   }
   else if(JCT_PTYPENAME_LCL_TRANSLATION   == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_LCL_TRANSLATION;
   }
   else if(JCT_PTYPENAME_LCL_ROTATION      == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_LCL_ROTATION;
   }
   else if(JCT_PTYPENAME_LCL_SCALING       == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_LCL_SCALING;
   }
   else if(JCT_PTYPENAME_VISIBLITY         == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeFloat();
      this->m_ePType = JCT_PTYPE_VISIBLITY;
   }
   else if(JCT_PTYPENAME_VECTOR3D          == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeVector();
      this->m_ePType = JCT_PTYPE_VECTOR3D;
   }
   else if(JCT_PTYPENAME_ACTION            == sPType)
   {
      this->m_pPropertyValue = new JCTPTypeBool();
      this->m_ePType = JCT_PTYPE_ACTION;
   }
}

JCTFBXProperty::~JCTFBXProperty(void)
{
}
