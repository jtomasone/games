// JCTFBXConverter.cpp : Defines the entry point for the console application.
//

/*
#include "DisplayCommon.h"
#include "DisplayHierarchy.h"
#include "DisplayAnimation.h"
//#include "DisplayMarker.h"
#include "DisplaySkeleton.h"
#include "DisplayMesh.h"
//#include "DisplayNurb.h"
//#include "DisplayPatch.h"
//#include "DisplayLodGroup.h"
#include "DisplayCamera.h"
#include "DisplayLight.h"
#include "DisplayGlobalSettings.h"
#include "DisplayPose.h"
#include "DisplayPivotsAndLimits.h"
//#include "DisplayUserProperties.h"
#include "DisplayGenericInfo.h"
*/

#include "JCTFBXConvert.h"
#include "Common.h"

#include <fbxfilesdk/kfbxio/kfbxio.h>
#include <fbxfilesdk/kfbxio/kfbxexporter.h>
#include <fbxfilesdk/kfbxio/kfbximporter.h>

#include <fbxfilesdk/kfbxplugins/kfbxsdkmanager.h>
#include <fbxfilesdk/kfbxplugins/kfbxscene.h>
#include <fbxfilesdk/kfbxplugins/kfbxutilities.h>

#include <fbxfilesdk/components/kbaselib/klib/kerror.h>
#include <fbxfilesdk/components/kbaselib/klib/kstring.h>

#include <fbxfilesdk/fbxfilesdk_nsuse.h>
// Local function prototypes.
/*
void JCTFBXConvert::DisplayContent(KFbxScene* pScene, JCTFile *pOut);
void JCTFBXConvert::DisplayContent(KFbxNode* pNode, JCTFile *pOut);
void JCTFBXConvert::DisplayTarget(KFbxNode* pNode, JCTFile *pOut);
void JCTFBXConvert::DisplayTransformPropagation(KFbxNode* pNode, JCTFile *pOut);
void JCTFBXConvert::DisplayGeometricTransform(KFbxNode* pNode, JCTFile *pOut);
void JCTFBXConvert::DisplayMetaData(KFbxScene* pScene, JCTFile *pOut);
*/
int main(int argc, char** argv)
{
   KFbxSdkManager* lSdkManager = NULL;
    KFbxScene* lScene = NULL;
    bool lResult;
   
   JCTFBXConvert *pConvertObj = new JCTFBXConvert(argv[2]);
   
    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);
    // Load the scene.

    // The example can take a FBX file as an argument.
    if(argc > 1)
    {
        printf("\n\nFile: %s\n\n", argv[1]);
        lResult = LoadScene(lSdkManager, lScene, argv[1]);
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
        return 0;
    }
    else 
    {
        // Display the scene.
        pConvertObj->DisplayMetaData(lScene);
/*
        //printf("\n\n---------------------\nGlobal Light Settings\n---------------------\n\n");

        pConvertObj->DisplayGlobalLightSettings(&lScene->GetGlobalSettings());

        //printf("\n\n----------------------\nGlobal Camera Settings\n----------------------\n\n");

        pConvertObj->DisplayGlobalCameraSettings(&lScene->GetGlobalSettings());

        //printf("\n\n--------------------\nGlobal Time Settings\n--------------------\n\n");

        pConvertObj->DisplayGlobalTimeSettings(&lScene->GetGlobalSettings());

       //printf("\n\n---------\nHierarchy\n---------\n\n");
*/
        pConvertObj->DisplayHierarchy(lScene);

        //printf("\n\n---------\nGeneric Information\n---------\n\n");
        pConvertObj->DisplayGenericInfo(lScene);

        //printf("\n\n------------\nNode Content\n------------\n\n");

        pConvertObj->DisplayContent(lScene);

        //printf("\n\n----\nPose\n----\n\n");
/*
        pConvertObj->DisplayPose(lScene);

        //printf("\n\n---------\nAnimation\n---------\n\n");

        pConvertObj->DisplayAnimation(lScene);

        //now display generic information
*/

    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager);

    return 0;
}
