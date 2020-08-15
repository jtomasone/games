#pragma once

#include <fbxsdk.h>

#include <stdio.h>


#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include <fbxfilesdk/kfbxplugins/kfbxobject.h>
#include "JCTFile.h"


class FBXFILESDK_NAMESPACE::KFbxNode;
class FBXFILESDK_NAMESPACE::KFbxCamera;


class JCTFBXConvert
{
   JCTFile* m_pOutFile;
public:
   JCTFBXConvert(char* pFileName = "");
   DWORD m_dwError;
   void DisplaySkeleton(KFbxNode* pNode);
   void DisplayMesh(KFbxNode* pNode);
   void DisplayPose(KFbxScene* pScene);
   void DisplayPivotsAndLimits(KFbxNode* pNode);
   void DisplayMaterial(KFbxGeometry* pGeometry);
   void DisplayLink(KFbxGeometry* pGeometry);
   void DisplayMetaDataConnections(KFbxObject* pObject);
   void DisplayString(const char* pHeader, const char* pValue = "", const char* pSuffix = "");
   void DisplayBool(const char* pHeader, bool pValue, const char* pSuffix = "");
   void DisplayInt(const char* pHeader, int pValue, const char* pSuffix = "");
   void DisplayDouble(const char* pHeader, double pValue, const char* pSuffix = "");
   void Display2DVector(const char* pHeader, KFbxVector2 pValue, const char* pSuffix = "");
   void Display3DVector(const char* pHeader, KFbxVector4 pValue, const char* pSuffix = "");
   void Display4DVector(const char* pHeader, KFbxVector4 pValue, const char* pSuffix = "");
   void DisplayColor(const char* pHeader, KFbxPropertyDouble3 pValue, const char* pSuffix = "");
   void DisplayColor(const char* pHeader, KFbxColor pValue, const char* pSuffix = "");
   void DisplayProperties(KFbxObject* pObject);
   void DisplayGenericInfo(KFbxNode* pNode, int pDepth);
   void DisplayGenericInfo(KFbxScene* pScene);
   void DisplayGlobalLightSettings(KFbxGlobalSettings* pGlobalSettings);
   void DisplayGlobalCameraSettings(KFbxGlobalSettings* pGlobalSettings);
   void DisplayGlobalTimeSettings(KFbxGlobalSettings* pGlobalSettings);
   void DisplayHierarchy(KFbxNode* pNode, int pDepth);
   void DisplayHierarchy(KFbxScene* pScene);
   void DisplayTextureInfo(KFbxTexture* pTexture, int pBlendMode);
   void FindAndDisplayTextureInfoByProperty(KFbxProperty pProperty, bool& pDisplayHeader, int pMaterialIndex);
   void DisplayTexture(KFbxGeometry* pGeometry);
   void JCTFBXConvert::DisplayLight(KFbxNode* pNode);
   void JCTFBXConvert::DisplayDefaultAnimationValues(KFbxLight* pLight);

   void DisplayShape(KFbxGeometry* pGeometry);
   void DisplayCamera(FBXFILESDK_NAMESPACE::KFbxCamera* pCamera, char* pName, FBXFILESDK_NAMESPACE::KFbxNode* pTargetNode = NULL, FBXFILESDK_NAMESPACE::KFbxNode* pTargetUpNode = NULL);
   void DisplayCamera(FBXFILESDK_NAMESPACE::KFbxNode* pNode);
   void DisplayControlsPoints(KFbxMesh* pMesh);
   void DisplayPolygons(KFbxMesh* pMesh);
   void DisplayMaterialMapping(KFbxMesh* pMesh);
   void DisplayTextureMapping(KFbxMesh* pMesh);
   void DisplayTextureNames( KFbxProperty &pProperty, KString& pConnectionString );
   void DisplayMaterialConnections(KFbxMesh* pMesh);
   void DisplayMaterialTextureConnections( KFbxSurfaceMaterial* pMaterial, char * header, int pMatId, int l );
   void DisplayAnimation(KFbxAnimStack* pAnimStack, KFbxNode* pNode, bool isSwitcher = false);
   void DisplayAnimation(KFbxAnimLayer* pAnimLayer, KFbxNode* pNode, bool isSwitcher = false);
   void DisplayAnimation(KFbxScene* pScene);
   void DisplayChannels(KFbxNode* pNode, KFbxAnimLayer* pAnimLayer, void (*DisplayCurve) (KFCurve *pCurve), void (*DisplayListCurve) (KFCurve *pCurve, KFbxProperty* pProperty), bool isSwitcher);
   void DisplayCurveKeys(KFCurve *pCurve = NULL);
   void DisplayCurveDefault(KFCurve *pCurve = NULL);
   void DisplayListCurveKeys(KFCurve *pCurve, KFbxProperty* pProperty);
   void DisplayListCurveDefault(KFCurve *pCurve, KFbxProperty* pProperty);
   
   void DisplayContent(KFbxScene* pScene);
   void DisplayContent(KFbxNode* pNode);
   void DisplayTarget(KFbxNode* pNode);
   void DisplayTransformPropagation(KFbxNode* pNode);
   void DisplayGeometricTransform(KFbxNode* pNode);
   void DisplayMetaData(KFbxScene* pScene);

   //void DisplayCamera(KFbxCamera* pCamera, char* pName, KFbxNode* pTargetNode = NULL, KFbxNode* pTargetUpNode = NULL);
   void DisplayDefaultAnimationValues(KFbxCamera* pCamera);
   void DisplayRenderOptions(KFbxCamera* pCamera);
   void DisplayCameraViewOptions(KFbxCamera* pCamera);
   void DisplayBackgroundProperties(KFbxCamera* pCamera);
   void DisplayApertureAndFilmControls(KFbxCamera* pCamera);
   void DisplayViewingAreaControls(KFbxCamera* pCamera);
   void DisplayCameraPositionAndOrientation(KFbxCamera* pCamera, KFbxNode* pTargetNode, KFbxNode* pUpTargetNode);
   
};