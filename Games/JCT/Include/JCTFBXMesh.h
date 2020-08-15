#pragma once
#include "jctfbxobject.h"
#include "JCTFBXPolygon.h"
#include "Vect.h"
#include "math3d.h"

typedef std::vector<JCTFBXPolygon*>JCTFBXPoly;
typedef std::vector<Vect*>JCTFBXVert;


class JCTFBXMesh :
   public JCTFBXObject
{
   //JCTFBXMaterial *m_pMaterials;
   //JCTFBXTexture *m_pTextures;
   unsigned int m_iPolyCount;
   unsigned int m_iVertCount;

public:
   void setVertCount(const unsigned int &iCount);
   void setPolyCount(const unsigned int &iCount);

   unsigned int getVertCount();
   unsigned int getPolyCount();


   JCTFBXPoly m_pPolygons;
   JCTFBXVert m_pVertices;
   JCTFBXMesh(void);
   ~JCTFBXMesh(void);
   JCTFBXMesh(const unsigned int &iCPointCount, const unsigned int &iPolyCount);
   virtual void Render();

};

/*

    Material layer 0: 
           Mapping: All Same
           ReferenceMode: Index to Direct
           Indices: 0

    Materials on layer 0: 
        Material 0
            Name: "Material #12"
            Ambient: 0.588235 (red), 0.588235 (green), 0.588235 (blue)
            Diffuse: 0.588235 (red), 0.588235 (green), 0.588235 (blue)
            Specular: 0.900000 (red), 0.900000 (green), 0.900000 (blue)
            Emissive: 1.000000 (red), 1.000000 (green), 1.000000 (blue)
            Opacity: 1.000000
            Shininess: 2.000000
            Reflectivity: 0.000000
            Shading Model: phong

    Textures connected to Material 0
    Textures for DiffuseColor
        Texture 0
            Name: "Map #2"
            File Name: "C:\Work\Mom_Net\3d\warbear.psd"
            Scale U: 1.000000
            Scale V: 1.000000
            Translation U: 0.000000
            Translation V: 0.000000
            Swap UV: false
            Rotation U: 0.000000
            Rotation V: 0.000000
            Rotation W: 0.000000
            Alpha Source: None
            Cropping Left: 0.000000
            Cropping Top: 0.000000
            Cropping Right: 0.000000
            Cropping Bottom: 0.000000
            Mapping Type: UV
            Alpha: 1.000000
            Material Use: Model Material
            Texture Use: Standard

    Polygons Material Connections
        All polygons share the same material on layer 0
            Material 0 (on layer 0) --  Texture  "Map #2" of DiffuseColor |
    Pivot Information
        Pivot State: Reference
        Pre-Rotation: -90.000000 0.000000 0.000000
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
        Rotation Space: Euler XYZ
        Use the Rotation Space for Limit specification only: No
        Transformation Inheritance: RSrs
    Geometric Transformations
        Translation: 0.000000 0.000000 0.000000
        Rotation:    0.000000 0.000000 0.000000
        Scaling:     1.000000 1.000000 1.000000
*/