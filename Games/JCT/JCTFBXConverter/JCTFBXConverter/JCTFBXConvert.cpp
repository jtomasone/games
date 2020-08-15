#include "JCTFBXConvert.h"

JCTFBXConvert::JCTFBXConvert(char* pFileName)
{
   if(!pFileName)
   {
      pFileName = "FBX_TempFile.txt";
   }

   this->m_pOutFile = new JCTFile();
   //char pChar[255] = "THIS IS A TEST OF MY FILE TYPE TEST TEST TEST";
   this->m_pOutFile->Create(pFileName,m_dwError, CREATE_NEW, JCTFILE_WRITE);
   //this->m_pOutFile->Write(pChar, 255, m_dwError);
   //glbOut->Close(dwError);

}
void JCTFBXConvert::DisplayContent(KFbxScene* pScene)
{
    int i;
    KFbxNode* lNode = pScene->GetRootNode();

    if(lNode)
    {
        for(i = 0; i < lNode->GetChildCount(); i++)
        {
            DisplayContent(lNode->GetChild(i));
        }
    }
}

void JCTFBXConvert::DisplayContent(KFbxNode* pNode)
{
    KFbxNodeAttribute::EAttributeType lAttributeType;
    int i;

    if(pNode->GetNodeAttribute() == NULL)
    {
        printf("NULL Node Attribute\n\n");
        KString lString = "NULL Node Attribute\n\n";
         this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    }
    else
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
        /*case KFbxNodeAttribute::eMARKER:  
            //DisplayMarker(pNode);
            break;
*/
        case KFbxNodeAttribute::eSKELETON:  
            DisplaySkeleton(pNode);
            break;

        case KFbxNodeAttribute::eMESH:      
            DisplayMesh(pNode);
            break;
/*
        case KFbxNodeAttribute::eNURB:      
            //DisplayNurb(pNode);
            break;

        case KFbxNodeAttribute::ePATCH:     
            //DisplayPatch(pNode);
            break;

        case KFbxNodeAttribute::eCAMERA:    
            DisplayCamera(pNode);
            break;

        case KFbxNodeAttribute::eLIGHT:     
            DisplayLight(pNode);
            break;

        case KFbxNodeAttribute::eLODGROUP:
            //DisplayLodGroup(pNode);
            break;
            */
        }   
    }

//    DisplayUserProperties(pNode);
/*    DisplayTarget(pNode);
    DisplayPivotsAndLimits(pNode);
    DisplayTransformPropagation(pNode);
    DisplayGeometricTransform(pNode);
*/
    for(i = 0; i < pNode->GetChildCount(); i++)
    {
        DisplayContent(pNode->GetChild(i));
    }
}


void JCTFBXConvert::DisplayTarget(KFbxNode* pNode)
{
    if(pNode->GetTarget() != NULL)
    {
        DisplayString("    Target Name: ", (char *) pNode->GetTarget()->GetName());
    }
}

void JCTFBXConvert::DisplayTransformPropagation(KFbxNode* pNode)
{
    KString lString;
      lString = "    Transformation Propagation\n";
      printf(lString.Buffer());

//      this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    // 
    // Rotation Space
    //
    ERotationOrder lRotationOrder;
    pNode->GetRotationOrder(KFbxNode::eSOURCE_SET, lRotationOrder);

   lString += "        Rotation Space: ";
   printf(lString.Buffer());

   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    switch (lRotationOrder)
    {
    case eEULER_XYZ: 
       lString += "Euler XYZ\n";
        printf("Euler XYZ\n");
        break;
    case eEULER_XZY:
       lString += "Euler XZY\n";
        printf("Euler XZY\n");
        break;
    case eEULER_YZX:
       lString += "Euler YZX\n";
        printf("Euler YZX\n");
        break;
    case eEULER_YXZ:
       lString += "Euler YXZ\n";
        printf("Euler YXZ\n");
        break;
    case eEULER_ZXY:
       lString += "Euler ZXY\n";
        printf("Euler ZXY\n");
        break;
    case eEULER_ZYX:
       lString += "Euler ZYX\n";
        printf("Euler ZYX\n");
        break;
    case eSPHERIC_XYZ:
       lString += "Spheric XYZ\n";
        printf("Spheric XYZ\n");
        break;
    }

    //
    // Use the Rotation space only for the limits
    // (keep using eEULER_XYZ for the rest)
    //
    printf("        Use the Rotation Space for Limit specification only: %s\n",
        pNode->GetUseRotationSpaceForLimitOnly(KFbxNode::eSOURCE_SET) ? "Yes" : "No");
       lString += "        Use the Rotation Space for Limit specification only: \n";
       lString += pNode->GetUseRotationSpaceForLimitOnly(KFbxNode::eSOURCE_SET) ? "Yes" : "No";



    //
    // Inherit Type
    //
    ETransformInheritType lInheritType;
    pNode->GetTransformationInheritType(lInheritType);

    printf("        Transformation Inheritance: ");
    lString += "        Transformation Inheritance: \n";
    switch (lInheritType)
    {
    case eINHERIT_RrSs:
        printf("RrSs\n");
       lString += "RrSs\n";
       break;
    case eINHERIT_RSrs:
        printf("RSrs\n");
       lString += "RSrs\n";
        break;
    case eINHERIT_Rrs:
        printf("Rrs\n");
       lString += "Rrs\n";
        break;
    }
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}

void JCTFBXConvert::DisplayGeometricTransform(KFbxNode* pNode)
{
    KFbxVector4 lTmpVector;
    KString lString;

    printf("    Geometric Transformations\n");
   lString = "    Geometric Transformations\n";
    //
    // Translation
    //
    lTmpVector = pNode->GetGeometricTranslation(KFbxNode::eSOURCE_SET);
    printf("        Translation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
    lString = "        Translation:     ";
    lString += lTmpVector[0];
    lString += " ";
    lString += lTmpVector[1];
    lString += " ";
    lString += lTmpVector[2];
    lString += "\n";
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    //
    // Rotation
    //
    lTmpVector = pNode->GetGeometricRotation(KFbxNode::eSOURCE_SET);
    printf("        Rotation:    %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
    lString = "        Translation:     ";
    lString += lTmpVector[0];
    lString += " ";
    lString += lTmpVector[1];
    lString += " ";
    lString += lTmpVector[2];
    lString += "\n";
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    //
    // Scaling
    //
    lTmpVector = pNode->GetGeometricScaling(KFbxNode::eSOURCE_SET);
    printf("        Scaling:     %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);
    lString = "        Scaling:     ";
    lString += lTmpVector[0];
    lString += " ";
    lString += lTmpVector[1];
    lString += " ";
    lString += lTmpVector[2];
    lString += "\n";
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);
}


void JCTFBXConvert::DisplayMetaData(KFbxScene* pScene)
{
    KFbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
    KString lString;
    if (sceneInfo)
    {
        printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
        printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
        printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
        printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
        printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
        printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
        printf("    Comment: %s\n", sceneInfo->mComment.Buffer());

        lString = "\n\n--------------------\nMeta-Data\n--------------------\n\n";
        lString += "    Title: "; 
        lString += sceneInfo->mTitle.Buffer();
        lString += "\n"; 
        lString += "    Subject: "; 
        lString += sceneInfo->mSubject.Buffer();
        lString += "\n"; 
        lString += "    Author: "; 
        lString += sceneInfo->mAuthor.Buffer();
        lString += "\n"; 
        lString += "    Keywords: "; 
        lString += sceneInfo->mKeywords.Buffer();
        lString += "\n"; 
        lString += "    Revision: "; 
        lString += sceneInfo->mRevision.Buffer();
        lString += "\n"; 
        lString += "    Comment: "; 
        lString += sceneInfo->mComment.Buffer();
        lString += "\n"; 
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

        KFbxThumbnail* thumbnail = sceneInfo->GetSceneThumbnail();
        if (thumbnail)
        {
            printf("    Thumbnail:\n");
            lString = "    Thumbnail:\n"; 
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

            switch (thumbnail->GetDataFormat())
            {
            case KFbxThumbnail::eRGB_24:
                printf("        Format: RGB\n");
               lString = "        Format: RGB\n"; 
               this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

                break;
            case KFbxThumbnail::eRGBA_32:
                printf("        Format: RGBA\n");
               lString = "        Format: RGBA\n"; 
               this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);
                break;
            }

            switch (thumbnail->GetSize())
            {
            case KFbxThumbnail::eNOT_SET:
                //printf("        Size: no dimensions specified (%ld bytes)\n", thumbnail->GetSizeInBytes());
                this->DisplayInt("        Size: no dimensions specified (", thumbnail->GetSizeInBytes(), " bytes)\n");
                break;
            case KFbxThumbnail::e64x64:
                //printf("        Size: 64 x 64 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
                this->DisplayInt("        Size: 64 x 64 pixels (", thumbnail->GetSizeInBytes(), " bytes)\n");
                break;
            case KFbxThumbnail::e128x128:
                //printf("        Size: 128 x 128 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
                this->DisplayInt("        Size: 128 x 128 pixels (", thumbnail->GetSizeInBytes(), " bytes)\n");

            }
        }
    }
}

