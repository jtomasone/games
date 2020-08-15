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

void JCTFBXConvert::DisplayMaterial(KFbxGeometry* pGeometry)
{
    int lMaterialCount = 0;
    KFbxNode* lNode = NULL;
    if(pGeometry){
        lNode = pGeometry->GetNode();
        if(lNode)
            lMaterialCount = lNode->GetMaterialCount();    
    }

    for (int l = 0; l < pGeometry->GetLayerCount(); l++)
    {
        KFbxLayerElementMaterial* leMat = pGeometry->GetLayer(l)->GetMaterials();
        if (leMat)
        {
            if (leMat->GetReferenceMode() == KFbxLayerElement::eINDEX)
                // Materials are in an undefined external table
                continue;

            if (lMaterialCount > 0)
            {
                char header[100];
                KFbxPropertyDouble3 lKFbxDouble3;
                KFbxPropertyDouble1 lKFbxDouble1;
                KFbxColor theColor;

                sprintf(header, "    Materials on layer %d: ", l); 
                DisplayString(header);

                for (int lCount = 0; lCount < lMaterialCount; lCount ++)
                {
                    DisplayInt("        Material ", lCount);

                    KFbxSurfaceMaterial *lMaterial = lNode->GetMaterial(lCount);

                    DisplayString("            Name: \"", (char *) lMaterial->GetName(), "\""); 

                    //Get the implementation to see if it's a hardware shader.
                    const KFbxImplementation* lImplementation = GetImplementation(lMaterial, ImplementationHLSL);
                    KString lImplemenationType = "HLSL";
                    if(!lImplementation)
                    {
                        lImplementation = GetImplementation(lMaterial, ImplementationCGFX);
                        lImplemenationType = "CGFX";
                    }
                    if(lImplementation)
                    {
                        //Now we have a hardware shader, let's read it
                        printf("            Hardware Shader Type: %s\n", lImplemenationType.Buffer());
                        KFbxBindingTable const* lRootTable = lImplementation->GetRootTable();
                        fbxString lFileName = lRootTable->DescAbsoluteURL.Get();
                        fbxString lTechniqueName = lRootTable->DescTAG.Get(); 


                        KFbxBindingTable const* lTable = lImplementation->GetRootTable();
                        size_t lEntryNum = lTable->GetEntryCount();

                        for(int i=0;i <(int)lEntryNum; ++i)
                        {
                            const KFbxBindingTableEntry& lEntry = lTable->GetEntry(i);
                            const char* lEntrySrcType = lEntry.GetEntryType(true); 
                            KFbxProperty lFbxProp;


                            KString lTest = lEntry.GetSource();
                            printf("            Entry: %s\n", lTest.Buffer());


                            if ( strcmp( KFbxPropertyEntryView::sEntryType, lEntrySrcType ) == 0 )
                            {   
                                lFbxProp = lMaterial->FindPropertyHierarchical(lEntry.GetSource()); 
                                if(!lFbxProp.IsValid())
                                {
                                    lFbxProp = lMaterial->RootProperty.FindHierarchical(lEntry.GetSource());
                                }


                            }
                            else if( strcmp( KFbxConstantEntryView::sEntryType, lEntrySrcType ) == 0 )
                            {
                                lFbxProp = lImplementation->GetConstants().FindHierarchical(lEntry.GetSource());
                            }
                            if(lFbxProp.IsValid())
                            {
                                if( lFbxProp.GetSrcObjectCount( FBX_TYPE(KFbxTexture) ) > 0 )
                                {
                                    //do what you want with the texture
                                    for(int j=0; j<lFbxProp.GetSrcObjectCount(FBX_TYPE(KFbxTexture)); ++j)
                                    {
                                        KFbxTexture *lTex = lFbxProp.GetSrcObject(FBX_TYPE(KFbxTexture),j);
                                        printf("                Texture: %s\n", lTex->GetFileName());
                                    }
                                }
                                else
                                {
                                    KFbxDataType lFbxType = lFbxProp.GetPropertyDataType();
                                    KString blah = lFbxType.GetName();
                                    if(DTBool == lFbxType)
                                    {
                                        DisplayBool("                Bool: ", KFbxGet <bool> (lFbxProp) );
                                    }
                                    else if ( DTInteger == lFbxType ||  DTEnum  == lFbxType )
                                    {
                                        DisplayInt("                Int: ", KFbxGet <int> (lFbxProp));
                                    }
                                    else if ( DTFloat == lFbxType)
                                    {
                                        DisplayDouble("                Float: ", KFbxGet <float> (lFbxProp));

                                    }
                                    else if ( DTDouble == lFbxType)
                                    {
                                        DisplayDouble("                Double: ", KFbxGet <double> (lFbxProp));
                                    }
                                    else if ( DTString == lFbxType
                                        ||  DTUrl  == lFbxType
                                        ||  DTXRefUrl  == lFbxType )
                                    {
                                        DisplayString("                String: ", (KFbxGet <fbxString> (lFbxProp)).Buffer());
                                    }
                                    else if ( DTDouble2 == lFbxType)
                                    {
                                        fbxDouble2 lDouble2=KFbxGet <fbxDouble2> (lFbxProp);
                                        KFbxVector2 lVect;
                                        lVect[0] = lDouble2[0];
                                        lVect[1] = lDouble2[1];

                                        Display2DVector("                2D vector: ", lVect);
                                    }
                                    else if ( DTVector3D == lFbxType||DTDouble3 == lFbxType || DTColor3 == lFbxType)
                                    {
                                        fbxDouble3 lDouble3 = KFbxGet <fbxDouble3> (lFbxProp);


                                        KFbxVector4 lVect;
                                        lVect[0] = lDouble3[0];
                                        lVect[1] = lDouble3[1];
                                        lVect[2] = lDouble3[2];
                                        Display3DVector("                3D vector: ", lVect);
                                    }

                                    else if ( DTVector4D == lFbxType || DTDouble4 == lFbxType || DTColor4 == lFbxType)
                                    {
                                        fbxDouble4 lDouble4 = KFbxGet <fbxDouble4> (lFbxProp);
                                        KFbxVector4 lVect;
                                        lVect[0] = lDouble4[0];
                                        lVect[1] = lDouble4[1];
                                        lVect[2] = lDouble4[2];
                                        lVect[3] = lDouble4[3];
                                        Display4DVector("                4D vector: ", lVect);
                                    }
                                    else if ( DTDouble44 == lFbxType)
                                    {
                                        fbxDouble44 lDouble44 = KFbxGet <fbxDouble44> (lFbxProp);
                                        for(int j=0; j<4; ++j)
                                        {

                                            KFbxVector4 lVect;
                                            lVect[0] = lDouble44[j][0];
                                            lVect[1] = lDouble44[j][1];
                                            lVect[2] = lDouble44[j][2];
                                            lVect[3] = lDouble44[j][3];
                                            Display4DVector("                4x4D vector: ", lVect);
                                        }

                                    }
                                }

                            }   
                        }
                    }
                    else if(lMaterial->GetClassId().Is(KFbxSurfaceLambert::ClassId) )
                    {
                        // We found a Lambert material. Display its properties.
                        // Display the Ambient Color
                        lKFbxDouble3=((KFbxSurfaceLambert *)lMaterial)->GetAmbientColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Ambient: ", theColor);

                        // Display the Diffuse Color
                        lKFbxDouble3 =((KFbxSurfaceLambert *)lMaterial)->GetDiffuseColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Diffuse: ", theColor);

                        // Display the Emissive
                        lKFbxDouble3 =((KFbxSurfaceLambert *)lMaterial)->GetEmissiveColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Emissive: ", theColor);

                        // Display the Opacity
                        lKFbxDouble1 =((KFbxSurfaceLambert *)lMaterial)->GetTransparencyFactor();
                        DisplayDouble("            Opacity: ", 1.0-lKFbxDouble1.Get());
                    }
                    else if (lMaterial->GetClassId().Is(KFbxSurfacePhong::ClassId))
                    {
                        // We found a Phong material.  Display its properties.

                        // Display the Ambient Color
                        lKFbxDouble3 =((KFbxSurfacePhong *) lMaterial)->GetAmbientColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Ambient: ", theColor);

                        // Display the Diffuse Color
                        lKFbxDouble3 =((KFbxSurfacePhong *) lMaterial)->GetDiffuseColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Diffuse: ", theColor);

                        // Display the Specular Color (unique to Phong materials)
                        lKFbxDouble3 =((KFbxSurfacePhong *) lMaterial)->GetSpecularColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Specular: ", theColor);

                        // Display the Emissive Color
                        lKFbxDouble3 =((KFbxSurfacePhong *) lMaterial)->GetEmissiveColor();
                        theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
                        DisplayColor("            Emissive: ", theColor);

                        //Opacity is Transparency factor now
                        lKFbxDouble1 =((KFbxSurfacePhong *) lMaterial)->GetTransparencyFactor();
                        DisplayDouble("            Opacity: ", 1.0-lKFbxDouble1.Get());

                        // Display the Shininess
                        lKFbxDouble1 =((KFbxSurfacePhong *) lMaterial)->GetShininess();
                        DisplayDouble("            Shininess: ", lKFbxDouble1.Get());

                        // Display the Reflectivity
                        lKFbxDouble1 =((KFbxSurfacePhong *) lMaterial)->GetReflectionFactor();
                        DisplayDouble("            Reflectivity: ", lKFbxDouble1.Get());
                    }
                    else
                        DisplayString("Unknown type of Material");

                    KFbxPropertyString lString;
                    lString = lMaterial->GetShadingModel();
                    DisplayString("            Shading Model: ", lString.Get().Buffer());
                    DisplayString("");
                }
            }
        }
    }
}
