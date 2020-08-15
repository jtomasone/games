#pragma once
#include "jctfbxobject.h"
#include "mathengine.h"

/*
             Color
             Number
             Bool
             Enum
             Vector
             object
             Integer
             Lcl Translation
             Lcl Rotation
             Lcl Scaling
             Visiblity
             Vector3D
             Action

            Display Name: Show
            Internal Name: Show
            Type: Bool
            Is Animatable: false
            Is Temporary: false
            Default Value: true
*/

struct JCTPType
{
//   JCTPType(){};
public:
//   void setValue(const int &vTemp){this->m_iBaseValue = vTemp;};
//   Vect getValue() const {return this->m_iBaseValue;};
//   virtual void process()=0;
   virtual ~JCTPType() {}

private:
   int m_iBaseValue;
};

struct JCTPTypeVector : public JCTPType
{
   void setValue(const Vect &vTemp){this->m_vValue = vTemp;};
   Vect getValue() const {return this->m_vValue;};
   virtual void process(){};
private:
   Vect m_vValue;
};

struct JCTPTypeFloat : public JCTPType
{
   
   void setValue(const float &fValue){this->m_fValue = fValue;};
   float getValue() const {return this->m_fValue;};
   virtual void process(){};
private:
   float m_fValue;
};

struct JCTPTypeBool : public JCTPType
{
   void setValue(const bool &bTemp){this->m_bValue = bTemp;};
   const bool getValue() const {return this->m_bValue;};
   virtual void process(){};
private:
   bool m_bValue;
};

struct JCTPTypeInteger : public JCTPType
{
   void setValue(const int &iValue){this->m_iValue = iValue;};
   int getValue() const {return this->m_iValue;};
   virtual void process(){};
private:
   int m_iValue;
};

struct JCTPTypeString : public JCTPType
{
   void setValue(const string &sTemp){this->m_sValue = sTemp;};
   string getValue() const {return m_sValue;};
   virtual void process(){};
private:
   string m_sValue;
};

/*


struct JCTPTypeObject : public JCTPType
{
   void setValue(const string &sTemp){this->m_sValue = sTemp;};
   string getValue() const {return m_sValue;};
   virtual void process(){};
private:
   string m_sValue;
};


struct JCTPTypeLclTranslation : public JCTPType
{
   void setValue(const Vect &vTemp){this->m_vValue = vTemp;};
   Vect getValue() const {return this->m_vValue;};
   virtual void process(){};
private:
   Vect m_vValue;
};

struct JCTPTypeLclRotation : public JCTPType
{
   void setValue(const Vect &vTemp){this->m_vValue = vTemp;};
   Vect getValue() const {return this->m_vValue;};
   virtual void process(){};
private:
   Vect m_vValue;
};

struct JCTPTypeLclScaling : public JCTPType
{
   void setValue(const Vect &vTemp){this->m_vValue = vTemp;};
   Vect getValue() const {return this->m_vValue;};
   virtual void process(){};
private:
   Vect m_vValue;
};

struct JCTPTypeVisibility : public JCTPType
{
   void setValue(const float &fValue){this->m_fValue = fValue;};
   float getValue() const {return this->m_fValue;};
   virtual void process(){};
private:
   float m_fValue;
};

struct JCTPTypeVector3D : public JCTPType
{
   void setValue(const Vect &vTemp){this->m_vValue = vTemp;};
   Vect getValue() const {return this->m_vValue;};
   virtual void process(){};
private:
   Vect m_vValue;
};

struct JCTPTypeAction : public JCTPType
{
   void setValue(const bool &bTemp){this->m_bValue = bTemp;};
   const bool getValue() const {return this->m_bValue;};
   virtual void process(){};
private:
   bool m_bValue;
};
*/


const string JCT_PTYPENAMENAME_COLOR = "Color";
const string JCT_PTYPENAME_NUMBER = "Number";
const string JCT_PTYPENAME_BOOL = "Bool";
const string JCT_PTYPENAME_ENUM = "Enum";
const string JCT_PTYPENAME_VECTOR = "Vector";
const string JCT_PTYPENAME_OBJECT = "object";
const string JCT_PTYPENAME_INTEGER = "Integer";
const string JCT_PTYPENAME_LCL_TRANSLATION = "Lcl Translation";
const string JCT_PTYPENAME_LCL_ROTATION = "Lcl Rotation";
const string JCT_PTYPENAME_LCL_SCALING = "Lcl Scaling";
const string JCT_PTYPENAME_VISIBLITY = "Visiblity";
const string JCT_PTYPENAME_VECTOR3D = "Vector3D";
const string JCT_PTYPENAME_ACTION = "Action";


enum JCT_PTYPES
{
   JCT_PTYPE_COLOR            = 0, 
   JCT_PTYPE_NUMBER            ,
   JCT_PTYPE_BOOL              ,
   JCT_PTYPE_ENUM              ,
   JCT_PTYPE_VECTOR            ,
   JCT_PTYPE_OBJECT            ,
   JCT_PTYPE_INTEGER           ,
   JCT_PTYPE_LCL_TRANSLATION   ,
   JCT_PTYPE_LCL_ROTATION      ,
   JCT_PTYPE_LCL_SCALING       ,
   JCT_PTYPE_VISIBLITY         ,
   JCT_PTYPE_VECTOR3D          ,
   JCT_PTYPE_ACTION            
};

class JCTFBXProperty //:
   //public JCTFBXObject
{
private:
   string m_sDisplayName;
   string m_sInternalName;
   enum JCT_PTYPES m_ePType;
   bool m_bAnimatable;
   bool m_bTemporary;

public:
   JCTPType *m_pPropertyValue;

   JCTFBXProperty(const string &sPType);
   ~JCTFBXProperty(void);
   enum JCT_PTYPES getPropertyType(){return this->m_ePType;};
   void setPropertyType(enum JCT_PTYPES eType){this->m_ePType = eType;};

   bool getIsAnimatable(){return this->m_bAnimatable;};
   void setIsAnimatable(bool bIsAnimatable){this->m_bAnimatable = bIsAnimatable;};
   bool getIsTemporary(){return this->m_bTemporary;};
   void setIsTemporary(bool bIsTemporary){this->m_bTemporary = bIsTemporary;};

   string getDisplayName(){return this->m_sDisplayName;};
   void setDisplayName(string sDisplayName){this->m_sDisplayName = sDisplayName;};
   string getInternalName(){return this->m_sInternalName;};
   void setInternalName(string sInternalName){this->m_sInternalName = sInternalName;};


};
