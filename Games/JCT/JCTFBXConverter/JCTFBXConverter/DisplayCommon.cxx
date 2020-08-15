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


void JCTFBXConvert::DisplayMetaDataConnections(KFbxObject* pObject)
{
    int nbMetaData = KFbxGetSrcCount<KFbxObjectMetaData>(pObject);
    if (nbMetaData > 0)
        DisplayString("    MetaData connections ");

    for (int i = 0; i < nbMetaData; i++)
    {
        KFbxObjectMetaData* metaData = KFbxGetSrc<KFbxObjectMetaData>(pObject, i);
        DisplayString("        Name: ", (char*)metaData->GetName());
    }
}

void JCTFBXConvert::DisplayString(const char* pHeader, const char* pValue /* = "" */, const char* pSuffix /* = "" */)
{
    KString lString;

    lString = pHeader;
    lString += pValue;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::DisplayBool(const char* pHeader, bool pValue, const char* pSuffix /* = "" */)
{
    KString lString;

    lString = pHeader;
    lString += pValue ? "true" : "false";
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::DisplayInt(const char* pHeader, int pValue, const char* pSuffix /* = "" */)
{
    KString lString;

    lString = pHeader;
    lString += pValue;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);
}


void JCTFBXConvert::DisplayDouble(const char* pHeader, double pValue, const char* pSuffix /* = "" */)
{
    KString lString;
    KString lFloatValue = (float) pValue;

    lFloatValue = pValue <= -HUGE_VAL ? "-INFINITY" : lFloatValue.Buffer();
    lFloatValue = pValue >=  HUGE_VAL ?  "INFINITY" : lFloatValue.Buffer();

    lString = pHeader;
    lString += lFloatValue;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::Display2DVector(const char* pHeader, KFbxVector2 pValue, const char* pSuffix  /* = "" */)
{
    KString lString;
    KString lFloatValue1 = (float)pValue[0];
    KString lFloatValue2 = (float)pValue[1];

    lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
    lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
    lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
    lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();

    lString = pHeader;
    lString += lFloatValue1;
    lString += ", ";
    lString += lFloatValue2;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::Display3DVector(const char* pHeader, KFbxVector4 pValue, const char* pSuffix /* = "" */)
{
    KString lString;
    KString lFloatValue1 = (float)pValue[0];
    KString lFloatValue2 = (float)pValue[1];
    KString lFloatValue3 = (float)pValue[2];

    lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
    lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
    lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
    lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();
    lFloatValue3 = pValue[2] <= -HUGE_VAL ? "-INFINITY" : lFloatValue3.Buffer();
    lFloatValue3 = pValue[2] >=  HUGE_VAL ?  "INFINITY" : lFloatValue3.Buffer();

    lString = pHeader;
    lString += lFloatValue1;
    lString += ", ";
    lString += lFloatValue2;
    lString += ", ";
    lString += lFloatValue3;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}

void JCTFBXConvert::Display4DVector(const char* pHeader, KFbxVector4 pValue, const char* pSuffix /* = "" */)
{
    KString lString;
    KString lFloatValue1 = (float)pValue[0];
    KString lFloatValue2 = (float)pValue[1];
    KString lFloatValue3 = (float)pValue[2];
    KString lFloatValue4 = (float)pValue[3];

    lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
    lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
    lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
    lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();
    lFloatValue3 = pValue[2] <= -HUGE_VAL ? "-INFINITY" : lFloatValue3.Buffer();
    lFloatValue3 = pValue[2] >=  HUGE_VAL ?  "INFINITY" : lFloatValue3.Buffer();
    lFloatValue4 = pValue[3] <= -HUGE_VAL ? "-INFINITY" : lFloatValue3.Buffer();
    lFloatValue4 = pValue[3] >=  HUGE_VAL ?  "INFINITY" : lFloatValue3.Buffer();

    lString = pHeader;
    lString += lFloatValue1;
    lString += ", ";
    lString += lFloatValue2;
    lString += ", ";
    lString += lFloatValue3;
    lString += ", ";
    lString += lFloatValue4;
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::DisplayColor(const char* pHeader, KFbxPropertyDouble3 pValue, const char* pSuffix /* = "" */)

{
    KString lString;

    lString = pHeader;
    //lString += (float) pValue.mRed;
    //lString += (double)pValue.GetArrayItem(0);
    lString += " (red), ";
    //lString += (float) pValue.mGreen;
    //lString += (double)pValue.GetArrayItem(1);
    lString += " (green), ";
    //lString += (float) pValue.mBlue;
    //lString += (double)pValue.GetArrayItem(2);
    lString += " (blue)";
    lString += pSuffix;
    lString += "\n";
    printf(lString);
   this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}


void JCTFBXConvert::DisplayColor(const char* pHeader, KFbxColor pValue, const char* pSuffix /* = "" */)
{
    KString lString;

    lString = pHeader;
    lString += (float) pValue.mRed;

//    lString += " (red), ";
    lString += ",";
    lString += (float) pValue.mGreen;

//    lString += " (green), ";
    lString += ",";
    lString += (float) pValue.mBlue;

//    lString += " (blue)";
    lString += pSuffix;
    lString += "\n";
    printf(lString);
    this->m_pOutFile->Write(lString.Buffer(), lString.GetLen(), m_dwError);

}

