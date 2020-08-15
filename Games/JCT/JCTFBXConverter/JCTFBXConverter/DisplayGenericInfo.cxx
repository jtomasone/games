
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

void JCTFBXConvert::DisplayGenericInfo(KFbxScene* pScene)
{
    int i;
    KFbxNode* lRootNode = pScene->GetRootNode();
    KString lString;
    lString = "GenericInfo:\n";
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

    for( i = 0; i < lRootNode->GetChildCount(); i++)
    {
        DisplayGenericInfo(lRootNode->GetChild(i), 0);
    }

	//Other objects directly connected onto the scene
	for( i = 0; i < pScene->GetSrcObjectCount(FBX_TYPE(KFbxObject)); ++i )
	{
		DisplayProperties(pScene->GetSrcObject(FBX_TYPE(KFbxObject), i));
	}
}


void JCTFBXConvert::DisplayGenericInfo(KFbxNode* pNode, int pDepth)
{
    KString lString;
    int i;

    for(i = 0; i < pDepth; i++)
    {
        lString += "     ";
    }

    lString += pNode->GetName();
    lString += "\n";

    DisplayString(lString.Buffer());

    //Display generic info about that Node
    DisplayProperties(pNode);
    DisplayString("");
    for(i = 0; i < pNode->GetChildCount(); i++)
    {
        DisplayGenericInfo(pNode->GetChild(i), pDepth + 1);
    }
}

void JCTFBXConvert::DisplayProperties(KFbxObject* pObject)
{

    DisplayString("Name: ", (char *)pObject->GetName());

    // Display all the properties
    int i,  lCount = 0;
    KFbxProperty lProperty = pObject->GetFirstProperty();
    while (lProperty.IsValid())
    {
        lCount++;
        lProperty = pObject->GetNextProperty(lProperty);
    }

    KString lTitleStr = "    Property Count: ";

    if (lCount == 0)
        return; // there are no properties to display

    DisplayInt(lTitleStr.Buffer(), lCount);

    i=0;
	lProperty = pObject->GetFirstProperty();
    while (lProperty.IsValid())
    {
        // exclude user properties

        KString lString;
        DisplayInt("        Property ", i);
        lString = lProperty.GetLabel();
        DisplayString("            Display Name: ", lString.Buffer());
        lString = lProperty.GetName();
        DisplayString("            Internal Name: ", lString.Buffer());
        lString = lProperty.GetPropertyDataType().GetName();
        DisplayString("            Type: ",lString.Buffer());
        if (lProperty.HasMinLimit()) DisplayDouble("            Min Limit: ", lProperty.GetMinLimit());
        if (lProperty.HasMaxLimit()) DisplayDouble("            Max Limit: ", lProperty.GetMaxLimit());
        DisplayBool  ("            Is Animatable: ", lProperty.GetFlag(KFbxProperty::eANIMATABLE));
        DisplayBool  ("            Is Temporary: ", lProperty.GetFlag(KFbxProperty::eTEMPORARY));


        switch (lProperty.GetPropertyDataType().GetType())
        {
        case eBOOL1:
            DisplayBool("            Default Value: ", KFbxGet<bool>(lProperty));
            break;

        case eDOUBLE1:
            DisplayDouble("            Default Value: ",KFbxGet<double>(lProperty));
            break;

        case eDOUBLE4:
            {
                KFbxColor lDefault;
                char      lBuf[64];

                lDefault=KFbxGet <KFbxColor> (lProperty);
                sprintf(lBuf, "R=%f, G=%f, B=%f, A=%f", lDefault.mRed, lDefault.mGreen, lDefault.mBlue, lDefault.mAlpha);
                DisplayString("            Default Value: ", lBuf);
            }
            break;

        case eINTEGER1:
            DisplayInt("            Default Value: ", KFbxGet <int> (lProperty));
            break;

        case eDOUBLE3:
            {
                fbxDouble3 lDefault;
                char   lBuf[64];

                lDefault = KFbxGet <fbxDouble3> (lProperty);
                sprintf(lBuf, "%f,%f,%f", lDefault[0], lDefault[1], lDefault[2]);
                DisplayString("            Default Value: ", lBuf);
            }
            break;

        //case DTEnum:
        //    DisplayInt("            Default Value: ", KFbxGet <int> (lProperty));
        //    break;

        case eFLOAT1:
            DisplayDouble("            Default Value: ", KFbxGet <float> (lProperty));
            break;
        case eSTRING:
            lString = (KFbxGet <KString> (lProperty));
            DisplayString("            Default Value: ", lString.Buffer());
            break;

        default:
            DisplayString("            Default Value: UNIDENTIFIED");
            break;
        }
        i++;
        lProperty = pObject->GetNextProperty(lProperty);
    }
}

