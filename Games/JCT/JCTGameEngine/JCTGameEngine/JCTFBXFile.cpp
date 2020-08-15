#pragma once
#ifdef __JCTFBX__
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

string getPropertyKeyword(enum JCTPROP_TYPE eType)
{
   string sReturn;
   switch(eType)
   {
   case JCTP_Hierarchy                : sReturn =  "Hierarchy:";
      break;
   case JCTP_Camera                   : sReturn =  "Camera";
      break;
   case JCTP_Light                    : sReturn =  "Light ";
      break;
   case JCTP_GenericInfo              : sReturn =  "GenericInfo:";
      break;
   case JCTP_Name                     : sReturn =  "Name: ";
      break;
   case JCTP_Property_Count           : sReturn =  "Property Count: ";
      break;
   case JCTP_Property                 : sReturn =  "Property ";
      break;
   case JCTP_Display_Name             : sReturn =  "Display Name: ";
      break;
   case JCTP_Internal_Name            : sReturn =  "Internal Name: ";
      break;
   case JCTP_Type                     : sReturn =  "Type: ";
      break;
   case JCTP_Is_Animatable            : sReturn =  "Is Animatable: ";
      break;
   case JCTP_Is_Temporary             : sReturn =  "Is Temporary: ";
      break;
   case JCTP_Default_Value            : sReturn =  "Default Value: ";
      break;
   case JCTP_Name_Character_group     : sReturn =  "Name: Character group: ";
      break;
   case JCTP_Name_Constraint_Group    : sReturn =  "Name: Constraint Group: ";
      break;
   case JCTP_Skeleton_Name            : sReturn =  "Skeleton Name: ";
      break;
   case JCTP_Limb_Node_Size           : sReturn =  "Limb Node Size: ";
      break;
   case JCTP_Color                    : sReturn =  "Color: ";
      break;
   case JCTP_Mesh_Name                : sReturn =  "Mesh Name: ";
      break;
   case JCTP_Polygons                 : sReturn =  "Polygons ";
      break;
   case JCTP_Polygon                  : sReturn =  "Polygon ";
      break;
   case JCTP_Polygon_Size             : sReturn =  "Polygon Size: ";
      break;
   case JCTP_Coordinates              : sReturn =  "Coordinates: ";
      break;
   case JCTP_Texture_UV               : sReturn =  "Texture UV (on layer 0): ";
      break;
   case JCTP_Normal                   : sReturn =  "Normal (on layer 0): ";
      break;
   case JCTP_Material_Layer           : sReturn = "Material layer 0:";
      break;
   case JCTP_Material_On_Layer           : sReturn = "Material On layer 0:";
      break;
   case JCTP_Textures_On_Material           : sReturn = "Textures connected to Material 0";
      break;
   case JCTP_File_Name           : sReturn = "File Name: ";
      break;



   }
   return sReturn;
};


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

      scanf_s("%s", lPassword);
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
   HANDLE hFile = Create((char*)filename, dwError, 0, JCTFILE_READ);//this->Create((char*)filename, dwError, OPEN_EXISTING);
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
   int lMaterialIndex;
   int lTextureIndex;
   KFbxProperty lProperty;
   int lNbTex;
   KFbxTexture* lTexture = NULL; 
   KFbxSurfaceMaterial *lMaterial = NULL;
   int lNbMat = pNode->GetSrcObjectCount(KFbxSurfaceMaterial::ClassId);
   DWORD dwError = 0;

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

         for (lMaterialIndex = 0; lMaterialIndex < lNbMat; lMaterialIndex++)
         {
           lMaterial = KFbxCast <KFbxSurfaceMaterial>(pNode->GetSrcObject(KFbxSurfaceMaterial::ClassId, lMaterialIndex));
           if(lMaterial)
           {                                                          
               lProperty = lMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
               if(lProperty.IsValid())
               {
                   lNbTex = lProperty.GetSrcObjectCount(KFbxTexture::ClassId);
                   for (lTextureIndex = 0; lTextureIndex < lNbTex; lTextureIndex++)
                   {
                       lTexture = KFbxCast <KFbxTexture> (lProperty.GetSrcObject(KFbxTexture::ClassId, lTextureIndex)); 
                       if(lTexture)
                       {
                           this->m_pTga2 = new JCTTGAFile();
                           this->m_sTGAFile2 = this->m_pTga2->getTGAData();
                           this->m_pTga2->Load(lTexture->GetFileName(), NULL, dwError);   

                           //LoadTexture(lTexture, pTextureArray);
                       }
                   }
               }
           }
         }

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
/*
void LoadTexture(KFbxTexture* pTexture, KArrayTemplate<VSTexture*>& pTextureArray)
{
    // First find if the texture is already loaded
    int i, lCount = pTextureArray.GetCount();

    for (i = 0; i < lCount; i++)
    {
        if (pTextureArray[i]->mRefTexture == pTexture) return;
    }

    // Right now, only Targa textures are loaded by this sample
    KString lFileName = pTexture->GetFileName();

    if (lFileName.Right(3).Upper() == "TGA")
    {
        tga_image lTGAImage;

        if (tga_read(&lTGAImage, lFileName.Buffer()) == TGA_NOERR)
        {
            // Make sure the image is left to right
            if (tga_is_right_to_left(&lTGAImage)) tga_flip_horiz(&lTGAImage);

            // Make sure the image is bottom to top
            if (tga_is_top_to_bottom(&lTGAImage)) tga_flip_vert(&lTGAImage);

            // Make the image BGR 24
            tga_convert_depth(&lTGAImage, 24);

            VSTexture* lTexture = new VSTexture;

            lTexture->mW = lTGAImage.width;
            lTexture->mH = lTGAImage.height;
            lTexture->mRefTexture = pTexture;
            lTexture->mImageData  = new unsigned char[lTGAImage.width*lTGAImage.height*lTGAImage.pixel_depth/8];
            memcpy(lTexture->mImageData, lTGAImage.image_data, lTGAImage.width*lTGAImage.height*lTGAImage.pixel_depth/8);

            tga_free_buffers(&lTGAImage);

            pTextureArray.Add(lTexture);
        }
    }
}
*/

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
   JCTFBXMesh *pTemp = 0;
   JCTFBXPolygon *pPoly = 0;
   Vect *pNormal = 0;
   Vect *pColor = 0;
   Vect *pVect = 0;


   int vertexId = 0;
   pTemp = new JCTFBXMesh(pMesh->GetControlPointsCount(), pMesh->GetPolygonCount());
   pTemp->setType(JCTFBX_MESH);

   for (i = 0; i < lPolygonCount; i++)
   {
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
                  //sprintf(header, "      Assigned to group (on layer %d): ", l); 
                  int polyGroupId = lePolgrp->GetIndexArray().GetAt(i);
                  //DisplayInt(header, polyGroupId);
                  break;
               }
            default:
               // any other mapping modes don't make sense
               //DisplayString("      \"unsupported group assignment\"");
               break;
            }
         }
         
      }

      int lPolygonSize = pMesh->GetPolygonSize(i);

      pPoly = new JCTFBXPolygon(lPolygonSize);
      pPoly->setType(JCTFBX_POLYGON);

      for (j = 0; j < lPolygonSize; j++)
      {
         int lControlPointIndex = pMesh->GetPolygonVertex(i, j);
         
         /*pVect = new Vect(lControlPoints[lControlPointIndex].mData[0],
                                                    lControlPoints[lControlPointIndex].mData[1],
                                                    lControlPoints[lControlPointIndex].mData[2]);*/
         
         pPoly->m_pPoints.push_back(new (JCTHEAP_GENERAL, 
         #ifdef _DEBUG
            __FILE__, __LINE__, 
         #endif 
          MEM_ALIGN_64_BYTES) Vect(lControlPoints[lControlPointIndex].mData[0],
                                              lControlPoints[lControlPointIndex].mData[1],
                                              lControlPoints[lControlPointIndex].mData[2],
                                              lControlPoints[lControlPointIndex].mData[3]));
                                               
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
                     /*pColor = new Vect(leVtxc->GetDirectArray().GetAt(vertexId).mRed,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mGreen,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mBlue,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mAlpha);

                     pPoly->m_pUVs.push_back(pColor);*/
                     //DisplayColor(header, leVtxc->GetDirectArray().GetAt(lControlPointIndex));
                     break;
                  case KFbxLayerElement::eINDEX_TO_DIRECT:
                     {
                        int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
                        /*pColor = new Vect(leVtxc->GetDirectArray().GetAt(id).mRed,
                                          leVtxc->GetDirectArray().GetAt(id).mGreen,
                                          leVtxc->GetDirectArray().GetAt(id).mBlue,
                                          leVtxc->GetDirectArray().GetAt(id).mAlpha);

                        pPoly->m_pUVs.push_back(pColor);*/

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
                        /*pColor = new Vect(leVtxc->GetDirectArray().GetAt(vertexId).mRed,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mGreen,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mBlue,
                                          leVtxc->GetDirectArray().GetAt(vertexId).mAlpha);

                        pPoly->m_pUVs.push_back(pColor);*/
                        //DisplayColor(header, leVtxc->GetDirectArray().GetAt(vertexId));
                        break;
                     case KFbxLayerElement::eINDEX_TO_DIRECT:
                        {
                           int id = leVtxc->GetIndexArray().GetAt(vertexId);
                           /*pColor = new Vect(leVtxc->GetDirectArray().GetAt(id).mRed,
                                             leVtxc->GetDirectArray().GetAt(id).mGreen,
                                             leVtxc->GetDirectArray().GetAt(id).mBlue,
                                             leVtxc->GetDirectArray().GetAt(id).mAlpha);

                           pPoly->m_pUVs.push_back(pColor);*/

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
            /*if(pColor)
            {
               delete pColor;
               pColor = 0;
            }*/

            KFbxLayerElementUV* leUV = pMesh->GetLayer(l)->GetUVs();
            if (leUV)
            {
               sprintf_s(header, "         Texture UV (on layer %d): ", l); 

               switch (leUV->GetMappingMode())
               {
               case KFbxLayerElement::eBY_CONTROL_POINT:
                  switch (leUV->GetReferenceMode())
                  {
                  case KFbxLayerElement::eDIRECT:
                     
                     pColor = new (JCTHEAP_GENERAL, 
                     #ifdef _DEBUG
                        __FILE__, __LINE__, 
                     #endif
                                       MEM_ALIGN_64_BYTES) Vect(leUV->GetDirectArray().GetAt(lControlPointIndex).mData[0],
                                       leUV->GetDirectArray().GetAt(lControlPointIndex).mData[1],
                                       leUV->GetDirectArray().GetAt(lControlPointIndex).mData[2],
                                       leUV->GetDirectArray().GetAt(lControlPointIndex).mData[3]);

                     pPoly->m_pUVs.push_back(pColor);
                     //Display2DVector(header, leUV->GetDirectArray().GetAt(lControlPointIndex));
                     break;
                  case KFbxLayerElement::eINDEX_TO_DIRECT:
                     {
                        int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
                        pColor = new (JCTHEAP_GENERAL, 
                           #ifdef _DEBUG
                              __FILE__, __LINE__, 
                           #endif
                                          MEM_ALIGN_64_BYTES)  Vect(leUV->GetDirectArray().GetAt(id).mData[0],
                                          leUV->GetDirectArray().GetAt(id).mData[1],
                                          leUV->GetDirectArray().GetAt(id).mData[2],
                                          leUV->GetDirectArray().GetAt(id).mData[3]);
                        pPoly->m_pUVs.push_back(pColor);
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
                           pColor = new (JCTHEAP_GENERAL, 
                                                         #ifdef _DEBUG
                                                            __FILE__, __LINE__, 
                                                         #endif 
                                                         MEM_ALIGN_64_BYTES) Vect(leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[0],
                                             leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[1],
                                             leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[2],
                                             leUV->GetDirectArray().GetAt(lTextureUVIndex).mData[3]);
                           pPoly->m_pUVs.push_back(pColor);
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

            if(pColor)
            {
               //delete pColor;
               pColor = 0;
            }

				KFbxLayerElementNormal* leNormal = pMesh->GetLayer(l)->GetNormals();
				if (leNormal)
				{
					sprintf_s(header, "         Normal (on layer %d): ", l); 

					if(leNormal->GetMappingMode() == KFbxLayerElement::eBY_POLYGON_VERTEX)
					{
						switch (leNormal->GetReferenceMode())
						{
						case KFbxLayerElement::eDIRECT:
                     pNormal = new (JCTHEAP_GENERAL, 
                                                         #ifdef _DEBUG
                                                            __FILE__, __LINE__, 
                                                         #endif
                                        MEM_ALIGN_64_BYTES) Vect(leNormal->GetDirectArray().GetAt(vertexId)[0],
                                        leNormal->GetDirectArray().GetAt(vertexId)[1],
                                        leNormal->GetDirectArray().GetAt(vertexId)[2],
                                        leNormal->GetDirectArray().GetAt(vertexId)[3]);

                     pPoly->m_pNormals.push_back(pNormal);
                     
							//Display3DVector(header, leNormal->GetDirectArray().GetAt(vertexId));
							break;
						case KFbxLayerElement::eINDEX_TO_DIRECT:
							{
                        int id = leNormal->GetIndexArray().GetAt(vertexId);
								//Display3DVector(header, leNormal->GetDirectArray().GetAt(id));
                        pNormal = new (JCTHEAP_GENERAL, 
                                                         #ifdef _DEBUG
                                                            __FILE__, __LINE__, 
                                                         #endif
                                           MEM_ALIGN_64_BYTES) Vect(leNormal->GetDirectArray().GetAt(id)[0],
                                           leNormal->GetDirectArray().GetAt(id)[1],
                                           leNormal->GetDirectArray().GetAt(id)[2],
                                           leNormal->GetDirectArray().GetAt(id)[3]);

                        pPoly->m_pNormals.push_back(pNormal);
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
         
                  if(pNormal)
                  {
                     //delete pNormal;
                     pNormal = 0;
                  }
					}
            }
         }
         if(pVect)
         {
            //delete pVect;
            pVect = 0;
         } 
      }
      pTemp->m_pPolygons.push_back(pPoly);
      if(pPoly)
      {
         //delete pPoly;
         pPoly = 0;
      }
      
   }
   
   this->m_pFBXObjs.push_back(pTemp);
   
   if(pTemp)
   {
      //delete pTemp;
      pTemp = 0;
   }


   }
bool JCTFBXFile::LoadBones(const char *filename, DWORD &dwError)
{

   //tgaFile = this->getTGAData();
   //FILE *file;
   bool bSuccess=false;
   DWORD dwBytesRead = 0, dwPtr = 0;//, dwError = 0;
   //    file = fopen(filename, "rb");
   HANDLE hFile = Create((char*)filename, dwError, 0, JCTFILE_READ);//this->Create((char*)filename, dwError, OPEN_EXISTING);
   unsigned short nValue=0;
   JCTFBXSkeleton *pTemp = 0;
   pTemp = new JCTFBXSkeleton();
   pTemp->setType(JCTFBX_SKELETON);

   if (dwError)
   {
     dwError = GetLastError();
     if (dwError)
         return false;
   }
   size_t iSize = this->GetSize(hFile, dwError);
   if(JCTFILE_SUCCESS != dwError)
   {
      iSize = 80;
   }
   unsigned char *pBones = new unsigned char[iSize];
   
   this->Read((unsigned char*)pBones, 80, dwError);
   //bSuccess = ReadFile(hFile, &tgaFile->header, sizeof(tgaFile->header), &dwBytesRead, NULL);
   dwError = GetLastError();
   
   printf("Data from FBX >>>%s\n", pBones);

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
};

bool JCTFBXFile::LoadFBXTxt(const char *filename, DWORD &dwError)
{

   this->Create((char*)filename,dwError,NULL, JCTFILE_READ);
   size_t iSize = 0;
   iSize = this->GetSize(this->getHandle(), dwError);
   dwError = GetLastError();
   int iVertCount = 0;
   if (dwError)
   {
      return false;
   }
   unsigned char *pFBX = new unsigned char[iSize];
   this->Read((unsigned char*)pFBX, iSize, dwError);
   //bSuccess = ReadFile(hFile, &tgaFile->header, sizeof(tgaFile->header), &dwBytesRead, NULL);
   dwError = GetLastError();
   if (dwError)
   {
      return false;
   }
   size_t iIncrement = 0, result =0, iLevel = 0, iPriorLevel = 0;
   unsigned char* pTemp, *pTemp2;
   struct JCTTEMP_PROP pTempProp;

   unsigned char* pBegining = pFBX;
   unsigned char *pPriorName = new unsigned char[128];
   unsigned char *pSkeletonName = new unsigned char[128];
   unsigned char *pName = new unsigned char[128];
   unsigned char *pNameStart = pName;
   unsigned char *pPriorNameStart = pPriorName;
   Vect *vTemp;
   bool  bUV = false;
   bool  bNormal = false;

   bool bTemp = false;
   int iTempInt = 0;
   iSkeletonNameSize = 0;

   
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Hierarchy).data());
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt = getPropertyKeyword(JCTP_Hierarchy).length();
   iIncrement += result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp = (unsigned char *)strstr((char*) pFBX, ":" );
   result = (int)((char*)pTemp - (char*)pFBX);
   iIncrement+=result;
//   strncpy((char*)pSkeletonName,(char*)pFBX,result);
   memcpy((char*)pSkeletonName, (const char *)pFBX, result);
   pSkeletonName[result] = '\0';
   iSkeletonNameSize = result;
   iIncrement+= result+1;
   pFBX+=result+1;
   //Load the Skeleton
   size_t uiReturn=0;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);
   
//      pFBX += result + 1;
   //strncpy((char*)pPriorName, (const char *)pFBX, result);
   memcpy((char*)pPriorName, (const char *)pFBX, result);
   pPriorName[result] = '\0';
   JCTFBXSkeleton *pSkeleton = new JCTFBXSkeleton((char*)pPriorName);
   JCTFBXMesh *pMesh;
   JCTFBXPolygon *pPoly;
   pSkeleton->setSkeletonName((const char*)pSkeletonName);
   //pSkeleton->setNodeName((char*)pTemp);
   iIncrement+= result+1;
   pFBX+=result+1;
   JCTFBXBone *pBone, *pBoneTemp;
   size_t iCount=0;
   JCTFBXProperty *pProp;
   float fX=0.0, fY=0.0, fZ=0.0;
   bool bBonesDone = false;

   //iLevel = 1;
   if(pSkeleton)
   {
      while(result > 0)
      {
         pTemp = (unsigned char *)strchr((char*) pFBX, ':');
         result = (int)((char*)pTemp - (char*)pFBX)+1;
         result -= iSkeletonNameSize;
         iLevel = result;
         iIncrement+=iSkeletonNameSize + result;
         pFBX +=iSkeletonNameSize + result;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);

         strncpy((char*)pName, (const char *)pFBX, result);
         pName[result] = '\0';

         pBone = new JCTFBXBone((char*)pName);
         if(iPriorLevel > iLevel)
         {
            pBoneTemp = (JCTFBXBone*)pSkeleton->NodeExists((char*)pPriorName,bTemp,uiReturn);
            while(pBoneTemp && pBoneTemp->getLevel() >= (int)iLevel)
            {
               pBoneTemp = (JCTFBXBone*)pBoneTemp->getParent();
            }
            memcpy((char*)pPriorName, (const char *)pBoneTemp->getNodeName().data(), result);
            pPriorName[result] = '\0';
            pSkeleton->insertChild(pBone,(char*)pPriorName,"",uiReturn);
            iPriorLevel = pBoneTemp->getLevel();
            bTemp = false;
         }
         else
         {
            pSkeleton->insertChild(pBone,(char*)pPriorName,"",uiReturn);
         }
         pBone = 0;
         strncpy((char*)pPriorName, (const char *)pName, result);
         pPriorName[result] = '\0';
         pFBX += result;
         iIncrement+= result;
         iPriorLevel = iLevel;
         //if(pFBX[])
      }

   //Bone Properties
      bTemp = false;
      iLevel = 0;
   //   PCSInfo pInfo = pSkeleton->getInfo();
      iLevel = 1;
      while(!bBonesDone)
      {
         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Name).data() );
         result = (int)((char*)pTemp - (char*)pFBX);
         iTempInt = getPropertyKeyword(JCTP_Name).length();
         iIncrement+=result + iTempInt + iSkeletonNameSize;
         pFBX+=result + iTempInt + iSkeletonNameSize;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);

         strncpy((char*)pName, (const char *)pFBX, result);
         pName[result] = '\0';
         pFBX+=result;

         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Property_Count).data() );
         result = (int)((char*)pTemp - (char*)pFBX);
         iTempInt = getPropertyKeyword(JCTP_Property_Count).length();
         iIncrement+=result + iTempInt;
         pFBX+=result + iTempInt;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);

         iCount = atoi((const char *)pFBX);
         pFBX+=result;

   /*
               Display Name: QuaternionInterpolate
               Internal Name: QuaternionInterpolate
               Type: Bool
               Is Animatable: false
               Is Temporary: false
               Default Value: false
   */
         if(pSkeleton->getNodeCount())
         {
            pBone = (JCTFBXBone*)pSkeleton->NodeExists((char*)pName, bTemp, result);
            if(pBone)
            {
               pBone->m_pProperties = new JCTFBXBoneProps();
               pBone->m_pProperties->reserve(iCount);

               for(size_t x=0; x<iCount; x++)
               {
                  fX = fY = fZ = 0.0;

                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Property).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt=getPropertyKeyword(JCTP_Property).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);
                  pFBX+=result;

                  //Display Name
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Display_Name).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt=getPropertyKeyword(JCTP_Display_Name).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  memcpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pTempProp.m_sDisplayName = (char*)pPriorName;
                  pFBX+=result;


                  //Internal Name
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Internal_Name).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Internal_Name).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pTempProp.m_sInternalName = (char*)pPriorName;
                  pFBX+=result;

                  //Type
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Type).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Type).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pTempProp.m_sType = (char*)pPriorName;
                  pFBX+=result;

                  //Is Animatable
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Is_Animatable).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Is_Animatable).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pTempProp.m_bAnimatable = (bool)!strcmp((char*)pPriorName, "true");
                  pFBX+=result;

                  //Is Temporary
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Is_Temporary).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Is_Temporary).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pTempProp.m_Temporary = (bool)!strcmp((char*)pPriorName, "true");
                  pFBX+=result;

                  //Default Value
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Default_Value).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Default_Value).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp2 = (unsigned char *)strchr((char*) pTemp, '\n');
                  result = (int)((char*)pTemp2 - (char*)pTemp);

                  strncpy((char*)pPriorName, (const char *)pTemp, result);
                  pPriorName[result] = '\0';


                  //pTempProp.m_sInternalName = (char*)pPriorName;
                  //pFBX+=result;
                  
                  JCTPTypeVector *pTypeTemp;
                  pProp = new JCTFBXProperty(pTempProp.m_sType);

                  if(pProp)
                  {
                     //pTempProp.m_ePType = pProp->getPropertyType();
                     pProp->setInternalName(pTempProp.m_sInternalName);
                     pProp->setIsAnimatable(pTempProp.m_bAnimatable);
                     pProp->setDisplayName(pTempProp.m_sDisplayName);
                     iTempInt = pProp->getPropertyType();
                     switch(iTempInt)
                     {
                        case JCT_PTYPE_COLOR          :
                        case JCT_PTYPE_VECTOR         :
                        case JCT_PTYPE_LCL_TRANSLATION:
                        case JCT_PTYPE_LCL_ROTATION   :
                        case JCT_PTYPE_LCL_SCALING    :
                        case JCT_PTYPE_VECTOR3D       :
                        {
                           //memset(pName, '\0', 128);
                           pTypeTemp = dynamic_cast<JCTPTypeVector *>(pProp->m_pPropertyValue);
                           pTemp = (unsigned char *)strchr((char*) pPriorName, ',');
                           result = (int)((char*)pTemp - (char*)pPriorName);
                           strncpy((char*)pName, (const char *)pPriorName, result);
                           pName[result] = '\0';
                           //pTemp+=result;
                           fX = (float)atof((char*)pName);
                           pTemp++;
                           pTemp2 = (unsigned char *)strchr((char*) pTemp, ',');
                           result = (int)((char*)pTemp2 - (char*)pTemp);
                           strncpy((char*)pName, (const char *)pTemp, result);
                           pName[result] = '\0';
                           fY = (float)atof((char*)pName);
                           pTemp2++;
                           //pTemp+=result;
                           //pTemp++;
                           //strncpy((char*)pName, (const char *)pTemp2, result);
                           //pName[result] = '\0';
                           fZ = (float)atof((char*)pTemp2);
                           pTypeTemp->setValue(Vect(fX, fY, fZ));//(Vect)pPriorName);
                           break;
                        };
                        case JCT_PTYPE_VISIBLITY      :
                        case JCT_PTYPE_NUMBER         :
                        {
                           JCTPTypeFloat *pTypeTemp = dynamic_cast<JCTPTypeFloat *>(pProp->m_pPropertyValue);
                           pTypeTemp->setValue((float)atof((char*)pPriorName));
                           break;                  
                        };
                        case JCT_PTYPE_ACTION         :
                        case JCT_PTYPE_BOOL           :
                        {
                           JCTPTypeBool *pTypeTemp = dynamic_cast<JCTPTypeBool *>(pProp->m_pPropertyValue);
                           pTypeTemp->setValue((bool)!strcmp((char*)pPriorName, "true"));//(Vect)pPriorName);
                           break;                  
                        };
                        case JCT_PTYPE_OBJECT         :
                        case JCT_PTYPE_ENUM           :
                        {
                           JCTPTypeString *pTypeTemp = dynamic_cast<JCTPTypeString *>(pProp->m_pPropertyValue);
                           pTemp = (unsigned char *)strchr((char*) pPriorName, '\n');
                           result = (int)((char*)pTemp - (char*)pPriorName);
                           pTypeTemp->setValue((char*)pPriorName);
                           break;
                        };
                        case JCT_PTYPE_INTEGER        :
                        {
                           JCTPTypeInteger *pTypeTemp = dynamic_cast<JCTPTypeInteger *>(pProp->m_pPropertyValue);
                           pTemp = (unsigned char *)strchr((char*) pPriorName, '\n');
                           result = (int)((char*)pTemp - (char*)pPriorName);
                           pTypeTemp->setValue((int)atoi((char*)pPriorName));
                           break;
                        };
                     };
                     bTemp = false;
                  pBone->m_pProperties->push_back(pProp);
                  pProp = 0;
                  }
                  memset(pPriorName, ' ', 128);
                  memset(pName, ' ', 128);

               }
            }
            else
            {
               if(result != 0)
               {
                  bBonesDone = true;
                  break;
               }
            }
         }
         bBonesDone = true;
      }
   }
   //Mesh Name
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Mesh_Name).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt=getPropertyKeyword(JCTP_Mesh_Name).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp += iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);

   memcpy((char*)pName, (const char *)pFBX, result);
   pName[result] = '\0';

   pFBX+=result;
   
   //Polygons
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Polygons).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt = getPropertyKeyword(JCTP_Polygons).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);

   iCount = atoi((const char *)pFBX);
   pFBX+=result;

   //Polygon Size
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Polygon_Size).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt = getPropertyKeyword(JCTP_Polygon_Size).length();
   iIncrement+=result + iTempInt;
   pTemp+=iTempInt;

   pTemp2 = (unsigned char *)strchr((char*) pTemp, '\n');
   result = (int)((char*)pTemp2 - (char*)pTemp);

   iVertCount = atoi((const char *)pTemp);


   pMesh = new JCTFBXMesh(iVertCount*iCount,iCount);
   if(pMesh)
   {
      pMesh->setName((char*)pName);
      bUV = false;
      bNormal = false;

      for(size_t x=0; x<iCount; x++)
      {
         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Polygon).data() );
         result = (int)((char*)pTemp - (char*)pFBX);
         iTempInt = getPropertyKeyword(JCTP_Polygon).length();
         iIncrement+=result + iTempInt;
         pFBX+=result + iTempInt;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);

         strncpy((char*)pName, (const char *)pFBX, result);
         pName[result] = '\0';
         pFBX+=result;

         //Polygon Size
         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Polygon_Size).data() );
         result = (int)((char*)pTemp - (char*)pFBX);
         iTempInt = getPropertyKeyword(JCTP_Polygon_Size).length();
         iIncrement+=result + iTempInt;
         pFBX+=result + iTempInt;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);

         iVertCount = atoi((const char *)pFBX);
         pFBX+=result;
   
         //Polygon Size
         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Texture_UV).data() );
         if(pTemp)
         {
            bUV = true;
         }
         pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Normal).data() );
         if(pTemp)
         {
            bNormal = true;
         }

         pPoly = new JCTFBXPolygon(iVertCount);
         if(pPoly)
         {
            for(size_t y=0; y<iVertCount; y++)
            {
               //Coordinates
               pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Coordinates).data() );
               result = (int)((char*)pTemp - (char*)pFBX);
               iTempInt = getPropertyKeyword(JCTP_Coordinates).length();
               iIncrement+=result + iTempInt;
               pFBX+=result + iTempInt;
               pTemp += iTempInt;

               pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
               result = (int)((char*)pTemp - (char*)pFBX);

               strncpy((char*)pPriorName, (const char *)pFBX, result);
               pPriorName[result] = '\0';
               pFBX+=result;
               
               pTemp = (unsigned char *)strchr((char*) pPriorName, ',');
               result = (int)((char*)pTemp - (char*)pPriorName);
               strncpy((char*)pName, (const char *)pPriorName, result);
               pName[result] = '\0';
               //pTemp+=result;
               fX = (float)atof((char*)pName);
               pTemp++;
               pTemp2 = (unsigned char *)strchr((char*) pTemp, ',');
               result = (int)((char*)pTemp2 - (char*)pTemp);
               strncpy((char*)pName, (const char *)pTemp, result);
               pName[result] = '\0';
               fY = (float)atof((char*)pName);
               pTemp2++;
               //pTemp+=result;
               //pTemp++;
               //strncpy((char*)pName, (const char *)pTemp2, result);
               //pName[result] = '\0';
               fZ = (float)atof((char*)pTemp2);
               vTemp = new (JCTHEAP_GENERAL, 
                           #ifdef _DEBUG
                              __FILE__, __LINE__, 
                           #endif
                           MEM_ALIGN_64_BYTES) Vect(fX, fY, fZ);
               pPoly->m_pPoints.push_back(vTemp);
               vTemp = 0;

               if(bUV)
               {
                  //Coordinates
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Texture_UV).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Texture_UV).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pFBX+=result;
                  
                  pTemp = (unsigned char *)strchr((char*) pPriorName, ',');
                  result = (int)((char*)pTemp - (char*)pPriorName);
                  strncpy((char*)pName, (const char *)pPriorName, result);
                  pName[result] = '\0';
                  //pTemp+=result;
                  fX = (float)atof((char*)pName);
                  pTemp++;
                  //pTemp2 = (unsigned char *)strchr((char*) pTemp, '\n');
                  //result = (int)((char*)pTemp2 - (char*)pTemp);
                  strncpy((char*)pName, (const char *)pTemp, result);
                  //pName[result] = '\0';
                  fY = (float)atof((char*)pName);
                  //pTemp2++;
                  //pTemp+=result;
                  //pTemp++;
                  //strncpy((char*)pName, (const char *)pTemp2, result);
                  //pName[result] = '\0';
                  //fZ = (float)atof((char*)pTemp2);
                  vTemp = new (JCTHEAP_GENERAL, 
                                 #ifdef _DEBUG
                                    __FILE__, __LINE__, 
                                 #endif
                                 MEM_ALIGN_64_BYTES) Vect(fX, fY, 0.0);

                  pPoly->m_pUVs.push_back(vTemp);
                  vTemp = 0;
               }
               if(bNormal)
               {
                  //Coordinates
                  pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Normal).data() );
                  result = (int)((char*)pTemp - (char*)pFBX);
                  iTempInt = getPropertyKeyword(JCTP_Normal).length();
                  iIncrement+=result + iTempInt;
                  pFBX+=result + iTempInt;
                  pTemp += iTempInt;

                  pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
                  result = (int)((char*)pTemp - (char*)pFBX);

                  strncpy((char*)pPriorName, (const char *)pFBX, result);
                  pPriorName[result] = '\0';
                  pFBX+=result;
                  
                  pTemp = (unsigned char *)strchr((char*) pPriorName, ',');
                  result = (int)((char*)pTemp - (char*)pPriorName);
                  strncpy((char*)pName, (const char *)pPriorName, result);
                  pName[result] = '\0';
                  //pTemp+=result;
                  fX = (float)atof((char*)pName);
                  pTemp++;
                  pTemp2 = (unsigned char *)strchr((char*) pTemp, ',');
                  result = (int)((char*)pTemp2 - (char*)pTemp);
                  strncpy((char*)pName, (const char *)pTemp, result);
                  pName[result] = '\0';
                  fY = (float)atof((char*)pName);
                  pTemp2++;
                  //pTemp+=result;
                  //pTemp++;
                  //strncpy((char*)pName, (const char *)pTemp2, result);
                  //pName[result] = '\0';
                  fZ = (float)atof((char*)pTemp2);
                  vTemp = new (JCTHEAP_GENERAL, 
                                                #ifdef _DEBUG
                                                   __FILE__, __LINE__, 
                                                #endif
                                                   MEM_ALIGN_64_BYTES) Vect(fX, fY, fZ);
                  pPoly->m_pNormals.push_back(vTemp);
                  vTemp = 0;
               }
            }
         }
         pMesh->m_pPolygons.push_back(pPoly);
      }
      this->m_pFBXObjs.push_back(pMesh);
   }
//   bool bTemp = false;
   //LoadBonesRecursive(pSkeleton, (char*)pPriorName, (char*) pFBX, iLevel, iIncrement, bTemp);
/*//Material layer
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Material_Layer).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt=getPropertyKeyword(JCTP_Material_Layer).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp += iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);

   memcpy((char*)pName, (const char *)pFBX, result);
   pName[result] = '\0';

   pFBX+=result;
   
//Material layer    

   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Material_On_Layer).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt=getPropertyKeyword(JCTP_Material_On_Layer).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp += iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);

   //memcpy((char*)pName, (const char *)pFBX, result);
   //pName[result] = '\0';

   pFBX+=result;*/

   //Textures On Material
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_Textures_On_Material).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt=getPropertyKeyword(JCTP_Textures_On_Material).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp += iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);

//   memcpy((char*)pName, (const char *)pFBX, result);
//   pName[result] = '\0';

   pFBX+=result;

//File Name
   pTemp = (unsigned char *)strstr((char*) pFBX, getPropertyKeyword(JCTP_File_Name).data() );
   result = (int)((char*)pTemp - (char*)pFBX);
   iTempInt=getPropertyKeyword(JCTP_File_Name).length();
   iIncrement+=result + iTempInt;
   pFBX+=result + iTempInt;
   pTemp += iTempInt;

   pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
   result = (int)((char*)pTemp - (char*)pFBX);
   this->m_cTGAFile = new char[result];
   memcpy((char*)this->m_cTGAFile, (const char *)pFBX+1, result-1);
   this->m_cTGAFile[result-2] = '\0';
   pName[result] = '\0';

   pFBX+=result;


//File Name: 

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
}

/*
send the prior name and level, the char* buffer and incrementer
get the level from the spacing
compare it to the prior level
if it is greater insert as a child
if it is equal insert as a sibling
if it is less than then fall out until it is



*/
void JCTFBXFile::LoadBonesRecursive(JCTFBXSkeleton *pSkeleton, char *pPriorName, char* pFBX, size_t &iLevel, size_t &iIncrement, bool &bBack)
{
   JCTFBXBone *pBone2;
   size_t result=1;
   size_t iLevel2 = 0, iLevel3 = 0;
   unsigned char *pTemp;
   unsigned char *pName = new unsigned char[128];
   unsigned char *pLocalName = new unsigned char[128];
   JCTFBXBone *pLocal;
   unsigned int uiReturn=0;
   bool bReturn = false;
   pLocal = (JCTFBXBone*)pSkeleton->NodeExists(pPriorName, bReturn, uiReturn);
   
   iLevel3 = pLocal->getLevel();
   
   memcpy(pLocalName, pPriorName, 128); 
   
   while(iLevel3 <= iLevel)
   {
      if(!bBack)
      {
         pTemp = (unsigned char *)strchr((char*) pFBX, ':');
         result = (int)((char*)pTemp - (char*)pFBX)+1;
         result -= iSkeletonNameSize;
         iLevel3 = iLevel2 = result;
         iIncrement+=iSkeletonNameSize + result;
         pFBX +=iSkeletonNameSize + result;

         pTemp = (unsigned char *)strchr((char*) pFBX, '\n');
         result = (int)((char*)pTemp - (char*)pFBX);
      }
      else
      {
         iLevel2 = pLocal->getLevel();
         pLocal = (JCTFBXBone*)pSkeleton->NodeExists(pPriorName, bReturn, uiReturn);

      }
      if(result)
      {
         if(!bBack)
         {
            strncpy((char*)pName, (const char *)pFBX, result);
            pName[result] = '\0';
            pBone2 = new JCTFBXBone((char*)pName);
            pFBX += result;
            iIncrement+= result;
         }
         if(iLevel2 > iLevel)
         {
            pSkeleton->insertChild(pBone2, (char*)pPriorName, "", uiReturn);
            LoadBonesRecursive(pSkeleton, (char*)pName, (char*)pFBX, iLevel2, iIncrement, bBack);
         }
         else if(iLevel2 == iLevel)
         {
            pSkeleton->insertChild(pBone2,"", (char*)pPriorName, uiReturn);
            LoadBonesRecursive(pSkeleton, (char*)pName, (char*)pFBX, iLevel2, iIncrement, bBack);
         }
         else
         {
            bBack = true;
         }
         /*else
         {
            return false;
         }*/

         //pBone = 0;
         //strncpy((char*)pPriorName, (const char *)pName, result);
         //pPriorName[result] = '\0';
         //if(pFBX[])
         
      }
   }
   
}
/*
JCTP_Hierarchy             
JCTP_Camera                
JCTP_Light                 
JCTP_GenericInfo           
JCTP_Name                  
JCTP_Display Name          
JCTP_Internal Name         
JCTP_Type                  
JCTP_Is Animatable         
JCTP_Is Temporary          
JCTP_Default Value         
JCTP_Property Count        
JCTP_Property              
JCTP_Display Name          
JCTP_Internal Name         
JCTP_Type                  
JCTP_Is Animatable         
JCTP_Is Temporary          
JCTP_Default Value         
JCTP_Name: Character group 
JCTP_Name: Constraint Group
JCTP_Skeleton Name         
JCTP_Type                  
JCTP_Limb Node Size        
JCTP_Color                 
JCTP_Mesh Name             
JCTP_Polygons              
JCTP_Polygon               
*/
#endif