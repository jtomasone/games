/**************************************************************************************

 Copyright (C) 2001 - 2009 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material 
 (collectively the "Data") in these files contain unpublished information 
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by 
 Canada and United States of America federal copyright law and by international 
 treaties. 
 
 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, 
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE. 
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE. 
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE. 

**************************************************************************************/

#include "JCTFBXConvert.h"


void JCTFBXConvert::DisplayTextureInfo(KFbxTexture* pTexture, int pBlendMode)
{


    DisplayString("            Name: \"", (char *) pTexture->GetName(), "\"");
    DisplayString("            File Name: \"", (char *) pTexture->GetFileName(), "\"");
    DisplayDouble("            Scale U: ", pTexture->GetScaleU());
    DisplayDouble("            Scale V: ", pTexture->GetScaleV());
    DisplayDouble("            Translation U: ", pTexture->GetTranslationU());
    DisplayDouble("            Translation V: ", pTexture->GetTranslationV());
    DisplayBool("            Swap UV: ", pTexture->GetSwapUV());
    DisplayDouble("            Rotation U: ", pTexture->GetRotationU());
    DisplayDouble("            Rotation V: ", pTexture->GetRotationV());
    DisplayDouble("            Rotation W: ", pTexture->GetRotationW());

    char* lAlphaSources[] = { "None", "RGB Intensity", "Black" };

    DisplayString("            Alpha Source: ", lAlphaSources[pTexture->GetAlphaSource()]);
    DisplayDouble("            Cropping Left: ", pTexture->GetCroppingLeft());
    DisplayDouble("            Cropping Top: ", pTexture->GetCroppingTop());
    DisplayDouble("            Cropping Right: ", pTexture->GetCroppingRight());
    DisplayDouble("            Cropping Bottom: ", pTexture->GetCroppingBottom());

    char* lMappingTypes[] = { "Null", "Planar", "Spherical", "Cylindrical", 
        "Box", "Face", "UV", "Environment" };

    DisplayString("            Mapping Type: ", lMappingTypes[pTexture->GetMappingType()]);

    if (pTexture->GetMappingType() == KFbxTexture::ePLANAR)
    {
        char* lPlanarMappingNormals[] = { "X", "Y", "Z" };

        DisplayString("            Planar Mapping Normal: ", lPlanarMappingNormals[pTexture->GetPlanarMappingNormal()]);
    }

    char* lBlendModes[]   = { "Translucent", "Add", "Modulate", "Modulate2" };   
    if(pBlendMode >= 0)
        DisplayString("            Blend Mode: ", lBlendModes[pBlendMode]);
    DisplayDouble("            Alpha: ", pTexture->GetDefaultAlpha());

    char* lMaterialUses[] = { "Model Material", "Default Material" };

    DisplayString("            Material Use: ", lMaterialUses[pTexture->GetMaterialUse()]);

    char* pTextureUses[] = { "Standard", "Shadow Map", "Light Map", 
        "Spherical Reflexion Map", "Sphere Reflexion Map", "Bump Normal Map" };

    DisplayString("            Texture Use: ", pTextureUses[pTexture->GetTextureUse()]);
    DisplayString("");                

}

void JCTFBXConvert::FindAndDisplayTextureInfoByProperty(KFbxProperty pProperty, bool& pDisplayHeader, int pMaterialIndex){

    if( pProperty.IsValid() )
    {

        KFbxTexture * lTexture= NULL;

        //Here we have to check if it's layeredtextures, or just textures:
        int lLayeredTextureCount = pProperty.GetSrcObjectCount(KFbxLayeredTexture::ClassId);
        if(lLayeredTextureCount > 0)
        {
            for(int j=0; j<lLayeredTextureCount; ++j)
            {
                DisplayInt("    Layered Texture: ", j);
                KFbxLayeredTexture *lLayeredTexture = KFbxCast <KFbxLayeredTexture>(pProperty.GetSrcObject(KFbxLayeredTexture::ClassId, j));
                int lNbTextures = lLayeredTexture->GetSrcObjectCount(KFbxTexture::ClassId);
                for(int k =0; k<lNbTextures; ++k)
                {
                    KFbxTexture* lTexture = KFbxCast <KFbxTexture> (lLayeredTexture->GetSrcObject(KFbxTexture::ClassId,k));
                    if(lTexture)
                    {

                        if(pDisplayHeader){                    
                            DisplayInt("    Textures connected to Material ", pMaterialIndex);
                            pDisplayHeader = false;
                        }

                        //NOTE the blend mode is ALWAYS on the LayeredTexture and NOT the one on the texture.
                        //Why is that?  because one texture can be shared on different layered textures and might
                        //have different blend modes.

                        KFbxLayeredTexture::EBlendMode lBlendMode;
                        lLayeredTexture->GetTextureBlendMode(k, lBlendMode);
                        DisplayString("    Textures for ", pProperty.GetName());
                        DisplayInt("        Texture ", k);  
                        DisplayTextureInfo(lTexture, (int) lBlendMode);   
                    }

                }
            }
        }
        else
        {
            //no layered texture simply get on the property
            int lNbTextures = pProperty.GetSrcObjectCount(KFbxTexture::ClassId);
            for(int j =0; j<lNbTextures; ++j)
            {

                KFbxTexture* lTexture = KFbxCast <KFbxTexture> (pProperty.GetSrcObject(KFbxTexture::ClassId,j));
                if(lTexture)
                {
                    //display connectMareial header only at the first time
                    if(pDisplayHeader){                    
                        DisplayInt("    Textures connected to Material ", pMaterialIndex);
                        pDisplayHeader = false;
                    }             

                    DisplayString("    Textures for ", pProperty.GetName());
                    DisplayInt("        Texture ", j);  
                    DisplayTextureInfo(lTexture, -1);
                }
            }
        }


        int lNbTex = pProperty.GetSrcObjectCount(KFbxTexture::ClassId);
        for (int lTextureIndex = 0; lTextureIndex < lNbTex; lTextureIndex++){
            lTexture = (KFbxTexture *)pProperty.GetSrcObject(KFbxTexture::ClassId, lTextureIndex); 


        }//end for 
    }//end if pProperty

}


void JCTFBXConvert::DisplayTexture(KFbxGeometry* pGeometry)
{
    int lMaterialIndex;
    KFbxProperty lProperty;    
    int lNbMat = pGeometry->GetNode()->GetSrcObjectCount(KFbxSurfaceMaterial::ClassId);
    for (lMaterialIndex = 0; lMaterialIndex < lNbMat; lMaterialIndex++){
        KFbxSurfaceMaterial *lMaterial = (KFbxSurfaceMaterial *)pGeometry->GetNode()->GetSrcObject(KFbxSurfaceMaterial::ClassId, lMaterialIndex);
        bool lDisplayHeader = true;

        //go through all the possible textures
        if(lMaterial){

            int lTextureIndex;
            FOR_EACH_TEXTURE(lTextureIndex)
            {
                lProperty = lMaterial->FindProperty(KFbxLayerElement::TEXTURE_CHANNEL_NAMES[lTextureIndex]);
                FindAndDisplayTextureInfoByProperty(lProperty, lDisplayHeader, lMaterialIndex); 
            }

        }//end if(lMaterial)

    }// end for lMaterialIndex     
}
