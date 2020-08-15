#pragma once
#include "jctfbxobject.h"
class JCTFBXMaterial :
   public JCTFBXObject
{
public:
   JCTFBXMaterial(void);
   ~JCTFBXMaterial(void);
   virtual void Render();
};

/*
    Material layer 0: 
           Mapping: All Same
           ReferenceMode: Index to Direct

    Materials on layer 0: 
        Material 0
            Name: "blinn2"
            Ambient: 0.590000,0.590000,0.590000
            Diffuse: 1.000000,1.000000,1.000000
            Specular: 0.000000,0.000000,0.000000
            Emissive: 0.000000,0.000000,0.000000
            Opacity: 1.000000
            Shininess: 1.245731
            Reflectivity: 0.000000
            Shading Model: Phong

    Textures connected to Material 0
    Textures for DiffuseColor
        Texture 0
            Name: "Texture file6"
            File Name: "c:\Dev\Workspaces\Gam575\jtomasone_JCT-GRAPHICS-PC\keenan2010spring_gam575\student\jtomasone\JCTFBXConverter\JCTFBXConverter\Mixamo-Soldier_8k_poly.fbm/Soldier_new-1.tga"
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
*/