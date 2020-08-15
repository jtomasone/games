//#include "Stdio.h"
#include "JCTFBXFile.h"

#include <fbxfilesdk/kfbxio/kfbxiosettings.h>
#ifdef IOS_REF
	#undef  IOS_REF
	#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif


JCTFBXFile::JCTFBXFile(void)
{
}


JCTFBXFile::~JCTFBXFile(void)
{
}


void InitializeSdkObjects(KFbxSdkManager*& pSdkManager, KFbxScene*& pScene)
{
   // The first thing to do is to create the FBX SDK manager which is the 
   // object allocator for almost all the classes in the SDK.
   pSdkManager = KFbxSdkManager::Create();

   if (!pSdkManager)
   {
      printf("Unable to create the FBX SDK manager\n");
      exit(0);
   }

	// create an IOSettings object
	KFbxIOSettings * ios = KFbxIOSettings::Create(pSdkManager, IOSROOT );
	pSdkManager->SetIOSettings(ios);

	// Load plugins from the executable directory
	KString lPath = KFbxGetApplicationDirectory();
#if defined(KARCH_ENV_WIN)
	KString lExtension = "dll";
#elif defined(KARCH_ENV_MACOSX)
	KString lExtension = "dylib";
#elif defined(KARCH_ENV_LINUX)
	KString lExtension = "so";
#endif
	pSdkManager->LoadPluginsDirectory(lPath.Buffer(), lExtension.Buffer());

   // Create the entity that will hold the scene.
   pScene = KFbxScene::Create(pSdkManager,"");
}

void DestroySdkObjects(KFbxSdkManager* pSdkManager)
{
   // Delete the FBX SDK manager. All the objects that have been allocated 
   // using the FBX SDK manager and that haven't been explicitly destroyed 
   // are automatically destroyed at the same time.
   if (pSdkManager) pSdkManager->Destroy();
   pSdkManager = NULL;
}

bool SaveScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename, int pFileFormat, bool pEmbedMedia)
{
   int lMajor, lMinor, lRevision;
   bool lStatus = true;

   // Create an exporter.
   KFbxExporter* lExporter = KFbxExporter::Create(pSdkManager, "");

   if( pFileFormat < 0 || pFileFormat >= pSdkManager->GetIOPluginRegistry()->GetWriterFormatCount() )
   {
      // Write in fall back format if pEmbedMedia is true
      pFileFormat = pSdkManager->GetIOPluginRegistry()->GetNativeWriterFormat();

      if (!pEmbedMedia)
      {
         //Try to export in ASCII if possible
         int lFormatIndex, lFormatCount = pSdkManager->GetIOPluginRegistry()->GetWriterFormatCount();

         for (lFormatIndex=0; lFormatIndex<lFormatCount; lFormatIndex++)
         {
            if (pSdkManager->GetIOPluginRegistry()->WriterIsFBX(lFormatIndex))
            {
               KString lDesc =pSdkManager->GetIOPluginRegistry()->GetWriterFormatDescription(lFormatIndex);
               char *lASCII = "ascii";
               if (lDesc.Find(lASCII)>=0)
               {
                  pFileFormat = lFormatIndex;
                  break;
               }
            }
         }
      }
   }

   // Set the export states. By default, the export states are always set to 
   // true except for the option eEXPORT_TEXTURE_AS_EMBEDDED. The code below 
   // shows how to change these states.

   IOS_REF.SetBoolProp(EXP_FBX_MATERIAL,      true);
   IOS_REF.SetBoolProp(EXP_FBX_TEXTURE,       true);
   IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED,      pEmbedMedia);
   IOS_REF.SetBoolProp(EXP_FBX_SHAPE,         true);
   IOS_REF.SetBoolProp(EXP_FBX_GOBO,         true);
   IOS_REF.SetBoolProp(EXP_FBX_ANIMATION,      true);
   IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);

   // Initialize the exporter by providing a filename.
   if(lExporter->Initialize(pFilename, pFileFormat, pSdkManager->GetIOSettings()) == false)
   {
      printf("Call to KFbxExporter::Initialize() failed.\n");
      printf("Error returned: %s\n\n", lExporter->GetLastErrorString());
      return false;
   }

   KFbxSdkManager::GetFileFormatVersion(lMajor, lMinor, lRevision);
   printf("FBX version number for this version of the FBX SDK is %d.%d.%d\n\n", lMajor, lMinor, lRevision);

   // Export the scene.
   lStatus = lExporter->Export(pScene); 

   // Destroy the exporter.
   lExporter->Destroy();
   return lStatus;
}

bool LoadScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename)
{
   int lFileMajor, lFileMinor, lFileRevision;
   int lSDKMajor,  lSDKMinor,  lSDKRevision;
   //int lFileFormat = -1;
   int i, lAnimStackCount;
   bool lStatus;
   char lPassword[1024];

   // Get the file version number generate by the FBX SDK.
   KFbxSdkManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

   // Create an importer.
   KFbxImporter* lImporter = KFbxImporter::Create(pSdkManager,"");

   // Initialize the importer by providing a filename.
   const bool lImportStatus = lImporter->Initialize(pFilename, -1, pSdkManager->GetIOSettings());
   lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

   if( !lImportStatus )
   {
      printf("Call to KFbxImporter::Initialize() failed.\n");
      printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

      if (lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_YET ||
         lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_ANYMORE)
      {
         printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
         printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
      }

      return false;
   }

   printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

   if (lImporter->IsFBX())
   {
      printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

      // From this point, it is possible to access animation stack information without
      // the expense of loading the entire file.

      printf("Animation Stack Information\n");

      lAnimStackCount = lImporter->GetAnimStackCount();

      printf("   Number of Animation Stacks: %d\n", lAnimStackCount);
      printf("   Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
      printf("\n");

      for(i = 0; i < lAnimStackCount; i++)
      {
         KFbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

         printf("   Animation Stack %d\n", i);
         printf("       Name: \"%s\"\n", lTakeInfo->mName.Buffer());
         printf("       Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

         // Change the value of the import name if the animation stack should be imported 
         // under a different name.
         printf("       Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

         // Set the value of the import state to false if the animation stack should be not
         // be imported. 
         printf("       Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
         printf("\n");
      }

      // Set the import states. By default, the import states are always set to 
      // true. The code below shows how to change these states.
      IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,      false);//true);
      IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,       true);
      IOS_REF.SetBoolProp(IMP_FBX_LINK,         false);//true);
      IOS_REF.SetBoolProp(IMP_FBX_SHAPE,         true);
      IOS_REF.SetBoolProp(IMP_FBX_GOBO,         false);//true);
      IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,      false);//true);
      IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
   }

   // Import the scene.
   lStatus = lImporter->Import(pScene);

   if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
   {
      printf("Please enter password: ");

      lPassword[0] = '\0';

      scanf("%s", lPassword);
      KString lString(lPassword);

      IOS_REF.SetStringProp(IMP_FBX_PASSWORD,     lString);
      IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

      lStatus = lImporter->Import(pScene);

      if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
      {
         printf("\nPassword is wrong, import aborted.\n");
      }
   }

   // Destroy the importer.
   lImporter->Destroy();

   return lStatus;
}


bool JCTFBXFile::Load(const char *filename, DWORD &dwError)
{
   LoadIntoMemory(filename, dwError);
   return 1;
   //tgaFile = this->getTGAData();
   //FILE *file;
   bool bSuccess=false;
   DWORD dwBytesRead = 0, dwPtr = 0;//, dwError = 0;
   //    file = fopen(filename, "rb");
   HANDLE hFile = Create((char*)filename, dwError, 0);//this->Create((char*)filename, dwError, OPEN_EXISTING);
   unsigned short nValue=0;

   if (dwError)
   {
     dwError = GetLastError();if (dwError)
     return false;
   }
   
   m_pSceneData = new unsigned char[10000000];

   
   this->Read((unsigned char*)m_pSceneData, 100000, dwError);
   //bSuccess = ReadFile(hFile, &tgaFile->header, sizeof(tgaFile->header), &dwBytesRead, NULL);
   dwError = GetLastError();
   
   printf("Data from FBX >>>%s\n", m_pSceneData);

   if (dwError)
   {
     return false;
   }
   /*
   if ( ((tgaFile->header.imageTypeCode != TGA_RGB) && (tgaFile->header.imageTypeCode != TGA_GRAYSCALE) && 
      (tgaFile->header.imageTypeCode != TGA_RGB_RLE) && (tgaFile->header.imageTypeCode != TGA_GRAYSCALE_RLE)) ||
      tgaFile->header.colorMapType != 0)
   {
     Close(dwError);
     return false;
   }

   // get image width and height
   this->setWidth(tgaFile->header.width);
   this->setHeight(tgaFile->header.height);

   tgaFile->width = this->getWidth();
   tgaFile->height = this->getHeight();;

   // colormode -> 3 = BGR, 4 = BGRA
   int colorMode = tgaFile->header.bpp / 8;

   // we don't handle less than 24 bit
   if (colorMode < 3)
   {
     CloseHandle(this->getHandle());
     return false;
   }

   this->setImageSize(this->getWidth() * this->getHeight() * colorMode);

   //allocate memory for image data
   tgaFile->data = new unsigned char[this->getImageSize()];

   // skip past the id if there is one
   if (tgaFile->header.idLength > 0)
   {
     this->Seek(tgaFile->header.idLength, dwError);
     if (dwError == JCTFILE_ERROR_SEEKFAIL) // Test for failure.
     { 
       return false;
     }
   }

   //read in image data
   if (tgaFile->header.imageTypeCode == TGA_RGB || tgaFile->header.imageTypeCode == TGA_GRAYSCALE)
   {
     Read((unsigned char*)tgaFile->data, this->getImageSize(), dwError);
     if (dwError == JCTFILE_ERROR_READFAIL)
     {
       return false;
     }
   }
   else
   {
     // this is an RLE compressed image
     unsigned char id;
     unsigned char length;
     rgba_t color = { 0, 0, 0, 0 };
     unsigned int i = 0;

     while (i < this->getImageSize())
     {
       this->Read((unsigned char*)&id, sizeof(unsigned char), dwError);

       // see if this is run length data
       if (id >= 128)// & 0x80)
       {
         // find the run length
         length = (unsigned char)(id - 127);

         // next 3 (or 4) bytes are the repeated values
         this->Read((unsigned char*)&color.b, sizeof(unsigned char), dwError);
         this->Read((unsigned char*)&color.g, sizeof(unsigned char), dwError);
         this->Read((unsigned char*)&color.r, sizeof(unsigned char), dwError);

         if (colorMode == 4)
         {
            Read((unsigned char*)&color.a, sizeof(unsigned char), dwError);
         }

         // save everything in this run
         while (length > 0)
         {
            this->m_pImageData[i++] = color.b;
            this->m_pImageData[i++] = color.g;
            this->m_pImageData[i++] = color.r;

            if (colorMode == 4)
              this->m_pImageData[i++] = color.a;

            --length;
         }
       }
       else
       {
         // the number of non RLE pixels
         length = unsigned char(id + 1);

         while (length > 0)
         {
            this->Read((unsigned char*)&color.b, sizeof(unsigned char), dwError);
            this->Read((unsigned char*)&color.g, sizeof(unsigned char), dwError);
            this->Read((unsigned char*)&color.r, sizeof(unsigned char), dwError);

            if (colorMode == 4)
            {
              this->Read((unsigned char*)&color.a, sizeof(unsigned char), dwError);
            }

            this->m_pImageData[i++] = color.b;
            this->m_pImageData[i++] = color.g;
            this->m_pImageData[i++] = color.r;

            if (colorMode == 4)
              this->m_pImageData[i++] = color.a;

            --length;
         }
       }
     }
   }

   this->Close(dwError);

   switch(tgaFile->header.imageTypeCode)
   {
   case TGA_RGB:
   case TGA_RGB_RLE:
     if (3 == colorMode)
     {
       this->setImageDataFormat(IMAGE_RGB);
       this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
       this->setColorDepth(24);
     }
     else
     {
       this->setImageDataFormat(IMAGE_RGBA);
       this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
       this->setColorDepth(32);
     }
     break;

   case TGA_GRAYSCALE:
   case TGA_GRAYSCALE_RLE:
     this->setImageDataFormat(IMAGE_LUMINANCE);
     this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
     this->setColorDepth(8);
     break;
   }

   //if ((tgaFile->header.imageDesc & TOP_LEFT) == TOP_LEFT)
   //   FlipVertical();

   // swap the red and blue components in the image data
   //SwapRedBlue();

   //close file
   //CloseHandle(this->getHandle());
   return (NULL != tgaFile->data);
   */
}

void JCTFBXFile::LoadContent(KFbxNode* pNode)
{
   KFbxNodeAttribute::EAttributeType lAttributeType;
   int i;

   if(pNode->GetNodeAttribute() == NULL)
   {
      printf("NULL Node Attribute\n\n");
   }
   else
   {
      lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());
      KFbxMesh* lMesh = 0;
      switch (lAttributeType)
      {
      case KFbxNodeAttribute::eMARKER:  
         //DisplayMarker(pNode);
         break;

      case KFbxNodeAttribute::eSKELETON:  
         //DisplaySkeleton(pNode);
         break;

      case KFbxNodeAttribute::eMESH:    
         lMesh = (KFbxMesh*) pNode->GetNodeAttribute ();

         LoadMesh(lMesh);
         //DisplayMesh(pNode);
         
         break;

      case KFbxNodeAttribute::eNURB:     
         //DisplayNurb(pNode);
         break;

      case KFbxNodeAttribute::ePATCH:    
         //DisplayPatch(pNode);
         break;

      case KFbxNodeAttribute::eCAMERA:   
         //DisplayCamera(pNode);
         break;

      case KFbxNodeAttribute::eLIGHT:    
         //DisplayLight(pNode);
         break;

      case KFbxNodeAttribute::eLODGROUP:
         //DisplayLodGroup(pNode);
         break;
      }   
   }

   /*DisplayUserProperties(pNode);
   DisplayTarget(pNode);
   DisplayPivotsAndLimits(pNode);
   DisplayTransformPropagation(pNode);
   DisplayGeometricTransform(pNode);
*/

   for(i = 0; i < pNode->GetChildCount(); i++)
   {
      LoadContent(pNode->GetChild(i));
   }
}
void JCTFBXFile::LoadIntoMemory(const char *filename, DWORD &dwError)
{
      KFbxSdkManager* lSdkManager = NULL;
   KFbxScene* lScene = NULL;
   bool lResult;

   // Prepare the FBX SDK.
   InitializeSdkObjects(lSdkManager, lScene);
   // Load the scene.

   // The example can take a FBX file as an argument.
   if(filename)
   {
      printf("\n\nFile: %s\n\n", filename);
      lResult = LoadScene(lSdkManager, lScene, filename);
   }
   else
   {
      // Destroy all objects created by the FBX SDK.
      DestroySdkObjects(lSdkManager);
      lResult = false;

      printf("\n\nUsage: ImportScene <FBX file name>\n\n");
   }

   if(lResult == false)
   {
      printf("\n\nAn error occurred while loading the scene...");
   }
   else 
   {
     KFbxNode* lNode = lScene->GetRootNode();

     if(lNode)
     {
       for(int i = 0; i < lNode->GetChildCount(); i++)
       {
         LoadContent(lNode->GetChild(i));
       }
     }
      /*
      // Display the scene.
      DisplayMetaData(lScene);

      printf("\n\n---------------------\nGlobal Light Settings\n---------------------\n\n");

      DisplayGlobalLightSettings(&lScene->GetGlobalSettings());

      printf("\n\n----------------------\nGlobal Camera Settings\n----------------------\n\n");

      DisplayGlobalCameraSettings(&lScene->GetGlobalSettings());

      printf("\n\n--------------------\nGlobal Time Settings\n--------------------\n\n");

      DisplayGlobalTimeSettings(&lScene->GetGlobalSettings());

      printf("\n\n---------\nHierarchy\n---------\n\n");

      DisplayHierarchy(lScene);

      printf("\n\n------------\nNode Content\n------------\n\n");

      DisplayContent(lScene);

      printf("\n\n----\nPose\n----\n\n");

      DisplayPose(lScene);

      printf("\n\n---------\nAnimation\n---------\n\n");

      DisplayAnimation(lScene);

      //now display generic information

      printf("\n\n---------\nGeneric Information\n---------\n\n");
      DisplayGenericInfo(lScene);
      */

   }

   // Destroy all objects created by the FBX SDK.
   DestroySdkObjects(lSdkManager);

}

void JCTFBXFile::LoadMesh(KFbxMesh* pMesh)
{
   int i, j, lPolygonCount = pMesh->GetPolygonCount();
   KFbxVector4* lControlPoints = pMesh->GetControlPoints(); 
   char header[100];


   int vertexId = 0;
   for (i = 0; i < lPolygonCount; i++)
   {
      int l;

      /*for (l = 0; l < pMesh->GetLayerCount(); l++)
      {
         KFbxLayerElementPolygonGroup* lePolgrp = pMesh->GetLayer(l)->GetPolygonGroups();
         if (lePolgrp)
         {
            switch (lePolgrp->GetMappingMode())
            {
            case KFbxLayerElement::eBY_POLYGON:
               if (lePolgrp->GetReferenceMode() == KFbxLayerElement::eINDEX)
               {
                  sprintf(header, "      Assigned to group (on layer %d): ", l); 
                  int polyGroupId = lePolgrp->GetIndexArray().GetAt(i);
                  DisplayInt(header, polyGroupId);
                  break;
               }
            default:
               // any other mapping modes don't make sense
               DisplayString("      \"unsupported group assignment\"");
               break;
            }
         }
         */
      }

      int lPolygonSize = pMesh->GetPolygonSize(i);
      JCTFBXMesh *pTemp = new JCTFBXMesh(pMesh->GetControlPointsCount(), pMesh->GetPolygonCount());
      for (j = 0; j < lPolygonSize; j++)
      {
         int lControlPointIndex = pMesh->GetPolygonVertex(i, j);
         //pTemp->m_pVertices[lControlPointIndex] = (dynamic_cast (double *(lControlPoints[lControlPointIndex].mData));
         //Display3DVector("         Coordinates: ", lControlPoints[lControlPointIndex]);
         int l=0;
         for (l = 0; l < pMesh->GetLayerCount(); l++)
         {
            KFbxLayerElementVertexColor* leVtxc = pMesh->GetLayer(l)->GetVertexColors();
            if (leVtxc)
            {
               //sprintf(header, "         Color vertex (on layer %d): ", l); 

               switch (leVtxc->GetMappingMode())
               {
               case KFbxLayerElement::eBY_CONTROL_POINT:
                  switch (leVtxc->GetReferenceMode())
                  {
                  case KFbxLayerElement::eDIRECT:
                     //DisplayColor(header, leVtxc->GetDirectArray().GetAt(lControlPointIndex));
                     break;
                  case KFbxLayerElement::eINDEX_TO_DIRECT:
                     {
                        int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
                        //DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
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
                        //DisplayColor(header, leVtxc->GetDirectArray().GetAt(vertexId));
                        break;
                     case KFbxLayerElement::eINDEX_TO_DIRECT:
                        {
                           int id = leVtxc->GetIndexArray().GetAt(vertexId);
                           //DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
                        }
                        break;
                     default:
                        break; // other reference modes not shown here!
                     }
                  }
                  break;

               case KFbxLayerElement::eBY_POLYGON: // doesn't make much sense for UVs
               case KFbxLayerElement::eALL_SAME:   // doesn't make much sense for UVs
               case KFbxLayerElement::eNONE:      // doesn't make much sense for UVs
                  break;
               }
            }

            KFbxLayerElementUV* leUV = pMesh->GetLayer(l)->GetUVs();
            if (leUV)
            {
               sprintf(header, "         Texture UV (on layer %d): ", l); 

               switch (leUV->GetMappingMode())
               {
               case KFbxLayerElement::eBY_CONTROL_POINT:
                  switch (leUV->GetReferenceMode())
                  {
                  case KFbxLayerElement::eDIRECT:
                     //Display2DVector(header, leUV->GetDirectArray().GetAt(lControlPointIndex));
                     break;
                  case KFbxLayerElement::eINDEX_TO_DIRECT:
                     {
                        int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
                        //Display2DVector(header, leUV->GetDirectArray().GetAt(id));
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
                           //Display2DVector(header, leUV->GetDirectArray().GetAt(lTextureUVIndex));
                        }
                        break;
                     default:
                        break; // other reference modes not shown here!
                     }
                  }
                  break;

               case KFbxLayerElement::eBY_POLYGON: // doesn't make much sense for UVs
               case KFbxLayerElement::eALL_SAME:   // doesn't make much sense for UVs
               case KFbxLayerElement::eNONE:      // doesn't make much sense for UVs
                  break;
               }
            }


				KFbxLayerElementNormal* leNormal = pMesh->GetLayer(l)->GetNormals();
				if (leNormal)
				{
					sprintf(header, "         Normal (on layer %d): ", l); 

					if(leNormal->GetMappingMode() == KFbxLayerElement::eBY_POLYGON_VERTEX)
					{
						switch (leNormal->GetReferenceMode())
						{
						case KFbxLayerElement::eDIRECT:
							//Display3DVector(header, leNormal->GetDirectArray().GetAt(vertexId));
							break;
						case KFbxLayerElement::eINDEX_TO_DIRECT:
							{
								int id = leNormal->GetIndexArray().GetAt(vertexId);
								//Display3DVector(header, leNormal->GetDirectArray().GetAt(id));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
            }
         } 
      }   
   }
              