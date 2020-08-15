#pragma once
#include "jctfile.h"

class JCTImageFile :
   public JCTFile
{
public:
   JCTImageFile(void);
   ~JCTImageFile(void);
   const unsigned char  getColorDepth();
   const unsigned char  getImageDataType();
   const unsigned char  getImageDataFormat();
   const unsigned char *getPImageData();
   const unsigned short getWidth();
   const unsigned short getHeight();
   const unsigned long  getImageSize();

   void setColorDepth      (const unsigned char &ucIcolorDepth);
   void setImageDataType   (const unsigned char  &ucImageDataType);
   void setImageDataFormat (const unsigned char  &ucImageDataFormat);
   void setPImageData      (const unsigned char &pImageData);
   void setWidth           (const unsigned short &usWidth);
   void setHeight          (const unsigned short &usHeight);
   void setImageSize       (const unsigned long &lImageSize);
   unsigned char *m_pImageData;
private:
	unsigned char  m_colorDepth;
	unsigned char  m_imageDataType;
	unsigned char  m_imageDataFormat;
	
	unsigned short m_width;
	unsigned short m_height;	
	unsigned long  m_imageSize;
};
