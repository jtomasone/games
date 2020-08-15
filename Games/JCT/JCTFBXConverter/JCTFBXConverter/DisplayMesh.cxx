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

#define MAT_HEADER_LENGTH 200


void JCTFBXConvert::DisplayMesh(KFbxNode* pNode)
{
    KFbxMesh* lMesh = (KFbxMesh*) pNode->GetNodeAttribute ();

    DisplayString("Mesh Name: ", (char *) pNode->GetName());
    //DisplayMetaDataConnections(lMesh);
    //DisplayControlsPoints(lMesh);
    DisplayPolygons(lMesh);
    DisplayMaterialMapping(lMesh);
    DisplayMaterial(lMesh);
    DisplayTexture(lMesh);
    DisplayMaterialConnections(lMesh);
    DisplayLink(lMesh);
    DisplayShape(lMesh);
    
}


void JCTFBXConvert::DisplayControlsPoints(KFbxMesh* pMesh)
{
    int i, lControlPointsCount = pMesh->GetControlPointsCount();
    KFbxVector4* lControlPoints = pMesh->GetControlPoints();

    DisplayString("    Control Points");

    for (i = 0; i < lControlPointsCount; i++)
    {
        DisplayInt("        Control Point ", i);
        Display3DVector("            Coordinates: ", lControlPoints[i]);

        for (int j = 0; j < pMesh->GetLayerCount(); j++)
        {
            KFbxLayerElementNormal* leNormals = pMesh->GetLayer(j)->GetNormals();
            if (leNormals)
            {
                if (leNormals->GetMappingMode() == KFbxLayerElement::eBY_CONTROL_POINT)
                {
                    char header[100];
                    sprintf(header, "            Normal Vector (on layer %d): ", j); 
                    if (leNormals->GetReferenceMode() == KFbxLayerElement::eDIRECT)
                        Display3DVector(header, leNormals->GetDirectArray().GetAt(i));
                }
            }
        }
    }

    DisplayString("");
}


void JCTFBXConvert::DisplayPolygons(KFbxMesh* pMesh)
{
    int i, j, lPolygonCount = pMesh->GetPolygonCount();
    KFbxVector4* lControlPoints = pMesh->GetControlPoints(); 
    char header[100];

    //DisplayString("    Polygons");
    DisplayInt("        Polygons ", lPolygonCount);

    int vertexId = 0;
    for (i = 0; i < lPolygonCount; i++)
    {
        DisplayInt("        Polygon ", i);
        int l;

        for (l = 0; l < pMesh->GetLayerCount(); l++)
        {
            KFbxLayerElementPolygonGroup* lePolgrp = pMesh->GetLayer(l)->GetPolygonGroups();
            if (lePolgrp)
            {
                switch (lePolgrp->GetMappingMode())
                {
                case KFbxLayerElement::eBY_POLYGON:
                    if (lePolgrp->GetReferenceMode() == KFbxLayerElement::eINDEX)
                    {
                        sprintf(header, "        Assigned to group (on layer %d): ", l); 
                        int polyGroupId = lePolgrp->GetIndexArray().GetAt(i);
                        DisplayInt(header, polyGroupId);
                        break;
                    }
                default:
                    // any other mapping modes don't make sense
                    DisplayString("        \"unsupported group assignment\"");
                    break;
                }
            }
        }

        int lPolygonSize = pMesh->GetPolygonSize(i);

        DisplayInt("        Polygon Size: ", lPolygonSize);

        for (j = 0; j < lPolygonSize; j++)
        {
            int lControlPointIndex = pMesh->GetPolygonVertex(i, j);

            Display3DVector("            Coordinates: ", lControlPoints[lControlPointIndex]);

            for (l = 0; l < pMesh->GetLayerCount(); l++)
            {
                KFbxLayerElementVertexColor* leVtxc = pMesh->GetLayer(l)->GetVertexColors();
                if (leVtxc)
                {
                    sprintf(header, "            Color vertex (on layer %d): ", l); 

                    switch (leVtxc->GetMappingMode())
                    {
                    case KFbxLayerElement::eBY_CONTROL_POINT:
                        switch (leVtxc->GetReferenceMode())
                        {
                        case KFbxLayerElement::eDIRECT:
                            DisplayColor(header, leVtxc->GetDirectArray().GetAt(lControlPointIndex));
                            break;
                        case KFbxLayerElement::eINDEX_TO_DIRECT:
                            {
                                int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
                                DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
                            }
                            break;
                        default:
                            break; // other reference modes not shown here!
                        }
                        break;

                    case KFbxLayerElement::eBY_POLYGON_VERTEX:
                        {
                            switch (leVtxc->GetReferenceMode())
                            {
                            case KFbxLayerElement::eDIRECT:
                                DisplayColor(header, leVtxc->GetDirectArray().GetAt(vertexId));
                                break;
                            case KFbxLayerElement::eINDEX_TO_DIRECT:
                                {
                                    int id = leVtxc->GetIndexArray().GetAt(vertexId);
                                    DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
                                }
                                break;
                            default:
                                break; // other reference modes not shown here!
                            }
                        }
                        break;

                    case KFbxLayerElement::eBY_POLYGON: // doesn't make much sense for UVs
                    case KFbxLayerElement::eALL_SAME:   // doesn't make much sense for UVs
                    case KFbxLayerElement::eNONE:       // doesn't make much sense for UVs
                        break;
                    }
                }

                KFbxLayerElementUV* leUV = pMesh->GetLayer(l)->GetUVs();
                if (leUV)
                {
                    sprintf(header, "            Texture UV (on layer %d): ", l); 

                    switch (leUV->GetMappingMode())
                    {
                    case KFbxLayerElement::eBY_CONTROL_POINT:
                        switch (leUV->GetReferenceMode())
                        {
                        case KFbxLayerElement::eDIRECT:
                            Display2DVector(header, leUV->GetDirectArray().GetAt(lControlPointIndex));
                            break;
                        case KFbxLayerElement::eINDEX_TO_DIRECT:
                            {
                                int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
                                Display2DVector(header, leUV->GetDirectArray().GetAt(id));
                            }
                            break;
                        default:
                            break; // other reference modes not shown here!
                        }
                        break;

                    case KFbxLayerElement::eBY_POLYGON_VERTEX:
                        {
                            int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
                            switch (leUV->GetReferenceMode())
                            {
                            case KFbxLayerElement::eDIRECT:
                            case KFbxLayerElement::eINDEX_TO_DIRECT:
                                {
                                    Display2DVector(header, leUV->GetDirectArray().GetAt(lTextureUVIndex));
                                }
                                break;
                            default:
                                break; // other reference modes not shown here!
                            }
                        }
                        break;

                    case KFbxLayerElement::eBY_POLYGON: // doesn't make much sense for UVs
                    case KFbxLayerElement::eALL_SAME:   // doesn't make much sense for UVs
                    case KFbxLayerElement::eNONE:       // doesn't make much sense for UVs
                        break;
                    }
                }


				KFbxLayerElementNormal* leNormal = pMesh->GetLayer(l)->GetNormals();
				if (leNormal)
				{
					sprintf(header, "            Normal (on layer %d): ", l); 

					if(leNormal->GetMappingMode() == KFbxLayerElement::eBY_POLYGON_VERTEX)
					{
						switch (leNormal->GetReferenceMode())
						{
						case KFbxLayerElement::eDIRECT:
							Display3DVector(header, leNormal->GetDirectArray().GetAt(vertexId));
							break;
						case KFbxLayerElement::eINDEX_TO_DIRECT:
							{
								int id = leNormal->GetIndexArray().GetAt(vertexId);
								Display3DVector(header, leNormal->GetDirectArray().GetAt(id));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
				}

				KFbxLayerElementTangent* leTangent = pMesh->GetLayer(l)->GetTangents();
				if (leTangent)
				{
					sprintf(header, "            Tangent (on layer %d): ", l); 

					if(leTangent->GetMappingMode() == KFbxLayerElement::eBY_POLYGON_VERTEX)
					{
						switch (leTangent->GetReferenceMode())
						{
						case KFbxLayerElement::eDIRECT:
							Display3DVector(header, leTangent->GetDirectArray().GetAt(vertexId));
							break;
						case KFbxLayerElement::eINDEX_TO_DIRECT:
							{
								int id = leTangent->GetIndexArray().GetAt(vertexId);
								Display3DVector(header, leTangent->GetDirectArray().GetAt(id));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
				}

				KFbxLayerElementBinormal* leBinormal = pMesh->GetLayer(l)->GetBinormals();
				if (leBinormal)
				{
					sprintf(header, "            Binormal (on layer %d): ", l); 

					if(leBinormal->GetMappingMode() == KFbxLayerElement::eBY_POLYGON_VERTEX)
					{
						switch (leBinormal->GetReferenceMode())
						{
						case KFbxLayerElement::eDIRECT:
							Display3DVector(header, leBinormal->GetDirectArray().GetAt(vertexId));
							break;
						case KFbxLayerElement::eINDEX_TO_DIRECT:
							{
								int id = leBinormal->GetIndexArray().GetAt(vertexId);
								Display3DVector(header, leBinormal->GetDirectArray().GetAt(id));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
				}
            } // for layer
            vertexId++;
        } // for polygonSize




    } // for polygonCount


    //check visibility for the edges of the mesh
    for(int l=0; l<pMesh->GetLayerCount(); ++l)
    {
        KFbxLayerElementVisibility* leVisibility=pMesh->GetLayer(0)->GetVisibility();
        if(leVisibility)
        {
            sprintf(header, "    Edge Visibility (on layer %d): ", l);
            DisplayString(header);
            switch(leVisibility->GetMappingMode())
            {
                //should be eBY_EDGE
            case KFbxLayerElement::eBY_EDGE:
                //should be eDIRECT
                for(int j=0; j!=pMesh->GetMeshEdgeCount();++j)
                {
                    DisplayInt("        Edge ", j);
                    DisplayBool("              Edge visibility: ", leVisibility->GetDirectArray().GetAt(j));
                }

                break;
            }

        }
    }
    DisplayString("");
}

void JCTFBXConvert::DisplayTextureNames( KFbxProperty &pProperty, KString& pConnectionString )
{
    int lLayeredTextureCount = pProperty.GetSrcObjectCount(KFbxLayeredTexture::ClassId);
    if(lLayeredTextureCount > 0)
    {
        for(int j=0; j<lLayeredTextureCount; ++j)
        {
            KFbxLayeredTexture *lLayeredTexture = KFbxCast <KFbxLayeredTexture>(pProperty.GetSrcObject(KFbxLayeredTexture::ClassId, j));
            int lNbTextures = lLayeredTexture->GetSrcObjectCount(KFbxTexture::ClassId);
            pConnectionString += " Texture ";

            for(int k =0; k<lNbTextures; ++k)
            {
                //lConnectionString += k;
                pConnectionString += "\"";
                pConnectionString += (char*)lLayeredTexture->GetName();
                pConnectionString += "\"";
                pConnectionString += " ";
            }
            pConnectionString += "of ";
            pConnectionString += pProperty.GetName();
            pConnectionString += " on layer ";
            pConnectionString += j;
        }
        pConnectionString += " |";
    }
    else
    {
        //no layered texture simply get on the property
        int lNbTextures = pProperty.GetSrcObjectCount(KFbxTexture::ClassId);

        if(lNbTextures > 0)
        {
            pConnectionString += " Texture ";
            pConnectionString += " ";

            for(int j =0; j<lNbTextures; ++j)
            {
                KFbxTexture* lTexture = KFbxCast <KFbxTexture> (pProperty.GetSrcObject(KFbxTexture::ClassId,j));
                if(lTexture)
                {
                    pConnectionString += "\"";
                    pConnectionString += (char*)lTexture->GetName();
                    pConnectionString += "\"";
                    pConnectionString += " ";
                }
            }
            pConnectionString += "of ";
            pConnectionString += pProperty.GetName();
            pConnectionString += " |";
        }
    }
}

void JCTFBXConvert::DisplayMaterialTextureConnections( KFbxSurfaceMaterial* pMaterial, char * header, int pMatId, int l )
{
    KString lConnectionString = "            Material %d (on layer %d) -- ";
    //Show all the textures

    KFbxProperty lProperty;
    //Diffuse Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
    DisplayTextureNames(lProperty, lConnectionString);

    //DiffuseFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuseFactor);
    DisplayTextureNames(lProperty, lConnectionString);

    //Emissive Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sEmissive);
    DisplayTextureNames(lProperty, lConnectionString);

    //EmissiveFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sEmissiveFactor);
    DisplayTextureNames(lProperty, lConnectionString);


    //Ambient Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sAmbient);
    DisplayTextureNames(lProperty, lConnectionString); 

    //AmbientFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sAmbientFactor);
    DisplayTextureNames(lProperty, lConnectionString);          

    //Specular Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sSpecular);
    DisplayTextureNames(lProperty, lConnectionString);  

    //SpecularFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sSpecularFactor);
    DisplayTextureNames(lProperty, lConnectionString);

    //Shininess Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sShininess);
    DisplayTextureNames(lProperty, lConnectionString);

    //Bump Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sBump);
    DisplayTextureNames(lProperty, lConnectionString);

    //Normal Map Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sNormalMap);
    DisplayTextureNames(lProperty, lConnectionString);

    //Transparent Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sTransparentColor);
    DisplayTextureNames(lProperty, lConnectionString);

    //TransparencyFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sTransparencyFactor);
    DisplayTextureNames(lProperty, lConnectionString);

    //Reflection Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sReflection);
    DisplayTextureNames(lProperty, lConnectionString);

    //ReflectionFactor Textures
    lProperty = pMaterial->FindProperty(KFbxSurfaceMaterial::sReflectionFactor);
    DisplayTextureNames(lProperty, lConnectionString);

    //Update header with material info
	bool lStringOverflow = (lConnectionString.GetLen() + 10 >= MAT_HEADER_LENGTH); // allow for string length and some padding for "%d"
	if (lStringOverflow)
	{
		// Truncate string!
		lConnectionString = lConnectionString.Left(MAT_HEADER_LENGTH - 10);
		lConnectionString = lConnectionString + "...";
	}
	sprintf(header, lConnectionString.Buffer(), pMatId, l);
	DisplayString(header);
}

void JCTFBXConvert::DisplayMaterialConnections(KFbxMesh* pMesh)
{
    int i, l, lPolygonCount = pMesh->GetPolygonCount();

    char header[MAT_HEADER_LENGTH];

    DisplayString("    Polygons Material Connections");

    //check whether the material maps with only one mesh
    bool lIsAllSame = true;
    for (l = 0; l < pMesh->GetLayerCount(); l++)
    {

        KFbxLayerElementMaterial* lLayerMaterial = pMesh->GetLayer(l)->GetMaterials();
        if (lLayerMaterial) 
        {
            KFbxSurfaceMaterial* lMaterial = NULL;
            int lMatId = -1;
            if( lLayerMaterial->GetMappingMode() == KFbxLayerElement::eBY_POLYGON) 
            {
                lIsAllSame = false;
                break;
            }
        }
    }

    //For eALL_SAME mapping type, just out the material and texture mapping info once
    if(lIsAllSame)
    {
        for (l = 0; l < pMesh->GetLayerCount(); l++)
        {

            KFbxLayerElementMaterial* lLayerMaterial = pMesh->GetLayer(l)->GetMaterials();
            if (lLayerMaterial) 
            {
                if( lLayerMaterial->GetMappingMode() == KFbxLayerElement::eALL_SAME) 
                {
                    KFbxSurfaceMaterial* lMaterial = pMesh->GetNode()->GetMaterial(lLayerMaterial->GetIndexArray().GetAt(0));    
                    int lMatId = lLayerMaterial->GetIndexArray().GetAt(0);
                    if(lMatId >=0)
                    {
                        DisplayInt("        All polygons share the same material on layer ", l);
                        DisplayMaterialTextureConnections(lMaterial, header, lMatId, l);
                    }
                }
            }
            else
            {
                //layer 0 has no material
                if(l == 0)
                    DisplayString("        no material applied");
            }
        }
    }

    //For eBY_POLYGON mapping type, just out the material and texture mapping info once
    else
    {
        for (i = 0; i < lPolygonCount; i++)
        {
            DisplayInt("        Polygon ", i);

            for (l = 0; l < pMesh->GetLayerCount(); l++)
            {

                KFbxLayerElementMaterial* lLayerMaterial = pMesh->GetLayer(l)->GetMaterials();
                if (lLayerMaterial) 
                {
                    KFbxSurfaceMaterial* lMaterial = NULL;
                    int lMatId = -1;
                    lMaterial = pMesh->GetNode()->GetMaterial(lLayerMaterial->GetIndexArray().GetAt(i));
                    lMatId = lLayerMaterial->GetIndexArray().GetAt(i);

                    if(lMatId >= 0)
                    {
                        DisplayMaterialTextureConnections(lMaterial, header, lMatId, l);
                    }
                }
            }
        }
    }
}


void JCTFBXConvert::DisplayMaterialMapping(KFbxMesh* pMesh)
{
    char* lMappingTypes[] = { "None", "By Control Point", "By Polygon Vertex", "By Polygon", "By Edge", "All Same" };
    char* lReferenceMode[] = { "Direct", "Index", "Index to Direct"};

    int lMtrlCount = 0;
    KFbxNode* lNode = NULL;
    if(pMesh){
        lNode = pMesh->GetNode();
        if(lNode)
            lMtrlCount = lNode->GetMaterialCount();    
    }

    for (int l = 0; l < pMesh->GetLayerCount(); l++)
    {
        KFbxLayerElementMaterial* leMat = pMesh->GetLayer(l)->GetMaterials();
        if (leMat)
        {
            char header[100];
            sprintf(header, "    Material layer %d: ", l); 
            DisplayString(header);


            DisplayString("           Mapping: ", lMappingTypes[leMat->GetMappingMode()]);
            DisplayString("           ReferenceMode: ", lReferenceMode[leMat->GetReferenceMode()]);

            int lMaterialCount = 0;
            KString lString;

            if (leMat->GetReferenceMode() == KFbxLayerElement::eDIRECT ||
                leMat->GetReferenceMode() == KFbxLayerElement::eINDEX_TO_DIRECT)
            {
                lMaterialCount = lMtrlCount;
            }

            if (leMat->GetReferenceMode() == KFbxLayerElement::eINDEX ||
                leMat->GetReferenceMode() == KFbxLayerElement::eINDEX_TO_DIRECT)
            {
                int i;

                lString = "           Indices: ";

                int lIndexArrayCount = leMat->GetIndexArray().GetCount(); 
                for (i = 0; i < lIndexArrayCount; i++)
                {
                    lString += leMat->GetIndexArray().GetAt(i);

                    if (i < lIndexArrayCount - 1)
                    {
                        lString += ", ";
                    }
                }

                lString += "\n";

                printf(lString);
            }
        }
    }

    DisplayString("");
}

