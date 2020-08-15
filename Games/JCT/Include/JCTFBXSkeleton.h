#pragma once
#include "JCTFBXObject.h"
#include "JCTFBXBone.h"
#include "Vect.h"
#include "math3d.h"
#include "JCTPCSTree.h"

class JCTFBXSkeleton : public JCTTree, public JCTFBXBone
{
   //JCTFBXMaterial *m_pMaterials;
   //JCTFBXTexture *m_pTextures;
   unsigned int m_iPolyCount;
   unsigned int m_iVertCount;
   string m_sSkeletonName;
public:

   void setSkeletonName(const char *pName){this->m_sSkeletonName.assign(pName);};
   string getSkeletonName(){return this->m_sSkeletonName;};

   /*JCTFBXPoly m_pPolygons;
   JCTFBXVert m_pVertices;*/
   JCTFBXSkeleton(const string &name);
   JCTFBXSkeleton(void);
  
   ~JCTFBXSkeleton(void);
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