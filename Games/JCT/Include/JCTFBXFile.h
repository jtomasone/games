#pragma once
#ifdef __JCTFBX__
#include "jctfile.h"
#include "jctTGAFile.h"
#include "JCTFBXObject.h"
#include "JCTFBXMesh.h"
#include "JCTFBXSkeleton.h"
#include "JCTFBXBone.h"


#include <fbxsdk.h>
#include <fbxfilesdk/fbxfilesdk_nsuse.h>

#include <fbxfilesdk/kfbxio/kfbximporter.h>
#include <fbxfilesdk/kfbxplugins/kfbxsdkmanager.h>
#include <fbxfilesdk/kfbxplugins/kfbxscene.h>
#include <fbxfilesdk/fbxfilesdk_nsuse.h>

struct JCTTEMP_PROP
{
   string m_sDisplayName;
   string m_sInternalName;
   string m_sType;
   bool m_bAnimatable;
   bool m_Temporary;
};

enum JCTPROP_TYPE
{
      JCTP_Hierarchy           =0, 
      JCTP_Camera                , 
      JCTP_Light                 , 
      JCTP_GenericInfo           , 
      JCTP_Name                  , 
      JCTP_Property_Count        , 
      JCTP_Property              , 
      JCTP_Display_Name          , 
      JCTP_Internal_Name         , 
      JCTP_Type                  , 
      JCTP_Is_Animatable         , 
      JCTP_Is_Temporary          , 
      JCTP_Default_Value         , 
      JCTP_Name_Character_group  , 
      JCTP_Name_Constraint_Group , 
      JCTP_Skeleton_Name         , 
      JCTP_Limb_Node_Size        , 
      JCTP_Color                 , 
      JCTP_Mesh_Name             , 
      JCTP_Polygons              , 
      JCTP_Polygon               ,
      JCTP_Polygon_Size          ,
      JCTP_Coordinates           ,
      JCTP_Texture_UV            ,
      JCTP_Normal                ,
      JCTP_Material_Layer        ,
      JCTP_Material_On_Layer     ,
      JCTP_Textures_On_Material  ,
      JCTP_File_Name           
}; 


void InitializeSdkObjects(KFbxSdkManager*& pSdkManager, KFbxScene*& pScene);
void DestroySdkObjects(KFbxSdkManager* pSdkManager);
void CreateAndFillIOSettings(KFbxSdkManager* pSdkManager);


bool SaveScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename, int pFileFormat=-1, bool pEmbedMedia=false);
bool LoadScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename);

typedef std::vector<JCTFBXObject*>JCTFBXObjs;

class JCTFBXFile :
   public JCTFile
{
   
public:
   JCTFBXObjs m_pFBXObjs;
   unsigned char *m_pSceneData;
   char *m_cTGAFile;
   JCTTGAFile *m_pTga2;
   STGA *m_sTGAFile2;
   size_t iSkeletonNameSize;

   JCTFBXFile(void);
   ~JCTFBXFile(void);
   bool Load(const char *filename, DWORD &dwError);
   void LoadIntoMemory(const char *filename, DWORD &dwError);
   void LoadContent(KFbxNode* pNode);
   void LoadMesh(KFbxMesh* pMesh);
   bool LoadBones(const char *filename, DWORD &dwError);
   bool LoadFBXTxt(const char *filename, DWORD &dwError);
   void LoadBonesRecursive(JCTFBXSkeleton *pSkeleton, char *pPriorName, char* pFBX, size_t &iLevel, size_t &iIncrement, bool &bBack);

};

#endif