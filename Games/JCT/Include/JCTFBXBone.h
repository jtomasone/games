#pragma once
#include "JCTFBXobject.h"
#include "JCTFBXPolygon.h"
#include "JCTFBXProperty.h"
#include "Vect.h"
#include "Matrix.h"
#include "JCTPCSTree.h"
#include "math3d.h"

using namespace std;
typedef std::vector<JCTFBXProperty*>JCTFBXBoneProps;

class JCTFBXBone :
   public JCTFBXObject, public JCTNode
{
   //JCTFBXMaterial *m_pMaterials;
   //JCTFBXTexture *m_pTextures;
   unsigned int m_iPolyCount;
   unsigned int m_iVertCount;
   float m_fSize;
   Vect m_vColor;
   Matrix m_mAttrib;

public:
   JCTFBXBoneProps *m_pProperties;
   void setVertCount(const unsigned int &iCount);
   void setPolyCount(const unsigned int &iCount);

   const float getSize();
   void setSize(const float &fSize);

   const Vect getColor();
   void setColor(const Vect &vColor);

   const Matrix getAttri();
   void setAttrib(const Matrix &vColor);

   unsigned int getVertCount();
   unsigned int getPolyCount();

   /*JCTFBXPoly m_pPolygons;
   JCTFBXVert m_pVertices;*/
   JCTFBXBone(void);
   JCTFBXBone(const string &name,const unsigned int &iCount=0);

   ~JCTFBXBone(void);
   JCTFBXBone(const unsigned int &iCPointCount, const unsigned int &iPolyCount);
   virtual void Render();

};

/*
Skeleton Name: soldier:LeftArm
    Type: Limb Node
    Limb Node Size: 6000.000000
    Color: 0.129496 (red), 0.481631 (green), 0.800000 (blue)
    Property Count: 3
        Property 0
            Display Name: DefaultAttributeIndex
            Internal Name: DefaultAttributeIndex
            Type: Integer
            Min Limit: 0.000000
            Max Limit: 0.000000
            Is Animatable: false
            Is Temporary: false
            Default Value: 0
        Property 1
            Display Name: LeftArm.Custom_Attributes.DefaultAttributeIndex
            Internal Name: LeftArm.Custom_Attributes.DefaultAttributeIndex
            Type: Integer
            Min Limit: 0.000000
            Max Limit: 0.000000
            Is Animatable: true
            Is Temporary: false
            Default Value: 1769108608
        Property 2
            Display Name: LeftArm.Custom_Attributes.LimbLength
            Internal Name: LeftArm.Custom_Attributes.LimbLength
            Type: Number
            Min Limit: 0.000000
            Max Limit: 0.000000
            Is Animatable: true
            Is Temporary: false
            Default Value: 0.000000
    Pivot Information
        Pivot State: Reference
        Pre-Rotation: 0.000000 0.000000 0.000000
        Post-Rotation: 0.000000 0.000000 0.000000
        Rotation Pivot: 0.000000 0.000000 0.000000
        Rotation Offset: 0.000000 0.000000 0.000000
        Scaling Pivot: 0.000000 0.000000 0.000000
        Scaling Offset: 0.000000 0.000000 0.000000
    Limits Information
        Translation limits: Inactive
            X
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
            Y
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
            Z
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
        Rotation limits: Active
            X
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
            Y
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
            Z
                Min Limit: Inactive
                Min Limit Value: 0.000000
                Max Limit: Inactive
                Max Limit Value: 0.000000
        Scaling limits: Inactive
            X
                Min Limit: Inactive
                Min Limit Value: 1.000000
                Max Limit: Inactive
                Max Limit Value: 1.000000
            Y
                Min Limit: Inactive
                Min Limit Value: 1.000000
                Max Limit: Inactive
                Max Limit Value: 1.000000
            Z
                Min Limit: Inactive
                Min Limit Value: 1.000000
                Max Limit: Inactive
                Max Limit Value: 1.000000
    Transformation Propagation
        Rotation Space: Euler YXZ
        Use the Rotation Space for Limit specification only: No
        Transformation Inheritance: RSrs
    Geometric Transformations
        Translation: 0.000000 0.000000 0.000000
        Rotation:    0.000000 0.000000 0.000000
        Scaling:     0.010000 0.010000 0.010000
        */